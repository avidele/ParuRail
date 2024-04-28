// Copyright by Avidel.


#include "Player/ParuRailPlayerState.h"

#include "Net/UnrealNetwork.h"

void AParuRailPlayerState::OnRep_PawnData()
{
}

void AParuRailPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, PawnData, SharedParams);
}