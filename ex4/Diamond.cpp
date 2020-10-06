#include "Diamond.h"


//--------------------Diamond CTOR-------------------------------------------------------
Diamond::Diamond(const sf::Vector2f &left,const sf::Vector2f& up,const sf::Vector2f& right, const sf::Vector2f &down)
	:Shape(left,up, right),m_down(down)
{
	m_circle.setPointCount(SIZE);
	m_circle.setPoint(0, m_left);
	m_circle.setPoint(1, m_up);
	m_circle.setPoint(2, m_right);
	m_circle.setPoint(3, m_down);
}
//----------------------------------------------------------------------------------------

//------------ ~Diamond DTOR--------------------------------------------------------------
Diamond::~Diamond()
{
}
//----------------------------------------------------------------------------------------

//---------------------getDown-----------------------------------------------------------
// GET THE  woun cord of diamond
sf::Vector2f Diamond::getDown() const
{
	return m_down;
}
//---------------------------------------------------------------------------------------

