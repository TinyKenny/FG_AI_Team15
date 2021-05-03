#pragma once

#include "Components/ActorComponent.h"
#include "FGDirectAttackComponent.generated.h"

class UFGDirectAttackSettings;

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UFGDirectAttackComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFGDirectAttackComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	bool PerformAttackOnTarget(AActor* AttackTarget);

	UPROPERTY(EditAnywhere, Category = Attacking)
	UFGDirectAttackSettings* AttackSettings = nullptr;

	float CurrentAttackCooldown = 0.0f;
};