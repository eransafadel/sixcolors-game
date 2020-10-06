#include "Board.h"
#include "Macros.h"


//----------------------Board -ctor------------------------------------------------------
Board::Board(sf::RenderWindow & window)
	:m_width(ROWS),m_length(COLS),  m_row_neighbors(0),m_window(window)
{
	startGame();
}
//---------------------------------------------------------------------------------------

//--------------------------dtor of board------------------------------------------------
Board::~Board()
{
}
//---------------------------------------------------------------------------------------

//----------------buildMatrix------------------------------------------------------------
//---------- build the matrix of diamond on statr that helps us to build 
// the vector of shapes - actually that matrix is just to begin and after we dont need
// that database
void Board::buildMatrix()
{
	sf::Vector2f left = LEFT_START;
	sf::Vector2f up = { LEFT_START.x + RADIUS,LEFT_START.x - RADIUS };
	sf::Vector2f right = { LEFT_START.x + RADIUS*2,LEFT_START.x };
	sf::Vector2f down = { LEFT_START.x + RADIUS,LEFT_START.x + RADIUS };
	m_matrix.resize(m_width);
	for (int i = 0; i < m_width ; i+=2)
	{
		for (int j = 0; j < m_length; j++)
		{
			m_matrix[i].emplace_back(std::make_unique<Diamond>(left, up, right, down));
			if(i<m_width-1)
				m_matrix[i + 1].emplace_back(std::make_unique<Diamond>
				(down, right, sf::Vector2f{ down.x + RADIUS*2,down.y }, sf::Vector2f{ right.x,down.y + RADIUS }));//create Green DIAMOND

			left = right;
			up = { up.x + RADIUS * 2,up.y };
			right = { right.x + RADIUS * 2, right.y };
			down = { down.x + RADIUS * 2,down.y };
		}
		left = {LEFT_START.x,left.y+ RADIUS * 2 };
		up = { left.x + RADIUS,left.y - RADIUS };
		right = { left.x + RADIUS * 2,left.y };
		down = { left.x+ RADIUS,left.y + RADIUS };
	}
}
//---------------------------------------------------------------------------------------

//-------------------startGame-----------------------------------------------------------
//general func that holds all the func we need to start new game 
void Board::startGame()
{
	buildMatrix();
	createDataBase();
	drawDataBase();
	fillIdOnDataBase();
	createNeighbors();
	m_window.display();
}
//----------------------------------------------------------------------------------------


//----------------refreshData--------------------------------------------------------------
// refresh all the data base - clear them
void Board::refreshData()
{
	
	m_row_neighbors = 0;

	for (int i = 0; i < m_neighbors.size(); i++)
		for (int j = 0; j < m_neighbors[i].size(); j++)
			m_neighbors[i][j].reset(nullptr);
	m_neighbors.clear();

	for (int i = 0; i < m_data_base.size(); i++)
		m_data_base[i].reset(nullptr);
	m_data_base.clear();

	for (int i = 0; i < m_type.size(); i++)
		m_type[i].clear();
	m_type.clear();

	for (int i = 0; i < m_matrix.size(); i++)
		for (int j = 0; j < m_matrix[i].size(); j++)
			m_matrix[i][j].reset(nullptr);
	m_matrix.clear();
}
//----------------------------------------------------------------------------------------



//----------------------------drawDataBase-----------------------------------------------
//-------------draw the data base----------------------------------------------------
void Board::drawDataBase()
{
	for (int i = 0; i < m_data_base.size(); i++)
			m_data_base[i]->draw(m_window);
}
//------------------------------------------------------------------------------------

//--------------------------drawAllGroups----------------------------------------------
//draw the index of grup that on data_base
void Board::drawAllGroups(int i,sf::Color color)
{
	m_data_base[i]->drawOfSpecificColor(m_window,color);
}
//-------------------------------------------------------------------------------------

//-----------------fillIdOnDataBase-----------------------------------------------------
//set the id of cell on data base 
//thares is a 3 types: PLAYER,COMPUTER,FREE
void Board::fillIdOnDataBase()
{
	for (int i = 0; i < m_data_base.size(); i++)
	{
		if (i == m_number_player)
			m_data_base[i]->setId(PLAYER);
		else if (i == m_number_enemy)
			m_data_base[i]->setId(COMPUTER);
		else
			m_data_base[i]->setId(FREE);
	}

}
//----------------------------------------------------------------------------------

