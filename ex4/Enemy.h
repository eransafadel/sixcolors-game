//------------------------------INCLUDE_SECTION-----------------------------------------
#pragma once
#include "Entity.h"
const int ENEMY = 2;
class Board;


//-------------class Diamond_Section-------------------------------------------------------
class Enemy:public Entity
{
public:
	Enemy(Board & board);//ctor of Enemy
	void refreshData();// refreshData to refresh game
	void startEnemy();// all functions of ememt on one func to initialsation the enemy
	void turn(sf::RenderWindow & window, sf::Color);// turn of enemy 
	void drawGroup(sf::RenderWindow &window) final;//drawGroup
	void setColor(sf::Color color){ m_color = color; }//setColor
	sf::Color getColor()const { return m_color; }//getColor
	bool helperScanAbsuluteGroup(int)const;// check if the neigbors alreay in group
	float caclConquer()const final { return m_absulute_group.size() / size; }//calculate how much of area we conqer 
	~Enemy();//dtor

private:
	Board& mBoard;//Board
	std::vector<int>m_max_group;//m_max_group
	std::vector<int>m_absulute_group;//m_absulute_group
	sf::Color m_temp_color;//m_temp_color
	float size;//size
	
};
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

