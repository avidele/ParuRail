// Copyright by Avidel.


#include "Character/ParuRailPawnExtComponent.h"
#include "Character/ParuRailPawnData.h"
#include "ParuRailGameplayTags.h"
#include "Net/UnrealNetwork.h"

struct FGameplayTag;

void UParuRailPawnExtComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UParuRailPawnExtComponent, PawnData);
}

UParuRailPawnExtComponent::UParuRailPawnExtComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);

	PawnData = nullptr;
	// AbilitySystemComponent = nullptr;
}

void UParuRailPawnExtComponent::SetPawnData(const UParuRailPawnData* InPawnData)
{
		check(InPawnData);
		APawn* Pawn = GetPawnChecked<APawn>();
		if (Pawn->GetLocalRole() != ROLE_Authority)
		{
			return;
		}
		if (PawnData)
		{
			UE_LOG(LogTemp, Error, TEXT("Trying to set PawnData [%s] on pawn [%s] that already has valid PawnData [%s]."), *GetNameSafe(InPawnData), *GetNameSafe(Pawn), *GetNameSafe(PawnData));
			return;
		}
		PawnData = InPawnData;
		Pawn->ForceNetUpdate();
		CheckDefaultInitialization();
}

void UParuRailPawnExtComponent::OnRep_PawnData()
{
	CheckDefaultInitialization();
}

void UParuRailPawnExtComponent::CheckDefaultInitialization()
{
	// Before checking our progress, try progressing any other features we might depend on
	CheckDefaultInitializationForImplementers();
	
	FParuRailGameplayTags ParuRailGameplayTags = FParuRailGameplayTags::Get();
	static const TArray<FGameplayTag> StateChain = {
		ParuRailGameplayTags.InitState_Spawned,
		ParuRailGameplayTags.InitState_DataAvailable,
		ParuRailGameplayTags.InitState_DataInitialized,
		ParuRailGameplayTags.InitState_GameplayReady };

	// This will try to progress from spawned (which is only set in BeginPlay) through the data initialization stages until it gets to gameplay ready
	ContinueInitStateChain(StateChain);
}