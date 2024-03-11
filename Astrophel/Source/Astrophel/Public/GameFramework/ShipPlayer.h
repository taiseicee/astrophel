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
class USpringArmComponent;
class UPhysicsHandleComponent;
class USceneComponent;

DECLARE_DYNAMIC_DELEGATE(FOnInteractSignature);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Movement", meta=(AllowPrivateAccess="true"))
	UShipPlayerMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Interact", meta=(AllowPrivateAccess="true"))
	UPhysicsHandleComponent* PhysicsHandleAttachment;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Interact", meta=(AllowPrivateAccess="true"))
	USceneComponent* PointAttachment;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Movement", meta=(AllowPrivateAccess="true"))
	UInputMappingContext* MappingContextPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Movement", meta=(AllowPrivateAccess="true"))
	UInputAction* ActionThrust;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|Movement", meta=(AllowPrivateAccess="true"))
	UInputAction* ActionRotationalThrust;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* ActionInteract;

	void HandleInputThrust(const FInputActionValue& Value);
	void HandleInputRotationalThrust(const FInputActionValue& Value);
	void HandleInteract(const FInputActionValue& Value);

	FVector InputVelocity = FVector::ZeroVector;
	FRotator InputRotationalVelocity = FRotator::ZeroRotator;

public:
	FOnInteractSignature OnInteractDelegate;

	void AttachItemToShip(UPrimitiveComponent* Item);
	void DetachItemToShip(UPrimitiveComponent* Item);

};
