// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject6.h"
#include "MyScene.h"

//Default contructor
MyScene::MyScene()
{

}

//Contructor with scene name, and number of Pane in this scene
MyScene::MyScene(string name, int size)
{
	sceneName = name;
	numberOfPane = size;
	for (int i = 0; i < size; i++)
		paneCollection.push_back(Pane());
}

MyScene::~MyScene()
{
}

//Below are GET and SET functions for each variable in MyScene's class and Pane's class
//
string MyScene::getSceneName()
{
	return sceneName;
}

void MyScene::setSceneName(string newSceneName)
{
	sceneName = newSceneName;
}
Pane MyScene::getPaneNumber(int num)
{
	return paneCollection.at(num);
}

bool MyScene::getIsActive()
{
	return isActive;
}

void MyScene::setIsActive(bool isAct)
{
	isActive = isAct;
}

int MyScene::getXpos_atPaneNumber(int panNumber)
{
	return paneCollection.at(panNumber).getX_pos();
}

void MyScene::setXpost_atPaneNumber(int panNumber, int nNew)
{
	return paneCollection.at(panNumber).setX_pos(nNew);
}

int MyScene::getYpos_atPaneNumber(int panNumber)
{
	return paneCollection.at(panNumber).getY_pos();
}

void MyScene::setYpost_atPaneNumber(int panNumber, int nNew)
{
	return paneCollection.at(panNumber).setY_pos(nNew);
}

bool MyScene::getIsOn_atPaneNumber(int panNumber)
{
	return paneCollection.at(panNumber).getIsOn();
}

void MyScene::setIsOn_atPaneNumber(int panNumber, bool nNew)
{
	return paneCollection.at(panNumber).setIsOn(nNew);
}

UTexture* MyScene::getTexture_atPaneNumber(int panNumber)
{
	return paneCollection.at(panNumber).getMyTexture();
}
void MyScene::setTexture_atPaneNumber(int panNumber, UTexture* nNew)
{
	paneCollection.at(panNumber).setMyTexture(nNew);

}