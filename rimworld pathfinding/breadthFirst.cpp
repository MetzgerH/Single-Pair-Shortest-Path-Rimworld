#include "breadthFirst.hpp"

bool useHardTurns{ false };
//useHardTurns is a variable that decides whether you can move at a right angle to the the move you just took (taking a hard turn)
//if enabled, the pathing will complete in with O(n^5) created nodes (tested moves), where n the length of the shortest route, 
	// but it is guaranteed to find the shortest route (I think)
//if disabled, the pathing will complete in with O(n^3) created nodes (tested moves), where n the length of the shortest route, 
	// but it could fail to find the shortest route if there are tiles with very high walkOverSpeed

int PathNode::proceed(double minDist, PathNode** target)
{
	int output = 0;

	for (int count = 0; count < childrenCount; count++)
		output += children[count]->proceed(minDist, target);
	if (!isDead)
	{
		//if (path.size() > 1)
		//{
		//	auto prevPoint = path.end();
		//	prevPoint--;
		//	prevPoint--;
		//	for (int x = currentX - 1; x <= currentX + 1; x++)
		//		for (int y = currentY - 1; y <= currentY + 1; y++)
		//			if (!(x < 0 || y < 0 || x >= MAPSIZE || y >= MAPSIZE)) //check if target is out of bounds
		//				if ((useHardTurns &&(abs(x - prevPoint->first) + abs(y - prevPoint->second)) > 1) || (!useHardTurns  && (abs(x - prevPoint->first) + abs(y - prevPoint->second)) > 2)) 
		//					//check if target is too close to prev point
		//					if (x != currentX || y != currentY) //check if target is not current point
		//						if (graph->tiles[x][y].isPassable)//check if target is passable
		//							if (graph->travelTime(speed, currentX, currentY, x, y) + cost < minDist) //check if target is within next increment
		//							{
		//								bool hasAddedTile = false;
		//								for (int count = 0; count < childrenCount; count++)
		//									if (children[count]->currentX == x && children[count]->currentY == y)
		//										hasAddedTile = true;
		//								if (!hasAddedTile)
		//								{
		//									bool isInPath = false;
		//									for (auto iterator = path.begin(); iterator != path.end(); iterator++)
		//										if (iterator->first == x && iterator->second == y)
		//											isInPath = true;

		//									if (!isInPath)
		//									{
		//										children[childrenCount] = new PathNode(x, y, graph, speed, cost, destination.first, destination.second, &path);
		//										if (x == destination.first && y == destination.second)
		//										{
		//											if (*target == nullptr)
		//												*target = children[childrenCount];
		//											else if ((*target)->cost > children[childrenCount]->cost)
		//												*target = children[childrenCount];
		//										}
		//										else
		//										{
		//											output += children[childrenCount]->proceed(minDist, target);
		//										}
		//										childrenCount++;
		//										output++;

		//									}
		//								}
		//							}
		//}
		//else
		 
		int x = currentX - 1;
		int maxX = currentX + 1;
		if (path.size() > 1)
		{
			auto prevPoint = path.end();
			prevPoint--;
			prevPoint--;
			switch (prevPoint->first - currentX) //direction of last move
			{
			case -1: //going east
				if (prevPoint->second == currentY) //going straight east
					x++;
				if (!useHardTurns)
					x++;
				break;
			case 0: //going straight north or straight south
				break;
			case 1: // going west
				if (prevPoint->second == currentY) //going straight west
					maxX--;
				if (!useHardTurns)
					maxX--;
			}
		}
			
		for (; x <= maxX; x++)
		{
			int y = currentY - 1;
			int maxY = currentY + 1;
			if (path.size() > 1)
			{
				auto prevPoint = path.end();
				prevPoint--;
				prevPoint--;
				switch (prevPoint->second - currentY) //direction of last move
				{
				case -1: //going north
					switch (prevPoint->first - currentX) //direction of last move (X)
					{
					case -1: //going east (overall northeast)
						if (x == currentX - 1) //if currently checking column to the left
							y = currentY + 1; //this is only possible if we're using hard turns, so we resolve for that
						else if (x == currentX) //if currently checking column of origin
							y = currentY + 1;
						else if (!useHardTurns) //if currently checking column to the left, and we're not using hard turns
							y = currentY;
						break;
					case 0: //going straight north
						y++;
						if (!useHardTurns)
							y++;
						break;
					case 1: //going west (overall northwest)
						if (x == currentX - 1 && !useHardTurns) //if currently checking column to the left and we're not using hard turns
							y = currentY;
						else if (x > currentX - 1)
							y = currentY + 1;
						break;
					}

					break;
				case 0: //going straight east or west
					break; //do nothing because X filtering does the work
				case 1: //going south
					switch (prevPoint->first - currentX) //direction of last move (X)
					{
					case -1: //going east (overall southeast)
						if (x == currentX - 1) //if currently checking column to the left
							maxY = currentY - 1; //this is only possible if we're using hard turns, so we resolve for that
						else if (x == currentX) //if currently checking column of origin
							maxY = currentY - 1;
						else if (!useHardTurns) //if currently checking column to the left, and we're not using hard turns
							maxY = currentY;
						break;
					case 0: //going straight south
						maxY--;
						if (!useHardTurns)
							maxY--;
						break;
					case 1: //going west (overall southwest)
						if (x == currentX - 1 && !useHardTurns) //if currently checking column to the left and we're not using hard turns
							maxY = currentY;
						else if (x > currentX - 1)
							maxY = currentY - 1;
						break;
					}
				}
			}

			for (; y <= maxY; y++)
				if (isAcceptableTile(x, y, minDist))
				{
					children[childrenCount] = new PathNode(x, y, graph, speed, cost, destination.first, destination.second, &path);
					if (x == destination.first && y == destination.second)
					{
						if (*target == nullptr)
							*target = children[childrenCount];
						else if ((*target)->cost > children[childrenCount]->cost)
							*target = children[childrenCount];
					}
					else
					{
						output += children[childrenCount]->proceed(minDist, target);
					}
					childrenCount++;
					output++;

				}
		}
		
		this->killCheck();
	}
	return output;
}


