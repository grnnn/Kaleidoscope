// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MyProject6.h"
#include "MyProject6GameMode.h"
#include "MyProject6Character.h"
//#include "MyHUD.h"
AMyProject6GameMode::AMyProject6GameMode(const FObjectInitializer& ObjectInitializer)
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
	
	//Use Blueprint custom HUD
	//static ConstructorHelpers::FObjectFinder<UClass> PlayerHUDBPClass(TEXT("Class'/Game/Blueprints/HUD1.HUD1_C'"));
	
	
	HUDClass = PlayerHUDBPClass.Object;
	
	
}
