#include "field.h"

const float CField::animationTime = 0.800;

CField::CField() : m_typeId(-1), m_x(0), m_y(0) { }
CField::CField(unsigned x, unsigned y, unsigned typeId) : m_x(x), m_y(y), m_typeId(typeId) { }
void CField::showSign()
{
	m_lastTime = glfwGetTime();
	m_isAnimationStarted = true;
	m_isHideAnimation = false;

	m_showSign = true;
}
void CField::hideSign()
{
	m_lastTime = glfwGetTime();
	m_isAnimationStarted = true;
	m_isHideAnimation = true;

	m_showSign = false;
}
float CField::getAnimationTime()
{
	if (!m_isAnimationStarted)
		return 1.f;

	float temp = static_cast<float>(glfwGetTime() - m_lastTime) / animationTime;

	if (temp >= 1.0)
	{
		temp = 1.0;
		m_isAnimationStarted = false;
	}
	return temp;
}