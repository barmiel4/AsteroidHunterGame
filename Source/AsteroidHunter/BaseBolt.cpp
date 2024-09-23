// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBolt.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/SceneComponent.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ABaseBolt::ABaseBolt()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComp->ProjectileGravityScale = 0;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	
	BoltMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoltMesh"));
	BoltMesh->SetupAttachment(Root);
	BoltMesh->SetCollisionProfileName(TEXT("Bolt"));
}

// Called when the game starts or when spawned
void ABaseBolt::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMovementComp->InitialSpeed = ProjectileMovementComp->MaxSpeed = BoltSpeed;

	ProjectileMovementComp->Velocity = BoltSpeed * GetActorForwardVector();
}

void ABaseBolt::SpawnCooler()
{

}

// Called every frame
void ABaseBolt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

