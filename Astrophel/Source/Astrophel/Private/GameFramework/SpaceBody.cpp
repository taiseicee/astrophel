// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/SpaceBody.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"

// Sets default values
ASpaceBody::ASpaceBody() {
	PrimaryActorTick.bCanEverTick = true;

	ColliderSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));

	RootComponent = ColliderSphere;
	Flipbook->SetupAttachment(RootComponent);
}

void ASpaceBody::BeginPlay() {
	Super::BeginPlay();
	
}

void ASpaceBody::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}
