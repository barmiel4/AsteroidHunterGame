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

	void HandleCollision(AActor* HitActor);

	void TriggerChaosExplosion(const FVector& HitDirection);

	UFUNCTION()
	void Destroy();

	UFUNCTION()
	void OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	AAsteroid();

	FVector HitLocationCache;

protected:
	virtual void BeginPlay() override;
};