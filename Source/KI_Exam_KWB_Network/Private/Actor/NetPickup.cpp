// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/NetPickup.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Framework/NetPlayerState.h"

ANetPickup::ANetPickup()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(50.0f);
	SetRootComponent(Collision);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetRelativeLocation(FVector::UpVector * 30.0f);
}

void ANetPickup::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ANetPickup::OnOverlap);
}

void ANetPickup::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character)
	{
		return;
	}

	if (ANetPlayerState* NetPlayerState = Character->GetPlayerState<ANetPlayerState>())
	{
		NetPlayerState->AddPickupCount(PickupValue);
		Destroy();
	}
}
