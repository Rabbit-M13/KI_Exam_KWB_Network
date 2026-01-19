// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/NetSpawner.h"
#include "Components/BoxComponent.h"
//#include "Kismet/KismetMathLibrary.h"

ANetSpawner::ANetSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SetRootComponent(SpawnArea);
	SpawnArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnArea->SetBoxExtent(FVector(1000.0f, 1000.0f, 200.0f));
}

void ANetSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(
			SpawnTimerHandle,
			this,
			&ANetSpawner::TrySpawnPickup,
			SpawnInterval,
			true);
	}
}

void ANetSpawner::TrySpawnPickup()
{
	if (!HasAuthority() || !PickupClass)
	{
		return;
	}

	FVector SpawnLocation;
	if (!FindSpawnLocation(SpawnLocation))
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AActor>(PickupClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
}

bool ANetSpawner::FindSpawnLocation(FVector& OutLocation) const
{
	return false;
}
