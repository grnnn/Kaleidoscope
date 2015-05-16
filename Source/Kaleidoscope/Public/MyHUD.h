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
	Custom,
	FirstPane,
	LastPane
};
/**
 * 
 */
UCLASS()
class KALEIDOSCOPE_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	
	AMyHUD(const FObjectInitializer& ObjectInitializer);

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	//Draw a pane on the screen
	void drawPane(UTexture*, float, float, float, float,int,bool,bool);

	void drawSubtitle(UTexture* Texture, float ScreenX, float ScreenY, float ScreenW, float ScreenH, int alphaValue);

	//Helper function to count how many step player walk
	void setWalkStep(int);

	float getOffsetValue(float inputValue, float startValue, float baseValue);

	//Blueprint function
	//Toggle on/off on specific pane number
	UFUNCTION(BlueprintCallable, Category = "Pane")
		void setPaneNumberOnOff(bool isOn, int32 paneNumber);


	UFUNCTION(BlueprintCallable, Category = "Pane")
	void turnOffAllPane();

	//Blueprint function
	//Initialize a new pane
	UFUNCTION(BlueprintCallable, Category = "Pane")
		void InitializePane(int32 PaneNumber, AActor* Camera, float x, float y, float width, float height, bool isOn, bool isMemory, bool hasFadeIn, float fadeInSpeed, float fadeOutSpeed, EBehavior Behavior, float x_dest, float y_dest, float speed);

	UFUNCTION(BlueprintCallable, Category = "Pane")
	void InitializeSpecialPane(int32 PaneNumber, UTexture* T_MAP, float x, float y, float width, float height, bool isOn, bool isMemory, bool hasFadeIn, EBehavior Behavior, float x_dest, float y_dest,bool isUpper,bool isLower);


	UFUNCTION(BlueprintCallable, Category = "Pane")
	void DrawMyText(FString & Text, FLinearColor TextColor, float x, float y, UFont * Font, float Scale, bool bScalePosition);

	UFUNCTION(BlueprintCallable, Category = "Pane")
	void DisplaySubtitle(UTexture* subtitle, float x, float y, float width, float height);

	UFUNCTION(BlueprintCallable, Category = "Pane")
	void TurnOffSubtitle();



	UFUNCTION(BlueprintCallable, Category = "Screen")
	void SetScreenSize(FString res);


	
	//UFUNCTION(BlueprintCallable, Category = "Pane")
	//void DrawMyText2(FString & Text, FLinearColor TextColor, float x, float y, UFont * Font, float Scale, bool bScalePosition);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD Propertys")
	UFont* Font;
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Scene)
	FString Text;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Scene)
	FString Text2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Scene)
	float TextX;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Scene)
	float TextX2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Scene)
	float TextY;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Scene)
	float TextY2;
	
	//Blueprint variable
	//CurrentScene will be set in level blueprint 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Scene)
	UMyScene* CurrentScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Text)
	FString mytext;

	UFUNCTION(BlueprintCallable, Category = "Letter")
	FString getLetterText();
	

	
private:

	/** Crosshair asset pointer */
	class UTexture* boderTexture;
	class UTexture* mainboderTexture;

	float baseX;
	float baseY;
	FIntPoint ViewSize;
	bool isDebug;


	int32 screenX;
	int32 screenY;

	int letterCount;
	FString letterText;

	class UTexture* subtitleTexture;
	float duration;
	float subDuration;
	float subX;
	float subY;
	float subW;
	float subH;
	float subAlpha;
	bool subOut;

	class UTexture* newSubtitleTexture;
	float newSubX;
	float newSubY;
	float newSubW;
	float newSubH;

};
