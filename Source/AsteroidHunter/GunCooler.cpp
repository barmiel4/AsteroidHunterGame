// Fill out your copyright notice in the Description page of Project Settings.


#include "GunCooler.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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
	CollisionComponent->SetCollisionProfileName(TEXT("Pickup"));
	CollisionComponent->SetupAttachment(Root);

	//ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	////ProjectileMovement->InitialSpeed = ProjectileMovement->MaxSpeed = IncomingSpeed;
	//ProjectileMovement->ProjectileGravityScale = 0;
	//ProjectileMovement->bRotationFollowsVelocity = true;
	//ProjectileMovement->bIsHomingProjectile = true;
	////ProjectileMovement->HomingAccelerationMagnitude = IncomingAcceleration;

	CoolerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoolerMesh"));
	CoolerMesh->SetupAttachment(CollisionComponent);
	CoolerMesh->SetCollisionProfileName(TEXT("NoCollision"));

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AGunCooler::OnColliderBeginOverlap);

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
}

void AGunCooler::OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

	PlayerSpaceship = Cast<ASpaceship>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	/*ProjectileMovement->HomingAccelerationMagnitude = IncomingAcceleration;
	ProjectileMovement->InitialSpeed = ProjectileMovement->MaxSpeed = IncomingSpeed;

	ProjectileMovement->HomingTargetComponent = PlayerSpaceship->GetRootComponent();*/
}

// Called every frame
void AGunCooler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//handle custom homing positioning
	FVector TargetLocation = PlayerSpaceship->GetActorLocation();
	//TargetLocation.X -= 100.f;

	FVector NewLocation = UKismetMathLibrary::VInterpTo_Constant(GetActorLocation(), TargetLocation, DeltaTime, IncomingSpeed);
	SetActorLocation(NewLocation);

	//handle rotation towards the target
	//float TargetRotationYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerSpaceship->GetActorLocation()).Yaw;
	FRotator TargetRotation = GetActorRotation();
	TargetRotation.Yaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerSpaceship->GetActorLocation()).Yaw;

	SetActorRotation(TargetRotation);
}

