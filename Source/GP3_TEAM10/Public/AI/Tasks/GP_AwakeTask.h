// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GP_AwakeTask.generated.h"

struct FAwakeTaskMemory
{
	UBehaviorTreeComponent* OwnerComp = nullptr;
	uint8* NodeMemory = nullptr;
};

UCLASS()
class GP3_TEAM10_API UGP_AwakeTask : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UGP_AwakeTask();

	virtual uint16 GetInstanceMemorySize() const override
	{
		return sizeof(FAwakeTaskMemory);
	}

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
