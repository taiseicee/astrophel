// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceBody.generated.h"

class USphereComponent;
class UPaperFlipbookComponent;

UCLASS()
class ASpaceBody : public AActor {
	GENERATED_BODY()
	
public:
	ASpaceBody();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	USphereComponent* ColliderSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UPaperFlipbookComponent* Flipbook;

};
