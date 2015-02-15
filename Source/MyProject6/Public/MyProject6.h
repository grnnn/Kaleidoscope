// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#ifndef __MYPROJECT6_H__
#define __MYPROJECT6_H__

#include "Engine.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(YourLog, Log, All);

//Logging during game startup
DECLARE_LOG_CATEGORY_EXTERN(YourInit, Log, All);

//Logging for your AI system
DECLARE_LOG_CATEGORY_EXTERN(YourAI, Log, All);

//Logging for Critical Errors that must always be addressed
DECLARE_LOG_CATEGORY_EXTERN(YourCriticalErrors, Log, All);


#endif
