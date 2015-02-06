// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"

#include <vector>
#include <string>
#include "MyScene.h"


#include "MyHUD.generated.h"
using namespace std;


UENUM(BlueprintType, Category = "Behavior")
enum EBehavior
{
	None,
	MoveRight,
	MoveLeft,
	MoveUp,
	MoveDown,
	Bigger,
	Smaller
};
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

	//Draw a pane on the screen
	void drawPane(UTexture*, float, float, float, float);
	//Helper function to count how many step player walk
	void setWalkStep(int);

	//Blueprint function
	//Toggle on/off on specific pane number
	UFUNCTION(BlueprintCallable, Category = "Pane")
	void setPaneNumberOnOff(bool isOn, int32 paneNumber);

	//Blueprint function
	//Initialize a new pane
	UFUNCTION(BlueprintCallable, Category = "Pane")
	void InitializePane(int32 PaneNumber, int32 CameraNumber, float x, float y, float width, float height, bool isOn, EBehavior Behavior);

	
	//Blueprint variable
	//CurrentScene will be set in level blueprint 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Scene)
	UMyScene* CurrentScene;

	

	
private:

	/** Crosshair asset pointer */
	class UTexture* MiniTexture1;
	class UTexture* MiniTexture2;
	class UTexture* MiniTexture3;
	class UTexture* MiniTexture4;
	class UTexture* MiniTexture5;
	class UTexture* MiniTexture6;
	
	
	
};
