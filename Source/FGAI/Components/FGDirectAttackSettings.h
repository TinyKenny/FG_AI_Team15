#pragma once

#include "Engine/DataAsset.h"
#include "FGDirectAttackSettings.generated.h"

UCLASS()
class UFGDirectAttackSettings : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = Attacking, meta = (ClampMin = "0.0"))
	float Cooldown = 1.0f;

	UPROPERTY(EditAnywhere, Category = Attacking, meta = (ClampMin = "0.0"))
	float Range = 100.0f;

	UPROPERTY(EditAnywhere, Category = Attacking, meta = (ClampMin = "0.0"))
	float Damage = 10.0f;
};