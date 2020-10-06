//------------------------------INCLUDE_SECTION-----------------------------------------
#pragma once
#include "Diamond.h"
#include "Triangle.h"
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <memory>

//-----------------------------------CONST_SECTION-----------------------------------------
const float EPSILON =5.0f;//Epsilon
const int  PLAYER = 1;// recognize when the player pos
const int COMPUTER = 2;// recognize when the enemy  pos 
const int FREE = 0;// not player and not enemy

//-------------class Board_Section--------------------------------------------------------
class Board
{
public:
	Board(sf::RenderWindow & window);// Ctor of Board
	~Board();//Dtor of board
	void buildMatrix();// build matrix od diamond
	void startGame();// all functions on one func to start game
	void refreshData();// all functions on one func to refresh game
	unsigned int  getSizeDataBase()const{ return m_data_base.size(); }// get size of database
	void drawDataBase();//drawDataBase
	void drawAllGroups(int,sf::Color);//drawAllGroups for neighbors
	void fillIdOnDataBase();//fill member on data base which kind is he 
	void showDataBase(sf::RenderWindow & window);//show the Data Base
	
	void createDataBase();//createDataBase
	void createNeighbors();//createNeighbors
	const sf::Color& scanDataBase(int);// return the color of cell that chossen
	void upperRow(int i, int j);// func that handle with the upper row of diamond matrix 
	void leftCol(int i, int j);// func that handle with the leftCol of diamond matrix
	void rightCol(int i, int j);// func that handle with the rightCol of diamond matrix
	void downRow(int i, int j);// func that handle with the downRow of diamond matrix
	void insertNeighborsShapes(int i,int j,int,int );//insertNeighborsShapes to m_neighbors
	int getIndex(int )const;//getIndex
	int setIdOfMamaNeighbors( const Shape* shape );// check that this cell (shape)
	//													on m_neighbors where is it on m_data_base

	bool compareTwoVector2f(const sf::Vector2f&, const sf::Vector2f&)const;//compare between 2 positions if that is same pos
	void  getSameColorNeigb(int i , const sf::Color color, std::vector<int>&);//getSameColorNeigb

private:
	sf::RenderWindow & m_window;// ref to window on controller
	std::vector<std::vector <std::unique_ptr<Diamond>>> m_matrix;//matrix of diamonds
	std::vector < std::unique_ptr<Shape>> m_data_base;// The vector that contains the shapes
	std::vector<std::vector< std::unique_ptr<Shape>>>m_neighbors;//list of neighbors 
	std::vector<std::vector<int>> m_type;// matrix of type -which type you are
	const int m_width;// m_width of diamond matrix
	const int m_length;// m_length of diamond matrix
	int m_row_neighbors;//m_row_neighbors
	int m_number_enemy;//m_number_enemy
	int m_number_player;//m_number_player

};
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------


