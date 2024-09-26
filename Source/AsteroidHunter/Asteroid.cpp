// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"

#include "GeometryCollection/GeometryCollectionComponent.h"

#include "Field/FieldSystemComponent.h"
#include "Field/FieldSystemObjects.h"

#include "Components/SphereComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "GameFramework/RotatingMovementComponent.h"

#include "Spaceship.h"


AAsteroid::AAsteroid()
{
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAsteroid::OnMeshBeginOverlap);

	DestructibleAsteroid = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("DestructibleAsteroid"));
	DestructibleAsteroid->SetSimulatePhysics(false);
	DestructibleAsteroid->SetupAttachment(RootComponent);

	Exploder = CreateDefaultSubobject<UFieldSystemComponent>(TEXT("Exploder"));
	Exploder->SetupAttachment(RootComponent);

	RadialFalloff = CreateDefaultSubobject<URadialFalloff>(TEXT("RadialFalloff"));

	RadialVector = CreateDefaultSubobject<URadialVector>(TEXT("RadialVector"));

	CullingField = CreateDefaultSubobject<UCullingField>(TEXT("CullingField"));

	CollisionComponent->SetCollisionProfileName("Asteroid");
	CollisionComponent->SetSphereRadius(65.f);
}

void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

}

void AAsteroid::HandleCollision(AActor* HitActor)
{
	ProjectileMovement->Deactivate();

	DestructibleAsteroid->SetSimulatePhysics(true);

	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &AAsteroid::Destroy, LifeTime, false);

	auto HitDirection = GetActorLocation();
	HitDirection -= HitActor ? HitActor->GetActorLocation() : HitLocationCache;
	HitDirection.Normalize();

	TriggerChaosExplosion(HitDirection);
}

void AAsteroid::TriggerChaosExplosion(const FVector& HitDirection)
{

}

void AAsteroid::Destroy()
{
	AActor::Destroy();
}

void AAsteroid::OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HandleCollision(OtherActor);

	if (auto Spaceship = Cast<ASpaceship>(OtherActor))
	{
		Spaceship->TakeDamage(20);

		Spaceship->CollisionReaction(GetActorLocation());
	}

	Destroy();
}
