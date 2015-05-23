// Fill out your copyright notice in the Description page of Project Settings.

#include "Kaleidoscope.h"
#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "CanvasTypes.h"
#include "UnrealClient.h"

#include "Classes/GameFramework/GameUserSettings.h"





AMyHUD::AMyHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	Text = " ";
	TextX = TextY = 0;

	baseX = 1280;
	baseY = 720;
	screenX = baseX;
	screenY = baseY;
	isDebug = false;
	subtitleTexture = NULL;
	newSubtitleTexture = NULL;
	fadeInEffect = false;
	fadeOutEffect = false;
	duration = 0;
	subOut = false;
	
	//Find the texture object in the game editor
	static ConstructorHelpers::FObjectFinder<UTexture> CrosshiarTexObj(TEXT("/Game/Material/overlay3"));
	boderTexture = CrosshiarTexObj.Object;

	static ConstructorHelpers::FObjectFinder<UTexture> CrosshiarTexObj2(TEXT("/Game/Material/main_border"));
	mainboderTexture = CrosshiarTexObj2.Object;

	
	
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
	//float x1 = GetLastConfirmedScreenResolution();
	//float x = OptionsScripts::screenX;

	UGameViewportClient* Viewport = GetWorld()->GetGameViewport();
	//ViewSize = Viewport->Viewport->GetSizeXY();
	
	if (GEngine && !isDebug)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT("Debug Screen_Size_X = %i , Screen_Size Y = %i"), ViewSize.X, ViewSize.Y));
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT("Debug Screen_Size_X = %i , Screen_Size Y = %i"), screenX, screenY));
		//isDebug = true;
	}
	if (CurrentScene != NULL && CurrentScene->getIsActive()) // check if CurrentScene is active
		for (int i = 0; i < 100; i++)
		{
			//Only draw isOn pane
			if (CurrentScene->getIsOn_atPaneNumber(i)) 
			{
				float x = CurrentScene->getXpos_atPaneNumber(i);
				float y = CurrentScene->getYpos_atPaneNumber(i);
				float w = CurrentScene->getWidth_atPaneNumber(i);
				float h = CurrentScene->getHeight_atPaneNumber(i);
				
				//convert to screen size
				//ScreenX = getOffsetValue(x, ViewSize.X, baseX);
				//ScreenY = getOffsetValue(y, ViewSize.Y, baseY);
				//ScreenW = getOffsetValue(w, ViewSize.X, baseX);
				//ScreenH = getOffsetValue(h, ViewSize.Y, baseY);


				ScreenX = getOffsetValue(x, screenX, baseX);
				ScreenY = getOffsetValue(y, screenY, baseY);
				ScreenW = getOffsetValue(w, screenX, baseX);
				ScreenH = getOffsetValue(h, screenY, baseY);
				
				//Get alpha for fade in effect
				if (CurrentScene->getHasFadeIn_atPaneNumber(i))
					AlphaValue = CurrentScene->getAlphaValue_atPaneNumber(i);
				else
					AlphaValue = 255;

				//Get texture
				nTexture = CurrentScene->getTexture_atPaneNumber(i);
				
				//Get behavior
				if (CurrentScene->getHasBahavior_atPaneNumber(i) == true)
				{
					CurrentScene->updateViewportXY_atPaneNumber(i, screenX, screenY);
					CurrentScene->updateOnBehavior_atPaneNumber(i);

				}

				if (CurrentScene->getIsSpecial_atPaneNumber(i))
				{
					if (CurrentScene->getIsUpper_atPaneNumber(i))
						drawPane(nTexture, ScreenX, ScreenY, ScreenW, ScreenH, AlphaValue, true, true);
					else
						drawPane(nTexture, ScreenX, ScreenY, ScreenW, ScreenH, AlphaValue, true, false);
				}
				else
					drawPane(nTexture, ScreenX, ScreenY, ScreenW, ScreenH, AlphaValue, false,false);
				
				//If memory pane, draw an overlay border
				if (CurrentScene->getIsMemory_atPaneNumber(i))
					drawPane(boderTexture, ScreenX, ScreenY, ScreenW, ScreenH, 255,false,false);
				else
					drawPane(mainboderTexture, ScreenX, ScreenY, ScreenW, ScreenH, 255, false, false);

				if (CurrentScene->getFadeOut_atPaneNumber(i))
				{
					float fadeOutSpeed = CurrentScene->getFadeOutSpeed_atPaneNumber(i);
					CurrentScene->setAlphaValue_atPaneNumber(i, AlphaValue - fadeOutSpeed);
					if (AlphaValue < 1)
					{
						CurrentScene->turnOffCapture_atPaneNumber(i);
						CurrentScene->setIsOn_atPaneNumber(i, false);
						CurrentScene->setFadeOut_atPaneNumber(i, false);
						CurrentScene->setAlphaValue_atPaneNumber(i, 255);
					}
						
				}
				else
				{
					//Increase alpha value overtime
					if (AlphaValue < 255)
					{
						float fadeInSpeed = CurrentScene->getFadeInSpeed_atPaneNumber(i);
						CurrentScene->setAlphaValue_atPaneNumber(i, AlphaValue + fadeInSpeed);
					}
				}
				
				//Super::DrawText(mytext, TintColor, 0, 0, NULL, 1, false);
			}

			
			

		}

	if (subtitleTexture != NULL && !subOut)
	{

		newSubtitleTexture = subtitleTexture;

		ScreenX = getOffsetValue(subX, screenX, baseX);
		ScreenY = getOffsetValue(subY, screenY, baseY);
		ScreenW = getOffsetValue(subW, screenX, baseX);
		ScreenH = getOffsetValue(subH, screenY, baseY);

		drawSubtitle(subtitleTexture, ScreenX, ScreenY, ScreenW, ScreenH, subAlpha);
		if (subAlpha < 255 && fadeInEffect)
			subAlpha += 2;
		else if (subAlpha < 255 && !fadeInEffect)
			subAlpha = 255;

	}
	else if (subtitleTexture != NULL && subOut)
	{
		//subtitleTexture = NULL;
		//subAlpha = 0;
		ScreenX = getOffsetValue(subX, screenX, baseX);
		ScreenY = getOffsetValue(subY, screenY, baseY);
		ScreenW = getOffsetValue(subW, screenX, baseX);
		ScreenH = getOffsetValue(subH, screenY, baseY);
		if (fadeOutEffect)
			subAlpha -= 2;
		else
			subAlpha = 0;
		if (subAlpha <= 0)
		{
			subAlpha = 0;
			subOut = false;
			subtitleTexture = NULL;
		}
		if (subtitleTexture)
			drawSubtitle(subtitleTexture, ScreenX, ScreenY, ScreenW, ScreenH, subAlpha);
	}

	Super::DrawText(Text, TintColor, TextX, TextY, Font, 200, false);
	Super::DrawText(Text2, TintColor, TextX2, TextY2, Font, 200, false);
}

