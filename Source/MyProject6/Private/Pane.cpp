// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject6.h"
#include "Pane.h"

//Default contructor
//
Pane::Pane()
{
	x_pos = 0;
	y_pos = 0;

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
}

float Pane::getY_pos()
{
	return y_pos;
}

void Pane::setY_pos(float nNew)
{
	y_pos = nNew;
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
}

float Pane::getHeight()
{
	return height;
}

void Pane::setHeight(float nNew)
{
	height = nNew;
}

UTexture* Pane::getMyTexture()
{
	return myTexture;
}

void Pane::setMyTexture(UTexture* nNew)
{
	myTexture = nNew;
}