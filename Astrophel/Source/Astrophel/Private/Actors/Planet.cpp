// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"

// Sets default values
APlanet::APlanet() {
	PrimaryActorTick.bCanEverTick = true;

	ColliderSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	TriggerPlanetEntrance = CreateDefaultSubobject<USphereComponent>(TEXT("Planet Entrance Trigger"));

	RootComponent = ColliderSphere;
	Flipbook->SetupAttachment(RootComponent);
	TriggerPlanetEntrance->SetupAttachment(RootComponent);

	TriggerPlanetEntrance->OnComponentBeginOverlap.AddDynamic(this, &APlanet::UpdatePlayerContext);
}

void APlanet::BeginPlay() {
	Super::BeginPlay();
	
}

void APlanet::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void APlanet::UpdatePlayerContext(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (!OtherActor || OtherActor == this) return;
	UE_LOG(LogTemp, Warning, TEXT("Actor Overlapped: %s"), *OtherActor->GetName());
}
