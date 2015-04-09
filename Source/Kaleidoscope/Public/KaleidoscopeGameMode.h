// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "MyScene.h"
#include "KaleidoscopeGameMode.generated.h"

UCLASS(minimalapi)
class AKaleidoscopeGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AKaleidoscopeGameMode(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* sceneOpenning;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene6;
};



