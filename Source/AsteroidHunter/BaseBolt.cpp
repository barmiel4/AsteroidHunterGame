// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBolt.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Asteroid.h"

#include "Spaceship.h"

#include "WeaponInteractionComponent.h"


#define PRINT(mess, mtime)  GEngine->AddOnScreenDebugMessage(-1, mtime, FColor::Green, TEXT(mess));
#define PRINTC(mess, color)  GEngine->AddOnScreenDebugMessage(-1, 5, color, TEXT(mess));
#define PRINT_F(prompt, mess, mtime) GEngine->AddOnScreenDebugMessage(-1, mtime, FColor::Green, FString::Printf(TEXT(prompt), mess));
#define PRINTC_F(prompt, mess, mtime, color) GEngine->AddOnScreenDebugMessage(-1, mtime, color, FString::Printf(TEXT(prompt), mess));
#define PRINT_B(prompt, mess) GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, FString::Printf(TEXT(prompt), mess ? TEXT("TRUE") : TEXT("FALSE")));


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
	BoltMesh->SetCollisionProfileName(TEXT("DestructionTool"));
	BoltMesh->bRenderCustomDepth = true;
	BoltMesh->CustomDepthStencilValue = 1;

	BoltMesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseBolt::OnMeshBeginOverlap);
}

// Called when the game starts or when spawned
void ABaseBolt::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMovementComp->InitialSpeed = ProjectileMovementComp->MaxSpeed = BoltSpeed;

	ProjectileMovementComp->Velocity = BoltSpeed * GetActorForwardVector();
}

void ABaseBolt::OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AAsteroid* Asteroid = Cast<AAsteroid>(OtherActor))
	{
		Asteroid->HitLocationCache = GetActorLocation();

		auto Player = Cast<ASpaceship>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (Player)
			Player->IncreaseScore(PointsOnImpact);

		Destroy();
	}
}

// Called every frame
void ABaseBolt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

