// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rifle.generated.h"

UCLASS()
class SIMPLESHOOTER_API ARifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifle();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* Flash;

	UPROPERTY(EditDefaultsOnly)
		USoundBase* MuzzleSound;

	UPROPERTY(EditDefaultsOnly)
		USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere)
		float ShootRange = 100; //Default Value.

	UPROPERTY(EditAnywhere)
		UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
		float Damage = 10;


};
