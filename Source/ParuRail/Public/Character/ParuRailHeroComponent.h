// Copyright by Avidel.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnComponent.h"
#include "ParuRailHeroComponent.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Character), meta = (BlueprintSpawnableComponent))
class PARURAIL_API UStarRailHeroComponent : public UPawnComponent
{
	GENERATED_BODY()
public:
	explicit UStarRailHeroComponent(const FObjectInitializer& ObjectInitializer);
protected:
	void Move(const FInputActionValue& InputActionValue);

	void Look(const FInputActionValue& InputActionValue);
	void Jump();
	void StopJumping();


public:
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
};
