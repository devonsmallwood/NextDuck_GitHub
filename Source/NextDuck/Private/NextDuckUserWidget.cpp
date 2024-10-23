// Fill out your copyright notice in the Description page of Project Settings.


#include "NextDuckUserWidget.h"
#include "Components/Widget.h"
#include "Components/CanvasPanelSlot.h"

void UNextDuckUserWidget::InitializeNextDuckUserWidgetVariables()
{
	canGetDuck = false;
	canLoadNextDuck = false;
	gotDuck = false;
	breadTimerReset = true;
	eggTimerReset = true;
	numDucks = 0;
	bread = 190;
	breadPerTick = 10;
	breadCost = 10;
	breadInflation = 2;
	clickBreadCost = 1;
	eggChance = 1;
	duckPercent = 0.0F;
	duckDifficultyMult = 1.0F;
	duckDifficultyIncrease = 2.0F;
	duckProgressBase = 0.1F;
	breadTimerInterval = 5.0F;
	duckPercentText = "0%";
	numDucksText = "Ducks: 0";
	nextDuckButtonText = "Next Duck\n10 Bread";
	breadText = "Bread: 190";
	breadIncreaseText = "+10";
}

void UNextDuckUserWidget::ClickDuck()
{
	UE_LOG(LogTemp, Log, TEXT("Bread Timer Interval: %f"), breadTimerInterval);
	UE_LOG(LogTemp, Log, TEXT("Bread Time: %f"), breadTime);
	UE_LOG(LogTemp, Log, TEXT("Bread Time Reset: %s"), (breadTimerReset ? TEXT("true") : TEXT("false")));
	if (!gotDuck)
	{
		if (duckPercent < 1.0F)
		{
			if (bread - clickBreadCost >= 0)
			{
				bread -= clickBreadCost;
				RefreshBreadText();
				duckPercent += duckProgressBase * duckDifficultyMult;
				if (duckPercent > 1.0F) duckPercent = 1.0F; // Prevents float rounding errors from causing duckPercent to exceed 1.0F (100%)
				RefreshDuckPercentText();

				int randomAnimIndex = FMath::RandRange(0, 1);

				switch (randomAnimIndex)
				{
					case 0:
						PlayAnimation(DuckPercentIncreaseAnimation1, 0.0F, 1, EUMGSequencePlayMode::Forward, 1.0F, false);
						break;
					case 1:
						PlayAnimation(DuckPercentIncreaseAnimation2, 0.0F, 1, EUMGSequencePlayMode::Forward, 1.0F, false);
						break;
				}

				if (QuackAnimation && !IsAnimationPlaying(QuackAnimation))
				{
					PlayAnimation(QuackAnimation, 0.0F, 1, EUMGSequencePlayMode::Forward, 3.0F, false);
					//Probably should use an AudioComponent and play with SetPitchMultiplier()
					PlaySound(quackSound);
				}
			}
			else
			{
				PlayAnimation(InsufficientBreadAnimation, 0.0F, 1, EUMGSequencePlayMode::Forward, 1.0F, false);
			}
		}
		
		if ((int)truncf(duckPercent * 100.0F) != 100)
		{
			canGetDuck = false;
		}
		else
		{
			canGetDuck = true;
		}
	}
}

void UNextDuckUserWidget::GetDuck()
{
	if (DuckDisappearAnimation && !IsAnimationPlaying(DuckDisappearAnimation))
	{
		PlayAnimation(DuckDisappearAnimation, 0.0F, 1, EUMGSequencePlayMode::Forward, 3.0F, false);

		int randomAnimIndex = FMath::RandRange(0, 2);

		switch (randomAnimIndex)
		{
			case 0:
				PlayAnimation(GetDuckAnimation1, 0.0F, 1, EUMGSequencePlayMode::Forward, 1.0F, false);
				break;
			case 1:
				PlayAnimation(GetDuckAnimation2, 0.0F, 1, EUMGSequencePlayMode::Forward, 1.0F, false);
				break;
			case 2:
				PlayAnimation(GetDuckAnimation3, 0.0F, 1, EUMGSequencePlayMode::Forward, 1.0F, false);
				break;
		}
	}

	if (!gotDuck)
	{
		numDucks++;
		UE_LOG(LogTemp, Log, TEXT("Number of Ducks Collected: %i"), numDucks);
		numDucksText = FString::Printf(TEXT("Ducks: %i"), numDucks);
		ResetDuckPercent();
		RefreshDuckPercentText();
	}

	gotDuck = true;
	canGetDuck = false;
}

