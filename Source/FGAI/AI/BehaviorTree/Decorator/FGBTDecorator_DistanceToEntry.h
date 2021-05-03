#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "FGBTDecorator_DistanceToEntry.generated.h"

class UBehaviorTree;
class UBlackboardComponent;
class APawn;

UENUM(BlueprintType)
enum class EFGBTDistanceComparisonEntry : uint8
{
	Greater,
	Lower
};

UENUM(BlueprintType)
enum class EFGBTEntryType : uint8
{
	Value,
	BBEntry,
	Self
};

/*
	Compare the distance (squared) between two entires.
*/

UCLASS(HideCategories = (Condition))
class UFGBTDecorator_DistanceToEntry : public UBTDecorator
{
	GENERATED_BODY()
public:
	struct FFGBTDecoratorMemory
	{
		
	};

	UFGBTDecorator_DistanceToEntry(const FObjectInitializer& ObjectInitializer);

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual FString GetStaticDescription() const override;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual uint16 GetInstanceMemorySize() const override;

	float GetDistance(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

	// Get location from selected entry. bSuccess will be set to false if entry is Blackboard and Object, but currently nullptr.
	FVector GetFrom(const UBehaviorTreeComponent& OwnerComp, bool& bSuccess) const;
	// Get location from selected entry. bSuccess will be set to false if entry is Blackboard and Object, but currently nullptr.
	FVector GetTo(const UBehaviorTreeComponent& OwnerComp, bool& bSuccess) const;

	const APawn* GetPawnFromBehaviorTree(const UBehaviorTreeComponent& OwnerComp) const;

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = Entry)
	EFGBTDistanceComparisonEntry ComparisonType = EFGBTDistanceComparisonEntry::Greater;

	UPROPERTY(EditAnywhere, Category = Entry)
	EFGBTEntryType DistanceEntryType = EFGBTEntryType::Value;

	UPROPERTY(EditAnywhere, Category = Entry, meta = (EditCondition = "DistanceEntryType == EFGBTEntryType::Value", EditConditionHides, DisplayName = "Distance"))
	float DistanceValue = 200.0f;
	UPROPERTY(EditAnywhere, Category = Entry, meta = (EditCondition = "DistanceEntryType == EFGBTEntryType::BBEntry", EditConditionHides, DisplayName = "Distance"))
	FBlackboardKeySelector DistanceBlackboard;


	UPROPERTY(EditAnywhere, Category = Entry)
	EFGBTEntryType FromEntryType = EFGBTEntryType::Self;

	UPROPERTY(EditAnywhere, Category = Entry, meta = (EditCondition = "FromEntryType == EFGBTEntryType::BBEntry", EditConditionHides, DisplayName = "From"))
	FBlackboardKeySelector FromBlackboard;

	UPROPERTY(EditAnywhere, Category = Entry)
	EFGBTEntryType ToEntryType = EFGBTEntryType::BBEntry;

	UPROPERTY(EditAnywhere, Category = Entry, meta = (EditCondition = "ToEntryType == EFGBTEntryType::BBEntry", EditConditionHides, DisplayName = "To"))
	FBlackboardKeySelector ToBlackboard;

	// Select to use DistSquared2D instead of DistSquared.
	UPROPERTY(EditAnywhere, Category = Entry)
	bool bDistSquared2D = true;

};
