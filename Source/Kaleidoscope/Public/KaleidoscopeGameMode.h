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
	UGameUserSettings* GetGameUserSettings();

	UFUNCTION(BlueprintCallable, Category = "Screen")
	void changeRes(FString res);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* sceneOpening;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* puzzleScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* endScene;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene2actual;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene3actual;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene4actual;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene6;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene7;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene8;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene9;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Scene)
	UMyScene* scene10;


	int32 screenX;
	int32 screenY;











	


};



