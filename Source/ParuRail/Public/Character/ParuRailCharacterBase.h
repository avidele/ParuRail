// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParuRailHeroComponent.h"
#include "GameFramework/Character.h"
#include "ParuRailCharacterBase.generated.h"

class UParuRailPawnExtComponent;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;

UCLASS()
class PARURAIL_API AParuRailCharacterBase : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/**
	 * Pawn Component
	 **/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStarRailHeroComponent> StarRailHeroComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParuRailPawnExtComponent> ParuRailPawnExtComponent;

public:
	AParuRailCharacterBase();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();
	
	virtual void PossessedBy(AController* NewController) override;
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
