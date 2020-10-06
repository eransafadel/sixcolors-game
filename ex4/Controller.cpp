#include "Controller.h"

//-------------------restartGame------------------------------------------------------
// function that handle with restartGame contains all the func we need to restartGame
void Controller::restartGame()
{
	m_board.refreshData();
	m_board.startGame();
	m_menu.startMenu(m_window);
	m_player.refreshData();
	m_player.startPlayer();
	m_enemy.refreshData();
	m_enemy.startEnemy();

}
//--------------------------------------------------------------------------------------


//------------------------------playerWin-----------------------------------------------
//--------------- function that handle if the player is win---------------------------
void Controller::playerWin()
{
	m_window.clear();
	m_text_player.setFillColor(sf::Color::Green);
	m_text_player.setPosition({ 350.0f,350.0f });
	m_text_player.setString("Congratulations!/n you win");
	m_window.draw(m_text_player);
	m_window.display();
	sf::sleep(sf::milliseconds(5000));
	end();
	
}
//---------------------------------------------------------------------------------------

//---------------- function that handle if the game is over-----------------------------
void Controller::end()
{
	m_board.refreshData();
	m_player.refreshData();
	m_enemy.refreshData();
	m_menu.refreshMenu();
	exit(EXIT_SUCCESS);
}
//---------------------------------------------------------------------------------------

//-------------------enemyPlayerText---------------------------------------------------
//----------------print if enemy is win------------------------------------------------
void Controller::enemyPlayerText()
{
	m_window.clear();
	m_text_enemy.setFillColor(sf::Color::Red);
	m_text_enemy.setPosition({ 300.0f,350.0f });
	m_text_enemy.setString("you lose");
	m_text_enemy.setCharacterSize(100);
	m_window.draw(m_text_enemy);
	m_window.display();
	sf::sleep(sf::milliseconds(5000));
	end();

}
//-------------------------------------------------------------------------------------

//------------------run-----------------------------------------------------------------
// run the game 
void Controller::run()
{	
	
		m_window.display();
	
	//function that run while window open 
	while (m_window.isOpen())
	{
		m_window.clear();
		m_board.showDataBase(m_window);
		m_menu.drawMenu(m_window);
		m_menu.showbuttonx(m_player.getIndexByColor(m_player.getColor()),
			m_enemy.getIndexByColor(m_enemy.getColor()),m_window);
		showScore();
		m_window.display();
		handleEvents();

	}


}
//------------------handleEvents-------------------------------------------------------
//---------- handleEvents of game 
void Controller::handleEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			end();
			break;
		}
		
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
		int index = m_menu.isClick(mousePos);
		if (index == RESTART)
		{
			restartGame();
			return;
		}
		if (index == -1)
			return;
		if (!m_player.setColor(m_menu.click(index), m_enemy.getColor()))
			return;
		if(m_player.turn(m_window,m_enemy.getColor())) //fill the group
			m_enemy.turn(m_window, m_player.getColor());

		sf::sleep(sf::milliseconds(400));

	
	}
}
//-------------------------------------------------------------------------------------

//-----------------showScore-------------------------------------------------------------
//-----------showScore on screen 
void Controller::showScore()
{
	m_str_score_player = std::to_string(m_player.caclConquer()*PERCENT);
	if ((m_player.caclConquer() * PERCENT) >= MAX_VAL_TO_WIN)
		playerWin();

	m_str_score_enemy = std::to_string(m_enemy.caclConquer()*PERCENT);
	if ((m_enemy.caclConquer() * PERCENT) >= MAX_VAL_TO_WIN)
		enemyPlayerText();

	
	m_text_player.setString("player: " + m_str_score_player + "%");
	m_window.draw(m_text_player);
	m_text_enemy.setString("computer: " + m_str_score_enemy+ "%");
	m_window.draw(m_text_enemy);
}
//----------------------------------------------------------------------------------------

//------------------Controller -CTOR------------------------------------------------------
Controller::Controller()
	:m_window(sf::VideoMode(800, 800), "window",
		sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize),
	m_board(m_window),m_menu(m_window),m_player(m_board),m_enemy(m_board)

{
	if (!m_font.loadFromFile("font.ttf"))
		std::cout << "EROOR, cannot find the file ";
	m_text_player.setFont(m_font);
	m_text_enemy.setFont(m_font);
	m_text_player.setFillColor({ 215, 223, 46 });
	m_text_enemy.setFillColor({ 215, 223, 46 });
	m_text_enemy.setScale(0.5, 0.5);
	m_text_player.setScale(0.5, 0.5);
	m_text_player.setPosition(sf::Vector2f{ 100.0f,700.0f });
	m_text_enemy.setPosition(sf::Vector2f{ 540.0f,700.0f });
}

//-----------------------------------------------------------------------------------------

//--------------- ~Controller  DTOR---------------------------------------------------------
Controller::~Controller()
{
}
//-----------------------------------------------------------------------------------------

//-----------getInstance -SINGELTON OF Controller WE CREATE ONLY ONE INSTANCE------------
Controller & Controller::getInstance()
{
	static Controller Master; // make new instance
	return Master;
}
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
