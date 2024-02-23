// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlanetEntrance.generated.h"

UCLASS()
class APlanetEntrance : public AActor {
	GENERATED_BODY()
	
public:
	APlanetEntrance();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
