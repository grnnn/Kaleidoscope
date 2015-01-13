// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

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
	
	//Testing function, ignore it for now
	void MakeNewCamera();

private:


	

	/** Crosshair asset pointer */
	class UTexture* MiniTexture;
	class UTexture* MiniTexture2;
	/** Camera feed pointer*/
	//class UMaterial* feedMat;
	
	
};
