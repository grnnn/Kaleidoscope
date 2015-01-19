// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MyProject6.h"


IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, MyProject6, "MyProject6" );
//General Log
DEFINE_LOG_CATEGORY(YourLog);

//Logging during game startup
DEFINE_LOG_CATEGORY(YourInit);

//Logging for your AI system
DEFINE_LOG_CATEGORY(YourAI);

//Logging for Critical Errors that must always be addressed
DEFINE_LOG_CATEGORY(YourCriticalErrors);