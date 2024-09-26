// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBolt.generated.h"

UCLASS()
class ASTEROIDHUNTER_API ABaseBolt : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int PointsOnImpact = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bDestroyOnImpact = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float BoltSpeed;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<;*/ //<--- COOLER

	//UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CoolerChance = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComp;

	class USceneComponent* Root;

	void SpawnCooler();

	//void SetUpProjectileMovement();

	
public:	
	// Sets default values for this actor's properties
	ABaseBolt();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* BoltMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
