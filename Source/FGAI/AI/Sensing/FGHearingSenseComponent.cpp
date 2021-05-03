#include "FGHearingSenseComponent.h"
#include "FGAI/FGGameInstance.h"
#include "Kismet/GameplayStatics.h"


UFGHearingSenseComponent::UFGHearingSenseComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UFGHearingSenseComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	if (bDebugDrawHearingRange)
	{
		UKismetSystemLibrary::DrawDebugSphere(this, GetOwner()->GetActorLocation(), HearingRange, 12, FLinearColor::Red);
	}
}

void UFGHearingSenseComponent::BeginPlay()
{
	Super::BeginPlay();

	UFGGameInstance* GameInstance = Cast<UFGGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance != nullptr)
	{
		GameInstance->HearingComponents.Add(this);
	}
}

void UFGHearingSenseComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UFGGameInstance* GameInstance = Cast<UFGGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance != nullptr)
	{
		GameInstance->HearingComponents.Remove(this);
	}

	Super::EndPlay(EndPlayReason);
}

void UFGHearingSenseComponent::ReceiveNoise(AActor* NoiseInstigator, const FVector NoiseLocation, const float NoiseRange) const
{
	const float DistanceToNoiseSq = FVector::DistSquared(NoiseLocation, GetOwner()->GetActorLocation());
	const float HearableDistanceSq = FMath::Square(HearingRange + NoiseRange);
	if (DistanceToNoiseSq < HearableDistanceSq)
	{
		FFGHearingInfo HearingInfo;
		HearingInfo.NoiseInstigator = NoiseInstigator;
		HearingInfo.NoiseLocation = NoiseLocation;
		OnNoiseHeard.Broadcast(HearingInfo);
	}
}


