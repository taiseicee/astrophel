// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ShipPlayerMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"

AShipPlayer::AShipPlayer() {
	PrimaryActorTick.bCanEverTick = true;

	ColliderCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	SpringArmCamera = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpawnPointProjectile = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	
	RootComponent = ColliderCapsule;
	Flipbook->SetupAttachment(RootComponent);
	SpringArmCamera->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArmCamera);
	SpawnPointProjectile->SetupAttachment(Flipbook);

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

	// if (OutSweepHitResult->bBlockingHit) Velocity = FVector::ZeroVector;
}

void AShipPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(ActionThrust, ETriggerEvent::Triggered, this, &AShipPlayer::HandleInputThrust);
		EnhancedInputComponent->BindAction(ActionRotationalThrust, ETriggerEvent::Triggered, this, &AShipPlayer::HandleInputRotationalThrust);
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

	UE_LOG(LogTemp, Warning, TEXT("Rotational Thrust: %f"), Input);
}
