// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObstacle.h"

#include "Asteroid.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDHUNTER_API AAsteroid : public ABaseObstacle
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UGeometryCollectionComponent* DestructibleAsteroid;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UFieldSystemComponent* Exploder;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class URadialFalloff* RadialFalloff;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class URadialVector* RadialVector;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCullingField* CullingField;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float LifeTime;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float ExplosionStreangth;

	UPROPERTY()
	FTimerHandle DestroyTimer = FTimerHandle();

	FVector HitLocationCache;

	void HandleCollision(AActor* HitActor);

	void TriggerChaosExplosion(const FVector& HitDirection);

	UFUNCTION()
	void Destroy();

public:
	AAsteroid();

protected:
	virtual void BeginPlay() override;
};