#pragma once

#include "Engine/GameInstance.h"
#include "FGGameInstance.generated.h"

class UFGHearingSenseComponent;

UCLASS()
class UFGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", DisplayName="FG Make Noise"))
	static void MakeNoise(const UObject* WorldContextObject, AActor* NoiseInstigator, FVector NoiseLocation, float NoiseRange);

	TArray<UFGHearingSenseComponent*> HearingComponents;
};

