// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDHUNTER_API UWeaponInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int PointsOnImpact = 1;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float CoolerChance = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AGunCooler> GunCoolerClass;

public:	
	// Sets default values for this component's properties
	UWeaponInteractionComponent();

	void OnInteraction(const FTransform& HitActorTranform);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
