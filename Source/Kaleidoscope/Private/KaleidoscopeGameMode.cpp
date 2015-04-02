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
	sceneOpenning = new UMyScene("Openning scene", 100); //openning scene with 4 panes
	sceneOpenning->setIsActive(true);

	scene2 = new UMyScene("Scene2", 100); 
	scene2->setIsActive(true);

	scene3 = new UMyScene("Scene3", 100);
	scene3->setIsActive(true);

	scene4 = new UMyScene("Scene3", 100);
	scene4->setIsActive(true);

	scene5 = new UMyScene("Scene3", 100);
	scene5->setIsActive(true);

	scene6 = new UMyScene("Scene3", 100);
	scene6->setIsActive(true);
}
