// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunCooler.generated.h"

UCLASS()
class ASTEROIDHUNTER_API AGunCooler : public AActor
{
	GENERATED_BODY()

	UFUNCTION()
	virtual void OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* CoolerMesh;

	class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere)
	class URotatingMovementComponent* RotatingMovement;

	// Sets default values for this actor's properties
	AGunCooler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
