#include "FGLevelLoadBox.h"
#include "FGCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AFGLevelLoadBox::AFGLevelLoadBox() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = BoxComp;
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AFGLevelLoadBox::HandleBeginOverlap);
}

void AFGLevelLoadBox::Tick(float DeltaSeconds)
{
	UKismetSystemLibrary::DrawDebugBox(this, GetActorLocation(), BoxComp->GetScaledBoxExtent(), FLinearColor::Blue, GetActorRotation());
}

void AFGLevelLoadBox::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!LevelToLoad.IsNull())
	{
		//UE_LOG(LogTemp, Log, TEXT("Level to load is not null"))
		AFGCharacter* Character = Cast<AFGCharacter>(OtherActor);
		if (Character != nullptr)
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelToLoad);
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Level to load is null"))
	}
}



