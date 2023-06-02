#include <math.h>
#include <random>

#define MAPSIZE 10

typedef struct tile
{
	double walkOverSpeed;
	double intoTime;
	bool hasThing;
	bool isPassable;
} Tile;

class Map
{
private:
	double root2;
public:
	Map()
	{
		for (int x = 0; x < MAPSIZE; x++)
		{
			for (int y = 0; y < MAPSIZE; y++)
			{
				if(rand()%10 == 0)
					tiles[x][y] = { 1.0,0.5,false,true };
				else if (rand() % 2 == 0)
					tiles[x][y] = { 1.0,0,false,true };
				else
					tiles[x][y] = { 0.5,0,false,true };
				/*if ((y == 3 || y == 4) && x > 2)
					tiles[x][y] = { 0.01,0,false,true };
				else
					tiles[x][y] = { 1.0,0,false,true };*/

			}
		}
		root2 = sqrt(2);
	}
	Tile tiles[MAPSIZE][MAPSIZE];
	double travelTime(double speed, int x1, int y1, int x2, int y2);
	//undefined behavior if tiles are not adjacent
};