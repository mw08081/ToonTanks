// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BodyCollider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnLocationComp = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Location"));
	ProjectileSpawnLocationComp->SetupAttachment(TurretMesh);
}


// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePawn::HandleDestruction()
{
	// VFS SFS
}

void ABasePawn::RotateToTarget(FRotator targetLocation)
{
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			targetLocation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			10.f)
	);
}

void ABasePawn::Fire()
{
	DrawDebugSphere(
		GetWorld(),
		ProjectileSpawnLocationComp->GetComponentLocation(),
		10,
		24,
		FColor::Red,
		false,
		1.f);

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
														ProjectileClass,
														ProjectileSpawnLocationComp->GetComponentLocation(),
														ProjectileSpawnLocationComp->GetComponentRotation()
													);
	Projectile->SetOwner(this);
}