//Draw a pane onto the view
//Input: texture object to draw, X coordinate on the view, Y coordinate, width of the mini screen, height of the mini screen
//Ouput: none
void AMyHUD::drawPane(UTexture* Texture, float ScreenX, float ScreenY, float ScreenW, float ScreenH,int alphaValue,bool isSpecial,bool isUpper)
{
	float TextureU = 0;
	float TextureV = 0;
	float TextureUWidth = 1;
	float TextureVHeight = 1;
	
	if (isSpecial)
	{
		if (isUpper)
		{
			TextureU = 0;
			TextureV = 0.5f;
			TextureUWidth = 1;
			TextureVHeight = .5f;
		}
		else
		{
			TextureU = 0;
			TextureV = 0;
			TextureUWidth = 1.0f;
			TextureVHeight = 0.5f;
		}
	}
	
	
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

void AMyHUD::drawSubtitle(UTexture* Texture, float ScreenX, float ScreenY, float ScreenW, float ScreenH, int alphaValue)
{
	float TextureU = 0;
	float TextureV = 0;
	float TextureUWidth = 1;
	float TextureVHeight = 1;
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT("Debug Screen_Size_X = %i"), alphaValue));

	if (alphaValue > 255)
		alphaValue = 255;
	FLinearColor TintColor = FColor(255, 255, 255, alphaValue);
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
void AMyHUD::InitializePane(int32 PaneNumber, AActor* Camera, float x, float y, float width, float height, bool isOn, bool isMemory, bool hasFadeIn, float fadeInSpeed, float fadeOutSpeed, EBehavior Behavior, float x_dest, float y_dest, float speed)
{
	if (PaneNumber > CurrentScene->getNumberOfPane())
	{
		//Pane number is Out of range
		return;
	}
	//USceneCaptureComponent2D = 
	if (!Camera)
		return;

	bool check = false;
	int maxChild = Camera->GetRootComponent()->GetNumChildrenComponents();
	USceneComponent *myscene = NULL;
	USceneCaptureComponent2D *mycapture = NULL;
	UTexture* T_MAP = NULL;
	for (int i = 0; i < maxChild; i++)
	{
		myscene = (USceneComponent*)Camera->GetRootComponent()->GetChildComponent(i);
		if (myscene->IsA(USceneCaptureComponent2D::StaticClass()))
		{
			mycapture = (USceneCaptureComponent2D*)myscene;
			mycapture->bCaptureEveryFrame = true;
			T_MAP = (UTexture*)mycapture->TextureTarget;
			if (T_MAP)
			{
				check = true;
				break;
			}
		}
		
		/*mycapture = (USceneCaptureComponent2D*)myscene;
		if (mycapture)
		{
			mycapture->bCaptureEveryFrame = true;
			T_MAP = (UTexture*)mycapture->TextureTarget;
			if (T_MAP)
				break;
		}*/
	}
	//USceneComponent *myscene = (USceneComponent*)Camera->GetRootComponent()->GetChildComponent(3);
	//USceneCaptureComponent2D *mycapture = (USceneCaptureComponent2D*)myscene;
	//mycapture->bCaptureEveryFrame = true;
	//UTexture* T_MAP = (UTexture*)mycapture->TextureTarget;
	//T_MAP->
	if (!check)
		return;
	CurrentScene->setmycapture_atPaneNumber(PaneNumber, mycapture);

	CurrentScene->setXpost_atPaneNumber(PaneNumber, x);
	CurrentScene->setYpost_atPaneNumber(PaneNumber, y);
	CurrentScene->setWidth_atPaneNumber(PaneNumber, width);
	CurrentScene->setHeight_atPaneNumber(PaneNumber, height);
	CurrentScene->setIsOn_atPaneNumber(PaneNumber, isOn);

	CurrentScene->setIsMemory_atPaneNumber(PaneNumber, isMemory);
	CurrentScene->setHasFadeIn_atPaneNumber(PaneNumber, hasFadeIn);

	CurrentScene->setTexture_atPaneNumber(PaneNumber, T_MAP);

	CurrentScene->setFadeInSpeed_atPaneNumber(PaneNumber, fadeInSpeed);
	CurrentScene->setFadeOutSpeed_atPaneNumber(PaneNumber, fadeOutSpeed);
	CurrentScene->setSpeed_atPaneNumber(PaneNumber, speed);

	if (Behavior != None)
	{
		CurrentScene->setHasBehavior_atPaneNumber(PaneNumber, true);
		CurrentScene->setBehaviorType_atPaneNumber(PaneNumber, Behavior,x_dest,y_dest);
	}

	return;
	
}


