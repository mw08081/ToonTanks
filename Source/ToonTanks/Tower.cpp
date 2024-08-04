// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TimerManager.h"

ATower::ATower()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


void ATower::BeginPlay()
{
	Super::BeginPlay();
	
	target = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::OnFire, FireInterval, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CheckFireCondition()) {
		AimToTarget();
	}
}

bool ATower::CheckFireCondition()
{
	double dist2Target = FVector::Distance(target->GetActorLocation(), GetActorLocation());
	//OnFire 함수로의 조건반환
	canFire = target && dist2Target <= TowerRange;
	
	//Tick 함수로의 조건반환
	if (canFire) {
		return true;
	}
	return false;
}

void ATower::AimToTarget()
{
	FVector aimVec = target->GetActorLocation() - GetActorLocation();
	FRotator aimRot = aimVec.Rotation();

	RotateToTarget(aimRot);
}

void ATower::OnFire()
{
	if (canFire) {
		Fire();
	}
}

