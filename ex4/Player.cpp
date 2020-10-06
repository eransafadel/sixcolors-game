#include "Player.h"
#include "Board.h"
#include <chrono>
#include <thread>
#include <iostream>



// ----------------------------------------ctor-----------------------------------
Player::Player(Board & board)
	:mBoard(board)
{
	startPlayer();
}
//-----------------------------------------------------------------------------------

//---------refreshData----------------------------------------------------------------
//function that containes all function we need to refresh game
void Player::refreshData()
{
	m_group.clear();
	m_buffer.clear();
}
//-----------------------------------------------------------------------------------

//----------------------startPlayer --------------------------------------------------
// contains all the func we need to start the player
void Player::startPlayer()
{
	m_color = mBoard.scanDataBase(1);
	m_group.push_back(mBoard.getIndex(1));
	size = mBoard.getSizeDataBase();
}
//------------------------------------------------------------------------------------

//------------------setColor---------------------------------------------------------
// set the color if it is possible- not the color of the click and the enemy
bool Player::setColor(sf::Color colorclick, sf::Color colorE)
{
	if (colorclick == m_color|| colorclick == colorE)
		return false;
	m_color = colorclick;
	return true;
}
//----------------------------------------------------------------------------------

//------------------------turn of player-------------------------------------------
bool Player::turn(sf::RenderWindow & window, sf::Color color_enemy)
{
	if (m_color == color_enemy )
		return false;
	scanGroup();

	drawGroup(window);
	window.display();
	return true;
}
//----------------------------------------------------------------------------------------

//---------------scanGroup--------------------------------------------------------------
// scan if the curr is in group if so do nothing else push him to group
void Player::scanGroup()
{
	for (int i = 0; i < m_group.size(); i++)
	{
		m_buffer.clear();
		 mBoard.getSameColorNeigb(m_group[i], m_color, m_buffer);
		for (int j = 0; j < m_buffer.size(); j++)
			if(helperScanGroup(m_buffer[j]))
				m_group.push_back(m_buffer[j]);
	}
}
//---------------------------------------------------------------------------------------

//--------------------drawGroup--------------------------------------------------------
//------------drawGroup of player
void Player::drawGroup(sf::RenderWindow & window)
{
		for (int i = 0; i < m_group.size(); i++)
			mBoard.drawAllGroups(m_group[i], m_color);

		
}
//-------------------------------------------------------------------------------------------




//------------------------------------ ~Player-------------------------------------------
Player::~Player()
{
}
void Player::flickeringColor(sf::RenderWindow & window)
{
	for (int i = 0; i < m_group.size(); i++)
		mBoard.drawAllGroups(m_group[i], sf::Color::Black);

}
//----------------------------------------------------------------------------------------
