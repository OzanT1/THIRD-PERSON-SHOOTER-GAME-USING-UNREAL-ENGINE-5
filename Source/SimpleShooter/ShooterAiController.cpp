// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAiController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"


void AShooterAiController::BeginPlay() {
	Super::BeginPlay();

	if (AIBehavior) {
		RunBehaviorTree(AIBehavior);
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AShooterAiController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

bool AShooterAiController::IsDead() {

	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if (ControlledCharacter) {
		return ControlledCharacter->IsDead();
	}
	return true;
}
