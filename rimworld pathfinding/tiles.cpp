#include "tiles.hpp"

double Map::travelTime(double speed, int x1, int y1, int x2, int y2)
{
	if (x1 == x2 || y1 == y2)
	{
		return  ((0.5 / tiles[x1][ y1].walkOverSpeed + 0.5 / tiles[x2][y2].walkOverSpeed) / speed) + tiles[x2][y2].intoTime;
	}
	else
	{
		return ((0.5 / tiles[x1][y1].walkOverSpeed + 0.5 / tiles[x2][y2].walkOverSpeed) / speed) * root2 + tiles[x2][y2].intoTime;
	}
}