void AMyHUD::InitializeSpecialPane(int32 PaneNumber, UTexture* T_MAP, float x, float y, float width, float height, bool isOn, bool isMemory, bool hasFadeIn, EBehavior Behavior, float x_dest, float y_dest, bool isUpper, bool isLower)
{
	if (PaneNumber > CurrentScene->getNumberOfPane())
	{
		//Pane number is Out of range
		return;
	}
	CurrentScene->setIsSpecial_atPaneNumber(PaneNumber, true);
	CurrentScene->setIsUpper_atPaneNumber(PaneNumber, isUpper);
	CurrentScene->setIsLower_atPaneNumber(PaneNumber, isLower);

	CurrentScene->setXpost_atPaneNumber(PaneNumber, x);
	CurrentScene->setYpost_atPaneNumber(PaneNumber, y);
	CurrentScene->setWidth_atPaneNumber(PaneNumber, width);
	CurrentScene->setHeight_atPaneNumber(PaneNumber, height);
	CurrentScene->setIsOn_atPaneNumber(PaneNumber, isOn);

	CurrentScene->setIsMemory_atPaneNumber(PaneNumber, isMemory);
	CurrentScene->setHasFadeIn_atPaneNumber(PaneNumber, hasFadeIn);

	CurrentScene->setTexture_atPaneNumber(PaneNumber, T_MAP);
	CurrentScene->setFadeInSpeed_atPaneNumber(PaneNumber, 2);
	CurrentScene->setFadeOutSpeed_atPaneNumber(PaneNumber, 2);
	CurrentScene->setSpeed_atPaneNumber(PaneNumber, 1);

	if (Behavior != None)
	{
		CurrentScene->setHasBehavior_atPaneNumber(PaneNumber, true);
		CurrentScene->setBehaviorType_atPaneNumber(PaneNumber, Behavior, x_dest, y_dest);
	}

	return;
}


