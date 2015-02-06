// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject6.h"
#include "Pane.h"

//Default contructor
//
Pane::Pane()
{
	x_pos = 0;
	y_pos = 0;
	numberOfWalk = 0;
	isOn = false;
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

void Pane::setBehaviorType(int nNew)
{
	behaviorType = nNew;
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
		MoveRight,
		MoveLeft,
		MoveUp,
		MoveDown,
		Bigger,
		Smaller
	};
	
	//behaviorType = nBahaviorType;
	switch (behaviorType)
	{
	case MoveRight:
		x_pos++;
		break;
	case MoveLeft:
		x_pos--;
		break;
	case MoveUp:
		y_pos++;
		break;
	case MoveDown:
		x_pos++;
		break;
	case Bigger:
		if (height < 350)
		{
			y_pos = Oldy_pos - numberOfWalk;
			width = Oldwidth + numberOfWalk;
			height = Oldheight + numberOfWalk;
		}
		break;
	case Smaller:
		width--;
		height--;
		break;
	}
}

void Pane::setNumberOfWalk(int nNew)
{
	numberOfWalk = nNew;

}
