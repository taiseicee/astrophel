// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShipPlayerMovementComponent.generated.h"

class UPrimitiveComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTROPHEL_API UShipPlayerMovementComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UShipPlayerMovementComponent();
	UPrimitiveComponent* UpdatedComponent;
	FVector GetVelocityGlobal(const float& DeltaTime, const FVector& InputVelocityGlobal);

protected:
	virtual void BeginPlay() override;

private:
	FVector VelocityGlobal = FVector::ZeroVector;

};
