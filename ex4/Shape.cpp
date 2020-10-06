#include "Shape.h"




//----------------------ctor pf shape------------------------------------------------------
Shape::Shape(const sf::Vector2f & left, const sf::Vector2f & up, const sf::Vector2f & right)
	:m_left(left), m_up(up), m_right(right)
{
	
}
//-------------------------------------------------------------------------------------------


//---------------------getLeft- get the left cor--------------------------------------------
sf::Vector2f Shape::getLeft() const
{
	return m_left;
}
//-------------------------------------------------------------------------------------------

//------------------getUp get the up cor-----------------------------------------------------------
sf::Vector2f Shape::getUp() const
{
	return m_up;
}
//------------------------------------------------------------------------------------------

//-----------------getRight ----------------------------------------------------------------
sf::Vector2f Shape::getRight() const
{
	return m_right;
}
//-------------------------------------------------------------------------------------------

//-----------------------getCenter-------------------------------------------------------
sf::Vector2f Shape::getCenter() const
{
	return sf::Vector2f({ m_up.x, m_left.y });
}
//--------------------------------------------------------------------------------------------

//-------------show the shape---------------------------------------------------------------
void Shape::show(sf::RenderWindow & window)
{
	window.draw(m_circle);
}
//-------------------------------------------------------------------------------------------


//------------------draw the shape-------------------------------------------------------------------
void Shape::draw(sf::RenderWindow & window)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6); // distribution in range [1, 6]
	

	switch (dist6(rng))
	{
	case 1:
		m_circle.setFillColor(sf::Color::Red);
		break;
	case 2:
		m_circle.setFillColor(sf::Color::Yellow);
		break;
	case 3:
		m_circle.setFillColor(sf::Color::Green);
		break;
	case 4:
		m_circle.setFillColor(sf::Color::Blue);
		break;
	case 5:
		m_circle.setFillColor(sf::Color::Magenta);
		break;
	case 6:
		m_circle.setFillColor({ 237,117,12 });
		break;

	default:
		break;
	}

	window.draw(m_circle);
	
}
//-----------------------------------------------------------------------------------------------------------------

//---------------------------drawOfSpecificColor-----------------------------------------------------------------
//setFillColor on our covex_shape
void Shape::drawOfSpecificColor(sf::RenderWindow & window, sf::Color color)
{
	m_circle.setFillColor(color);
	window.display();


	//m_circle.setFillColor(color);
	/*m_circle.setOutlineThickness(0.5);
	m_circle.setOutlineColor({128,128,128});*/
	
	
}
void Shape::drawOfSpecificColorBlack(sf::RenderWindow & window, sf::Color)
{

	m_circle.setFillColor(sf::Color::Black);
	window.display();
}
//-------------------------------------------------------------------------------------------------------------

//------------------getGlobalBounds---------------------------------------------------------------
sf::FloatRect Shape::getGlobalBounds()
{
	return m_circle.getGlobalBounds();
}
//-----------------------------------------------------------------------------------------------------

//------------------------getConvex------------------------------------------------------------------
sf::ConvexShape Shape::getConvex()
{
	return m_circle;
}
//------------------------------------------------------------------------------------------------------


