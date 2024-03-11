// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/ShipPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ShipPlayerMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

AShipPlayer::AShipPlayer() {
	PrimaryActorTick.bCanEverTick = true;

	ColliderCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	SpringArmCamera = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PhysicsHandleAttachment = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Attachment Physics Handle"));
	PointAttachment = CreateDefaultSubobject<USceneComponent>(TEXT("Attachment Point"));
	
	RootComponent = ColliderCapsule;
	Flipbook->SetupAttachment(RootComponent);
	SpringArmCamera->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArmCamera);
	PointAttachment->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UShipPlayerMovementComponent>(TEXT("Movement Component"));
	if (MovementComponent) {
		MovementComponent->UpdatedComponent = ColliderCapsule;
	}
}

void AShipPlayer::BeginPlay() {
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(MappingContextPlayer, 0);
		}
	}
}

void AShipPlayer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector Displacement = MovementComponent->GetDisplacementGlobal(DeltaTime, InputVelocity);
	FRotator Rotation = MovementComponent->GetRotation(DeltaTime, InputRotationalVelocity);

	FHitResult* OutTranslationalHitResult = new FHitResult();
	AddActorWorldOffset(Displacement, true, OutTranslationalHitResult, ETeleportType::ResetPhysics);
	
	FHitResult* OutRotationalHitResult = new FHitResult();
	AddActorLocalRotation(Rotation, true, OutRotationalHitResult, ETeleportType::ResetPhysics);

	MovementComponent->HandleDisplacementCollision(OutTranslationalHitResult);
	MovementComponent->HandleRotationCollision(OutRotationalHitResult);

	PhysicsHandleAttachment->SetTargetLocationAndRotation(
		PointAttachment->GetComponentLocation(),
		PointAttachment->GetComponentRotation()
	);
}

void AShipPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(ActionThrust, ETriggerEvent::Triggered, this, &AShipPlayer::HandleInputThrust);
		EnhancedInputComponent->BindAction(ActionRotationalThrust, ETriggerEvent::Triggered, this, &AShipPlayer::HandleInputRotationalThrust);
		EnhancedInputComponent->BindAction(ActionInteract, ETriggerEvent::Triggered, this, &AShipPlayer::HandleInteract);
	}
}

void AShipPlayer::HandleInputThrust(const FInputActionValue& Value) {
	const FVector2D Input = Value.Get<FVector2D>();
	InputVelocity = Input.X * GetActorForwardVector() +
					Input.Y * GetActorUpVector();
}

void AShipPlayer::HandleInputRotationalThrust(const FInputActionValue& Value) {
	const float Input = Value.Get<float>();
	InputRotationalVelocity.Pitch = Input;
}

void AShipPlayer::HandleInteract(const FInputActionValue& Value) {
	const bool Input = Value.Get<bool>();
	if (OnInteractDelegate.IsBound()) OnInteractDelegate.Execute();
}

void AShipPlayer::AttachItemToShip(UPrimitiveComponent* Item) {
	PhysicsHandleAttachment->GrabComponentAtLocationWithRotation(
		Item,
		NAME_None,
		Item->GetComponentLocation(),
		PointAttachment->GetComponentRotation()
	);
	UE_LOG(LogTemp, Warning, TEXT("Attaching to Ship"));
}

void AShipPlayer::DetachItemToShip(UPrimitiveComponent* Item) {
	PhysicsHandleAttachment->ReleaseComponent();
	UE_LOG(LogTemp, Warning, TEXT("Detaching to Ship"));
}