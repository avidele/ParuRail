// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameMode.h"
#include "Character/ParuRailPawnData.h"
#include "ParuRailGameModeBase.generated.h"

class AParuRailCharacterBase;
/**
 *
 */
UCLASS()
class PARURAIL_API AParuRailGameModeBase : public AModularGameModeBase
{
	GENERATED_BODY()

public:
	
	//~AGameModeBase interface
	// virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	// virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) override;
	// virtual bool ShouldSpawnAtStartSpot(AController* Player) override;
	// virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	// virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	// virtual void FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation) override;
	// virtual bool PlayerCanRestart_Implementation(APlayerController* Player) override;
	// virtual void InitGameState() override;
	// virtual bool UpdatePlayerStartSpot(AController* Player, const FString& Portal, FString& OutErrorMessage) override;
	// virtual void GenericPlayerInitialization(AController* NewPlayer) override;
	// virtual void FailedToRestartPlayer(AController* NewPlayer) override;
	//~End of AGameModeBase interface
	
	virtual void BeginPlay() override;
	AParuRailGameModeBase();

	static int GameRound;
protected:
	void SortBySpeed(TArray<AParuRailCharacterBase*> &ParuRailCharacters);

	UFUNCTION(BlueprintCallable, Category = "ParuRail|Pawn")
	const UParuRailPawnData* GetPawnDataForController(const AController* InController) const;
};
