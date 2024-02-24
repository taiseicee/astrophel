// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"

// Sets default values
APlanet::APlanet() {
	PrimaryActorTick.bCanEverTick = true;

	ColliderSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));

	RootComponent = ColliderSphere;
	Flipbook->SetupAttachment(RootComponent);
}

void APlanet::BeginPlay() {
	Super::BeginPlay();
	
}

void APlanet::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}
