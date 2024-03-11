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
	FRotator GetRotation(const float& DeltaTime, const FRotator& InputRotationalVelocity);
	void HandleDisplacementCollision(const FHitResult* HitResult);
	void HandleRotationCollision(const FHitResult* HitResult);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float ThrustMaxSpeed = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float ThrustAcceleration = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float RotationalMaxSpeed = 70.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float RotationalAcceleration = 15.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float ReflectionMultiplier = 1.5f;

	FVector ThustVelocity = FVector::ZeroVector;
	FRotator RotationalVelocity = FRotator::ZeroRotator;
};
