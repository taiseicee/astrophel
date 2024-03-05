// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Planet.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"

APlanet::APlanet() {
    PrimaryActorTick.bCanEverTick = true;

    RevealInteriorArea = CreateDefaultSubobject<USphereComponent>(TEXT("Planet Entrance Trigger"));
    FlipbookBackground = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite Background"));

    RevealInteriorArea->SetupAttachment(RootComponent);
    FlipbookBackground->SetupAttachment(RootComponent);
}

void APlanet::BeginPlay() {
	Super::BeginPlay();
	
    RevealInteriorArea->OnComponentBeginOverlap.AddDynamic(this, &APlanet::RevealInterior);
    RevealInteriorArea->OnComponentEndOverlap.AddDynamic(this, &APlanet::HideInterior);

    UMaterialInterface* CurrentPlanetMaterial = Flipbook->GetMaterial(0);
    if (!CurrentPlanetMaterial) return;
    PlanetMaterial = UMaterialInstanceDynamic::Create(CurrentPlanetMaterial, this);
}

void APlanet::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

    HandleRevealInterior(DeltaTime);
}

void APlanet::RevealInterior(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    if (!OtherActor || OtherActor == this) return;
    UE_LOG(LogTemp, Warning, TEXT("Revealing Interior"));
    ShouldHideInterior = false;

}

void APlanet::HideInterior(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
    if (!OtherActor || OtherActor == this) return;
    UE_LOG(LogTemp, Warning, TEXT("Hiding Interior"));
    // ShouldHideInterior = true;
}

void APlanet::HandleRevealInterior(float DeltaTime) {

    float BackgroundAlpha = Flipbook->GetSpriteColor().A;
    if (!ShouldHideInterior) {
        //FLinearColor
        FLinearColor UpdatedColor = FLinearColor::White;
        UpdatedColor.A = FMath::FInterpTo(BackgroundAlpha, 0.f, DeltaTime, RevealRate);
        Flipbook->SetSpriteColor(UpdatedColor);
        return;
    }
}
