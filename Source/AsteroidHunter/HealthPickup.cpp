// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"

#include "Components/SphereComponent.h"

#include "Spaceship.h"

AHealthPickup::AHealthPickup()
{
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickup::OnMeshBeginOverlap);
	CollisionComponent->SetCollisionProfileName(TEXT("Pickup"));
}

void AHealthPickup::OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Spaceship = Cast<ASpaceship>(OtherActor))
	{
		Spaceship->Heal(10.f);

		Destroy();
	}
}
