// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GP_AICharacter.generated.h"

class UBehaviorTree;
class UAnimMontage;
class UBoxComponent;
class UGP_HealthComponent;

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

	UPROPERTY(EditDefaultsOnly, Category = "AI|Animations")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Components")
	UBoxComponent* RightHandCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Components")
	UBoxComponent* LeftHandCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI|Components")
	UGP_HealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Attack", meta = (ClampMin = "0", ClampMax = "1000.0"))
	float DamageAmount;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "AI|Attack")
	void Attack();

private:
	bool bIsDamageDone = false;

	FTimerHandle AttackTimerHandle;

	void StopAttack();

	UFUNCTION()
	void OnOverlapHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleDeath();
};
