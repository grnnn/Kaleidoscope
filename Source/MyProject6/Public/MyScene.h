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
class MYPROJECT6_API UMyScene :public UObject
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

	bool getIsOn_atPaneNumber(int);
	void setIsOn_atPaneNumber(int, bool);

	bool getHasBahavior_atPaneNumber(int);
	void setHasBehavior_atPaneNumber(int, bool);

	int getBahaviorType_atPaneNumber(int);
	void setBehaviorType_atPaneNumber(int, int);

	void setNumberOfWalk_atPaneNumber(int);
	void updateOnBehavior_atPaneNumber(int);

	UTexture* getTexture_atPaneNumber(int);
	void setTexture_atPaneNumber(int,UTexture*);


	
};
