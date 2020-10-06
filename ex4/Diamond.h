//------------------------------INCLUDE_SECTION-----------------------------------------
#pragma once
#include "Shape.h"
//----------------------------CONST_SECTION-----------------------------------------------
const int SIZE = 4;


//-------------class Diamond_Section--------------------------------------------------------
class Diamond :public Shape
{
public:
	Diamond(const sf::Vector2f &left,  const sf::Vector2f& up,const sf::Vector2f& right, const sf::Vector2f &down);
	~Diamond();
	sf::Vector2f getDown()const;
private:
	
	sf::Vector2f m_down;

};
//----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------

