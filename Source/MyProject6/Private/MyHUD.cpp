// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject6.h"
#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "CanvasTypes.h"
#include "UnrealClient.h"






AMyHUD::AMyHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	Text = " ";
	TextX = TextY = 0;

	baseX = 1280;
	baseY = 720;
	isDebug = false;
	

	//Find the texture object in the game editor
	static ConstructorHelpers::FObjectFinder<UTexture> CrosshiarTexObj(TEXT("/Game/Material/black_border"));
	boderTexture = CrosshiarTexObj.Object;

	
	
	ConstructorHelpers::FObjectFinder<UFont> FontObject(TEXT("Font'/Game/Blueprints/NewFont.NewFont'"));
	if (FontObject.Object)
	{
		Font = FontObject.Object;
	}
	
}

//Override DrawHUD
//Call drawTexture to draw mini screen
void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
	
	float ScreenX = 0;
	float ScreenY = 0;
	float ScreenW = 0;
	float ScreenH = 0;
	float AlphaValue = 0;
	UTexture * nTexture;
	//UE_LOG(LogTemp, Warning, TEXT("Your message"));

	
	FLinearColor TintColor = WhiteColor;

	UGameViewportClient* Viewport = GetWorld()->GetGameViewport();
	ViewSize = Viewport->Viewport->GetSizeXY();
	if (GEngine && !isDebug)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT("Debug Screen_Size_X = %i , Screen_Size Y = %i"), ViewSize.X, ViewSize.Y));
		isDebug = true;
	}
	if (CurrentScene != NULL && CurrentScene->getIsActive()) // check if CurrentScene is active
		for (int i = 0; i < 100; i++)
		{
			if (CurrentScene->getIsOn_atPaneNumber(i)) // only draw active pane
			{
				float x = CurrentScene->getXpos_atPaneNumber(i);
				float y = CurrentScene->getYpos_atPaneNumber(i);
				float w = CurrentScene->getWidth_atPaneNumber(i);
				float h = CurrentScene->getHeight_atPaneNumber(i);
				
				ScreenX = getOffsetValue(x, ViewSize.X, baseX);
				ScreenY = getOffsetValue(y, ViewSize.Y, baseY);
				ScreenW = getOffsetValue(w, ViewSize.X, baseX);
				ScreenH = getOffsetValue(h, ViewSize.Y, baseY);
				
				if (CurrentScene->getHasFadeIn_atPaneNumber(i))
					AlphaValue = CurrentScene->getAlphaValue_atPaneNumber(i);
				else
					AlphaValue = 255;

				nTexture = CurrentScene->getTexture_atPaneNumber(i);
				if (CurrentScene->getHasBahavior_atPaneNumber(i) == true)
				{
					CurrentScene->updateViewportXY_atPaneNumber(i,ViewSize.X,ViewSize.Y);
					CurrentScene->updateOnBehavior_atPaneNumber(i);

				}

				drawPane(nTexture, ScreenX, ScreenY, ScreenW, ScreenH,AlphaValue);
				if (CurrentScene->getIsMemory_atPaneNumber(i))
					drawPane(boderTexture, ScreenX, ScreenY, ScreenW, ScreenH, 255);

				if (AlphaValue < 255)
					CurrentScene->setAlphaValue_atPaneNumber(i,AlphaValue+2);
				
				//Super::DrawText(mytext, TintColor, 0, 0, NULL, 1, false);
			}
		}

	Super::DrawText(Text, TintColor, TextX, TextY, Font, 200, false);
	Super::DrawText(Text2, TintColor, TextX2, TextY2, Font, 200, false);
}

