// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NetHUDWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class KI_EXAM_KWB_NETWORK_API UNetHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateTime();
	void UpdateScores();
	void UpdateResult();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> RemainingTimeText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MyScoreText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> OtherScoreText = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ResultText = nullptr;

private:
	bool bInputLocked = false;
};
