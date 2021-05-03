#pragma once

#include "Components/ActorComponent.h"
#include "FGHearingInfo.h"
#include "FGHearingSenseComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFGHearingSenseDelegate, const FFGHearingInfo&, HearingInfo);

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UFGHearingSenseComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFGHearingSenseComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void ReceiveNoise(AActor* NoiseInstigator, const FVector Location, const float Range) const;
	
	UPROPERTY(BlueprintAssignable)
	FFGHearingSenseDelegate OnNoiseHeard;

	UPROPERTY(EditDefaultsOnly)
	float HearingRange = 500.0f;

	UPROPERTY(EditAnywhere, Category = Debug)
	bool bDebugDrawHearingRange = true;
};