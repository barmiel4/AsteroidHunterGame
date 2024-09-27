// Fill out your copyright notice in the Description page of Project Settings.


#include "Spaceship.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "InputActionValue.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"

#include "Components/StaticMeshComponent.h"

#include "Particles/ParticleSystemComponent.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"

//#include "GameplaySta"

#include "BaseBolt.h"
#include "UltraBolt.h"



#define PRINT(mess, mtime)  GEngine->AddOnScreenDebugMessage(-1, mtime, FColor::Green, TEXT(mess));
#define PRINTC(mess, color)  GEngine->AddOnScreenDebugMessage(-1, 5, color, TEXT(mess));
#define PRINT_F(prompt, mess, mtime) GEngine->AddOnScreenDebugMessage(-1, mtime, FColor::Green, FString::Printf(TEXT(prompt), mess));
#define PRINTC_F(prompt, mess, mtime, color) GEngine->AddOnScreenDebugMessage(-1, mtime, color, FString::Printf(TEXT(prompt), mess));
#define PRINT_B(prompt, mess) GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, FString::Printf(TEXT(prompt), mess ? TEXT("TRUE") : TEXT("FALSE")));


ASpaceship::ASpaceship()
{
	PrimaryActorTick.bCanEverTick = true;

	bAddDefaultMovementBindings = false;

	GetMeshComponent()->SetCollisionProfileName(TEXT("NoCollision"));

	ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield Mesh"));
	ShieldMesh->SetupAttachment(RootComponent);
	ShieldMesh->SetVisibility(false);
	ShieldMesh->SetCollisionProfileName(TEXT("Shield"));

	ShieldMesh->OnComponentBeginOverlap.AddDynamic(this, &ASpaceship::OnMeshBeginOverlap);

	DamagedEffect = CreateDefaultSubobject< UParticleSystemComponent>(TEXT("Damaged Effect"));
	DamagedEffect->SetupAttachment(RootComponent);
	DamagedEffect->bAutoActivate = false;
}

void ASpaceship::IncreaseScore(int Points)
{
	Score += Points;
}

void ASpaceship::TakeDamage(float Damage)
{
	if (bIsUsingShield)
		return;

	ChangeHealthBy(-Damage);

	if (Health <= 0.f)
		OnDeath();
}

void ASpaceship::Heal(float HealAmount)
{
	ChangeHealthBy(HealAmount);
}

void ASpaceship::CoolGun()
{
	if (UKismetMathLibrary::RandomBool())
		RifleHeatLevel *= 0.5f;
	else
		ShotgunHeatLevel *= 0.2f;
}

void ASpaceship::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	//initialize defaults
	Health = MaxHealth;

	ShieldThreshold = ShieldCost;
	ShieldIntegrity = ShieldMaxIntegrity;

	ShieldDynamicMaterialInstance = ShieldMesh->CreateDynamicMaterialInstance(0);
	
	ShieldDynamicMaterialInstance->GetVectorParameterValue(FName("Color"), ShieldDefaultColor);
	ShieldMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	UltraBoltThreshold = UltraBoltCost;

	//set up timelines
	FOnTimelineFloat TimelineProgressRotation;
	TimelineProgressRotation.BindUFunction(this, FName("TimelineCollisionRotation"));
	CollisionReactionTimeline.AddInterpFloat(RotationCurve, TimelineProgressRotation);

	FOnTimelineFloat TimelineProgressLocationOffset;
	TimelineProgressLocationOffset.BindUFunction(this, FName("TimelineCollisionLocationOffset"));
	CollisionReactionTimeline.AddInterpFloat(LocationOffsetCurve, TimelineProgressLocationOffset);	

}

void ASpaceship::Move(const FInputActionValue& InputValue)
{
	AxisValue = InputValue.Get<float>();

	AddMovementInput(GetActorRightVector(), AxisValue);
}

void ASpaceship::MoveEnd(const FInputActionValue& InputValue)
{
	AxisValue = 0.f;
}

void ASpaceship::Shoot()
{
	//CoolGun();

	if (bIsShotgunEquipped)
		UseShotgun();
	else
		UseRifle();
}

void ASpaceship::UseShield()
{
	if (bIsUsingShield || Score < ShieldThreshold)
		return;
	
	ShieldMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ShieldMesh->SetVisibility(true);

	bIsUsingShield = true;
}

void ASpaceship::UseUltraBolt()
{
	if (Score < UltraBoltThreshold)
		return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.TransformScaleMethod = ESpawnActorScaleMethod::OverrideRootScale;

	GetWorld()->SpawnActor<AUltraBolt>(UltraBoltClass, GetActorTransform(), SpawnParams);

	UltraBoltThreshold = Score + UltraBoltCost;
}

void ASpaceship::ChangeWeapon()
{
	bIsShotgunEquipped = !bIsShotgunEquipped;

	OnWeaponChanged.Broadcast(bIsShotgunEquipped);
}

