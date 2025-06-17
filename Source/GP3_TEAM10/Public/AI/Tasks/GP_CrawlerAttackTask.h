// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GP_CrawlerAttackTask.generated.h"

class UBehaviorTreeComponent;

struct FCrawlerAttackTaskMemory
{
    UBehaviorTreeComponent* OwnerComp = nullptr;
    uint8* NodeMemory = nullptr;
};

UCLASS()
class GP3_TEAM10_API UGP_CrawlerAttackTask : public UBTTaskNode
{
	GENERATED_BODY()

public:

    UGP_CrawlerAttackTask();

    virtual uint16 GetInstanceMemorySize() const override
    {
        return sizeof(FCrawlerAttackTaskMemory);
    }

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector TargetActorKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector IsAttackingKey;

    /*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float PushingForce = 5000.f;*/

    UFUNCTION()
    void OnQTEComplete(bool bSuccess);

    virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

private:

    UBehaviorTreeComponent* CapturedComponent = nullptr;
    //FCrawlerAttackTaskMemory* CachedTaskMemory;

    bool bQTECompleted = false;
    bool bQTEStarted = false;
	
};
