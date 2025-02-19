// Copyright Epic Games, Inc. All Rights Reserved.

#include "InspectPrjCharacter.h"
#include "InspectPrjProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Game/intInteractInterface.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AInspectPrjCharacter

AInspectPrjCharacter::AInspectPrjCharacter()
{
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void AInspectPrjCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector StartPoint = FirstPersonCameraComponent->GetComponentLocation();
	FVector EndPoint = StartPoint + (FirstPersonCameraComponent->GetForwardVector() * LookAtDistance);

	FHitResult Hit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(Hit, StartPoint, EndPoint, ECollisionChannel::ECC_Camera, QueryParams);

	if (Hit.bBlockingHit)
	{
		if (Hit.GetActor()->GetClass()->ImplementsInterface(UintInteractInterface::StaticClass()))
		{
			IintInteractInterface::Execute_DisplayInteractableActor(Hit.GetActor(), Hit.ImpactNormal);
		}
	}
}

void AInspectPrjCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

//////////////////////////////////////////////////////////////////////////// Input

void AInspectPrjCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInspectPrjCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AInspectPrjCharacter::Look);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AInspectPrjCharacter::Interact);

		EnhancedInputComponent->BindAction(CleanerAction, ETriggerEvent::Started, this, &AInspectPrjCharacter::PlaceCleaner);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AInspectPrjCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AInspectPrjCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AInspectPrjCharacter::Interact(const FInputActionValue& Value)
{
	bool isInteracting = Value.Get<bool>();

	FVector StartPoint = FirstPersonCameraComponent->GetComponentLocation();
	FVector EndPoint = StartPoint + (FirstPersonCameraComponent->GetForwardVector() * LookAtDistance);

	FHitResult Hit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(Hit, StartPoint, EndPoint, ECollisionChannel::ECC_Camera, QueryParams);

	if (Hit.bBlockingHit)
	{
		if(Hit.GetActor()->GetClass()->ImplementsInterface(UintInteractInterface::StaticClass()))
		{
			IintInteractInterface::Execute_StartInteraction(Hit.GetActor());
		}
	}

}

void AInspectPrjCharacter::PlaceCleaner(const FInputActionValue& Value)
{

	bool isInteracting = Value.Get<bool>();

	FVector StartPoint = FirstPersonCameraComponent->GetComponentLocation();
	FVector EndPoint = StartPoint + (FirstPersonCameraComponent->GetForwardVector() * LookAtDistance);

	FHitResult Hit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(Hit, StartPoint, EndPoint, ECollisionChannel::ECC_Camera, QueryParams);

	if (Hit.bBlockingHit)
	{
		if (Hit.GetActor()->GetClass()->ImplementsInterface(UintInteractInterface::StaticClass()))
		{
			IintInteractInterface::Execute_StartPlaceCleaner(Hit.GetActor());
		}
	}

}