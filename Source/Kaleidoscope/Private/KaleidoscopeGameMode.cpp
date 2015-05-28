// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Kaleidoscope.h"
#include "KaleidoscopeGameMode.h"
#include "KaleidoscopeCharacter.h"
//#include "MyHUD.h"
AKaleidoscopeGameMode::AKaleidoscopeGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//Use C++ custom HUD
	static ConstructorHelpers::FObjectFinder<UClass> PlayerHUDBPClass(TEXT("Class'/Game/Blueprints/newHUD.newHUD_C'"));
	HUDClass = PlayerHUDBPClass.Object;
	

	//Initialize scene
	sceneOpening = new UMyScene("Openning scene", 100); //openning scene with 4 panes
	sceneOpening->setIsActive(true);

	scene2 = new UMyScene("Scene2", 100); 
	scene2->setIsActive(true);

	scene3 = new UMyScene("Scene3", 100);
	scene3->setIsActive(true);

	scene4 = new UMyScene("Scene3", 100);
	scene4->setIsActive(true);

	puzzleScene = new UMyScene("Scene3", 100);
	puzzleScene->setIsActive(true);

	endScene = new UMyScene("Scene3", 100);
	endScene->setIsActive(true);


	scene2actual = new UMyScene("Scene3", 100);
	scene2actual->setIsActive(true);

	scene3actual = new UMyScene("Scene3", 100);
	scene3actual->setIsActive(true);

	scene4actual = new UMyScene("Scene3", 100);
	scene4actual->setIsActive(true);

	scene5 = new UMyScene("Scene3", 100);
	scene5->setIsActive(true);

	scene6 = new UMyScene("Scene3", 100);
	scene6->setIsActive(true);

	scene7 = new UMyScene("Scene3", 100);
	scene7->setIsActive(true);

	scene8 = new UMyScene("Scene3", 100);
	scene8->setIsActive(true);

	scene9 = new UMyScene("Scene3", 100);
	scene9->setIsActive(true);

	scene10 = new UMyScene("Scene3", 100);
	scene10->setIsActive(true);

	screenX = 1280;
	screenY = 720;

	

	// ...

	

}


UGameUserSettings* AKaleidoscopeGameMode::GetGameUserSettings()
{
	if (GEngine != nullptr)
	{
		return GEngine->GameUserSettings;
	}
	return nullptr;
}

void AKaleidoscopeGameMode::changeRes(FString res)
{
	int32 x, y;

	x = 1280, y = 720;

	//if (res.Equals("1024x576"))
		//x = 1024, y = 576;
	//else
	if (res.Equals("1280x720"))
		x = 1280, y = 720;
	else if (res.Equals("1600x900"))
		x = 1600, y = 900;
	else if (res.Equals("1920x1080"))
		x = 1920, y = 1080;
	
	//int32 Width = 1600, Height = 900;
	UGameUserSettings* Settings = GetGameUserSettings(); // note we are using the function defined above
	screenX = x;
	screenY = y;
	if (Settings != nullptr)
	{
		Settings->RequestResolutionChange(x, y, EWindowMode::Type::Fullscreen, false); // we can choose to ignore the command line arguments, this is probably best when the game UI sets the mode after startup
		Settings->ConfirmVideoMode();

		// Save the requested settings to our local data now
		Settings->SetScreenResolution(Settings->GetLastConfirmedScreenResolution());
		Settings->SetFullscreenMode(Settings->GetLastConfirmedFullscreenMode());
		Settings->SaveSettings();
	}
}