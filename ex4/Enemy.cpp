#include "Enemy.h"
#include "Board.h"


//-----------Enemy CTOR ----------------------------------------------------------------
Enemy::Enemy(Board & board)
	:mBoard(board)
{
	startEnemy();
	
}
//----------------------------------------------------------------------------------------

//--------------refreshData--------------------------------------------------------------
// to a new level we alear the data of enemy 
void Enemy::refreshData()
{
	m_absulute_group.clear();
	m_buffer.clear();
	m_group.clear();
	m_max_group.clear();

}
//---------------------------------------------------------------------------------------


//------------------------------startEnemy----------------------------------------------
// func that contains all func we need to strat the enemy of new game
void Enemy::startEnemy()
{
	m_color = mBoard.scanDataBase(ENEMY);
	m_absulute_group.push_back(mBoard.getIndex(ENEMY));
	m_group.push_back(mBoard.getIndex(ENEMY));
	size = mBoard.getSizeDataBase();
}
//---------------------------------------------------------------------------------------


//--------------------turn---------------------------------------------------------------
// func that turn of enemy
void Enemy::turn(sf::RenderWindow & window, sf::Color color)
{

	for (int c = 0; c < m_colors.size(); c++) //choose color
	{
		if (m_color == m_colors[c] || m_colors[c] == color)
			continue;
		m_color = m_colors[c];
		m_group = m_absulute_group;
		for (int i = 0; i < m_group.size(); i++)
		{
			m_buffer.clear();// save the neigb by each cell we check
			mBoard.getSameColorNeigb(m_group[i], m_color, m_buffer);

			for (int j = 0; j < m_buffer.size(); j++)//if index twice
				if (helperScanGroup(m_buffer[j]))
					m_group.push_back(m_buffer[j]);
		}
		if (m_group.size() >= m_max_group.size())
		{
			m_max_group = m_group;
			m_temp_color = m_color;
		}
	}
	// update absulte group
	for (int i = 0; i < m_max_group.size(); i++)
	{
		if(helperScanAbsuluteGroup(m_max_group[i]))
			m_absulute_group.push_back(m_max_group[i]);
	}

	setColor(m_temp_color);
	drawGroup(window);
	m_group.clear();
	m_max_group.clear();
}
//-------------------------------------------------------------------------------------

//--------------drawGroup---------------------------------------------------------------
// drawGroup of  each cell on absulut group 
void Enemy::drawGroup(sf::RenderWindow & window)
{
	for (int i = 0; i < m_absulute_group.size(); i++)
		mBoard.drawAllGroups(m_absulute_group[i], m_color);
}
//---------------------------------------------------------------------------------------


//---------------helperScanAbsuluteGroup-------------------------------------------------
// check if the cell is already on group
bool Enemy::helperScanAbsuluteGroup(int var ) const
{
	for (int i = 0; i < m_absulute_group.size(); i++)
		if (m_absulute_group[i] == var)
			return false;
	return true;
}
//--------------------------------------------------------------------------------------

//--------------------------Enemy dtor ---------------------------------------------------
Enemy::~Enemy()
{
}
//----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
