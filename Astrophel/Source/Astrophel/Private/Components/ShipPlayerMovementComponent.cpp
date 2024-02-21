// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShipPlayerMovementComponent.h"

UShipPlayerMovementComponent::UShipPlayerMovementComponent() {
	PrimaryComponentTick.bCanEverTick = false;

}

void UShipPlayerMovementComponent::BeginPlay() {
	Super::BeginPlay();
	
}

FVector UShipPlayerMovementComponent::GetDisplacementGlobal(const float& DeltaTime, const FVector& InputVelocity) {
	FVector DesiredVelocity = InputVelocity * ThrustMaxSpeed + ThustVelocity;
	DesiredVelocity = DesiredVelocity.GetClampedToMaxSize(ThrustMaxSpeed);
	float SpeedChange = DeltaTime * ThrustAcceleration;

	ThustVelocity.X = FMath::FInterpTo(ThustVelocity.X, DesiredVelocity.X, DeltaTime, SpeedChange);
	ThustVelocity.Z = FMath::FInterpTo(ThustVelocity.Z, DesiredVelocity.Z, DeltaTime, SpeedChange);

	FVector Displacement = DeltaTime * ThustVelocity;

	return Displacement;
}

FRotator UShipPlayerMovementComponent::GetRotation(const float& DeltaTime, const FRotator& InputRotationalVelocity) {
	FRotator DesiredRotationalVelocity = InputRotationalVelocity * RotationalMaxSpeed + RotationalVelocity;
	DesiredRotationalVelocity.Pitch = FMath::Clamp(DesiredRotationalVelocity.Pitch, -RotationalMaxSpeed, RotationalMaxSpeed);
	float SpeedChange = DeltaTime * RotationalAcceleration;

	RotationalVelocity.Pitch = FMath::FInterpTo(RotationalVelocity.Pitch, DesiredRotationalVelocity.Pitch, DeltaTime, SpeedChange);

	FRotator Rotation = DeltaTime * RotationalVelocity;

	return Rotation;
}
