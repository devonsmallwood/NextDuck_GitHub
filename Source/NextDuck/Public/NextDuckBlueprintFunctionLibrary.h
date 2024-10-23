// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NextDuckBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class NEXTDUCK_API UNextDuckBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
private:
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	FString GetTestMessage();
};
