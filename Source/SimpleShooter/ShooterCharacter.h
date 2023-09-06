// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* TakeDamageAnimFront;

	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* TakeDamageAnimBack;

	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* TakeDamageAnimLeft;

	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* TakeDamageAnimRight;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
		bool IsDead();

	UFUNCTION(BlueprintPure)
		float GetHealthPercentage() const;

	void Shoot();

	UPROPERTY(EditAnywhere)
		UAnimMontage* ShootAnimMontage;

	UPROPERTY(VisibleAnywhere)
		bool isSprinting = false;


private:

	void MoveForward(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void MoveRight(float AxisValue);
	void EnterSprint();
	void ExitSprint();
	void AimFocus();


	UPROPERTY(EditAnywhere)
		float Rate = 1;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ARifle> GunClass;

	UPROPERTY()
		ARifle* Rifle;

	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
		float Health = 100;

	UPROPERTY(EditDefaultsOnly)
		float SprintSpeed = 800;

	UPROPERTY(EditDefaultsOnly)
		float NormalSpeed = 400;

	UPROPERTY()
		bool AimFocusOn = false;

};
