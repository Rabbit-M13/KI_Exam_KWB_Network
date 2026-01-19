// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NetHUD.h"
#include "Blueprint/UserWidget.h"

void ANetHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		if (HUDWidget.IsValid())
		{
			HUDWidget->AddToViewport();
		}
	}
}
