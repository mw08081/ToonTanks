// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public :
	ATower();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
private:
	class ATank* target = nullptr;
	UPROPERTY(EditAnywhere)
		float TowerRange = 1000.f;

	bool canFire;

	FTimerHandle FireRateTimerHandle;
	float FireInterval = 2.f;
public:
	void HandleDestruction();
private:
	bool CheckFireCondition();
	void AimToTarget();
	void OnFire();
};