void ASpaceship::HandleCollisionWithShield()
{
	if (--ShieldIntegrity <= 0)
	{
		ShieldMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ShieldMesh->SetVisibility(false);

		ShieldIntegrity = ShieldMaxIntegrity;

		bIsUsingShield = false;

		ShieldThreshold = Score + ShieldCost;
	}

	float LerpAlpha = (ShieldIntegrity - 1) / ShieldMaxIntegrity;
	FLinearColor ShieldColor = UKismetMathLibrary::LinearColorLerp(ShieldDamagedColor, ShieldDefaultColor, LerpAlpha);
	ShieldDynamicMaterialInstance->SetVectorParameterValue(FName("Color"), ShieldColor);
}

void ASpaceship::UseRifle()
{
	if (RifleHeatLevel >= RifleOverheatThreshold)
		return;

	RifleHeatLevel += RifleHeatStep;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.TransformScaleMethod = ESpawnActorScaleMethod::OverrideRootScale;

	GetWorld()->SpawnActor<ABaseBolt>(RifleBoltClass, FTransform(GetActorLocation()), SpawnParams);
}

void ASpaceship::UseShotgun()
{
	if (ShotgunHeatLevel >= ShotgunOverheatThreshold)
		return;

	ShotgunHeatLevel += ShotgunHeatStep;

	for (int BoltDir = -2; BoltDir <= 2; ++BoltDir)
	{
		FTransform BoltTransform(
			FRotator(0.f, BoltDir * 20, 0.f),
			GetActorLocation()
		);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.TransformScaleMethod = ESpawnActorScaleMethod::OverrideRootScale;

		GetWorld()->SpawnActor<ABaseBolt>(ShotgunBoltClass, BoltTransform, SpawnParams);
	}
}

void ASpaceship::DecreaseHeat()
{
	RifleHeatLevel = UKismetMathLibrary::FInterpTo(RifleHeatLevel, 0, GetWorld()->GetDeltaSeconds(), .3f);

	ShotgunHeatLevel = UKismetMathLibrary::FInterpTo(ShotgunHeatLevel, 0, GetWorld()->GetDeltaSeconds(), .1f);
}

void ASpaceship::OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HandleCollisionWithShield();
}

void ASpaceship::TimelineCollisionRotation(float Value)
{
	FRotator CollisionRotation = UKismetMathLibrary::RLerp(GetActorRotation(), FRotator(HitOffset.X, 0.f, -HitOffset.Y), Value, false);

	GetMeshComponent()->SetWorldRotation(CollisionRotation);
}

void ASpaceship::TimelineCollisionLocationOffset(float Value)
{
	FVector CollisionLocation = UKismetMathLibrary::VLerp(OnCollisionLocationCache, OnCollisionLocationCache - HitOffset, Value);

	SetActorLocation(CollisionLocation);
}

void ASpaceship::ChangeHealthBy(float Amount)
{
	Health = FMath::Clamp(Health + Amount, 0.f, MaxHealth);

	if ((Health / MaxHealth) <= CritacalDamageThresholdPrecent)
		DamagedEffect->Activate();
	else
		DamagedEffect->Deactivate();
}

void ASpaceship::OnDeath()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorTransform());

	SetActorHiddenInGame(true);

	SetActorEnableCollision(false);

	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &ASpaceship::LoadMainMenu, 2.f, false);
}

void ASpaceship::LoadMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Main Menu");
}

void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CollisionReactionTimeline.TickTimeline(DeltaTime);

	auto Mesh = GetMeshComponent();
	float InterpSpeed = AxisValue == 0.f ? 5.5f : 10.f;
	Mesh->SetWorldRotation(UKismetMathLibrary::RInterpTo(Mesh->GetComponentRotation(), Lean * AxisValue, GetWorld()->GetDeltaSeconds(), InterpSpeed));

	DecreaseHeat();
}

void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//movement
		EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASpaceship::Move);
		EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Completed, this, &ASpaceship::MoveEnd);

		//shooting
		EnhancedInputComp->BindAction(ShootAction, ETriggerEvent::Started, this, &ASpaceship::Shoot);

		//perks
		EnhancedInputComp->BindAction(LeftAbilityAction, ETriggerEvent::Started, this, &ASpaceship::UseShield);
		EnhancedInputComp->BindAction(RightAbilityAction, ETriggerEvent::Started, this, &ASpaceship::UseUltraBolt);

		//changing weapon
		EnhancedInputComp->BindAction(WeaponChangeAction, ETriggerEvent::Started, this, &ASpaceship::ChangeWeapon);
	}
}

void ASpaceship::CollisionReaction(const FVector& AsteroidLocation)
{
	if (bIsUsingShield)
		return;

	float CollisionRadius = GetCollisionComponent()->GetScaledSphereRadius();
	auto ToAstroid = AsteroidLocation - GetActorLocation();
	HitOffset = UKismetMathLibrary::ClampVectorSize(ToAstroid, CollisionRadius * .5f, CollisionRadius);

	OnCollisionLocationCache = GetActorLocation();

	CollisionReactionTimeline.PlayFromStart();
}
