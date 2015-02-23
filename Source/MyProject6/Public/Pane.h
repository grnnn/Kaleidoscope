// Pane will contain the information in which the mini screen will be display
//Including: XY position on the viewport, width and height
//			isOn or not, and what to display 
#pragma once




/**
 * 
 */
class MYPROJECT6_API Pane 
{
	float x_pos;	// x position on the view port
	float y_pos;	// y position on the view port
	float width;	// how big it's gonna look
	float height;	// how big it's gonna look
	float alphaValue;

	float Oldx_pos; 
	float Oldy_pos;
	float Oldwidth;
	float Oldheight;

	bool isOn;		// should be display or not (isTrigger?)
	bool hasBehavior;
	int behaviorType;
	bool isStartCountingWalk;
	int numberOfWalk;
	class UTexture* myTexture; //the content to be display
	

public:
	Pane();
	Pane(UTexture*);
	~Pane();

	float getX_pos();
	void setX_pos(float);

	float getY_pos();
	void setY_pos(float);

	float getAlphaValue();
	void setAlphaValue(float);

	bool getIsOn();
	void setIsOn(bool);

	float getWidth();
	void setWidth(float);

	float getHeight();
	void setHeight(float);

	bool getHasBehavior();
	void setHasBehavior(bool);

	int getBehaviorType();
	void setBehaviorType(int);

	UTexture* getMyTexture();
	void setMyTexture(UTexture*);

	void setNumberOfWalk(int);
	void updateOnBehavior();

	
};
