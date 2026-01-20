// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NetPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class KI_EXAM_KWB_NETWORK_API ANetPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ANetPlayerState();

	UFUNCTION(BlueprintCallable, Category = "KWB|Score")
	void AddPickupCount(int32 InAmount);

	UFUNCTION(BlueprintCallable, Category = "KWB|Score")
	int32 GetPickupCount() const { return PickupCount; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_PickupCount();

protected:
	UPROPERTY(ReplicatedUsing = OnRep_PickupCount, BlueprintReadOnly, Category = "KWB|Score")
	int32 PickupCount = 0;
};
