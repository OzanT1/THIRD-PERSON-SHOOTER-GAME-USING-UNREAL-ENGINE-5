// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Rifle.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/EngineTypes.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include "Kismet/GameplayStatics.h"



// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Rifle = GetWorld()->SpawnActor<ARifle>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Rifle->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Rifle->SetOwner(this);

}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterCharacter::LookRight);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);

	PlayerInputComponent->BindAction(TEXT("AimFocus"), EInputEvent::IE_Pressed, this, &AShooterCharacter::AimFocus);

	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &AShooterCharacter::EnterSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &AShooterCharacter::ExitSprint);



}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {

	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	const FPointDamageEvent& PointDamageEvent = static_cast<const FPointDamageEvent&>(DamageEvent);

	FVector DirectionVector = PointDamageEvent.ShotDirection;
	

	FRotator DirectionRotation = DirectionVector.Rotation();
	float DirectionDegree = DirectionRotation.Yaw;

	// Get the actor's transform
	FTransform ActorTransform;
	if (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {
		ActorTransform = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetTransform();
	}


	FVector EnemyLocation;
	if (DamageCauser) {
		EnemyLocation = DamageCauser->GetActorLocation();
	}
	FVector ForwardVector = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorForwardVector();
	FVector Direction = EnemyLocation - ActorTransform.GetLocation();
	Direction.Normalize();
	float Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(ForwardVector, Direction)));

	UE_LOG(LogTemp, Warning, TEXT("Angle:    %f"), Angle)

	if (Angle < 100) {
		PlayAnimMontage(TakeDamageAnimFront);
		UE_LOG(LogTemp, Warning, TEXT("front"))
	}
	else {
		PlayAnimMontage(TakeDamageAnimBack);
		UE_LOG(LogTemp, Warning, TEXT("back"))
	}


	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	if (IsDead()) {
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode) {
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}
	return DamageToApply;
	
}

bool AShooterCharacter::IsDead() {
	return Health <= 0;
}

void AShooterCharacter::MoveForward(float AxisValue) {

	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue) {

	AddMovementInput(GetActorRightVector() * AxisValue);
}

float AShooterCharacter::GetHealthPercentage() const {
	return Health / MaxHealth;
}

void AShooterCharacter::Shoot() {

	

	if (isSprinting) {
		return;
	}
	float asd = PlayAnimMontage(ShootAnimMontage, 1.0F, "Default");
	if (asd == 0)
		UE_LOG(LogTemp, Warning, TEXT("Anim montage failed !!!!!!"));

	Rifle->PullTrigger();
}

void AShooterCharacter::LookUp(float AxisValue) {

	AddControllerPitchInput(AxisValue * Rate);
}

void AShooterCharacter::LookRight(float AxisValue) {

	AddControllerYawInput(AxisValue * Rate);
}

void AShooterCharacter::EnterSprint() {

	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	isSprinting = true;
}

void AShooterCharacter::ExitSprint() {

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	isSprinting = false;
}

void AShooterCharacter::AimFocus() {

	AimFocusOn = true;

}
