// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBolt.h"
#include "UltraBolt.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDHUNTER_API AUltraBolt : public ABaseBolt
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AExplosiveMine> MineClass;

	void SpawnMines();

public:
	AUltraBolt();

protected:
	virtual void OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
