// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GP_AICharacter.generated.h"

class UBehaviorTree;
class UAnimMontage;
class UBoxComponent;
class UGP_HealthComponent;
class AGP_PatrolRoute;

DECLARE_MULTICAST_DELEGATE(FOnFinishedAttackSignature);
DECLARE_MULTICAST_DELEGATE(FOnFinishedAwakeSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQTEFinishedSignature, bool, bSuccess);

UENUM(BlueprintType)
enum class EAIAnimState : uint8
{
	None,
	Sleep,
	StandUp,
	Idle,
	Walk,
	Attack,
	Death
};

UCLASS()
class GP3_TEAM10_API AGP_AICharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AGP_AICharacter();

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

	FOnFinishedAttackSignature OnFinishedAttack;
	FOnFinishedAwakeSignature OnFinishedAwake;

	UPROPERTY(BlueprintAssignable)
	FOnQTEFinishedSignature OnQTEFinished;

	UFUNCTION(BlueprintCallable, Category = "AI|Behavior")
	void StartQTE();

	UFUNCTION(BlueprintCallable, Category = "AI|Behavior")
	void OnQTEButtonPressed();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|BehaviorTree")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Behavior")
	TObjectPtr<AGP_PatrolRoute> PatrolRoute;

	UPROPERTY(EditDefaultsOnly, Category = "AI|Behavior")
	EAIAnimState StartAnimState = EAIAnimState::Sleep;

	UFUNCTION(BlueprintCallable, Category = "AI|Behavior")
	bool IsAwakening() const { return bIsAwakening; };

	UFUNCTION(BlueprintCallable, Category = "AI|Behavior")
	void SetIsAwakening(bool IsAwakening) { bIsAwakening = IsAwakening; };

	UFUNCTION(BlueprintCallable, Category = "AI|Behavior")
	EAIAnimState GetCurrentAnimState() const { return CurrentAnimState; };

	UFUNCTION(BlueprintCallable, Category = "AI|Behavior")
	void SetCurrentAnimState(EAIAnimState NextAnimState);

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "AI|Attack")
	void Attack();

	void StopAttack();
	void FinishAwake();

private:

	FTimerHandle QTEFillTimerHandle;

	float QTEProgress = 0.0f;
	float QTEFillTime = 2.0f;
	float QTEDrainPerPress = 0.2f;
	float QTEThreshold = 1.0f;
	bool bQTEActive = false;

	void FailQTE();

	bool bIsDamageDone = false;

	FTimerHandle AttackTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "AI|Behavior")
	bool bIsAwakening = false;

	EAIAnimState CurrentAnimState = EAIAnimState::None;

	UFUNCTION()
	void OnOverlapHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleDeath();
};
