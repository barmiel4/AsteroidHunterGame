// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObstacle.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDHUNTER_API AHealthPickup : public ABaseObstacle
{
	GENERATED_BODY()
public:
	AHealthPickup();

private:
	UFUNCTION()
	void OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
