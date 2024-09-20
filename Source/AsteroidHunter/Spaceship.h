// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"

#include "Spaceship.generated.h"


class UInputAction;
struct FInputActionValue;


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

	//------------------------- misc -------------------------
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Visuals", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* DamagedEffect;
	

public:
	ASpaceship();

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

public:

	UPROPERTY(BlueprintReadOnly, Category = "Player Health")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Health")
	float CritacalDamageThresholdPrecent;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Overheating")
	float RifleHeatStep;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Overheating")
	float MaxRifleHeat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Overheating")
	float ShotgunHeatStep;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Overheating")
	float MaxShotgunHeat;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon Overheating")
	float RifleHeatLevel = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon Overheating")
	float ShotgunHeatLevel = 0.f;

	UFUNCTION()
	void CollisionReaction(const FVector& AsteroidLocation);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