void UNextDuckUserWidget::LoadNextDuck()
{
	if (DuckAppearAnimation && !IsAnimationPlaying(DuckAppearAnimation))
	{
		PlayAnimation(DuckAppearAnimation, 0.0F, 1, EUMGSequencePlayMode::Forward, 3.0F, false);
	}

	duckDifficultyMult /= duckDifficultyIncrease;
	gotDuck = false;
	bread -= breadCost;
	RefreshBreadText();
	breadCost *= breadInflation;
	nextDuckButtonText = FString::Printf(TEXT("Next Duck\n%i Bread"), breadCost);

	isEggEnabled = false; // Egg Testing

	if (isEggEnabled)
	{
		if (numDucks < 4)
		{
			// Do nothing
			UE_LOG(LogTemp, Log, TEXT("There will be no egg this day."));
		}
		else if (numDucks == 4)
		{
			SpawnEgg(RandomizeEggPosition());
			UE_LOG(LogTemp, Log, TEXT("Let there be egg."));
		}
		else
		{
			if (IsEggTime())
			{
				UE_LOG(LogTemp, Log, TEXT("Rolling the egg dice, babyyyy."));
				SpawnEgg(RandomizeEggPosition());
			}
		}
	}
}

void UNextDuckUserWidget::RefreshDuckPercentText()
{
	duckPercentText = FString::Printf(TEXT("%i"), (int)truncf(duckPercent * 100.0F)) + "%";
}

void UNextDuckUserWidget::ResetDuckPercent()
{
	duckPercent = 0.0F;
}

void UNextDuckUserWidget::ResetBreadTimer()
{
	breadTimerReset = true;
	GetWorld()->GetTimerManager().ClearTimer(breadTimerHandle);
}

void UNextDuckUserWidget::IncreaseBread()
{
	UE_LOG(LogTemp, Log, TEXT("Bread Timer: %f"), GetWorld()->GetTimerManager().GetTimerElapsed(breadTimerHandle));

	breadTime = 1.0F - GetWorld()->GetTimerManager().GetTimerElapsed(breadTimerHandle) / breadTimerInterval;

	if (breadTimerReset)
	{
		RefreshBreadIncreaseText();
		breadTime = 1.0F;
		breadTimerReset = false;
		bread += breadPerTick;
		UE_LOG(LogTemp, Log, TEXT("Bread: %i"), bread);
		GetWorld()->GetTimerManager().SetTimer(breadTimerHandle, this, &UNextDuckUserWidget::ResetBreadTimer, breadTimerInterval, false);
		RefreshBreadText();
		PlayAnimation(BreadIncreaseAnimation, 0.0F, 1, EUMGSequencePlayMode::Forward, 1.0F, false);
	}
}

bool UNextDuckUserWidget::CheckHasSufficientBread()
{
	if (bread >= breadCost && gotDuck)
	{
		canLoadNextDuck = true;
		return true;
	}
	else
	{
		canLoadNextDuck = false;
		return false;
	}
}

void UNextDuckUserWidget::RefreshBreadText()
{
	breadText = FString::Printf(TEXT("Bread: %i"), bread);
}

void UNextDuckUserWidget::RefreshBreadIncreaseText()
{
	breadIncreaseText = FString::Printf(TEXT("+ %i"), breadPerTick);
}

void UNextDuckUserWidget::ResetEggTimer()
{
	eggTimerReset = true;
	GetWorld()->GetTimerManager().ClearTimer(eggTimerHandle);
}

bool UNextDuckUserWidget::IsEggTime()
{
	int randomInt = FMath::RandRange(0, eggChance);

	UE_LOG(LogTemp, Log, TEXT("eggChance: %i"), eggChance);
	UE_LOG(LogTemp, Log, TEXT("randomInt: %i"), randomInt);

	if (randomInt == eggChance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

FVector2D UNextDuckUserWidget::RandomizeEggPosition()
{
	//GetWorld()->GetTimerManager().SetTimer(eggTimerHandle, this, &UNextDuckUserWidget::ResetEggTimer, eggTimerInterval, false);
	
	// Randomize this, and keep it on-screen where it won't overlap with //any other UI elements
	FVector2D randomizedEggPosition;
	int randomizeLR = FMath::RandRange(0, 1);
	int x = 0;
	int y = 0;
	randomizedEggPosition = FVector2D(FMath::Clamp(x, -800, -400), FMath::Clamp(y, -500, 500));
	if (randomizeLR == 0)
	{
		randomizedEggPosition = FVector2D(FMath::Clamp(x, -800, -400), FMath::Clamp(y, -500, 500));
	}
	else
	{
		randomizedEggPosition = FVector2D(FMath::Clamp(x, 400, 800), FMath::Clamp(y, -500, 500));
	}

	return randomizedEggPosition;
}

void UNextDuckUserWidget::SpawnEgg(FVector2D spawnPosition)
{
	UCanvasPanelSlot* eggButtonSlot = Cast<UCanvasPanelSlot>(eggButton->Slot);
	eggButtonSlot->SetPosition(eggButtonSlot->GetPosition() = spawnPosition);
	PlayAnimation(EggButtonAppearAnimation, 0.0F, 1, EUMGSequencePlayMode::Forward, 1.0F, false);
}

void UNextDuckUserWidget::ClickEgg()
{
	PlayAnimation(EggButtonDisappearAnimation, 0.0F, 1, EUMGSequencePlayMode::Forward, 3.0F, false);
}