#pragma once

#include "FGDamageInfo.generated.h"

class AActor;

USTRUCT(BlueprintType)
struct FFGDamageInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	float DamageAmount;
	UPROPERTY(BlueprintReadOnly)
	AActor* DamageInstigator;
	UPROPERTY(BlueprintReadOnly)
	FVector DamageDirection;
	UPROPERTY(BlueprintReadOnly)
	FVector DamageImpactLocation;
};