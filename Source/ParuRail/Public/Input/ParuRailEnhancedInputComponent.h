// Copyright by Avidel.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "ParuRailInputConfig.h"
#include "ParuRailEnhancedInputComponent.generated.h"

/**
 * Enhanced Input Component for ParuRail
 * Contains helper functions for binding input actions
 */

struct FGameplayTag;
class UParuRailInputConfig;

UCLASS()
class PARURAIL_API UParuRailEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UParuRailInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);

	template <class UserClass, class FuncType>
	void BindNativeAction(const UParuRailInputConfig* InputConfig, const FGameplayTag& InputTag,
	                      ETriggerEvent TriggerEvent,
	                      UserClass* Object, FuncType Func, bool bLogIfNotFound);
};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UParuRailEnhancedInputComponent::BindAbilityActions(const UParuRailInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	checkf(InputConfig, TEXT("InputConfig is null"));
	for(const auto& [InputAction, InputTag]:InputConfig)
	{
		if(PressedFunc)
		{
			BindAction(InputAction, ETriggerEvent::Started, Object, PressedFunc, InputTag);
		}
		if (ReleasedFunc)
		{
			BindAction(InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, InputTag);
		}
		if (ReleasedFunc)
		{
			BindAction(InputAction, ETriggerEvent::Triggered, Object, HeldFunc, InputTag);
		}
	}
}

template<class UserClass, typename FuncType>
void UParuRailEnhancedInputComponent::BindNativeAction(const UParuRailInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag, bLogIfNotFound))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}