//---------------showDataBase---------------------------------------------------------
//------------showDataBase on screen
void Board::showDataBase(sf::RenderWindow & window)
{
	for (int i = 0; i < m_data_base.size(); i++)
		m_data_base[i]->show(window);

}
//--------------------------------------------------------------------------------------

//-----------------createDataBase-----------------------------------------------------
// create the date base - vector of shapes* that contains all the shapes
void Board::createDataBase()
{
	m_type.resize(m_matrix.size());
	for (int i = 0; i < m_matrix.size(); i++)
	{
		for (int j = 0; j < m_length; j++)
		{
			if (i == 0)
				upperRow(i, j);
			else if (j == 0 && i % 2 == 0)
				leftCol(i, j);
			else if ((j == m_length - 1 && i % 2 != 0) || (j == m_length - 1 && i == m_width - 1))
				rightCol(i, j);
			else if (i == m_width - 1)
				downRow(i, j);
			

					else
			{ // if shape is diamond  
					std::random_device dev;
					std::mt19937 rng(dev());
					std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 3); // distribution in range [1, 6]
					switch (dist6(rng))
					{
					case 1:
						m_type[i].push_back(DIAMOND);
						m_data_base.emplace_back(std::make_unique<Diamond>(m_matrix[i][j]->getLeft(),
							m_matrix[i][j]->getUp(), m_matrix[i][j]->getRight(), m_matrix[i][j]->getDown()));
						break;
					case 2: // -
						m_type[i].push_back(TRIANLGLES_HORIZONTAL);
						m_data_base.emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getLeft(),
							m_matrix[i][j]->getUp(), m_matrix[i][j]->getRight()));
						m_data_base.emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getLeft(),
							m_matrix[i][j]->getDown(), m_matrix[i][j]->getRight()));
						break;
					case 3: // |
						m_type[i].push_back(TRIANLGLES_VERTICAL);
						m_data_base.emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getUp(),
							m_matrix[i][j]->getLeft(), m_matrix[i][j]->getDown()));
						m_data_base.emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getUp(),
							m_matrix[i][j]->getRight(), m_matrix[i][j]->getDown()));
						break;

					default:
						break;
					}
				}
		}
	}
}
//-------------------------------------------------------------------------------------


//----------------createNeighbors---------------------------------------------------
/*funcrion that create the neighbors of the vector of shapes 
we need that to know whare is located each shape that constains on data base

*/
void Board::createNeighbors()
{
	m_neighbors.resize(m_data_base.size());
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_length; j++, m_row_neighbors++)
		{
			
			if ((m_type[i][j] == DIAMOND) || (m_type[i][j] == TRIANLGLE))// case 1
			{
				if (i % 2 != 0)
				{

					insertNeighborsShapes(i - 1, j , DOWN, RIGHT);
					insertNeighborsShapes(i - 1, j + 1, DOWN, LEFT);
					insertNeighborsShapes(i + 1, j , UP, RIGHT);
					insertNeighborsShapes(i + 1, j + 1, UP, LEFT);
				}
				else {

					insertNeighborsShapes(i - 1, j - 1, DOWN, RIGHT);
					insertNeighborsShapes(i - 1, j, DOWN, LEFT);
					insertNeighborsShapes(i + 1, j - 1, UP, RIGHT);
					insertNeighborsShapes(i + 1, j, UP, LEFT);
				}
		
			}
			else if (m_type[i][j] == TRIANLGLES_HORIZONTAL)//case 2 -
			{
				m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getLeft(), m_matrix[i][j]->getDown(), m_matrix[i][j]->getRight()));// downer triangle
				
				if (i % 2 != 0)
				{
					insertNeighborsShapes(i - 1, j, DOWN, RIGHT);
					insertNeighborsShapes(i - 1, j + 1, DOWN, LEFT);
				}
				else
				{
					insertNeighborsShapes(i - 1, j - 1, DOWN, RIGHT);
					insertNeighborsShapes(i - 1, j, DOWN, LEFT);

				}
				
				m_row_neighbors++;
				m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getLeft(), m_matrix[i][j]->getUp(), m_matrix[i][j]->getRight()));// up triangle
				
				if (i % 2 != 0)
				{
					insertNeighborsShapes(i + 1, j, UP, RIGHT);
					insertNeighborsShapes(i + 1, j + 1, UP, LEFT);

				}
				else
				{
					insertNeighborsShapes(i + 1, j - 1, UP, RIGHT);
					insertNeighborsShapes(i + 1, j, UP, LEFT);

				}
				
			}

			else if (m_type[i][j] == TRIANLGLES_VERTICAL)//case 3 |
			{
				m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getUp(), m_matrix[i][j]->getRight(), m_matrix[i][j]->getDown()));//right triangle
				
				if (i % 2 != 0) 
				{
					insertNeighborsShapes(i - 1, j , DOWN, RIGHT);
					insertNeighborsShapes(i + 1, j , UP, RIGHT);
				}
				else
				{
					insertNeighborsShapes(i - 1, j - 1, DOWN, RIGHT);
					insertNeighborsShapes(i + 1, j - 1, UP, RIGHT);
				}
				m_row_neighbors++;
				m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getUp(), m_matrix[i][j]->getLeft(), m_matrix[i][j]->getDown()));//left triangle
					
				if (i % 2 != 0) 
				{
					insertNeighborsShapes(i - 1, j + 1, DOWN, LEFT);
					insertNeighborsShapes(i + 1, j + 1, UP, LEFT);
				}
				else
				{
					insertNeighborsShapes(i - 1, j, DOWN, LEFT);
					insertNeighborsShapes(i + 1, j, UP, LEFT);

				}
				
			}
		}
	}
	for (int i = 0; i < m_neighbors.size(); i++)
		for (int j = 0; j < m_neighbors[i].size(); j++)
			m_neighbors[i][j]->setId(setIdOfMamaNeighbors(m_neighbors[i][j].get()));


}
//-----------------------------------------------------------------------------------

