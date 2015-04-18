// Fill out your copyright notice in the Description page of Project Settings.

#include "Kaleidoscope.h"
#include "Pane.h"

//Default contructor
//
Pane::Pane()
{
	x_pos = 0;
	y_pos = 0;

	baseX = 1280;
	baseY = 720;
	viewportX = 0;
	viewportY = 0;
	

	alphaValue = 0;
	hasFadeIn = false;
	isMemory = false;
	numberOfWalk = 0;
	isOn = false;
	fadeOut = false;
	isStartCountingWalk = false;
}

//Contructor with UTexture
//
Pane::Pane(UTexture* n)
{
	myTexture = n;
}

Pane::~Pane()
{
}


//Below are a lot of SET and GET functions for each variable in Pane's class
//nothing fancy
float Pane::getX_pos()
{
	return x_pos;
}

void Pane::setX_pos(float nNew)
{
	x_pos = nNew;
	Oldx_pos = x_pos;
}

float Pane::getY_pos()
{
	return y_pos;
}

void Pane::setY_pos(float nNew)
{
	y_pos = nNew;
	Oldy_pos = y_pos;
}

float Pane::getAlphaValue()
{
	return alphaValue;
}

void Pane::setAlphaValue(float nNew)
{
	alphaValue = nNew;
}

bool Pane::getIsOn()
{
	return isOn;
}

void Pane::setIsOn(bool nNew)
{
	isOn = nNew;
}

float Pane::getWidth()
{
	return width;
}

void Pane::setWidth(float nNew)
{
	width = nNew;
	Oldwidth = width;
}

float Pane::getHeight()
{
	return height;
}

void Pane::setHeight(float nNew)
{
	height = nNew;
	Oldheight = height;
}


bool Pane::getIsMemory()
{
	return isMemory;
}

void Pane::setIsMemory(bool nNew)
{
	isMemory = nNew;
}


bool Pane::getHasFadeIn()
{
	return hasFadeIn;
}

void Pane::setHasFadeIn(bool nNew)
{
	hasFadeIn = nNew;
}

bool Pane::getFadeOut()
{
	return fadeOut;
}

void Pane::setFadeOut(bool nNew)
{
	fadeOut = nNew;
}


bool Pane::getHasBehavior()
{
	return hasBehavior;
}

void Pane::setHasBehavior(bool nNew)
{
	hasBehavior = nNew;
}

int Pane::getBehaviorType()
{
	return behaviorType;
}

void Pane::setBehaviorType(int nNew,float x_new,float y_new)
{
	behaviorType = nNew;
	x_dest = x_new;
	y_dest = y_new;
}

UTexture* Pane::getMyTexture()
{
	return myTexture;
}

void Pane::setMyTexture(UTexture* nNew)
{
	myTexture = nNew;
}

void Pane::updateOnBehavior()
{
	enum local
	{
		None,
		Custom,
		FirstPane,
		LastPane
	};
	isStartCountingWalk = true;
	//behaviorType = nBahaviorType;
	
	float limitHeight;

	switch (behaviorType)
	{
	case None:
		isStartCountingWalk = false;
		break;
	case Custom:
		if (x_pos < x_dest)
			x_pos++;
		else if (x_pos > x_dest)
			x_pos--;

		if (y_pos < y_dest)
			y_pos++;
		else if (y_pos > y_dest)
			y_pos--;
		
		
		break;
	
	case FirstPane:
		limitHeight = getOffsetValue(420, viewportY, baseY);
		if (height <= limitHeight)
		{
			height = Oldheight + numberOfWalk / 5;
			width = Oldwidth + numberOfWalk/4;
			x_pos = Oldx_pos - numberOfWalk/2;



		}
		break;
	case LastPane:
		limitHeight = getOffsetValue(100, viewportY, baseY);
		if (height >= limitHeight)
		{
			height = Oldheight - numberOfWalk / 5;
			width = Oldwidth - numberOfWalk / 4;
			x_pos = Oldx_pos - numberOfWalk / 2;
			y_pos = Oldy_pos + numberOfWalk / 4;


		}
	}
	
}

void Pane::setNumberOfWalk(int nNew)
{
	if (isStartCountingWalk)
		numberOfWalk = nNew;

}

void Pane::updateViewportXY(float x,float y)
{
	viewportX = x;
	viewportY = y;
}

float Pane::getOffsetValue(float inputValue, float startValue, float baseValue)
{
	float ratio = startValue / baseValue;
	return inputValue * ratio;
}
