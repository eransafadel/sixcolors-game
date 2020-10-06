//------------------------------INCLUDE_SECTION-----------------------------------------
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Board.h"//matrix
#include "Menu.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
//-----------------------------------CONST_SECTION--------------------------------------
const int  RESTART2 = 6;
const int PERCENT = 100;
const int MAX_VAL_TO_WIN = 50;
//--------------------------------------------------------------------------------------

//-------------class Controller_Section-------------------------------------------------
class Controller
{
public:
	~Controller();//Dtor
	static Controller& getInstance();// RETURN_THE_INSTANCE_OF the singleton of Controller
	Controller(const Controller&) = delete; // COPY CTOR AND ASSIGMENT OPERATOR isn't need
	Controller& operator=(const Controller&) = delete;// to stop user copy

	void restartGame();//func that  handle  restartGame 
	void playerWin();//playerWin
	void end();// end the game -clear all database on game
	void enemyPlayerText();//enemyPlayer
	void run();//run
	void handleEvents();//handleEvents
	void showScore();// show score 
private:
	Controller();//Ctor on private


	sf::RenderWindow m_window;//m_window
	Board m_board;//Board
	Menu m_menu;//m_menu
	Player m_player;//m_player
	Enemy m_enemy;//m_enemy
	
	//----------------------Text-------------------------------
	sf::Font m_font;//m_font
	sf::Text m_text_enemy;//m_text_enemy
	sf::Text m_text_player;//m_text_player
	std::string m_str_score_enemy;//m_str_score_enemy
	std::string m_str_score_player;//m_str_score_player
	
};
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

