// Copyright by Avidel.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ParuRailPlayerState.generated.h"

class UParuRailPawnData;
/**
 * 
 */
UCLASS()
class PARURAIL_API AParuRailPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	template <class T>
	const T* GetPawnData() const { return Cast<T>(PawnData); }
	
protected:

	UFUNCTION()
	void OnRep_PawnData();
	
	UPROPERTY(ReplicatedUsing = OnRep_PawnData)
	TObjectPtr<const UParuRailPawnData> PawnData;
};
