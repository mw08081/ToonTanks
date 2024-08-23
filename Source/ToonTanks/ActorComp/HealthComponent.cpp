// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComp/HealthComponent.h"
#include "System/ToonTanksBaseGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakenDamage);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakenDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	Health -= Damage;
	UE_LOG(LogTemp, Display, TEXT("Health Comp Callback Func -> Health : %f"), Health);

	if (Health <= 0)
	{
		AToonTanksBaseGameMode* Tt_BaseGameMode = Cast<AToonTanksBaseGameMode>(GetWorld()->GetAuthGameMode());
		Tt_BaseGameMode->ActorDied(DamagedActor);
	}
}

