// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"

#include "ShipPlayer.generated.h"

class UCapsuleComponent;
class UPaperFlipbookComponent;
class USpringArmComponent;
class UCameraComponent;
class USceneComponent;
class UShipPlayerMovementComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class AShipPlayer : public APawn {
	GENERATED_BODY()

public:
	AShipPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* ColliderCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Visual", meta=(AllowPrivateAccess="true"))
	UPaperFlipbookComponent* Flipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Camera", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* SpringArmCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Camera", meta=(AllowPrivateAccess="true"))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Combat", meta=(AllowPrivateAccess="true"))
	USceneComponent* SpawnPointProjectile;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	UShipPlayerMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement|Input", meta=(AllowPrivateAccess="true"))
	UInputMappingContext* MappingContextPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement|Input", meta=(AllowPrivateAccess="true"))
	UInputAction* ActionThrust;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement|Input", meta=(AllowPrivateAccess="true"))
	UInputAction* ActionRotationalThrust;

	void HandleInputThrust(const FInputActionValue& Value);
	void HandleInputRotationalThrust(const FInputActionValue& Value);

	FVector InputVelocity = FVector::ZeroVector;
	FRotator InputRotationalVelocity = FRotator::ZeroRotator;

};
