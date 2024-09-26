// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"

#include "Components/TimelineComponent.h"

#include "Spaceship.generated.h"


class UInputAction;
class UCurveFloat;
class UParticleSystem;
struct FInputActionValue;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponChanged, bool, bChangeToShotgun);


UCLASS(config = Game)
class ASTEROIDHUNTER_API ASpaceship : public ADefaultPawn
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* LeftAbilityAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* RightAbilityAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* WeaponChangeAction;

	//------------------------- input -------------------------
	float AxisValue = 0.f;

	FRotator Lean = FRotator(0.f, 0.f, 35.f);

	//------------------------- weapons -------------------------

	bool bIsShotgunEquipped = false;

	//------------------------- shield perk -------------------------
	bool bIsUsingShield = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shield Perk|Visuals", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShieldMesh;

	//------------------------- collision handling -------------------------
	FTimeline CollisionReactionTimeline;

	FVector HitOffset;

	FVector OnCollisionLocationCache;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collision Reaction Curves", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* LocationOffsetCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collision Reaction Curves", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* RotationCurve;

	//------------------------- misc -------------------------
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Visuals", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* DamagedEffect;

	UPROPERTY()
	FTimerHandle DestroyTimer = FTimerHandle();
	
	UFUNCTION()
	void OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void TimelineCollisionRotation(float Value);

	UFUNCTION()
	void TimelineCollisionLocationOffset(float Value);

	void ChangeHealthBy(float Amount);

	void OnDeath();

	UFUNCTION()
	void LoadMainMenu();

public:
	ASpaceship();

	void IncreaseScore(int Points);

	void TakeDamage(float Damage);

	void Heal(float HealAmount);

	void CoolGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& InputValue);

	void MoveEnd(const FInputActionValue& InputValue);

	void Shoot();

	void UseShield();

	void UseUltraBolt();

	void ChangeWeapon();

	void HandleCollisionWithShield();

	void UseRifle();

	void UseShotgun();

	void DecreaseHeat();

public:

	UPROPERTY(BlueprintReadOnly, Category = "Player Health")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Health")
	float CritacalDamageThresholdPrecent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Death")
	UParticleSystem* DeathParticle;

	UPROPERTY(BlueprintReadOnly)
	int Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Perk|Score")
	int ShieldCost;

	UPROPERTY(BlueprintReadOnly, Category = "Shield Perk|Score")
	int ShieldThreshold;

	UPROPERTY(BlueprintReadOnly, Category = "Shield Perk|Integrity")
	float ShieldIntegrity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Perk|Integrity")
	float ShieldMaxIntegrity;

	UPROPERTY(BlueprintReadOnly, Category = "Shield Perk|Visuals")
	FLinearColor ShieldDefaultColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Perk|Visuals")
	FLinearColor ShieldDamagedColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Perk|Visuals")
	class UMaterialInterface* ShieldMaterial;

	UPROPERTY(BlueprintReadOnly, Category = "Shield Perk|Visuals")
	class UMaterialInstanceDynamic* ShieldDynamicMaterialInstance;

	UPROPERTY(BlueprintReadOnly, Category = "Ultra Bolt Perk")
	int UltraBoltThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ultra Bolt Perk")
	int UltraBoltCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ultra Bolt Perk")
	TSubclassOf<class AUltraBolt> UltraBoltClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Rifle")
	TSubclassOf<class ABaseBolt> RifleBoltClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Rifle|Overheating")
	float RifleHeatStep;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Rifle|Overheating")
	float RifleOverheatThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Rifle|Overheating")
	float MaxRifleHeat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Shotgun")
	TSubclassOf<class ABaseBolt> ShotgunBoltClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Shotgun|Overheating")
	float ShotgunHeatStep;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Shotgun|Overheating")
	float ShotgunOverheatThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Shotgun|Overheating")
	float MaxShotgunHeat;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon Overheating")
	float RifleHeatLevel = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon Overheating")
	float ShotgunHeatLevel = 0.f;

	UPROPERTY(BlueprintAssignable)
	FOnWeaponChanged OnWeaponChanged;

	UFUNCTION()
	void CollisionReaction(const FVector& AsteroidLocation);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
