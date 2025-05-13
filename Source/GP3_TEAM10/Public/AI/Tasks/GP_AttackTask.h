// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GP_AttackTask.generated.h"

struct FAttackTaskMemory
{
	UBehaviorTreeComponent* OwnerComp = nullptr;
	uint8* NodeMemory = nullptr;
};

UCLASS()
class GP3_TEAM10_API UGP_AttackTask : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UGP_AttackTask();

	virtual uint16 GetInstanceMemorySize() const override
	{
		return sizeof(FAttackTaskMemory);
	}

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector TargetActorKey;

private:

	void OnAttackFinished();
};
