// Fill out your copyright notice in the Description page of Project Settings.


#include "FpsCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "InputBindingComponentInterface.h"
//#include "InteractableInterface.h"
//#include "InteractableBase.h"
//#include "Components/SlateWrapperTypes.h"

// Sets default values
AFpsCharacter::AFpsCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	//InteractionReach = 100.f;

	SpaceshipPawn = nullptr;

	// Hud
	//InteractionTextboxVisibilityHud = ESlateVisibility::Hidden;
	//InteractionTextboxTextHud = "";

	//CurrentInteractable = nullptr;
}

// Called when the game starts or when spawned
void AFpsCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Oh my loRD!"))
}

// Called every frame
void AFpsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//CheckForInteractable();
}

// Called to bind functionality to input
void AFpsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind actions
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFpsCharacter::SwapPawn);
	//PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFpsCharacter::InteractWithInteractable);

	// Bind axis
	PlayerInputComponent->BindAxis("MoveForward", this, &AFpsCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFpsCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	UE_LOG(LogTemp, Log, TEXT("SetupInputFpsCharacter"))
	TArray<UActorComponent*> Comps = GetComponentsByInterface(UInputBindingComponentInterface::StaticClass());
	for (int i = 0; i < Comps.Num(); i++)
	{
		UE_LOG(LogTemp, Log, TEXT("Comps..."))
		//UObject* comp = Comps[i];
		IInputBindingComponentInterface::Execute_SetupInputBindings(Comps[i], PlayerInputComponent);
		//Comps[i]->SetupInputBindings(NewController);
	}
}

void AFpsCharacter::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void AFpsCharacter::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void AFpsCharacter::SwapPawn()
{
	if (SpaceshipPawn != nullptr)
	{
		GetController()->Possess(SpaceshipPawn);
	}
}

void AFpsCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AFpsCharacter::UnPossessed()
{
	Super::UnPossessed();
	UE_LOG(LogTemp, Log, TEXT("UnPossessed FpsCharacter"))
}