void AMyHUD::DisplaySubtitle(UTexture* subtitle, float x, float y, float width, float height, bool fadeIn, bool fadeOut)
{
	
	int PaneNumber = 100;
	
	fadeInEffect = fadeIn;
	fadeOutEffect = fadeOut;
	subtitleTexture = subtitle;
	subX = x;
	subY = y;
	subW = width;
	subH = height;
	if (subtitleTexture != newSubtitleTexture)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT("AAAAAAAAAAAAAAAAAAAAA")));
		subAlpha = 0;
	}
	



	return;
}


void AMyHUD::TurnOffSubtitle()
{
	//subtitleTexture = NULL;
	subOut = true;
}


//Blueprint function
//Toggle on/off on specific pane number
//input: bool on/off, pane number
void AMyHUD::setPaneNumberOnOff(bool isOn, int32 paneNumber)
{
	
	//UTexture* T_MAP = (UTexture*)mycapture->TextureTarget;
	if (CurrentScene != NULL)
		if (paneNumber <= CurrentScene->getNumberOfPane())
		{

			if (CurrentScene->getHasFadeIn_atPaneNumber((int)paneNumber))
			{
				CurrentScene->setFadeOut_atPaneNumber((int)paneNumber, true);
				//CurrentScene->turnOffCapture_atPaneNumber((int)paneNumber);
			}
			else
			{
				CurrentScene->setIsOn_atPaneNumber((int)paneNumber, false);
				CurrentScene->turnOffCapture_atPaneNumber((int)paneNumber);
				//USceneCaptureComponent2D *mycapture = CurrentScene->getmycapture_atPaneNumber(paneNumber);
				//if (mycapture)
				//	mycapture->bCaptureEveryFrame = false;
			}

			//CurrentScene->setAlphaValue_atPaneNumber((int)paneNumber,0);
			//CurrentScene->setFadeOut_atPaneNumber((int)paneNumber, true);
			//CurrentScene->setIsOn_atPaneNumber((int)paneNumber, isOn);
		}
}


void AMyHUD::turnOffAllPane()
{
	if (CurrentScene != NULL && CurrentScene->getIsActive()) // check if CurrentScene is active
		for (int i = 0; i < 100; i++)
			if (CurrentScene->getIsOn_atPaneNumber(i))
			{
				if (CurrentScene->getHasFadeIn_atPaneNumber(i))
				{
					
					CurrentScene->setFadeOut_atPaneNumber(i, true);
					//CurrentScene->turnOffCapture_atPaneNumber(i);
				}
				else
				{
					CurrentScene->setIsOn_atPaneNumber(i, false);
					CurrentScene->turnOffCapture_atPaneNumber(i);
					//USceneCaptureComponent2D *mycapture = CurrentScene->getmycapture_atPaneNumber(i);
					//if (mycapture)
					//	mycapture->bCaptureEveryFrame = false;
				}
			}
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


void AMyHUD::SetScreenSize(FString res)
{
	int32 newX = 1280;
	int32 newY = 720;
	if (res.Equals("1024x576"))
		newX = 1024, newY = 576;
	else if (res.Equals("1280x720"))
		newX = 1280, newY = 720;
	else if (res.Equals("1600x900"))
		newX = 1600, newY = 900;
	else if (res.Equals("1920x1080"))
		newX = 1920, newY = 1080;

	screenX = newX;
	screenY = newY;
}

FString AMyHUD::getLetterText()
{
	letterCount += 1;
	letterText = FString::FromInt(letterCount) + "/6 Letters Found";
	return letterText;

}