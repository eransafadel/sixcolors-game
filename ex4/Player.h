//------------------------------INCLUDE_SECTION-----------------------------------------
#pragma once
#include "Entity.h"

class Board;

//-------------------------class Entity_section-------------------------------------------
class Player:public Entity
{
public:
	Player(Board& board);//ctor pf player
	void refreshData();//refreshData
	void startPlayer();//startPlayer
	bool setColor(sf::Color colorclick, sf::Color colorE);//setColor
	sf::Color getColor()const { return m_color; }//getColor
	bool turn(sf::RenderWindow & window, sf::Color);//turn
	void scanGroup();//scanGroup
	void drawGroup(sf::RenderWindow &window) final;//drawGroup
	float caclConquer()const final { return m_group.size() / size; }//caclConquer
	~Player();//dtor of player
	void flickeringColor(sf::RenderWindow & window);
	
private:
	

	Board& mBoard;//board
	float size;//size
	
	
};
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

