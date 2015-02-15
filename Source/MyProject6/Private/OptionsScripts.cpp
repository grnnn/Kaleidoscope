// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject6.h"
#include "OptionsScripts.h"
#include "Runtime/Engine/Public/AudioDevice.h"

UOptionsScripts::UOptionsScripts()
{
}

UOptionsScripts::~UOptionsScripts()
{
}

void UOptionsScripts::ChangeSoundClassVolume(FString ClassName, float Volume)
{
	UE_LOG(LogTemp, Warning, TEXT("Called volume change"));
	FAudioDevice* Device = GEngine->GetAudioDevice();
	if (!Device)
	{
		return;
	}

	USoundClass* SoundClass = NULL;
	for (TMap<USoundClass*, FSoundClassProperties>::TIterator It(Device->SoundClasses); It; ++It)
	{
		USoundClass* ThisSoundClass = It.Key();
		if (ThisSoundClass && ThisSoundClass->GetFullName().Find(ClassName) != INDEX_NONE)
		{
			SoundClass = ThisSoundClass;
			break;
		}
	}

	if (SoundClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Changed Volume"));
		//SoundClass->Properties.Volume = Volume;
		Device->SetClassVolume(SoundClass, Volume);
	}
}