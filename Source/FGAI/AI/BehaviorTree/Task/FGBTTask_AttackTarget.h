#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "FGBTTask_AttackTarget.generated.h"

struct FBTAttackTargetTaskMemory
{
	
};

UCLASS()
class UFGBTTask_AttackTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UFGBTTask_AttackTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual uint16 GetInstanceMemorySize() const override;
	virtual FString GetStaticDescription() const override;

	AActor* GetAttackTargetActor(UBehaviorTreeComponent& OwnerComp) const;

	UPROPERTY(EditAnywhere, Category = Entry)
	FBlackboardKeySelector AttackTarget;
};
