// Fill out your copyright notice in the Description page of Project Settings.


#include "Spaceship.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "InputActionValue.h"

#include "Kismet/KismetMathLibrary.h"


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
	float AxisValue = InputValue.Get<float>();

	PRINT_F("axis value %f", AxisValue, 4);

	AddMovementInput(GetActorRightVector(), AxisValue);

	auto Mesh = GetMeshComponent();
	FRotator Lean(0.f, 0.f, 30.f);
	Mesh->SetWorldRotation(UKismetMathLibrary::RInterpTo(Mesh->GetComponentRotation(), Lean * AxisValue, GetWorld()->GetDeltaSeconds(), 10));
}

void ASpaceship::MoveEnd(const FInputActionValue& InputValue)
{
	auto Mesh = GetMeshComponent();
	//Mesh->SetWorldRotation(UKismetMathLibrary::RInterpTo(Mesh->GetComponentRotation(), FRotator(0.f), GetWorld()->GetDeltaSeconds(), 5));

	Mesh->SetWorldRotation(FRotator(0.f));
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
		EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASpaceship::Move);
		EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Completed, this, &ASpaceship::MoveEnd);
	}
}
