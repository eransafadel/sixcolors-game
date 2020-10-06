//------------------------------INCLUDE_SECTION-----------------------------------------
#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <random>

//---------class Shape_section----------------------------------------------------------
class Shape
{
public:
	Shape(const sf::Vector2f &left, const sf::Vector2f &up, const sf::Vector2f &right);//ctor of shape
	virtual ~Shape(){}//dtor of shape
	sf::Vector2f getLeft()const;//getLeft cor of shape
	sf::Vector2f getUp()const;//getUp cor of shape
	sf::Vector2f getRight()const;//getRight cor of shape
	sf::Vector2f getCenter()const;//getCenter cor of shape
	void show(sf::RenderWindow & window);//show the shape
	const sf::Color& getColor()const { return m_circle.getFillColor(); }//getColor
	void setColor(sf::Color color) { m_circle.setFillColor(color); }//setColor
	sf::FloatRect getGlobalBounds();// get the getGlobalBounds of shape
	sf::ConvexShape getConvex();//getConvex
	unsigned int getId()const { return m_id; }//getId
	void setId(unsigned int id) { m_id = id; }//setId
	void draw(sf::RenderWindow & window);//draw the shape 
	void drawOfSpecificColor(sf::RenderWindow & window, sf::Color);//drawOfSpecificColor
	void drawOfSpecificColorBlack(sf::RenderWindow & window, sf::Color);//drawOfSpecificColor

protected:

	unsigned int m_id;// the id of shape
	sf::Vector2f m_left;//left cordinate
	sf::Vector2f m_up;//up cordinate
	sf::Vector2f m_right;//right cordinate
	sf::ConvexShape m_circle;//convex of shape
};
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

