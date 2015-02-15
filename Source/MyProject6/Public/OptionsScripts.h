// Fill out your copyright notice in the Description page of Project Settings.



#pragma once
#include "OptionsScripts.generated.h"
/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class MYPROJECT6_API UOptionsScripts: public UObject
{
	GENERATED_BODY()

public:
	UOptionsScripts();
	~UOptionsScripts();

	UFUNCTION(BlueprintCallable, Category = "Options")
	void ChangeSoundClassVolume(FString ClassName, float Volume);
};
