// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShipPlayerMovementComponent.h"

UShipPlayerMovementComponent::UShipPlayerMovementComponent() {
	PrimaryComponentTick.bCanEverTick = false;

}

void UShipPlayerMovementComponent::BeginPlay() {
	Super::BeginPlay();
	
}

FVector UShipPlayerMovementComponent::GetVelocityGlobal(const float& DeltaTime, const FVector& InputVelocityGlobal) {
	UE_LOG(LogTemp, Warning, TEXT("Translational Velocity: %s"), *InputVelocityGlobal.ToString());
	return InputVelocityGlobal;
}
