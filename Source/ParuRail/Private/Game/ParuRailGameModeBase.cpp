// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ParuRailGameModeBase.h"

#include "Character/ParuRailPawnExtComponent.h"
#include "Player/ParuRailPlayerController.h"
#include "Player/ParuRailPlayerState.h"
#include "System/ParuRailAssetManager.h"

APawn* AParuRailGameModeBase::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer,
                                                                         const FTransform& SpawnTransform)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;	// Never save the default player pawns into a map.
	SpawnInfo.bDeferConstruction = true;

	if (UClass* PawnClass = GetDefaultPawnClassForController(NewPlayer))
	{
		if (APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnClass, SpawnTransform, SpawnInfo))
		{
			if (UParuRailPawnExtComponent* PawnExtComp = UParuRailPawnExtComponent::FindPawnExtensionComponent(SpawnedPawn))
			{
				if (const UParuRailPawnData* PawnData = GetPawnDataForController(NewPlayer))
				{
					PawnExtComp->SetPawnData(PawnData);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Game mode was unable to set PawnData on the spawned pawn [%s]."), *GetNameSafe(SpawnedPawn));
				}
			}

			SpawnedPawn->FinishSpawning(SpawnTransform);

			return SpawnedPawn;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Game mode was unable to spawn Pawn of class [%s] at [%s]."), *GetNameSafe(PawnClass), *SpawnTransform.ToHumanReadableString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Game mode was unable to spawn Pawn due to NULL pawn class."));
	}

	return nullptr;
}

void AParuRailGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

AParuRailGameModeBase::AParuRailGameModeBase() {
    
}

void AParuRailGameModeBase::SortBySpeed(TArray<AParuRailCharacterBase*> &ParuRailCharacters)
{
	
}

const UParuRailPawnData* AParuRailGameModeBase::GetPawnDataForController(const AController* InController) const
{
	if (InController != nullptr)
	{
		if(const AParuRailPlayerState* PlayerState = InController->GetPlayerState<AParuRailPlayerState>())
		{
			if (const UParuRailPawnData* PawnData = PlayerState->GetPawnData<UParuRailPawnData>())
			{
				return PawnData;
			}
		}
		// If not, fall back to the default for the current experience
		
		// Experience is loaded and there's still no pawn data, fall back to the default for now
		return UParuRailAssetManager::Get().GetDefaultPawnData();
	}
	return nullptr;
}

