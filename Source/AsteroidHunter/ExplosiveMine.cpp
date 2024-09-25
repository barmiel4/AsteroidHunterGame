// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveMine.h"

#include "Materials/MaterialInstanceDynamic.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


#define PRINT(mess, mtime)  GEngine->AddOnScreenDebugMessage(-1, mtime, FColor::Green, TEXT(mess));
#define PRINTC(mess, color)  GEngine->AddOnScreenDebugMessage(-1, 5, color, TEXT(mess));
#define PRINT_F(prompt, mess, mtime) GEngine->AddOnScreenDebugMessage(-1, mtime, FColor::Green, FString::Printf(TEXT(prompt), mess));
#define PRINTC_F(prompt, mess, mtime, color) GEngine->AddOnScreenDebugMessage(-1, mtime, color, FString::Printf(TEXT(prompt), mess));
#define PRINT_B(prompt, mess) GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, FString::Printf(TEXT(prompt), mess ? TEXT("TRUE") : TEXT("FALSE")));


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
	TimelineProgressLocation.BindUFunction(this, FName("TimelineMineDistributionLocation"));
	MinesSpawnTimeline.AddInterpFloat(LocationCurve, TimelineProgressLocation);

	FOnTimelineFloat TimelineProgressZOffset;
	TimelineProgressZOffset.BindUFunction(this, FName("TimelineMineDistributionZOffset"));
	MinesSpawnTimeline.AddInterpFloat(ZBumpCurve, TimelineProgressZOffset);

	MinesSpawnTimeline.SetLooping(false);*/
}

// Called when the game starts or when spawned
void AExplosiveMine::BeginPlay()
{
	Super::BeginPlay();

	MineDynamicMaterial = MineMesh->CreateDynamicMaterialInstance(0);

	Start = GetActorLocation();
	Start.Z += 10;
	
	RandomDistance = UKismetMathLibrary::RandomFloatInRange(170.f, 300.f);

	FOnTimelineFloat TimelineProgressZOffset;
	TimelineProgressZOffset.BindUFunction(this, FName("TimelineMineDistributionZOffset"));
	MinesSpawnTimeline.AddInterpFloat(ZBumpCurve, TimelineProgressZOffset);

	FOnTimelineFloat TimelineProgressLocation;
	TimelineProgressLocation.BindUFunction(this, FName("TimelineMineDistributionLocation"));
	MinesSpawnTimeline.AddInterpFloat(LocationCurve, TimelineProgressLocation);

	//MinesSpawnTimeline.SetPlayRate(.1);

	MinesSpawnTimeline.SetLooping(false);

	MinesSpawnTimeline.PlayFromStart();
}

// Called every frame
void AExplosiveMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MinesSpawnTimeline.TickTimeline(DeltaTime);

	float Alpha = UKismetMathLibrary::MakePulsatingValue(UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld()), 2);
	FLinearColor MineColor = UKismetMathLibrary::LinearColorLerp(GlowColorMin, GlowColorMax, Alpha);

	MineDynamicMaterial->SetVectorParameterValue(FName("Color"), MineColor);
}


void AExplosiveMine::TimelineMineDistributionZOffset(float Value)
{
	//PRINTC("Z-Offset Timeline", FColor::Cyan);

	BumpInterpolated = Bump * Value;
}

void AExplosiveMine::TimelineMineDistributionLocation(float Value)
{
	//PRINTC("Location Timeline", FColor::White);

	FVector Target = Start + BumpInterpolated + (GetActorForwardVector() * RandomDistance);
	FVector NewLocation = UKismetMathLibrary::VEase(Start, Target, Value, EEasingFunc::EaseInOut);

	SetActorLocation(NewLocation);
}