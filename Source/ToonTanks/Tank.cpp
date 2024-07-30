// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	CamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Comp"));
	CamComp->SetupAttachment(SpringArm);
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	//PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAxis(TEXT("RightCaterpillar"), this, &ATank::SetRightCaterpillarValByInput);
	PlayerInputComponent->BindAxis(TEXT("LeftCaterpillar"), this, &ATank::SetLeftCaterpillarValByInput);
}

void ATank::Move(float value)
{
	//UE_LOG(LogTemp, Display, TEXT("%f"), value);
	forwardVec.X = value * moveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(forwardVec, true);
}

void ATank::Turn(float value)
{
	yawRot.Yaw = value * rotSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(yawRot, true);
}

void ATank::SetRightCaterpillarValByInput(float value)
{
	rightCaterpillarVal = value;
}

void ATank::SetLeftCaterpillarValByInput(float value)
{
	leftCaterpillarVal = value;
}

void ATank::Moving(float dt)
{
	if (leftCaterpillarVal == 0 || rightCaterpillarVal == 0) {

	}
	else {
		if (leftCaterpillarVal > 0 && rightCaterpillarVal > 0 ||
			leftCaterpillarVal < 0 && rightCaterpillarVal < 0) {
			forwardVec.X = leftCaterpillarVal * moveSpeed * dt;
			AddActorLocalOffset(forwardVec, true);
		}
		else {
			yawRot.Yaw = leftCaterpillarVal * rotSpeed * dt;
			AddActorLocalRotation(yawRot, true);
		}
	}
}

void ATank::Tick(float DeltaTime)
{
	if (leftCaterpillarVal != 0 && rightCaterpillarVal != 0) {
		Moving(DeltaTime);
	}

}

