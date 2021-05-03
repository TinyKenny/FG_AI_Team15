#pragma once

#include "FGHearingInfo.generated.h"

class AActor;

USTRUCT(BlueprintType)
struct FFGHearingInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	AActor* NoiseInstigator;
	
	UPROPERTY(BlueprintReadOnly)
	FVector NoiseLocation;
};