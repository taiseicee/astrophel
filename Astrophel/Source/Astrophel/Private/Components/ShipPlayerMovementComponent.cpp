// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShipPlayerMovementComponent.h"

UShipPlayerMovementComponent::UShipPlayerMovementComponent() {
	PrimaryComponentTick.bCanEverTick = true;

}

void UShipPlayerMovementComponent::BeginPlay() {
	Super::BeginPlay();
	
}

void UShipPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

