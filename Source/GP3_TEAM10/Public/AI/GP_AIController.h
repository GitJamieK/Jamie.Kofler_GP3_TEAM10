// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GP_AIController.generated.h"

class UGP_AIPerceptionComponent;

UCLASS()
class GP3_TEAM10_API AGP_AIController : public AAIController
{
	GENERATED_BODY()

public:

	AGP_AIController();

protected:

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UGP_AIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "TargetActor";

private:

	AActor* GetFocusOnActor() const;
};
