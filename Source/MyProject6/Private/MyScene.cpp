// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject6.h"
#include "MyScene.h"

//Default contructor
UMyScene::UMyScene()
{

}

//Contructor with scene name, and number of Pane in this scene
UMyScene::UMyScene(string name, int size)
{
	sceneName = name;
	numberOfPane = size;
	for (int i = 0; i < size; i++)
		paneCollection.push_back(Pane());
}

UMyScene::~UMyScene()
{
}

//Below are GET and SET functions for each variable in MyScene's class and Pane's class
//
string UMyScene::getSceneName()
{
	return sceneName;
}

void UMyScene::setSceneName(string newSceneName)
{
	sceneName = newSceneName;
}
int UMyScene::getNumberOfPane()
{
	return numberOfPane;
}

Pane UMyScene::getPaneNumber(int num)
{
	return paneCollection.at(num);
}

bool UMyScene::getIsActive()
{
	return isActive;
}

void UMyScene::setIsActive(bool isAct)
{
	isActive = isAct;
}

int UMyScene::getXpos_atPaneNumber(int panNumber)
{
	return paneCollection.at(panNumber).getX_pos();
}

void UMyScene::setXpost_atPaneNumber(int panNumber, int nNew)
{
	return paneCollection.at(panNumber).setX_pos(nNew);
}

int UMyScene::getYpos_atPaneNumber(int panNumber)
{
	return paneCollection.at(panNumber).getY_pos();
}

void UMyScene::setYpost_atPaneNumber(int panNumber, int nNew)
{
	return paneCollection.at(panNumber).setY_pos(nNew);
}

int UMyScene::getWidth_atPaneNumber(int panNumber)
{
	return paneCollection.at(panNumber).getWidth();
}

void UMyScene::setWidth_atPaneNumber(int panNumber, int nNew)
{
	return paneCollection.at(panNumber).setWidth(nNew);
}

int UMyScene::getHeight_atPaneNumber(int panNumber)
{
	return paneCollection.at(panNumber).getHeight();
}

void UMyScene::setHeight_atPaneNumber(int panNumber, int nNew)
{
	return paneCollection.at(panNumber).setHeight(nNew);
}

int UMyScene::getAlphaValue_atPaneNumber(int panNumber)
{
	return paneCollection.at(panNumber).getAlphaValue();
}

void UMyScene::setAlphaValue_atPaneNumber(int panNumber, int nNew)
{
	return paneCollection.at(panNumber).setAlphaValue(nNew);
}


bool UMyScene::getIsMemory_atPaneNumber(int panNumber)
{
	return paneCollection.at(panNumber).getIsMemory();
}

void UMyScene::setIsMemory_atPaneNumber(int panNumber, bool nNew)
{
	return paneCollection.at(panNumber).setIsMemory(nNew);
}


bool UMyScene::getHasFadeIn_atPaneNumber(int panNumber)
{
	return paneCollection.at(panNumber).getHasFadeIn();
}

void UMyScene::setHasFadeIn_atPaneNumber(int panNumber, bool nNew)
{
	return paneCollection.at(panNumber).setHasFadeIn(nNew);
}



bool UMyScene::getIsOn_atPaneNumber(int panNumber)
{
	return paneCollection.at(panNumber).getIsOn();
}

void UMyScene::setIsOn_atPaneNumber(int panNumber, bool nNew)
{
	return paneCollection.at(panNumber).setIsOn(nNew);
}

bool UMyScene::getHasBahavior_atPaneNumber(int panNumber)
{
	return paneCollection.at(panNumber).getHasBehavior();
}

void UMyScene::setHasBehavior_atPaneNumber(int panNumber, bool nNew)
{
	return paneCollection.at(panNumber).setHasBehavior(nNew);
}

int UMyScene::getBahaviorType_atPaneNumber(int panNumber)
{
	return paneCollection.at(panNumber).getBehaviorType();
}

void UMyScene::setBehaviorType_atPaneNumber(int panNumber, int nNew)
{
	return paneCollection.at(panNumber).setBehaviorType(nNew);
}

UTexture* UMyScene::getTexture_atPaneNumber(int panNumber)
{
	return paneCollection.at(panNumber).getMyTexture();
}
void UMyScene::setTexture_atPaneNumber(int panNumber, UTexture* nNew)
{
	paneCollection.at(panNumber).setMyTexture(nNew);

}


void UMyScene::setNumberOfWalk_atPaneNumber(int nNew)
{
	
	for (int i = 0; i < numberOfPane; i++)
		paneCollection.at(i).setNumberOfWalk(nNew);
	
}
void UMyScene::updateOnBehavior_atPaneNumber(int panNumber)
{
	paneCollection.at(panNumber).updateOnBehavior();
}
void UMyScene::updateViewportXY_atPaneNumber(int panNumber,float x,float y)
{
	paneCollection.at(panNumber).updateViewportXY(x,y);
}



