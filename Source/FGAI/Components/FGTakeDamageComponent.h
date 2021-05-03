#pragma once

#include "Components/ActorComponent.h"
#include "FGAI/FGDamageInfo.h"
#include "FGTakeDamageComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UFGTakeDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void OnTakeDamage(FHitResult Hit, float Damage, AActor* DamageInstigator) const;
	void OnTakeDamage(const FFGDamageInfo& DamageInfo) const;
};