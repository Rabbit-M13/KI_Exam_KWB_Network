// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetGameMode.h"
#include "Framework/NetGameState.h"
#include "Framework/NetPlayerState.h"
#include "Framework/NetPlayerController.h"
#include "UI/NetHUD.h"
#include "Kismet/GameplayStatics.h"

ANetGameMode::ANetGameMode()
{
	GameStateClass = ANetGameState::StaticClass();
	PlayerStateClass = ANetPlayerState::StaticClass();
	PlayerControllerClass = ANetPlayerController::StaticClass();
	HUDClass = ANetHUD::StaticClass();
}

void ANetGameMode::StartPlay()
{
	Super::StartPlay();

	if (HasAuthority())
	{
		if (ANetGameState* NetGameState = GetGameState<ANetGameState>())
		{
			NetGameState->InitializeMatch(MatchDuration);
		}
	}
}

void ANetGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (HasAuthority() && NewPlayer)
	{
		const int32 CurrentPlayers = GetNumPlayers();
		if (CurrentPlayers > ConnectionNumberLimit)
		{
			UE_LOG(LogTemp, Warning, TEXT("정원 가득참. 서버에서 연결해제."));
			NewPlayer->ClientReturnToMainMenuWithTextReason(FText::FromString(TEXT("정원 가득참.")));
			NewPlayer->Destroy();
		}
	}
}
