// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/NetSpawner.h"
#include "Components/BoxComponent.h"
#include "Framework/NetGameState.h"
#include "Kismet/KismetMathLibrary.h"

ANetSpawner::ANetSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SetRootComponent(SpawnArea);
	SpawnArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnArea->SetBoxExtent(FVector(1000.0f, 1000.0f, 200.0f)); // 1200, 1600, 120 정도로 테스트 일단 해봄
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

	if (const ANetGameState* NetGameState = GetWorld()->GetGameState<ANetGameState>())
	{
		if (NetGameState->IsGameOver())
		{
			GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
			return;
		}
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
	if (!SpawnArea)
	{
		return false;
	}

	const FVector Origin = SpawnArea->GetComponentLocation();
	const FVector Extent = SpawnArea->GetScaledBoxExtent();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	for (int32 Attempt = 0; Attempt < MaxSpawnAttempts; ++Attempt)
	{
		const FVector RandomOffset = UKismetMathLibrary::RandomPointInBoundingBox(FVector::ZeroVector, Extent);
		const FVector Candidate = Origin + RandomOffset;
		const bool bOverlapWorld = GetWorld()->OverlapAnyTestByChannel(
			Candidate,
			FQuat::Identity,
			ECC_WorldStatic,
			FCollisionShape::MakeSphere(SpawnCheckRadius),
			Params);

		if (bOverlapWorld)
		{
			continue;
		}

		const bool bOverlapPawn = GetWorld()->OverlapAnyTestByChannel(
			Candidate,
			FQuat::Identity,
			ECC_Pawn,
			FCollisionShape::MakeSphere(SpawnCheckRadius),
			Params);

		if (bOverlapPawn)
		{
			continue;
		}

		OutLocation = Candidate;
		return true;
	}

	return false;
}
