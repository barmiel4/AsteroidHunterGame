// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"

#include "GeometryCollection/GeometryCollectionComponent.h"

#include "Field/FieldSystemComponent.h"
#include "Field/FieldSystemObjects.h"


AAsteroid::AAsteroid()
{
	DestructibleAsteroid = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("DestructibleAsteroid"));
	DestructibleAsteroid->SetupAttachment(RootComponent);

	Exploder = CreateDefaultSubobject<UFieldSystemComponent>(TEXT("Exploder"));
	Exploder->SetupAttachment(RootComponent);
}

void AAsteroid::BeginPlay()
{

}

void AAsteroid::HandleCollision(AActor* HitActor)
{
	//ProjectileMovement


	// GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &AActor::Destroy, LifeTime);
}