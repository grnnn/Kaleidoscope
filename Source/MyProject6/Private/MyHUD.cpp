// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject6.h"
#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "CanvasTypes.h"
#include "UnrealClient.h"

int test1();
int biggerBehavior();
float ScreenX = 0;
float ScreenY = 0;
float ScreenW = 300;
float ScreenH = 300;
int cMove;

AMyHUD::AMyHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
	
	cMove = 0;
	isTrigger = false;
	isTriggerF = false;
	x_pos = 1;
	y_pos = 1;
	

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
	
	
	
	//Initialize scene1
	//This variable should be initialized in MyGameMode so every class could access to it
	// something like // currentScene = MyGameMode.getSceneName("scene1");
	
	//for now, we define scene1 here for quick testing.
	
	scene1 = new MyScene("s1", 4);
	scene1->setIsActive(true); 
	scene1->setXpost_atPaneNumber(0, 0);
	scene1->setYpost_atPaneNumber(0, 0);
	scene1->setWidth_atPaneNumber(0, 510);
	scene1->setHeight_atPaneNumber(0, 300);

	scene1->setXpost_atPaneNumber(1, 600);
	scene1->setYpost_atPaneNumber(1, 0);
	scene1->setWidth_atPaneNumber(1, 510);
	scene1->setHeight_atPaneNumber(1, 300);

	scene1->setXpost_atPaneNumber(2, 0);
	scene1->setYpost_atPaneNumber(2, 300);
	scene1->setWidth_atPaneNumber(2, 510);
	scene1->setHeight_atPaneNumber(2, 300);

	scene1->setXpost_atPaneNumber(3, 600);
	scene1->setYpost_atPaneNumber(3, 450);
	scene1->setWidth_atPaneNumber(3, 510);
	scene1->setHeight_atPaneNumber(3, 300);

	scene1->setIsOn_atPaneNumber(0, false);
	scene1->setIsOn_atPaneNumber(1, false);
	scene1->setIsOn_atPaneNumber(2, false);
	scene1->setIsOn_atPaneNumber(3, false);

	scene1->setTexture_atPaneNumber(0, MiniTexture1);
	scene1->setTexture_atPaneNumber(1, MiniTexture2);
	scene1->setTexture_atPaneNumber(2, MiniTexture3);
	scene1->setTexture_atPaneNumber(3, MiniTexture4);

	scene1->setBehavior_atPaneNumber(2, biggerBehavior);
	
}

//Override DrawHUD
//Call drawTexture to draw mini screen
void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
	


	
	UTexture * nTexture;
	//UE_LOG(LogTemp, Warning, TEXT("Your message"));
	

	if (scene1->getIsActive()) // check if we should draw scene1's panes
		for (int i = 0; i < 4; i++)
		{
			if (scene1->getIsOn_atPaneNumber(i)) // only draw active pane
			{
				ScreenX = scene1->getXpos_atPaneNumber(i);
				ScreenY = scene1->getYpos_atPaneNumber(i);
				ScreenW = scene1->getWidth_atPaneNumber(i);
				ScreenH = scene1->getHeight_atPaneNumber(i);
				nTexture = scene1->getTexture_atPaneNumber(i);
				if (i == 2)
				{
					auto temp1 = scene1->getBehavior_atPaneNumber(i);
					int n1 = temp1();
					scene1->setWidth_atPaneNumber(i, ScreenW);
					scene1->setHeight_atPaneNumber(i, ScreenH);
					scene1->setYpost_atPaneNumber(i, ScreenY);
					//UE_LOG(YourLog, Warning, TEXT("My test n1 %d"), n1);
					
				}

				drawTexture(nTexture, ScreenX, ScreenY, ScreenW, ScreenH);

			}
		}
	
}

//Draw mini screen onto the view
//Input: texture object to draw, X coordinate on the view, Y coordinate, width of the mini screen, height of the mini screen
//Ouput: none
void AMyHUD::drawTexture(UTexture* Texture, float ScreenX, float ScreenY, float ScreenW, float ScreenH)
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

//call when user pressed 'E' key to draw extra screen
//input: true or false
void AMyHUD::setIsTrigger(bool isTrig)
{
	scene1->setIsActive(isTrig);
}

void AMyHUD::setCamerNumberOn(bool isTrig, int32 cameNum)
{
	scene1->setIsOn_atPaneNumber((int)cameNum, isTrig);
	//scene1->setIsActive(isTrig);
}

//testing function
//ignore
void AMyHUD::setIsTriggerF(bool isTrig)
{
	isTriggerF = isTrig;
}

//testing
//ignore
void AMyHUD::Tick(float DeltaSeconds)
{
	if (x_pos > 0)
		x_pos++;
	if (y_pos > 0)
		y_pos++;
}


void AMyHUD::setWalkStep(int w)
{
	cMove = w;
}
int test1()
{
	ScreenX++;
	ScreenY++;
	return 10;
}
int biggerBehavior()
{
	if ( ScreenH < 350)
	{
		ScreenY = 300 - cMove;
		ScreenW = 510 + cMove;
		ScreenH = 300 + cMove;
	}
	return 0;
}
