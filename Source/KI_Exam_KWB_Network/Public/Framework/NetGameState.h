// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NetGameState.generated.h"

/**
 * 
 */
UCLASS()
class KI_EXAM_KWB_NETWORK_API ANetGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ANetGameState();

	void InitializeMatch(float InMatchDuration);

	UFUNCTION(BlueprintCallable, Category = "KWB|Game")
	float GetRemainingTime() const { return RemainingTime; }

	UFUNCTION(BlueprintCallable, Category = "KWB|Game")
	bool IsGameOver() const { return bGameOver; }

	UFUNCTION(BlueprintCallable, Category = "KWB|Game")
	int32 GetWinnerPlayerId() const { return WinnerPlayerId; }

	UFUNCTION(BlueprintCallable, Category = "KWB|Game")
	bool IsDraw() const { return bDraw; }

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void ResolveMatchResult();

protected:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "KWB|Game")
	float RemainingTime = 0.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "KWB|Game")
	bool bGameOver = false;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "KWB|Game")
	int32 WinnerPlayerId = -1;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "KWB|Game")
	bool bDraw = false;

private:
	float MatchDuration = 60.0f;
};
