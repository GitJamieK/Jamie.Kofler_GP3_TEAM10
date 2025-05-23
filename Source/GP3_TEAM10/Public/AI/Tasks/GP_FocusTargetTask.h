// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GP_FocusTargetTask.generated.h"



UCLASS()
class GP3_TEAM10_API UGP_FocusTargetTask : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UGP_FocusTargetTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector TargetActorKey;
	
};
