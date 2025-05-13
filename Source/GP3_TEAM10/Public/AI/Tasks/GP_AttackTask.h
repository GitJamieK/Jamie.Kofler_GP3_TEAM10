// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GP_AttackTask.generated.h"



UCLASS()
class GP3_TEAM10_API UGP_AttackTask : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UGP_AttackTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
