#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ParuRailPawnData.generated.h"

class UParuRailInputConfig;

UCLASS(BlueprintType, Const, Meta = (DisplayName = "ParuRail Pawn Data", ShortTooltip = "Data asset used to define a Pawn."))
class PARURAIL_API UParuRailPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// Input configuration used by player controlled pawns to create input mappings and bind input actions.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ParuRail|Input")
	TObjectPtr<UParuRailInputConfig> InputConfig;
};