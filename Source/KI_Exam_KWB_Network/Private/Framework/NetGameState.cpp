// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetGameState.h"
#include "Framework/NetPlayerState.h"
#include "Net/UnrealNetwork.h"

ANetGameState::ANetGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANetGameState::InitializeMatch(float InMatchDuration)
{
	MatchDuration = InMatchDuration;
	RemainingTime = MatchDuration;
	bGameOver = false;
	bDraw = false;
	WinnerPlayerId = -1;
}

void ANetGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority() && !bGameOver)
	{
		RemainingTime -= DeltaSeconds;
		if (RemainingTime <= 0.0f)
		{
			RemainingTime = 0.0f;
			bGameOver = true;
			ResolveMatchResult();
		}
	}
}

void ANetGameState::ResolveMatchResult()
{
	int32 BestScore = -1;
	WinnerPlayerId = -1;
	bDraw = false;

	for (APlayerState* PlayerState : PlayerArray)
	{
		if (const ANetPlayerState* NetPlayerState = Cast<ANetPlayerState>(PlayerState))
		{
			const int32 Score = NetPlayerState->GetPickupCount();

			if (Score > BestScore)
			{
				BestScore = Score;
				WinnerPlayerId = NetPlayerState->GetPlayerId();
				bDraw = false;
			}
			else if (Score == BestScore)
			{
				bDraw = false;
			}
		}
	}

	if (bDraw)
	{
		WinnerPlayerId = -1;
	}
}

void ANetGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetGameState, RemainingTime);
	DOREPLIFETIME(ANetGameState, bGameOver);
	DOREPLIFETIME(ANetGameState, WinnerPlayerId);
	DOREPLIFETIME(ANetGameState, bDraw);
}