//------------------------------INCLUDE_SECTION-----------------------------------------
#pragma once
#include <SFML/Graphics.hpp>
#include<string>
#include <vector>
//-----------------------------------CONST_SECTION-----------------------------------------
const std::vector <sf::Color> m_colors{ sf::Color::Red,sf::Color::Yellow,// const vector of colors
sf::Color::Green,sf::Color::Blue, { 237,117,12 }, sf::Color::Magenta };//

//-------------------------class Entity_section-------------------------------------------
class Entity
{
public:
	Entity();//ctor of Entity
	 virtual ~Entity()=0{}//dtor of enemy
	bool helperScanGroup(int)const;//check if the obj alreay in group
	int getIndexByColor(const sf::Color&)const;//getIndexByColor
	virtual void drawGroup(sf::RenderWindow &window) = 0;//drawGroup
	virtual float caclConquer()const = 0;////calculate how much of area we conqer 
protected:

	sf::Color m_color;//m_color
	std::vector <int> m_group;// vector that hold the group 
	std::vector<int>m_buffer;// buffer 
	int m_current_index = 0;//curr index

};
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

