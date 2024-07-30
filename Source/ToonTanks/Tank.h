// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public :
	ATank();
	virtual void Tick(float DeltaTime) override;

//Components
private:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CamComp;

//Editor Variable
public:

private: 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player" , meta = (AllowPrivateAccess = "true"))
		float moveSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player" , meta = (AllowPrivateAccess = "true"))
		float rotSpeed;

//Code Variable
public:

private:
	bool bIsCenterPivot = true;
	float rightCaterpillarVal = 0.f;
	float leftCaterpillarVal = 0.f;
	FVector forwardVec = FVector::ZeroVector;
	FRotator yawRot = FRotator::ZeroRotator;

//Function
public :
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Moving Function
	void Move(float value);
	void Turn(float value);
	void SetRightCaterpillarValByInput(float value);
	void SetLeftCaterpillarValByInput(float value);
	void SetPivotToTurn(bool bResetPivot, bool bLeftTurn);
	void Moving(float dt);
	void MovingLocation(float val, float dt);
	void MovingRotation(float val, float dt);

//private:
};
