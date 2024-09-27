// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponInteractionComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Spaceship.h"

#include "GunCooler.h"

// Sets default values for this component's properties
UWeaponInteractionComponent::UWeaponInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UWeaponInteractionComponent::OnInteraction(const FTransform& HitActorTranform)
{
	auto Player = Cast<ASpaceship>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		Player->IncreaseScore(PointsOnImpact);

		if (UKismetMathLibrary::RandomFloat() <= CoolerChance)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			GetWorld()->SpawnActor<AGunCooler>(GunCoolerClass, HitActorTranform, SpawnParams);
		}
	}
}


// Called when the game starts
void UWeaponInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

