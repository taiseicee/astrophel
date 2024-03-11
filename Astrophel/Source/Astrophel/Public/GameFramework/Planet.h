// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/SpaceBody.h"
#include "Planet.generated.h"

class USphereComponent;
class UPaperFlipbookComponent;
class UMaterialInstanceDynamic;

UCLASS()
class APlanet : public ASpaceBody {
    GENERATED_BODY()

public:
	APlanet();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UPaperFlipbookComponent* FlipbookBackground;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	USphereComponent* RevealInteriorArea;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
    float RevealRate = 0.5f;

    UFUNCTION()
    void RevealInterior(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void HideInterior(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    bool ShouldHideInterior = true;
    UMaterialInstanceDynamic* PlanetMaterial;

    void HandleRevealInterior(float DeltaTime);

};