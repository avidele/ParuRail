// Copyright by Avidel.


#include "Input/ParuRailInputConfig.h"

const UInputAction* UParuRailInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (const auto& [AbilityIInputAction, AbilityInputTag] : AbilityInputActions)
	{
		if (AbilityInputTag.MatchesTag(InputTag))
		{
			return AbilityIInputAction;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputTag %s not found in %s"), *InputTag.ToString(), *GetName());
	}
	return nullptr;
}

const UInputAction* UParuRailInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (const auto& [NativeInputAction, NativeInputTag] : NativeInputActions)
	{
		if (NativeInputAction && (NativeInputTag == InputTag))
		{
			return NativeInputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
