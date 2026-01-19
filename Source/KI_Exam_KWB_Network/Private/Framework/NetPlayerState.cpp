// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetPlayerState.h"
#include "Net/UnrealNetwork.h"

void ANetPlayerState::AddPickupCount(int32 InAmount)
{
	if (HasAuthority())
	{
		PickupCount += InAmount;
		OnRep_PickupCount();
	}
}

void ANetPlayerState::OnRep_PickupCount()
{
	// (재검토) 굳이 없어도 됨. 추후에 UI로 빼는 것 고려.
	UE_LOG(LogTemp, Log, TEXT("[%d] PickupCount : %d"), GetPlayerId(), PickupCount);
}

void ANetPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetPlayerState, PickupCount);
}

