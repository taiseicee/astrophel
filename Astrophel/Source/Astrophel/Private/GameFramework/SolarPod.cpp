// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/SolarPod.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/ShipPlayer.h"

ASolarPod::ASolarPod() {
	PrimaryActorTick.bCanEverTick = true;

	ColliderSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	ReachArea = CreateDefaultSubobject<USphereComponent>(TEXT("Reach Trigger"));

	RootComponent = ColliderSphere;
	Flipbook->SetupAttachment(RootComponent);
    ReachArea->SetupAttachment(RootComponent);
}

void ASolarPod::BeginPlay() {
	Super::BeginPlay();
	
	ReachArea->OnComponentBeginOverlap.AddDynamic(this, &ASolarPod::HandleWithinReach);
    ReachArea->OnComponentEndOverlap.AddDynamic(this, &ASolarPod::HandleExitReach);
}

void ASolarPod::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ASolarPod::HandleWithinReach(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (!OtherActor || OtherActor == this) return;

	Player = Cast<AShipPlayer>(OtherActor);
	if (!Player) return;

	UE_LOG(LogTemp, Warning, TEXT("Within Attach Reach"));
	Player->OnInteractDelegate.BindDynamic(this, &ASolarPod::AttachToShipPlayer);
}

void ASolarPod::HandleExitReach(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (!OtherActor || OtherActor == this) return;
	if (!Player) return;
	if (IsAttached) return;

	Player->OnInteractDelegate.Unbind();
    UE_LOG(LogTemp, Warning, TEXT("Exit Attach Reach"));
}

void ASolarPod::AttachToShipPlayer() {
	IsAttached = true;
	Player->AttachItemToShip(Cast<UPrimitiveComponent>(this));
	Player->OnInteractDelegate.Unbind();
	Player->OnInteractDelegate.BindDynamic(this, &ASolarPod::DetachFromShipPlayer);
}

void ASolarPod::DetachFromShipPlayer() {
	if (!IsAttached) return;
	Player->DetachItemToShip(Cast<UPrimitiveComponent>(this));
	Player->OnInteractDelegate.Unbind();
	IsAttached = false;
}
