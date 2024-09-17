// Fill out your copyright notice in the Description page of Project Settings.


#include "Spaceship.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

ASpaceship::ASpaceship()
{
	PrimaryActorTick.bCanEverTick = true;

	bAddDefaultMovementBindings = false;
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
}

void ASpaceship::Move(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("dupa"));
}

void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Started, this, &ASpaceship::Move);
	}
}
