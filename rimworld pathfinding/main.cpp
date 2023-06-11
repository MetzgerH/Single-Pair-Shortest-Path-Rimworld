#include "breadthFirst.hpp"


int main()
{
	srand(213);
	Map testmap;
	int startX = rand() % MAPSIZE,startY = rand() % MAPSIZE,destX = rand() % MAPSIZE, destY = rand() % MAPSIZE;
	//int startX = 8, startY = 8, destX = 2, destY = 2;
	PathNode* start = new PathNode(startX, startY, &testmap, 3.0, 0, destX,destY);
	bool go = true;
	double minDistance = 0;
	int nodeCount = 0;
	PathNode* emptyNode = nullptr;
	PathNode** target = &emptyNode;
	while (go)
	{
		
		minDistance += 0.05;
		nodeCount += start->proceed(minDistance, target);
		go = *target == nullptr;
	}
	std::cout << "Starting point: (" << startX << ", " << startY << ")" << std::endl;
	std::cout << "Finishing point: (" << (*target)->destination.first << ", " << (*target)->destination.second << ")" << std::endl;
	bool addPath = false;
	for (int count = 0; count < 2; count++)
	{
		for (int y = 0; y < MAPSIZE; y++)
		{
			for (int x = 0; x < MAPSIZE; x++)
			{
				bool isOnPath = false;
				for (auto it = (*target)->path.begin(); it != (*target)->path.end(); it++)
					if (it->first == x && it->second == y)
					{
						isOnPath = true;
					}
				if (addPath)
				{
					if (x == startX && y == startY)
						std::cout << "O";
					else if (x == (*target)->destination.first && y == (*target)->destination.second)
						std::cout << "X";
					else if (isOnPath)
						std::cout << "#";
					else if (testmap.tiles[x][y].intoTime > 0)
						std::cout << "H";
					else if (testmap.tiles[x][y].walkOverSpeed < 1)
						std::cout << "=";
					else
						std::cout << "-";
				}
				else
				{
					if (x == startX && y == startY)
						std::cout << "O";
					else if (x == (*target)->destination.first && y == (*target)->destination.second)
						std::cout << "X";
					else if (testmap.tiles[x][y].intoTime > 0)
						std::cout << "H";
					else if (testmap.tiles[x][y].walkOverSpeed < 1)
						std::cout << "=";
					else
						std::cout << "-";
				}
				std::cout << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		addPath = true;
	}
	std::cout << "Totally nodes (moves) created: " << nodeCount << std::endl;
	return 1;
}