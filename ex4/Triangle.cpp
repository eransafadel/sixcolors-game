#include "Triangle.h"

//--------------------------ctor of triangle---------------------------------------------------------
Triangle::Triangle(const sf::Vector2f  left, const sf::Vector2f  up, const sf::Vector2f  right)
	:Shape(left,up,right)
{
	m_circle.setPointCount(3);
	m_circle.setPoint(0,m_left);
	m_circle.setPoint(1, m_up);
	m_circle.setPoint(2, m_right);

}
//-------------------------------------------------------------------------------------------------

//------------------------dtor of triangle-------------------------------------------------------
Triangle::~Triangle()
{
}
//-----------------------------------------------------------------------------------------------

