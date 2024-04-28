#include "Character/ParuRailCharacterBase.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/ParuRailPawnExtComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/ParuRailEnhancedInputComponent.h"

AParuRailCharacterBase::AParuRailCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true; 
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	StarRailHeroComponent = CreateDefaultSubobject<UStarRailHeroComponent>(TEXT("StarRailHeroComponent"));
	// StarRailHeroComponent->DefaultMappingContext = nullptr;
	// StarRailHeroComponent->JumpAction = nullptr;
	// StarRailHeroComponent->MoveAction = nullptr;
	// StarRailHeroComponent->LookAction = nullptr;

	ParuRailPawnExtComponent = CreateDefaultSubobject<UParuRailPawnExtComponent>(TEXT("ParuRailPawnExtComponent"));
	
}

void AParuRailCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

}


void AParuRailCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AParuRailCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	StarRailHeroComponent->SetupPlayerInputComponent(GetController()->InputComponent);
}



