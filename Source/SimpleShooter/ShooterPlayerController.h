// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:

	virtual void BeginPlay() override;

	
private:

	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
		float RestartDelay = 4;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> LoseScreenWidgetClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> WinScreenWidgetClass;


	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY()
		UUserWidget* HUD;

};
