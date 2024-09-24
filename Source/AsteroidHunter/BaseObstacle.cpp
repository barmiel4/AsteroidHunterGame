// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseObstacle.h"

#include "Components/SphereComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "GameFramework/RotatingMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"


// Sets default values
ABaseObstacle::ABaseObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	CollisionComponent->SetSphereRadius(50.f);
	SetRootComponent(CollisionComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovement->ProjectileGravityScale = 0.f;

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	//RotatingMovement->RotationRate = FRotator(0.f, 180.f, 0.f);
}

// Called when the game starts or when spawned
void ABaseObstacle::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMovement->InitialSpeed = ProjectileMovement->MaxSpeed = UKismetMathLibrary::RandomFloatInRange(300.f, 700.f);

	ProjectileMovement->Velocity = ProjectileMovement->InitialSpeed * -GetActorForwardVector();
	
	//Speed = UKismetMathLibrary::RandomFloatInRange(300.f, 700.f);

	float MinScale = .7f;
	float MaxScale = 1.5f;
	FVector Scale(
		UKismetMathLibrary::RandomFloatInRange(MinScale, MaxScale),
		UKismetMathLibrary::RandomFloatInRange(MinScale, MaxScale),
		UKismetMathLibrary::RandomFloatInRange(MinScale, MaxScale));

	SetActorScale3D(Scale);

	RotatingMovement->RotationRate = UKismetMathLibrary::RandomRotator();
}

// Called every frame
void ABaseObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AddActorWorldOffset(FVector(-1, 0, 0) * Speed * GetWorld()->GetDeltaSeconds());
}