//Draw a pane onto the view
//Input: texture object to draw, X coordinate on the view, Y coordinate, width of the mini screen, height of the mini screen
//Ouput: none
void AMyHUD::drawPane(UTexture* Texture, float ScreenX, float ScreenY, float ScreenW, float ScreenH,int alphaValue)
{
	float TextureU = 0;
	float TextureV = 0;
	float TextureUWidth = 1;
	float TextureVHeight = 1;
	if (alphaValue > 255)
		alphaValue = 255;
	FLinearColor TintColor = FColor(255,255,255,alphaValue);
	EBlendMode BlendMode = BLEND_Translucent;
	float Scale = 1;
	bool bScalePosition = false;
	float Rotation = 0;
	FVector2D RotPivot = FVector2D(0, 0);
	//Canvas->SetDrawColor(255, 255, 255, 0);
	if (IsCanvasValid_WarnIfNot() && Texture)
	{
		FCanvasTileItem TileItem(FVector2D(ScreenX, ScreenY), Texture->Resource, FVector2D(ScreenW, ScreenH) * Scale, FVector2D(TextureU, TextureV), FVector2D(TextureU + TextureUWidth, TextureV + TextureVHeight), TintColor);
		TileItem.Rotation = FRotator(0, Rotation, 0);
		TileItem.PivotPoint = RotPivot;
		if (bScalePosition)
		{
			TileItem.Position *= Scale;
		}
		TileItem.BlendMode = FCanvas::BlendToSimpleElementBlend(BlendMode);
		Canvas->DrawItem(TileItem);
	}
}


void AMyHUD::DrawMyText(FString & Text, FLinearColor TextColor, float x, float y, UFont * Font, float Scale, bool bScalePosition)
{
	//Super::DrawText(Text, TextColor, x, y, Font, Scale, bScalePosition);
	

}


//Blueprint function
//Initialize a new pane
//Will be called in level blueprint when we want to show a new pane
void AMyHUD::InitializePane(int32 PaneNumber, UTexture* T_MAP, float x, float y, float width, float height, bool isOn, bool isMemory, bool hasFadeIn, EBehavior Behavior)
{
	if (PaneNumber > CurrentScene->getNumberOfPane())
	{
		//Pane number is Out of range
		return;
	}
	
	CurrentScene->setXpost_atPaneNumber(PaneNumber, x);
	CurrentScene->setYpost_atPaneNumber(PaneNumber, y);
	CurrentScene->setWidth_atPaneNumber(PaneNumber, width);
	CurrentScene->setHeight_atPaneNumber(PaneNumber, height);
	CurrentScene->setIsOn_atPaneNumber(PaneNumber, isOn);

	CurrentScene->setIsMemory_atPaneNumber(PaneNumber, isMemory);
	CurrentScene->setHasFadeIn_atPaneNumber(PaneNumber, hasFadeIn);

	CurrentScene->setTexture_atPaneNumber(PaneNumber, T_MAP);


	if (Behavior != None)
	{
		CurrentScene->setHasBehavior_atPaneNumber(PaneNumber, true);
		CurrentScene->setBehaviorType_atPaneNumber(PaneNumber, Behavior);
	}

	return;
	
}

//Blueprint function
//Toggle on/off on specific pane number
//input: bool on/off, pane number
void AMyHUD::setPaneNumberOnOff(bool isOn, int32 paneNumber)
{
	if (CurrentScene != NULL)
		if (paneNumber <= CurrentScene->getNumberOfPane())
		{
			CurrentScene->setAlphaValue_atPaneNumber((int)paneNumber,0);
			CurrentScene->setIsOn_atPaneNumber((int)paneNumber, isOn);
		}
}


void AMyHUD::turnOffAllPane()
{
	if (CurrentScene != NULL && CurrentScene->getIsActive()) // check if CurrentScene is active
		for (int i = 0; i < 100; i++)
			CurrentScene->setIsOn_atPaneNumber(i, false);
}

//Helper function to count how many step player has walked
//Called in MyChracter class when player moving forward/backward
//then pass to specific pane to calculate behavior
//input: number of step player has walked
void AMyHUD::setWalkStep(int w)
{
	if (CurrentScene != NULL)
		CurrentScene->setNumberOfWalk_atPaneNumber(w);
}

float AMyHUD::getOffsetValue(float inputValue,float startValue,float baseValue)
{
	float ratio = startValue / baseValue;
	return inputValue * ratio;
}