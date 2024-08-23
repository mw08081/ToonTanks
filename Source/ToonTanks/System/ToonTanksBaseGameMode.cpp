// Fill out your copyright notice in the Description page of Project Settings.


#include "System/ToonTanksBaseGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/Tank.h"
#include "Pawn/Tower.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"

void AToonTanksBaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksBaseGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();

		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
	}
	else if (DeadActor->IsA<ATower>())
	{
		ATower* DestroyedTower = Cast<ATower>(DeadActor);
		DestroyedTower->HandleDestruction();
	}
}

void AToonTanksBaseGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true
		);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}
}
