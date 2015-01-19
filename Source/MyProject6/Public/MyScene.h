// Scene will contain an array of Panes
// More information will be in design doc

#pragma once
#include <string>
#include <vector>
#include "Pane.h"
using namespace std;

typedef int(*fptr)();
/**
 * 
 */
class MYPROJECT6_API MyScene
{
	string sceneName;	
	int numberOfPane;
	bool isActive;
	std::vector<Pane> paneCollection;
	int(*updateFunction)();
	
public:
	MyScene();
	MyScene(string, int);
	~MyScene();

	void setSceneName(string);
	string getSceneName();
	Pane getPaneNumber(int);
	bool getIsActive();
	void setIsActive(bool);

	int getXpos_atPaneNumber(int);
	void setXpost_atPaneNumber(int,int);

	int getYpos_atPaneNumber(int);
	void setYpost_atPaneNumber(int,int);

	bool getIsOn_atPaneNumber(int);
	void setIsOn_atPaneNumber(int, bool);


	UTexture* getTexture_atPaneNumber(int);
	void setTexture_atPaneNumber(int,UTexture*);

	void setBehavior_atPaneNumber(int, int(*functocall)());
	fptr getBehavior_atPaneNumber(int);

};
