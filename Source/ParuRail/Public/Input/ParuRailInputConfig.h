// Copyright by Avidel.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ParuRailInputConfig.generated.h"

/**
 * 
 */

class UInputAction;

USTRUCT(BlueprintType)
struct PARURAIL_API FParuRailInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
	
};

UCLASS(BlueprintType, Const)
class PARURAIL_API UParuRailInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const;
	
	UFUNCTION(BlueprintCallable, Category = "Lyra|Pawn")
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FParuRailInputAction> AbilityInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FParuRailInputAction> NativeInputActions;
};
