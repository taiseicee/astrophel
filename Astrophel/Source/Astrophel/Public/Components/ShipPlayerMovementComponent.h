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
	FVector GetDisplacementGlobal(const float& DeltaTime, const FVector& InputVelocity);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float ThrustMaxSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float ThrustAcceleration = 200.f;

	FVector ThustVelocity = FVector::ZeroVector;
};
