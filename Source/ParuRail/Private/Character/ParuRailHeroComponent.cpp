// Copyright by Avidel.


#include "Character/ParuRailHeroComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "ParuRailGameplayTags.h"
#include "Character/ParuRailPawnData.h"
#include "Character/ParuRailPawnExtComponent.h"
#include "GameFramework/Character.h"
#include "Input/ParuRailEnhancedInputComponent.h"

void UStarRailHeroComponent::Jump()
{
	if(GetOwner() && GetOwner()->IsA<ACharacter>())
	{
		Cast<ACharacter>(GetOwner())->Jump();
	}
}

void UStarRailHeroComponent::StopJumping()
{
	if(GetOwner() && GetOwner()->IsA<ACharacter>())
	{
		Cast<ACharacter>(GetOwner())->StopJumping();
	}
}

UStarRailHeroComponent::UStarRailHeroComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, DefaultMappingContext(nullptr)
{
}

void UStarRailHeroComponent::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetPawn<APawn>()->GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void UStarRailHeroComponent::Look(const FInputActionValue& InputActionValue)
{
	APawn *Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}
	const FVector2D Value = InputActionValue.Get<FVector2D>();
	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X);
	}
	if (Value.Y != 0.0f)
	{
		Pawn->AddControllerPitchInput(Value.Y);
	}
}

void UStarRailHeroComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn) return;
	
	const APlayerController *PC = GetController<APlayerController>();
	check(PC);
	
	const ULocalPlayer *ParuRailPlayer = Cast<ULocalPlayer>(PC->GetLocalPlayer());
	check(ParuRailPlayer);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(ParuRailPlayer);
	if (!Subsystem) return;

	Subsystem->AddMappingContext(DefaultMappingContext,1);

	if(const UParuRailPawnExtComponent* PawnExtComponent = UParuRailPawnExtComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const UParuRailPawnData* ParuRailPawnData = PawnExtComponent->GetPawnData<UParuRailPawnData>())
		{
			if (const UParuRailInputConfig *InputConfig = ParuRailPawnData->InputConfig)
			{
				if (UParuRailEnhancedInputComponent* ParuInputComponent = Cast<UParuRailEnhancedInputComponent>(PlayerInputComponent))
				{
					FParuRailGameplayTags ParuRailGameplayTags = FParuRailGameplayTags::Get();
					ParuInputComponent->BindNativeAction(InputConfig, ParuRailGameplayTags.InputTag_Jump, ETriggerEvent::Started, this, &ThisClass::Jump, true);
					ParuInputComponent->BindNativeAction(InputConfig, ParuRailGameplayTags.InputTag_Jump, ETriggerEvent::Completed, this, &ThisClass::StopJumping, true);
					ParuInputComponent->BindNativeAction(InputConfig, ParuRailGameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Move, true);
					ParuInputComponent->BindNativeAction(InputConfig, ParuRailGameplayTags.InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Look, true);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
				}
			}
		}
	}
}

void UStarRailHeroComponent::AbilityInputTagPressed(FGameplayTag InputTag)
{
	// if (InputTag.MatchesTagExact(FParuRailGameplayTags::Get().InputTag_LMB))
	// {
	// 	bTargeting = ThisActor ? true : false;
	// 	bAutoRunning = false;
	// }
}

void UStarRailHeroComponent::AbilityInputTagReleased(FGameplayTag InputTag)
{
	// GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Blue, TEXT("AbilityInputTagReleased"));
	// if (!InputTag.MatchesTagExact(FParuRailGameplayTags::Get().InputTag_LMB) || bTargeting)
	// {
	// 	const auto Asc= GetASC();
	// 	if (Asc) Asc->AbilityInputTagReleased(InputTag);
	// 	return;
	// }
	// const auto ControlledPawn = GetPawn();
	// if (FollowTime <= ShortPressThreshold && ControlledPawn)
	// {
	// 	if (const auto NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), ControlledPawn->GetActorLocation(), CachedDestination))
	// 	{
	// 		Spline->ClearSplinePoints();
	// 		for (const auto& PathPoint : NavPath->PathPoints)
	// 		{
	// 			Spline->AddSplinePoint(PathPoint, ESplineCoordinateSpace::World);
	// 			DrawDebugSphere(GetWorld(), PathPoint, 25.f, 12, FColor::Green, false, 2.f);
	// 		}
	// 		bAutoRunning = true;
	// 		if (const auto Nav = NavPath->PathPoints.Num()-1 > 0)
	// 		CachedDestination = NavPath->PathPoints[Nav];
	// 	}
	// }
	// FollowTime = 0.f;
	// bTargeting = false;
}

void UStarRailHeroComponent::AbilityInputTagHeld(FGameplayTag InputTag)
{
	// GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Green, TEXT("AbilityInputTagHeld"));
	// if (!InputTag.MatchesTagExact(FParuRailGameplayTags::Get().InputTag_LMB))
	// {
	// 	if (GetASC())
	// 	{
	// 		GetASC()->AbilityInputTagHeld(InputTag);
	// 	}
	// 	return;
	// }
	// if (bTargeting)
	// {
	// 	if (GetASC())
	// 	{
	// 		GetASC()->AbilityInputTagHeld(InputTag);
	// 	}
	// }
	// else
	// {
	// 	FollowTime += GetWorld()->GetDeltaSeconds();
	// 	FHitResult HitResult;
	// 	if(GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	// 	{
	// 		CachedDestination = HitResult.ImpactPoint;
	// 	}
	// 	if (APawn* ControlledPawn = GetPawn())
	// 	{
	// 		const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
	// 		ControlledPawn->AddMovementInput(WorldDirection);
	// 	}
	// }
}