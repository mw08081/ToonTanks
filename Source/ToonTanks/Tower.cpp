// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

ATower::ATower()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


void ATower::BeginPlay()
{
	Super::BeginPlay();
	
	target = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (target) {
		AimToTarget();
	}
}

void ATower::AimToTarget()
{
	FVector aimVec = target->GetActorLocation() - GetActorLocation();
	FRotator aimRot = aimVec.Rotation();

	RotateToTarget(aimRot);
}

