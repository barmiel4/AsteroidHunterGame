// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"

#include "GeometryCollection/GeometryCollectionComponent.h"

#include "Field/FieldSystemComponent.h"
#include "Field/FieldSystemObjects.h"

#include "Components/SphereComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"

#include "Spaceship.h"

#include "GunCooler.h"

#define PRINT_F(prompt, mess, mtime) GEngine->AddOnScreenDebugMessage(-1, mtime, FColor::White, FString::Printf(TEXT(prompt), mess));


AAsteroid::AAsteroid()
{
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAsteroid::OnMeshBeginOverlap);

	DestructibleAsteroid = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("DestructibleAsteroid"));
	DestructibleAsteroid->SetSimulatePhysics(false);
	DestructibleAsteroid->bRenderCustomDepth = true;
	DestructibleAsteroid->CustomDepthStencilValue = 3;
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
	FVector ExplosionCenter = GetActorLocation() - (HitDirection * HitDirectionOffset);
	//FVector ExplosionCenter = GetActorLocation();

	RadialFalloff->SetRadialFalloff(9999999.0f, 0.f, 1.f, 0.f, ExplosionStrength, ExplosionCenter, ExplosionFalloffType);

	Exploder->ApplyPhysicsField(true, EFieldPhysicsType::Field_ExternalClusterStrain, nullptr, RadialFalloff);


	RadialVector->SetRadialVector(ExplosionStrength, ExplosionCenter);
	CullingField->SetCullingField(RadialFalloff, RadialVector, EFieldCullingOperationType::Field_Culling_Outside);

	Exploder->ApplyPhysicsField(true, EFieldPhysicsType::Field_LinearVelocity, nullptr, CullingField);
}

void AAsteroid::Destroy()
{
	AActor::Destroy();
}

void AAsteroid::OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HandleCollision(OtherActor);

	if (OtherComp->GetCollisionProfileName() == HitReactionProfileName)
	{
		if (UKismetMathLibrary::RandomFloat() <= CoolerChance)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			GetWorld()->SpawnActor<AGunCooler>(GunCoolerClass, GetActorLocation(), FRotator(0.f), SpawnParams);
		}
	}

	if (auto Spaceship = Cast<ASpaceship>(OtherActor))
	{
		Spaceship->TakeDamage(20);

		Spaceship->CollisionReaction(GetActorLocation());
	}
}
