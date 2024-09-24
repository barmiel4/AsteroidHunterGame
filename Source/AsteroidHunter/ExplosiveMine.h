// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosiveMine.generated.h"

UCLASS()
class ASTEROIDHUNTER_API AExplosiveMine : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FVector Bump;

	float RandomDistance;

	FVector Start;
	
	class UMaterialInstanceDynamic* MineDynamicMaterial;

public:	
	// Sets default values for this actor's properties
	AExplosiveMine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
