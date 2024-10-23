// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NextDuckUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEXTDUCK_API UNextDuckUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitializeNextDuckUserWidgetVariables();
	UFUNCTION(BlueprintCallable)
	void ClickDuck();
	UFUNCTION(BlueprintCallable)
	void GetDuck();
	UFUNCTION(BlueprintCallable)
	void LoadNextDuck();
	UFUNCTION(BlueprintCallable)
	void RefreshDuckPercentText();
	UFUNCTION(BlueprintCallable)
	void ResetDuckPercent();
	UFUNCTION(BlueprintCallable)
	void IncreaseBread();
	UFUNCTION(BlueprintCallable)
	void ResetBreadTimer();
	UFUNCTION(BlueprintCallable)
	bool CheckHasSufficientBread();
	UFUNCTION(BlueprintCallable)
	void RefreshBreadText();
	UFUNCTION(BlueprintCallable)
	void RefreshBreadIncreaseText();
	UFUNCTION(BlueprintCallable)
	void ResetEggTimer();
	UFUNCTION(BlueprintCallable)
	bool IsEggTime();
	UFUNCTION(BlueprintCallable)
	FVector2D RandomizeEggPosition();
	UFUNCTION(BlueprintCallable)
	void SpawnEgg(FVector2D spawnPosition);
	UFUNCTION(BlueprintCallable)
	void ClickEgg();

protected:
	UPROPERTY(BlueprintReadOnly)
	bool canGetDuck;
	UPROPERTY(BlueprintReadOnly)
	bool canLoadNextDuck;
	UPROPERTY(BlueprintReadOnly)
	bool gotDuck;
	UPROPERTY(BlueprintReadOnly)
	bool breadTimerReset;
	UPROPERTY(BlueprintReadOnly)
	bool eggTimerReset;
	UPROPERTY(BlueprintReadOnly)
	bool isEggEnabled;

	UPROPERTY(BlueprintReadOnly)
	int numDucks;
	UPROPERTY(BlueprintReadOnly)
	int bread;
	UPROPERTY(BlueprintReadOnly)
	int breadPerTick;
	UPROPERTY(BlueprintReadOnly)
	int breadCost;
	UPROPERTY(BlueprintReadOnly)
	int breadInflation;
	UPROPERTY(BlueprintReadOnly)
	int clickBreadCost = 1;
	UPROPERTY(BlueprintReadOnly)
	int eggChance; // chance of egg appearing after eggTimer resets, higher = less likely

	UPROPERTY(BlueprintReadOnly)
	float duckPercent;
	UPROPERTY(BlueprintReadOnly)
	float duckDifficultyMult; // lower = harder
	UPROPERTY(BlueprintReadOnly)
	float duckDifficultyIncrease;
	UPROPERTY(BlueprintReadOnly)
	float duckProgressBase;
	UPROPERTY(BlueprintReadOnly)
	float breadTimerInterval;
	UPROPERTY(BlueprintReadOnly)
	float breadTime;
	//UPROPERTY(BlueprintReadOnly)
	//float eggTimerInterval;

	UPROPERTY(BlueprintReadOnly)
	FString duckPercentText;
	UPROPERTY(BlueprintReadOnly)
	FString numDucksText;
	UPROPERTY(BlueprintReadOnly)
	FString nextDuckButtonText;
	UPROPERTY(BlueprintReadOnly)
	FString breadText;
	UPROPERTY(BlueprintReadOnly)
	FString breadIncreaseText;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle breadTimerHandle;
	UPROPERTY(BlueprintReadOnly)
	FTimerHandle eggTimerHandle;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* QuackAnimation;
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* DuckDisappearAnimation;
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* DuckAppearAnimation;
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* DuckPercentIncreaseAnimation1;
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* DuckPercentIncreaseAnimation2;
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* BreadIncreaseAnimation;
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* InsufficientBreadAnimation;
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* GetDuckAnimation1;
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* GetDuckAnimation2;
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* GetDuckAnimation3;
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* EggButtonAppearAnimation;
	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* EggButtonDisappearAnimation;

	UPROPERTY(BlueprintReadOnly, Transient, meta = (BindWidget))
	UWidget* eggButton;

	UPROPERTY(EditAnywhere)
	USoundBase* quackSound;
};
