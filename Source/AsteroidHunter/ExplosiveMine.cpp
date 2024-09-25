// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveMine.h"

#include "Materials/MaterialInstanceDynamic.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AExplosiveMine::AExplosiveMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MineMesh"));
	MineMesh->SetCollisionProfileName(TEXT("Mine"));
	SetRootComponent(MineMesh);

	//can timeline be here?
	/*FOnTimelineFloat TimelineProgressLocation;
	TimelineProgressLocation.BindUFunction(this, FName("TimelineProgessLocation"));
	TeleportTimeline.AddInterpFloat(LocationCurve, TimelineProgressLocation);*/
}

// Called when the game starts or when spawned
void AExplosiveMine::BeginPlay()
{
	Super::BeginPlay();

	MineDynamicMaterial = MineMesh->CreateDynamicMaterialInstance(0);

	FVector Start = GetActorLocation();
	Start.Z += 10;
	
	float RandomDistance = UKismetMathLibrary::RandomFloatInRange(170.f, 300.f);

	//add timeline
}

// Called every frame
void AExplosiveMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Alpha = UKismetMathLibrary::MakePulsatingValue(UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld()), 2);
	FLinearColor MineColor = UKismetMathLibrary::LinearColorLerp(GlowColorMin, GlowColorMax, Alpha);

	MineDynamicMaterial->SetVectorParameterValue(FName("Color"), MineColor);
}

void AExplosiveMine::TimelineMineDistribution(float Value)
{

}

