// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


// Sets default values
ARifle::ARifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	RootComponent = Root;
	Mesh->SetupAttachment(Root);

}

void ARifle::PullTrigger() {
	if (Flash) {
		UGameplayStatics::SpawnEmitterAttached(Flash, Mesh, TEXT("MuzzleFlashSocket"));
	}
	if (MuzzleSound) {
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	}
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector ViewportLocation;
	FRotator ViewportRotation;

	OwnerController->GetPlayerViewPoint(ViewportLocation, ViewportRotation);

	FVector TraceEnd = ViewportLocation + ViewportRotation.Vector() * ShootRange;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	bool HitSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, ViewportLocation, TraceEnd, ECC_GameTraceChannel1, Params);

	if (HitSuccess) {

		FVector ShotDirection = ViewportRotation.Vector();
		FVector Scale(1, 1, 1);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect, HitResult.Location, ShotDirection.Rotation(), Scale);
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, HitResult.Location);


		AActor* HitActor = HitResult.GetActor();

		if (HitActor) {

			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}

}

// Called when the game starts or when spawned
void ARifle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

