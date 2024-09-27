// Fill out your copyright notice in the Description page of Project Settings.


#include "GunCooler.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "Spaceship.h"


// Sets default values
AGunCooler::AGunCooler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CollisionComponent->SetupAttachment(Root);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->ProjectileGravityScale = 0;
	ProjectileMovement->bRotationFollowsVelocity = true;

	CoolerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoolerMesh"));
	CoolerMesh->SetupAttachment(CollisionComponent);
	CoolerMesh->SetCollisionProfileName(TEXT("Bolt"));

	CoolerMesh->OnComponentBeginOverlap.AddDynamic(this, &AGunCooler::OnMeshBeginOverlap);

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
}

void AGunCooler::OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Spaceship = Cast<ASpaceship>(OtherActor))
	{
		Spaceship->CoolGun();

		Destroy();
	}
}

// Called when the game starts or when spawned
void AGunCooler::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunCooler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

