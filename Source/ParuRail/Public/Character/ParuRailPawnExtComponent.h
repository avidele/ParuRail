// Copyright by Avidel.

#pragma once
#include "Components/GameFrameworkInitStateInterface.h"
#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "ParuRailPawnExtComponent.generated.h"

class UParuRailPawnData;
/**
 * 
 */
UCLASS()
class PARURAIL_API UParuRailPawnExtComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()
public:
	UParuRailPawnExtComponent(const FObjectInitializer& ObjectInitializer);
	UFUNCTION(BlueprintPure, Category = "ParuRail|Pawn")
	static UParuRailPawnExtComponent* FindPawnExtensionComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UParuRailPawnExtComponent>() : nullptr); }

	/** Gets the pawn data, which is used to specify pawn properties in data */
	template <class T>
	const T* GetPawnData() const { return Cast<T>(PawnData); }

	/** Sets the current pawn data */
	void SetPawnData(const UParuRailPawnData* InPawnData);

protected:
	UFUNCTION()
	void OnRep_PawnData();
	void CheckDefaultInitialization();

	/** Pawn data used to create the pawn. Specified from a spawn function or on a placed instance. */
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_PawnData, Category = "ParuRail|Pawn")
	TObjectPtr<const UParuRailPawnData> PawnData;
};
