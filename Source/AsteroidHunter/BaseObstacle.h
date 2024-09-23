// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseObstacle.generated.h"

UCLASS()
class ASTEROIDHUNTER_API ABaseObstacle : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollisionComponent;


public:	
	// Sets default values for this actor's properties
	ABaseObstacle();

protected:
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere)
	class URotatingMovementComponent* RotatingMovement;

	//UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float Speed;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
