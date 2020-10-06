#include "Menu.h"
#include <iostream>

//----------CTOR OF MENU-----------------------------------------------------------------
Menu::Menu(sf::RenderWindow & window)
	:m_menu(SIZEMENU),m_texture(SIZEMENU +1),m_xs(SIZEMENU +1)
{
	startMenu(window);
}
//--------------------------------------------------------------------------------------

//----------------startMenu-------------------------------------------------------------
// all functions we need to start menu------------------------------------------------ 
void Menu::startMenu(sf::RenderWindow&window)
{
	
	createMenu();
	loadPictures();
	setPicture();
	drawMenu(window);
}
//---------------------------------------------------------------------------------------

//-------------------------refreshMenu---------------------------------------------------
// clear all data base of menu-----------------------------------------------------------
void Menu::refreshMenu()
{
	m_texture.clear();
	m_menu.clear();
	m_xs.clear();

}
//----------------------------------------------------------------------------------------


//-----------------dtor of menu-----------------------------------------------------------
Menu::~Menu()
{
}
//----------------------------------------------------------------------------------------


//----------------loadPictures-----------------------------------------------------------
void Menu::loadPictures()
{
	if (!(m_texture[0].loadFromFile("red.png")))//loading pic to texture
		std::cout << "cannot allocate the picture";
	if (!(m_texture[1].loadFromFile("yellow.png")))
		std::cout << "cannot allocate the picture";
	if (!(m_texture[2].loadFromFile("green.png")))
		std::cout << "cannot allocate the picture";
	if (!(m_texture[3].loadFromFile("blue.png")))
		std::cout << "cannot allocate the picture";
	if (!(m_texture[4].loadFromFile("orange.png")))
		std::cout << "cannot allocate the picture";
	if (!(m_texture[5].loadFromFile("purple.png")))
		std::cout << "cannot allocate the picture";
	if (!m_texture[6].loadFromFile("restart1.png"))
		std::cout << "cannot allocate the picture";

}
//---------------------------------------------------------------------------------------


//----------------------setPicture-------------------------------------------------------
// set pictures to m_xs------------------------------------------------------------------
void Menu::setPicture()
//set pic from texture to sprite 
{
	for (int i = 0; i < m_xs.size()-1; i++)
	{
		m_xs[i].setTexture(m_texture[i]);
		m_xs[i].setPosition(sf::Vector2f{ 300.0f + 24.0f *i ,700.0f });
	}
	m_xs[m_xs.size() - 1].setTexture(m_texture[m_xs.size() - 1]);
	m_xs[m_xs.size() - 1].setPosition(sf::Vector2f{ 10.0f,10.0f });
}
//--------------------------------------------------------------------------------------

//-------------------createMenu--------------------------------------------------------
// create the menu 
void Menu::createMenu()
{
	for (int i = 0; i < m_menu.size(); i++)
		m_menu[i].setPosition(sf::Vector2f{ 300.0f + 24.0f *i ,700.0f });


	for (int i = 0; i < m_menu.size(); i++)
		m_menu[i].setSize(sf::Vector2f{ 24.0f, 24.0f });
	m_menu[0].setFillColor(sf::Color::Red);
	m_menu[1].setFillColor(sf::Color::Yellow);
	m_menu[2].setFillColor(sf::Color::Green);
	m_menu[3].setFillColor(sf::Color::Blue);
	m_menu[4].setFillColor({ 237,117,12 });
	m_menu[5].setFillColor(sf::Color::Magenta);
}
//----------------------------------------------------------------------------------------

//-----------------drawMenu--------------------------------------------------------------
// show the menu on screeen
void Menu::drawMenu(sf::RenderWindow &window) const
{
	for (int i = 0; i < m_menu.size(); i++)
		window.draw(m_menu[i]);
	window.draw(m_xs[SIZEMENU]);
}
//------------------------------------------------------------------------------------


//----------------------------------isClick--------------------------------------------
// check werher is  the click preesed 
int Menu::isClick(const sf::Vector2i & click) const
{
	if (m_xs[RESTART].getGlobalBounds().contains(static_cast<sf::Vector2f>(click)))
		return RESTART;
	for (int i = 0; i < m_menu.size(); i++)
	{
		if (m_menu[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(click)))
			return i;
	}
	return -1;// not found
}
//-----------------------------------------------------------------------------------

//------------------------click--------------------------------------------------------
//return the color of the button
sf::Color Menu::click(int i)
{
	return m_menu[i].getFillColor();
			
}
//--------------------------------------------------------------------------------------

//------------------------showbuttonx-----------------------------------------------------
//showbuttonx on screen
void Menu::showbuttonx(int index_color_player, int index_color_enemy, sf::RenderWindow & window)const
{
	window.draw(m_xs[index_color_player]);
	window.draw(m_xs[index_color_enemy]);

}
//--------------------------------------------------------------------------------------
