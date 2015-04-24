// Scene will contain an array of Panes
// More information will be in design doc

#pragma once
#include <string>
#include <vector>
#include "Pane.h"
#include "MyScene.generated.h"
using namespace std;


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class KALEIDOSCOPE_API UMyScene :public UObject
{
	GENERATED_BODY()
	string sceneName;	
	int numberOfPane;
	bool isActive;
	std::vector<Pane> paneCollection;
	
	
public:
	UMyScene();
	UMyScene(string, int);
	~UMyScene();

	void setSceneName(string);
	string getSceneName();
	Pane getPaneNumber(int);
	int getNumberOfPane();

	bool getIsActive();
	void setIsActive(bool);

	int getXpos_atPaneNumber(int);
	void setXpost_atPaneNumber(int,int);

	int getYpos_atPaneNumber(int);
	void setYpost_atPaneNumber(int,int);

	int getWidth_atPaneNumber(int);
	void setWidth_atPaneNumber(int, int);

	int getHeight_atPaneNumber(int);
	void setHeight_atPaneNumber(int, int);

	int getAlphaValue_atPaneNumber(int);
	void setAlphaValue_atPaneNumber(int, int);

	bool getIsMemory_atPaneNumber(int);
	void setIsMemory_atPaneNumber(int, bool);

	bool getHasFadeIn_atPaneNumber(int);
	void setHasFadeIn_atPaneNumber(int, bool);

	bool getFadeOut_atPaneNumber(int);
	void setFadeOut_atPaneNumber(int, bool);

	bool getIsOn_atPaneNumber(int);
	void setIsOn_atPaneNumber(int, bool);

	float getFadeInSpeed_atPaneNumber(int);
	void setFadeInSpeed_atPaneNumber(int, float);

	float getFadeOutSpeed_atPaneNumber(int);
	void setFadeOutSpeed_atPaneNumber(int, float);


	float getSpeed_atPaneNumber(int);
	void setSpeed_atPaneNumber(int, float);

	bool getHasBahavior_atPaneNumber(int);
	void setHasBehavior_atPaneNumber(int, bool);

	bool getIsSpecial_atPaneNumber(int);
	void setIsSpecial_atPaneNumber(int, bool);

	bool getIsUpper_atPaneNumber(int);
	void setIsUpper_atPaneNumber(int, bool);

	bool getIsLower_atPaneNumber(int);
	void setIsLower_atPaneNumber(int, bool);



	int getBahaviorType_atPaneNumber(int);
	void setBehaviorType_atPaneNumber(int, int,float,float);

	void setNumberOfWalk_atPaneNumber(int);
	void updateOnBehavior_atPaneNumber(int);
	void updateViewportXY_atPaneNumber(int,float, float);

	UTexture* getTexture_atPaneNumber(int);
	void setTexture_atPaneNumber(int,UTexture*);

	USceneCaptureComponent2D *getmycapture_atPaneNumber(int panNumber){ return paneCollection.at(panNumber).getMycapture(); }

	void setmycapture_atPaneNumber(int panNumber, USceneCaptureComponent2D *newcapture){
		paneCollection.at(panNumber).setMycapture(newcapture);
	}

	void turnOffCapture_atPaneNumber(int panNumber){
		paneCollection.at(panNumber).turnOffCapture();
	}
	
};
