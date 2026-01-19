// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NetHUD.generated.h"

/**
 * 
 */
UCLASS()
class KI_EXAM_KWB_NETWORK_API ANetHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "KWB|UI")
	TSubclassOf<UUserWidget> HUDWidgetClass = nullptr;

private:
	UPROPERTY()
	TWeakObjectPtr<UUserWidget> HUDWidget = nullptr;
};
