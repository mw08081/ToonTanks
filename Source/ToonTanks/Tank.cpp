// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(BaseMesh);

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

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (leftCaterpillarVal != 0 || rightCaterpillarVal != 0) {
		Moving(DeltaTime);
	}

	if (PlayerControllerRef) {
		ControllTurret();
	}
}


#pragma region Move Function
#pragma region legacy Moving Mechanism 
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
#pragma endregion

#pragma region Moving Mechanism (using Tick)

void ATank::SetRightCaterpillarValByInput(float value)
{
	rightCaterpillarVal = value;
}

void ATank::SetLeftCaterpillarValByInput(float value)
{
	leftCaterpillarVal = value;
}

void ATank::SetPivotToTurn(bool bResetPivot, bool bLeftTurn)
{
	if (bResetPivot == true) {

	}
	return;

	if (bIsCenterPivot == true) {
		bIsCenterPivot = false;	//더이상 피벗조정이 일어나지않도록

		FVector pivotLocation = FVector::ZeroVector;
		if (bLeftTurn == true) {
			pivotLocation = FVector(0, -45, 0);
		}
		else {
			pivotLocation = FVector(0, 45, 0);
		}

		AddActorLocalOffset(pivotLocation);
		BaseMesh->SetRelativeLocation(BaseMesh->GetRelativeLocation() + pivotLocation * -1);
	}
}

void ATank::Moving(float dt)
{
	if (leftCaterpillarVal == 0 || rightCaterpillarVal == 0) {
		if (leftCaterpillarVal == 0) {
			bIsCenterPivot = true;

			//turn left (↖ || ↙)
			SetPivotToTurn(false, true);
			MovingRotation(rightCaterpillarVal * -1, dt);

			//조금씩 앞으로 가면서 회전을 위함(현실고증)
			MovingLocation(rightCaterpillarVal, dt);
		}
		else {
			bIsCenterPivot = true;

			//turn right (↗ || ↘)
			SetPivotToTurn(false, false);
			MovingRotation(leftCaterpillarVal, dt);

			//조금씩 앞으로 가면서 회전을 위함(현실고증)
			MovingLocation(leftCaterpillarVal, dt);
		}
	}
	else {
		bIsCenterPivot = true;

		if (leftCaterpillarVal > 0 && rightCaterpillarVal > 0 ||
			leftCaterpillarVal < 0 && rightCaterpillarVal < 0) {
			MovingLocation(leftCaterpillarVal, dt);
		}
		else {
			MovingRotation(leftCaterpillarVal, dt);
		}
	}
}

void ATank::MovingLocation(float val, float dt)
{
	forwardVec.X = val * moveSpeed * dt;
	AddActorLocalOffset(forwardVec, true);
}

void ATank::MovingRotation(float val, float dt)
{
	yawRot.Yaw = val * rotSpeed * dt;
	AddActorLocalRotation(yawRot, true);
}
#pragma endregion
#pragma endregion

void ATank::ControllTurret()
{
	FHitResult hitResult;
	PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, hitResult);
	if (hitResult.bBlockingHit) {
		DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 25.f, 24, FColor::Red);

		//FVector CameraLocation = PlayerControllerRef->PlayerCameraManager->GetCameraLocation();
		//FVector CameraForwardVector = PlayerControllerRef->PlayerCameraManager->GetCameraRotation().Vector();

		//// 디버그 라인을 그립니다.
		//DrawDebugLine(GetWorld(), CameraLocation, hitResult.ImpactPoint, FColor::Green);
		FVector turret2HitPoint = hitResult.ImpactPoint - GetActorLocation();
		FRotator turretRot = turret2HitPoint.Rotation();
		turretRot.Roll = turretRot.Pitch = 0; 

		RotateToTarget(turretRot);
	}
}
