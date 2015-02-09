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
	
	
	

	//Find the texture object in the game editor
	static ConstructorHelpers::FObjectFinder<UTexture> CrosshiarTexObj(TEXT("/Game/Material/T_Map1"));
	MiniTexture1 = CrosshiarTexObj.Object;

	static ConstructorHelpers::FObjectFinder<UTexture> CrosshiarTexObj2(TEXT("/Game/Material/T_Map2"));
	MiniTexture2 = CrosshiarTexObj2.Object;
	
	static ConstructorHelpers::FObjectFinder<UTexture> CrosshiarTexObj3(TEXT("/Game/Material/T_Map3"));
	MiniTexture3 = CrosshiarTexObj3.Object;

	static ConstructorHelpers::FObjectFinder<UTexture> CrosshiarTexObj4(TEXT("/Game/Material/T_Map4"));
	MiniTexture4 = CrosshiarTexObj4.Object;

	static ConstructorHelpers::FObjectFinder<UTexture> CrosshiarTexObj5(TEXT("/Game/Material/T_Map5"));
	MiniTexture5 = CrosshiarTexObj5.Object;

	static ConstructorHelpers::FObjectFinder<UTexture> CrosshiarTexObj6(TEXT("/Game/Material/T_Map6"));
	MiniTexture6 = CrosshiarTexObj6.Object;
	
	
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
	UTexture * nTexture;
	//UE_LOG(LogTemp, Warning, TEXT("Your message"));

	if (CurrentScene != NULL && CurrentScene->getIsActive()) // check if CurrentScene is active
		for (int i = 0; i < 4; i++)
		{
			if (CurrentScene->getIsOn_atPaneNumber(i)) // only draw active pane
			{
				ScreenX = CurrentScene->getXpos_atPaneNumber(i);
				ScreenY = CurrentScene->getYpos_atPaneNumber(i);
				ScreenW = CurrentScene->getWidth_atPaneNumber(i);
				ScreenH = CurrentScene->getHeight_atPaneNumber(i);
				nTexture = CurrentScene->getTexture_atPaneNumber(i);
				if (CurrentScene->getHasBahavior_atPaneNumber(i) == true)
				{
					CurrentScene->updateOnBehavior_atPaneNumber(i);
				}

				drawPane(nTexture, ScreenX, ScreenY, ScreenW, ScreenH);

			}
		}
	
}

//Draw a pane onto the view
//Input: texture object to draw, X coordinate on the view, Y coordinate, width of the mini screen, height of the mini screen
//Ouput: none
void AMyHUD::drawPane(UTexture* Texture, float ScreenX, float ScreenY, float ScreenW, float ScreenH)
{
	float TextureU = 0;
	float TextureV = 0;
	float TextureUWidth = 1;
	float TextureVHeight = 1;
	FLinearColor TintColor = WhiteColor;
	EBlendMode BlendMode = BLEND_Opaque;
	float Scale = 1;
	bool bScalePosition = false;
	float Rotation = 0;
	FVector2D RotPivot = FVector2D(0, 0);

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


//Blueprint function
//Initialize a new pane
//Will be called in level blueprint when we want to show a new pane
void AMyHUD::InitializePane(int32 PaneNumber, int32 CameraNumber, float x, float y, float width, float height, bool isOn, EBehavior Behavior)
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

	UTexture* customeTextureMap = NULL;
	switch (CameraNumber)
	{
	case 0:
		CurrentScene->setTexture_atPaneNumber(PaneNumber, MiniTexture1);
		break;
	case 1:
		CurrentScene->setTexture_atPaneNumber(PaneNumber, MiniTexture1);
		break;
	case 2:
		CurrentScene->setTexture_atPaneNumber(PaneNumber, MiniTexture2);
		break;
	case 3:
		CurrentScene->setTexture_atPaneNumber(PaneNumber, MiniTexture3);
		break;
	case 4:
		CurrentScene->setTexture_atPaneNumber(PaneNumber, MiniTexture4);
		break;
	case 5:
		CurrentScene->setTexture_atPaneNumber(PaneNumber, MiniTexture5);
		break;
	case 6:
		CurrentScene->setTexture_atPaneNumber(PaneNumber, MiniTexture6);
		break;
	default:
		CurrentScene->setTexture_atPaneNumber(PaneNumber, MiniTexture1);
		break;
	
	}

	
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
			CurrentScene->setIsOn_atPaneNumber((int)paneNumber, isOn);
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