void PathNode::kill()
{
	isDead = true;
	path.clear();
}

void PathNode::killCheck()
{
	int maxChildren = 0;
	if (path.size() > 1)
	{
		maxChildren = 5;
	}
	else
	{
		maxChildren = 8;
	}

	int impassableCount = 0;
	for (int x = currentX - 1; x < currentX + 1; x++)
		for (int y = currentY - 1; y < currentY + 1; y++)
		{
			if (x < 0 || y < 0 || x >= MAPSIZE || y >= MAPSIZE)
				impassableCount++;
			else if (!graph->tiles[x][y].isPassable)
				impassableCount++;
		}
	if (childrenCount + impassableCount >= maxChildren)
		kill();


}

bool PathNode::isAcceptableTile(int x, int y, double minDist)
{
	if (!(x < 0 || y < 0 || x >= MAPSIZE || y >= MAPSIZE)) //check if target is out of bounds
		if (x != currentX || y != currentY) //check if target is not current point
			if (graph->tiles[x][y].isPassable) //check if target is passable
				if (graph->travelTime(speed, currentX, currentY, x, y) + cost < minDist) //check if target is within next increment
				{
					bool hasAddedTile = false;
					for (int count = 0; count < childrenCount; count++)
						if (children[count]->currentX == x && children[count]->currentY == y)
							hasAddedTile = true;

					if (!hasAddedTile)
					{
						
						for (auto iterator = path.begin(); iterator != path.end(); iterator++)
							if (iterator->first == x && iterator->second == y)
								return false;
						return true;
					}
				}
	return false;
}