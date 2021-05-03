#pragma once

#include "GameFramework/Actor.h"
#include "FGLevelLoadBox.generated.h"

class UBoxComponent;

UCLASS()
class AFGLevelLoadBox : public AActor
{
	GENERATED_BODY()

public:
	AFGLevelLoadBox();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> LevelToLoad;
};


