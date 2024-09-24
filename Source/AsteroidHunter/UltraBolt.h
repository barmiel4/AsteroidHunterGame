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
};
