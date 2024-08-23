// Fill out your copyright notice in the Description page of Project Settings.


#include "System/ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if (bPlayerEnabled) {
		GetPawn()->EnableInput(this);
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("Disable"));
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabled;
}
