// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetPickup.generated.h"

UCLASS()
class KI_EXAM_KWB_NETWORK_API ANetPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ANetPickup();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "KWB|Pickup")
	TObjectPtr<class USphereComponent> Collision = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "KWB|Pickup")
	TObjectPtr<class UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "KWB|Pickup")
	int32 PickupValue = 1;
};
