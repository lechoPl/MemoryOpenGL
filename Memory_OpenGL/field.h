#ifndef FIELD_DATA
#define FIELD_DATA

#include <GLFW\glfw3.h>

class CField
{
protected:
	int m_typeId; // if -1 - hide; other sign id; color = typeId + 2
	unsigned m_x;
	unsigned m_y;
	bool m_showSign = false; // show back or sign

	//to animation
	double m_lastTime;
	bool m_isAnimationStarted = false;
	bool m_isHideAnimation = false;

public:
	static const float animationTime;

	CField();
	CField(unsigned x, unsigned y, unsigned typeId);
	
	virtual void setTypeId(int n) { m_typeId = n; }
	virtual void setX(unsigned x) { m_x = x; }
	virtual void setY(unsigned y) { m_y = y; }

	virtual int getTypeId() const { return m_typeId; }
	
	virtual void showSign(); 
	virtual void hideSign();
	virtual bool isSignVisable() { return m_showSign; }

	virtual bool isAnimationStarted() { return m_isAnimationStarted; }
	virtual bool isHideAnimation() { return m_isHideAnimation; }
	virtual float getAnimationTime();
};

#endif