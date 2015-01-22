// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"

#include <vector>
#include "MyScene.h"
#include "MyHUD.generated.h"
using namespace std;
/**
 * 
 */
UCLASS()
class MYPROJECT6_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AMyHUD(const FObjectInitializer& ObjectInitializer);

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	//Draw mini screen
	void drawTexture(UTexture*, float, float, float, float);
	
	//void drawText(float, float);

	//Testing function, ignore it for now
	UFUNCTION(BlueprintCallable, Category = "Switch Functions")
	void setIsTrigger(bool isTrig);
	void setIsTriggerF(bool);

	void Tick(float DeltaSeconds);
	

private:

	MyScene* scene1;
	

	/** Crosshair asset pointer */
	class UTexture* MiniTexture1;
	class UTexture* MiniTexture2;
	class UTexture* MiniTexture3;
	class UTexture* MiniTexture4;
	class UTexture* MiniTexture5;
	class UTexture* MiniTexture6;
	bool isTrigger;
	bool isTriggerF;
	float x_pos;
	float y_pos;

	/** Camera feed pointer*/
	//class UMaterial* feedMat;
	
	
};
