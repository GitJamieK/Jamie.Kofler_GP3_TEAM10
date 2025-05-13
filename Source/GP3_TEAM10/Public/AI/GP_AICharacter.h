// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GP_AICharacter.generated.h"

class UBehaviorTree;
class UAnimMontage;

DECLARE_MULTICAST_DELEGATE(FOnFinishedAttackSignature);

UCLASS()
class GP3_TEAM10_API AGP_AICharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AGP_AICharacter();

	FOnFinishedAttackSignature OnFinishedAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|BehaviorTree")
	TObjectPtr<UBehaviorTree> BehaviorTree;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "AI|Animations")
	UAnimMontage* AttackAnimMontage;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "AI|Attack")
	void Attack();

private:

	FTimerHandle AttackTimerHandle;

	void StopAttack();
};
