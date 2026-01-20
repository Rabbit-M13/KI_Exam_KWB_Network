// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NetHUDWidget.h"
#include "Framework/NetGameState.h"
#include "Framework/NetPlayerState.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UNetHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateTime();
	UpdateScores();
	UpdateResult();
}

void UNetHUDWidget::UpdateTime()
{
	if (!RemainingTimeText)
	{
		return;
	}

	if (const ANetGameState* NetGameState = GetWorld()->GetGameState<ANetGameState>())
	{
		const int32 Total = FMath::Max(0, FMath::FloorToInt(NetGameState->GetRemainingTime()));
		const int32 Minutes = Total / 60;
		const int32 Seconds = Total % 60;
		RemainingTimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d : %02d"), Minutes, Seconds)));
	}
}

void UNetHUDWidget::UpdateScores()
{
	if (!MyScoreText || !OtherScoreText)
	{
		return;
	}

	const ANetGameState* NetGameState = GetWorld()->GetGameState<ANetGameState>();
	APlayerController* PlayerController = GetOwningPlayer();
	const ANetPlayerState* MyState = PlayerController ? PlayerController->GetPlayerState<ANetPlayerState>() : nullptr;

	int32 MyScore = 0;
	int32 OtherScore = 0;

	if (MyState)
	{
		MyScore = MyState->GetPickupCount();
	}

	if (NetGameState)
	{
		for (APlayerState* PlayerState : NetGameState->PlayerArray)
		{
			const ANetPlayerState* OtherState = Cast<ANetPlayerState>(PlayerState);
			if (OtherState && OtherState != MyState)
			{
				OtherScore = OtherState->GetPickupCount();
				break;
			}
		}
	}

	MyScoreText->SetText(FText::AsNumber(MyScore));
	OtherScoreText->SetText(FText::AsNumber(OtherScore));
}

void UNetHUDWidget::UpdateResult()
{
	if (!ResultText)
	{
		return;
	}

	const ANetGameState* NetGameState = GetWorld()->GetGameState<ANetGameState>();
	APlayerController* PlayerController = GetOwningPlayer();

	const ANetPlayerState* MyState = PlayerController ? PlayerController->GetPlayerState<ANetPlayerState>() : nullptr;

	if (!NetGameState || !NetGameState->IsGameOver())
	{
		ResultText->SetText(FText::GetEmpty());
		return;
	}

	if (NetGameState->IsDraw())
	{
		ResultText->SetText(FText::FromString(TEXT("Draw!")));
	}
	else if (MyState && NetGameState->GetWinnerPlayerId() == MyState->GetPlayerId())
	{
		ResultText->SetText(FText::FromString(TEXT("Victory!!")));
	}
	else
	{
		ResultText->SetText(FText::FromString(TEXT("Defeat")));
	}

	// 입력 & 움직임 비활성화
	if (!bInputLocked && PlayerController)
	{
		bInputLocked = true;
		PlayerController->SetIgnoreMoveInput(true);
		PlayerController->SetIgnoreLookInput(true);
		if (APawn* Pawn = PlayerController->GetPawn())
		{
			Pawn->DisableInput(PlayerController);
			if (ACharacter* Character = Cast<ACharacter>(Pawn))
			{
				if (Character->GetCharacterMovement())
				{
					Character->GetCharacterMovement()->DisableMovement();
				}
			}
		}
	}
}
