#include "Entity.h"
#include "Board.h"

//-----------------helperScanGroup--------------------------------------------------------
// check if the cell is already on group
bool Entity::helperScanGroup(int var) const
{
		for (int i = 0; i < m_group.size(); i++)
			if (m_group[i] == var)
				return false;
		return true;
}
//----------------------------------------------------------------------------------------

//-----------------------Entity ctor ---------------------------------------------------
Entity::Entity()
{

}
//-----------------------------------------------------------------------------------------

//-----------------getIndexByColor-------------------------------------------------------
// get the index by color 
int Entity::getIndexByColor(const sf::Color & color)const
{
	for (int i = 0; i < m_colors.size(); ++i)
		if (m_colors[i] == color)
			return i;
}
//----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
