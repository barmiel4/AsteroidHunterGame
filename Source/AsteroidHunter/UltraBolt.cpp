// Fill out your copyright notice in the Description page of Project Settings.


#include "UltraBolt.h"

#include "Kismet/KismetMathLibrary.h"

#include "ExplosiveMine.h"

#include "Asteroid.h"


#define PRINT(mess, mtime)  GEngine->AddOnScreenDebugMessage(-1, mtime, FColor::Green, TEXT(mess));
#define PRINTC(mess, color)  GEngine->AddOnScreenDebugMessage(-1, 5, color, TEXT(mess));
#define PRINT_F(prompt, mess, mtime) GEngine->AddOnScreenDebugMessage(-1, mtime, FColor::Green, FString::Printf(TEXT(prompt), mess));
#define PRINTC_F(prompt, mess, mtime, color) GEngine->AddOnScreenDebugMessage(-1, mtime, color, FString::Printf(TEXT(prompt), mess));
#define PRINT_B(prompt, mess) GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, FString::Printf(TEXT(prompt), mess ? TEXT("TRUE") : TEXT("FALSE")));



void AUltraBolt::SpawnMines()
{
	PRINTC("SPAWNED MINES", FColor::Cyan);

	for (int i = -4; i < 4; ++i)
	{
		float MineYaw = 36.f * UKismetMathLibrary::RandomFloatInRange(i, i + 1.f);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

		GetWorld()->SpawnActor<AExplosiveMine>(MineClass, GetActorLocation(), FRotator(0.f, MineYaw, 0.f), SpawnParams);
	}
}

AUltraBolt::AUltraBolt()
{
	BoltMesh->OnComponentBeginOverlap.AddDynamic(this, &AUltraBolt::OnMeshBeginOverlap);
}

void AUltraBolt::OnMeshBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnMeshBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	PRINTC("OnMeshBeginOverlap of UltraBolt", FColor::Green);

	if (Cast<AAsteroid>(OtherActor))
		SpawnMines();
}
