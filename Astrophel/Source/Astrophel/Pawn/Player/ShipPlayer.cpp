// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipPlayer.h"

AShipPlayer::AShipPlayer() {
	PrimaryActorTick.bCanEverTick = true;

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

