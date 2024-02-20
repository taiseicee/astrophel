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

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	SpringArmCamera = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Spring Arm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	
	RootComponent = CapsuleCollider;
	Flipbook->SetupAttachment(RootComponent);
	SpringArmCamera->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArmCamera);
	ProjectileSpawnPoint->SetupAttachment(Flipbook);

	MovementComponent = CreateDefaultSubobject<UShipPlayerMovementComponent>(TEXT("Movement Component"));
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

	UE_LOG(LogTemp, Warning, TEXT("Translational Thrust: %s"), *Input.ToString());
}

void AShipPlayer::HandleInputRotationalThrust(const FInputActionValue& Value) {
	const float Input = Value.Get<float>();

	UE_LOG(LogTemp, Warning, TEXT("Rotational Thrust: %f"), Input);
}
