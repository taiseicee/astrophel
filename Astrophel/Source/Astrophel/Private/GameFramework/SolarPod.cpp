// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/SolarPod.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"

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
    UE_LOG(LogTemp, Warning, TEXT("Handle Within Reach"));
}

void ASolarPod::HandleExitReach(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (!OtherActor || OtherActor == this) return;
    UE_LOG(LogTemp, Warning, TEXT("Handle Exit Reach"));
}
