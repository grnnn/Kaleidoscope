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
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture> CrosshiarTexObj(TEXT("/Game/Material/T_Map1"));
	MiniTexture = CrosshiarTexObj.Object;

	static ConstructorHelpers::FObjectFinder<UTexture> CrosshiarTexObj2(TEXT("/Game/Material/T_Map2"));
	MiniTexture2 = CrosshiarTexObj2.Object;
	//Get the camera feed material
	//static ConstructorHelpers::FObjectFinder<UMaterial> cameraFeedMat(TEXT("/Game/Textures/camerafeed_Mat"));
	//feedMat = cameraFeedMat.Object;
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
	
	
	ScreenW = 300;
	ScreenH = 300;
	drawTexture(MiniTexture, ScreenX, ScreenY, ScreenW, ScreenH);
	
	ScreenX = 600;
	drawTexture(MiniTexture2, ScreenX, ScreenY, ScreenW, ScreenH);
	
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

	if (IsCanvasValid_WarnIfNot() && MiniTexture)
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

//Testing function, ignore for now
void AMyHUD::MakeNewCamera()
{
	drawTexture(MiniTexture, 0, 300, 300, 300);
}

