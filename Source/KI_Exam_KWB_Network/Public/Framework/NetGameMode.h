// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetGameMode.generated.h"

/**
 * 
 */
UCLASS()
class KI_EXAM_KWB_NETWORK_API ANetGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ANetGameMode();

protected:
	virtual void StartPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "KWB|Rules")
	int32 ConnectionNumberLimit = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "KWB|Rules")
	float MatchDuration = 60.0f;
};
