// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetPlayerState.h"
#include "Net/UnrealNetwork.h"

ANetPlayerState::ANetPlayerState()
{
	NetUpdateFrequency = 60.0f;	// 파란 박스 위에 올라가는거 글리치 안나는지 다시 확인
	MinNetUpdateFrequency = 5.0f;
}

void ANetPlayerState::AddPickupCount(int32 InAmount)
{
	if (HasAuthority())
	{
		PickupCount += InAmount;
		OnRep_PickupCount();
		ForceNetUpdate();
	}
}

void ANetPlayerState::OnRep_PickupCount()
{
	// UE_LOG(LogTemp, Log, TEXT("[%d] PickupCount : %d"), GetPlayerId(), PickupCount);
}

void ANetPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetPlayerState, PickupCount);
}

