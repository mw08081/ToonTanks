// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksBaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
//public:
	//virtual void Tick(float DeltaTime) override;

public:
private:
	class ATank* Tank;

public:
	void ActorDied(AActor* DeadActor);
private:

	
};
