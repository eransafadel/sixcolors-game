//------------------------------INCLUDE_SECTION-----------------------------------------
#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

//-----------------------------------CONST_SECTION----------------------------------------

const int RESTART = 6;// restart a new game
const int SIZEMENU = 6;
//-------------------------class Menu_section-------------------------------------------
class Menu
{
public:
	~Menu();//dtor 
	Menu(sf::RenderWindow &window);//ctor of menu
	void startMenu(sf::RenderWindow&window);//startMenu
	void refreshMenu();//refreshMenu
	void loadPictures();//loadPictures
	void setPicture();//setPicture
	void createMenu();//createMenu
	void drawMenu(sf::RenderWindow &window)const;//drawMenu
	int isClick(const sf::Vector2i& click) const;//isClick
	sf::Color click(int i);//click
	sf::Color getColor(int i)const { return m_menu[i ].getFillColor(); }//getColor
	void setColor(int i, sf::Color color) { m_menu[i].setFillColor(color); }//setColor
	void showbuttonx(int, int, sf::RenderWindow &window)const;//showbuttonx
private:
		std::vector<sf::RectangleShape> m_menu;//vector<sf::RectangleShape that holdes the buttons
		std::vector<sf::Sprite> m_xs;//holds the xim that covers the menu
		std::vector<sf::Texture>m_texture;//m_texture
		sf::Color m_curr_color;//m_curr_color
		sf::Texture m_restart;//m_restart
		sf::Sprite m_sprite;//m_sprite
};
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

