// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GP_GameModeBase.generated.h"

UENUM(BlueprintType)
enum class EGameplayState : uint8
{
	InitState,
	PlayState,
	DeathState
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameplayStateChangedSignature, EGameplayState, PreviosGameplayState, EGameplayState, NextGameplayState);

UCLASS()
class GP3_TEAM10_API AGP_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "GameplayState")
	FOnGameplayStateChangedSignature OnGameplayStateChanged;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EGameplayState GetGameplayState() const { return GameplayState; }

	UFUNCTION(BlueprintCallable)
	void HandleDeathState();

	virtual void StartPlay() override;

private:

	UPROPERTY()
	EGameplayState GameplayState = EGameplayState::InitState;

	UFUNCTION(BlueprintCallable)
	void SetGameplayState(EGameplayState State);
};
