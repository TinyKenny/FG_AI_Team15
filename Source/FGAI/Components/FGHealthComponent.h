#pragma once

#include "Components/ActorComponent.h"
#include "FGHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFGReachZeroHealthDelegate);

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UFGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void ChangeHitpointsByAmount(float ChangeAmount);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HealthPoints = 100.0f;

	UPROPERTY(BlueprintAssignable)
	FFGReachZeroHealthDelegate OnReachZeroHealth;
};
