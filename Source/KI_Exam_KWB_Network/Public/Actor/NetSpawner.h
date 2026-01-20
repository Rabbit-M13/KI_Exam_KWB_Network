// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetSpawner.generated.h"

UCLASS()
class KI_EXAM_KWB_NETWORK_API ANetSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ANetSpawner();

protected:
	virtual void BeginPlay() override;

	void TrySpawnPickup();
	bool FindSpawnLocation(FVector& OutLocation) const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "KWB|Spawner")
	TObjectPtr<class UBoxComponent> SpawnArea = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "KWB|Spawner")
	TSubclassOf<AActor> PickupClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "KWB|Spawner")
	float SpawnInterval = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "KWB|Spawner")
	float SpawnCheckRadius = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "KWB|Spawner")
	int32 MaxSpawnAttempts = 19;

private:
	FTimerHandle SpawnTimerHandle;
};
