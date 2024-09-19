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

	//------------------------- input -------------------------
	float AxisValue = 0.f;

	FRotator Lean = FRotator(0.f, 0.f, 35.f);

	//------------------------- weapons -------------------------
	float RifleHeatLevel= 0.f;

	float ShotgunHeatLevel = 0.f;

	bool bIsShotgunEquipped = false;


public:
	ASpaceship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& InputValue);

	void MoveEnd(const FInputActionValue& InputValue);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Misc|Health")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Misc|Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Misc|Health")
	float CritacalDamageThreshold;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Misc")
	int Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Perk|Score")
	int ShieldCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Perk|Score")
	int ShieldThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Perk|Integrity")
	float ShieldIntegrity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Perk|Integrity")
	float ShieldMaxIntegrity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Perk|Visuals")
	FLinearColor ShieldDefaultColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Perk|Visuals")
	FLinearColor ShieldDamagedColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Perk|Visuals")
	class UMaterialInterface* ShieldMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield Perk|Visuals")
	class UMaterialInstanceDynamic* ShieldDynamicMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ultra Bolt Perk")
	int UltraBoltThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ultra Bolt Perk")
	int UltraBoltCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Overheating")
	float RifleHeatStep;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Overheating")
	float ShotgunHeatStep;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
