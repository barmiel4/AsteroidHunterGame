// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerSpaceship.generated.h"

class UInputAction;
struct FInputActionValue;

UCLASS()
class ASTEROIDHUNTER_API APlayerSpaceship : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	//ability actions

public:
	// Sets default values for this pawn's properties
	APlayerSpaceship();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& InputValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
