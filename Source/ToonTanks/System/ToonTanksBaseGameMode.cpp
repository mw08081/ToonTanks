// Fill out your copyright notice in the Description page of Project Settings.


#include "System/ToonTanksBaseGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/Tank.h"
#include "Pawn/Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksBaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AToonTanksBaseGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0))->SetPlayerEnabledState(false);
	}
	else if (DeadActor->IsA<ATower>())
	{
		ATower* DestroyedTower = Cast<ATower>(DeadActor);
		DestroyedTower->HandleDestruction();
	}
}
