// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/ShipPlayerMovementComponent.h"

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
}

void AShipPlayer::BeginPlay() {
	Super::BeginPlay();
	
}

void AShipPlayer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AShipPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

