// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay() {

	Super::BeginPlay();

	HUD = CreateWidget(this, HUDClass);
	if (HUD) {
		HUD->AddToViewport();
	}
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner) {

	Super::GameHasEnded(EndGameFocus, bIsWinner);

	HUD->RemoveFromViewport();

	if (bIsWinner) {
		UUserWidget* WinScreen = CreateWidget(this, WinScreenWidgetClass);
		if (WinScreen) {
			WinScreen->AddToViewport();
		}
		GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

	}
	else {
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenWidgetClass);
		if (LoseScreen) {
			LoseScreen->AddToViewport();
		}
		GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
	}
	

}
