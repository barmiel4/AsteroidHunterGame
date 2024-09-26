// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/TimelineComponent.h"

#include "ExplosiveMine.generated.h"


class UCurveFloat;


UCLASS()
class ASTEROIDHUNTER_API AExplosiveMine : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MineMesh;

	UPROPERTY(EditAnywhere, Category = "Mines Spawn Data", meta = (AllowPrivateAccess = "true"))
	FVector Bump;

	UPROPERTY(EditAnywhere, Category = Visuals, meta = (AllowPrivateAccess = "true"))
	FLinearColor GlowColorMin;

	UPROPERTY(EditAnywhere, Category = Visuals, meta = (AllowPrivateAccess = "true"))
	FLinearColor GlowColorMax;

	float RandomDistance;

	FVector Start;

	FVector BumpInterpolated = FVector(0.f);

	FTimeline MinesSpawnTimeline;
	
	class UMaterialInstanceDynamic* MineDynamicMaterial;

	UFUNCTION()
	void OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Sets default values for this actor's properties
	AExplosiveMine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, Category = Category = "Mines Spawn Data|Curves")
	UCurveFloat* LocationCurve;

	UPROPERTY(EditAnywhere, Category = Category = "Mines Spawn Data|Curves")
	UCurveFloat* ZBumpCurve;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void TimelineMineDistributionZOffset(float Value);

	UFUNCTION()
	void TimelineMineDistributionLocation(float Value);
};