//---------------scanDataBase---------------------------------------------------------
/* scan the data base and return the color of id we send him 
*/
const sf::Color& Board::scanDataBase(int id)
{
	for (int i = 0; i < m_data_base.size(); i++)
	{
		if (m_data_base[i]->getId() == id)
			return m_data_base[i]->getColor();
	}
	return sf::Color();
}

//--------------upperRow-----------------------------------------------------------------
// function that handle eith the upper row diamond matrix and create shape on data base 
void Board::upperRow(int i, int j)
{
	m_type[i].push_back(TRIANLGLE);
	if (j == 0)//top left corner 
	{
		m_data_base.emplace_back
		(std::make_unique<Triangle> (m_matrix[i][j]->getCenter(), m_matrix[i][j]->getRight(), m_matrix[i][j]->getDown()));
		return;
	}

	m_data_base.emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getLeft(), m_matrix[i][j]->getRight(), m_matrix[i][j]->getDown()));
	if (j == m_length - 1)
		m_number_enemy = m_data_base.size() - 1;
	
}
//----------------------------------------------------------------------------------------


//-----------------leftCol---------------------------------------------------------------
// function that handle eith the leftCol diamond matrix and create shape on data base
void Board::leftCol(int i, int j)
{
	if (i == 0)
		return;
	if (i % 2 == 0)//all the zugi
	{
		m_type[i].push_back(TRIANLGLE);
		m_data_base.emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getUp(), m_matrix[i][j]->getRight(), m_matrix[i][j]->getDown()));
	}
}
//---------------------------------------------------------------------------------------

//-----------------rightCol---------------------------------------------------------------
// function that handle eith the rightCol diamond matrix and create shape on data base
void Board::rightCol(int i, int j)
{
	if (i == m_width - 1)
	{
		m_type[i].push_back(TRIANLGLE);
		m_data_base.emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getUp(), m_matrix[i][j]->getCenter(), m_matrix[i][j]->getLeft()));
		return;
	}
	if (i % 2 != 0)
	{
		m_data_base.emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getLeft(), m_matrix[i][j]->getUp(), m_matrix[i][j]->getDown()));
		m_type[i].push_back(TRIANLGLE);
	}
}
//---------------------------------------------------------------------------------------

//-----------------downRow---------------------------------------------------------------
// function that handle eith the downRow diamond matrix and create shape on data base
void Board::downRow(int i, int j)
{
	if (j == m_length - 1)
		return;
	m_type[i].push_back(TRIANLGLE);
	m_data_base.emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getLeft(), m_matrix[i][j]->getRight(), m_matrix[i][j]->getUp()));
	if (j == 0)
		m_number_player = m_data_base.size() - 1;

}
//---------------------------------------------------------------------------------------

