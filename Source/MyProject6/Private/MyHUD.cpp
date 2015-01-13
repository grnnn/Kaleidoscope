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
	isTrigger = false;

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
	float ScreenW = 300;
	float ScreenH = 300;
	
	//UE_LOG(LogTemp, Warning, TEXT("Your message"));
	ScreenX = 0;
	ScreenY = 0;
	drawTexture(MiniTexture1, ScreenX, ScreenY, ScreenW, ScreenH);
	
	ScreenX = 600;
	ScreenY = 0;
	drawTexture(MiniTexture2, ScreenX, ScreenY, ScreenW, ScreenH);

	ScreenX = 0;
	ScreenY = 320;
	drawTexture(MiniTexture3, ScreenX, ScreenY, ScreenW, ScreenH);

	ScreenX = 600;
	ScreenY = 320;
	drawTexture(MiniTexture4, ScreenX, ScreenY, ScreenW, ScreenH);

	
	ScreenX = 300;
	ScreenY = 0;
	if (isTrigger)
		drawTexture(MiniTexture5, ScreenX, ScreenY, ScreenW, ScreenH);
	
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
	isTrigger = isTrig;
}
