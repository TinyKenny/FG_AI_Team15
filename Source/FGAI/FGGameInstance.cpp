#include "FGGameInstance.h"
#include "FGAI/AI/Sensing/FGHearingSenseComponent.h"
#include "Kismet/GameplayStatics.h"

void UFGGameInstance::MakeNoise(const UObject* WorldContextObject, AActor* NoiseInstigator, FVector NoiseLocation, float NoiseRange)
{
	UFGGameInstance* GameInstance = Cast<UFGGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	UKismetSystemLibrary::DrawDebugSphere(WorldContextObject, NoiseLocation, NoiseRange, 12, FLinearColor::Green, 1.5f);
	for (UFGHearingSenseComponent* HearingComponent : GameInstance->HearingComponents)
	{
		HearingComponent->ReceiveNoise(NoiseInstigator, NoiseLocation, NoiseRange);
	}
}