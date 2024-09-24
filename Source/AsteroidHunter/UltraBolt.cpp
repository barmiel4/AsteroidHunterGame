// Fill out your copyright notice in the Description page of Project Settings.


#include "UltraBolt.h"

#include "Kismet/KismetMathLibrary.h"

#include "ExplosiveMine.h"

void AUltraBolt::SpawnMines()
{
	for (int i = -4; i < 4; ++i)
	{
		float MineYaw = 36.f * UKismetMathLibrary::RandomFloatInRange(i, i + 1.f);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

		GetWorld()->SpawnActor<AExplosiveMine>(MineClass, GetActorLocation(), FRotator(0.f, MineYaw, 0.f), SpawnParams);
	}
}
