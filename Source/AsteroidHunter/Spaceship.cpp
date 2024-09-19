// Fill out your copyright notice in the Description page of Project Settings.


#include "Spaceship.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "InputActionValue.h"

#include "Kismet/KismetMathLibrary.h"

#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"


#define PRINT(mess, mtime)  GEngine->AddOnScreenDebugMessage(-1, mtime, FColor::Green, TEXT(mess));
#define PRINTC(mess, color)  GEngine->AddOnScreenDebugMessage(-1, 3, color, TEXT(mess));
#define PRINT_F(prompt, mess, mtime) GEngine->AddOnScreenDebugMessage(-1, mtime, FColor::Green, FString::Printf(TEXT(prompt), mess));
#define PRINTC_F(prompt, mess, mtime, color) GEngine->AddOnScreenDebugMessage(-1, mtime, color, FString::Printf(TEXT(prompt), mess));
#define PRINT_B(prompt, mess) GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, FString::Printf(TEXT(prompt), mess ? TEXT("TRUE") : TEXT("FALSE")));


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
	AxisValue = InputValue.Get<float>();

	AddMovementInput(GetActorRightVector(), AxisValue);
}

void ASpaceship::MoveEnd(const FInputActionValue& InputValue)
{
	AxisValue = 0.f;
}

void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto Mesh = GetMeshComponent();
	float InterpSpeed = AxisValue == 0.f ? 5.5f : 10.f;
	Mesh->SetWorldRotation(UKismetMathLibrary::RInterpTo(Mesh->GetComponentRotation(), Lean * AxisValue, GetWorld()->GetDeltaSeconds(), InterpSpeed));
}

void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASpaceship::Move);
		EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Completed, this, &ASpaceship::MoveEnd);
	}
}