//-----------------insertNeighborsShapes------------------------------------------------
// this function insert the neghbors to data structure m_neighbors -and create the 
//neighbors of data base
void Board::insertNeighborsShapes(int i, int j, int type1,int type2)
{
	if (i < 0 || i >= m_width || j < 0 || j >= m_length)
		return;
	if (m_type[i][j] == TRIANLGLE)
	{	
	
	if( i == 0 && j == 0)
		m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getCenter(), m_matrix[i][j]->getRight(), m_matrix[i][j]->getDown()));
	else if( i%2 == 0 && j ==0 ) //left col
		m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getUp(), m_matrix[i][j]->getRight(), m_matrix[i][j]->getDown()));
	else if(i == m_width-1 && j == m_length-1)
		m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getUp(), m_matrix[i][j]->getLeft(), m_matrix[i][j]->getCenter()));
	else if(i%2 != 0 && j == m_length-1) // right col
		m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getUp(), m_matrix[i][j]->getLeft(), m_matrix[i][j]->getDown()));
	else if(i == 0) // upper row
		m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getLeft(), m_matrix[i][j]->getDown(), m_matrix[i][j]->getRight()));
	else if(i == m_width-1)//down row
		m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getLeft(), m_matrix[i][j]->getUp(), m_matrix[i][j]->getRight()));
	else
		m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getLeft(), m_matrix[i][j]->getUp(), m_matrix[i][j]->getRight()));

	}
	else if (m_type[i][j] == DIAMOND)
	{
		m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Diamond>(m_matrix[i][j]->getLeft(), m_matrix[i][j]->getUp(),
			m_matrix[i][j]->getRight(), m_matrix[i][j]->getDown()));
		
	}
	else if (m_type[i][j] == TRIANLGLES_HORIZONTAL)//-
	{
		if (type1 == UP)
		{
			m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getLeft(), m_matrix[i][j]->getUp(), m_matrix[i][j]->getRight()));
			
		}
		else if (type1 == DOWN)
		{
			m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getLeft(), m_matrix[i][j]->getDown(), m_matrix[i][j]->getRight()));
			
		}
	}
	else if (m_type[i][j] == TRIANLGLES_VERTICAL)//|
	{
		if (type2 == RIGHT)
		{
			m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getUp(), m_matrix[i][j]->getRight(), m_matrix[i][j]->getDown()));
			
		}
		else if (type2 == LEFT)
		{
			m_neighbors[m_row_neighbors].emplace_back(std::make_unique<Triangle>(m_matrix[i][j]->getUp(), m_matrix[i][j]->getLeft(), m_matrix[i][j]->getDown()));
			
		}
	}
}
//-----------------------------------------------------------------------------------------

//----------------getIndex----------------------------------------------------------------
int Board::getIndex(int id) const// for set the position of player and computer
{
	for (int i = 0; i < m_data_base.size(); i++)
	{
		if (m_data_base[i]->getId() == id)
			return i;
	}
	return 0;
}
//---------------------------------------------------------------------------------------


//-----------------setIdOfMamaNeighbors---------------------------------------------------
// calculate where the position of  shape that on m_neighbors 
// is found on m_data_base 
int Board::setIdOfMamaNeighbors(const Shape* shape)
{
	for (int i = 0; i < m_data_base.size(); i++)
	{
		if ((compareTwoVector2f(m_data_base[i]->getLeft(), shape->getLeft())
			||
			compareTwoVector2f(m_data_base[i]->getRight(), shape->getLeft())
			||
			compareTwoVector2f(m_data_base[i]->getUp(), shape->getLeft()))
			&&
			(compareTwoVector2f(m_data_base[i]->getLeft(), shape->getRight())
			||
			compareTwoVector2f(m_data_base[i]->getRight(), shape->getRight())
			||
			compareTwoVector2f(m_data_base[i]->getUp(), shape->getRight()))
			&&
			(compareTwoVector2f(m_data_base[i]->getLeft(), shape->getUp())
			||
			compareTwoVector2f(m_data_base[i]->getRight(), shape->getUp())
			||
			compareTwoVector2f(m_data_base[i]->getUp(), shape->getUp())))
				return i;

		
	}
	return 0;
}
//---------------------------------------------------------------------------------------

//------------------------compareTwoVector2f---------------------------------------------
//-------------comparision function that return if the positions are equals
bool Board::compareTwoVector2f(const sf::Vector2f & f1, const sf::Vector2f & f2) const
{
	return std::abs(f1.x - f2.x) < EPSILON &&std::abs(f1.y - f2.y) < EPSILON;
	
}
//--------------------------------------------------------------------------------------

//-------------------------getSameColorNeigb--------------------------------------------
// checks if negibors are same color of the color we choose
void Board::getSameColorNeigb(int i, const sf::Color color, std::vector<int>& buffer)
{
	int index;
	for (int j = 0; j < m_neighbors[i].size(); j++)
	{
		index = m_neighbors[i][j]->getId();
		if (m_data_base[index]->getColor() == color)
			buffer.push_back(index);
	}
}
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

