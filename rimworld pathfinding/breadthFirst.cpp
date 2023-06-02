#include "breadthFirst.hpp"

int PathNode::proceed(double minDist, PathNode** target)
{
	int output = 0;

	for (int count = 0; count < childrenCount; count++)
		output += children[count]->proceed(minDist, target);
	if (!isDead)
	{
		if (path.size() > 1)
		{
			auto prevPoint = path.end();
			prevPoint--;
			prevPoint--;
			for (int x = currentX - 1; x <= currentX + 1; x++)
				for (int y = currentY - 1; y <= currentY + 1; y++)
					if (!(x < 0 || y < 0 || x >= MAPSIZE || y >= MAPSIZE)) //check if target is out of bounds
						if ((abs(x - prevPoint->first) + abs(y - prevPoint->second)) > 1) //check if target is too close to prev point
							if (x != currentX || y != currentY) //check if target is not current point
								if (graph->tiles[x][y].isPassable)//check if target is passable
									if (graph->travelTime(speed, currentX, currentY, x, y) + cost < minDist) //check if target is within next increment
									{
										bool hasAddedTile = false;
										for (int count = 0; count < childrenCount; count++)
											if (children[count]->currentX == x && children[count]->currentY == y)
												hasAddedTile = true;
										if (!hasAddedTile)
										{
											bool isInPath = false;
											for (auto iterator = path.begin(); iterator != path.end(); iterator++)
												if (iterator->first == x && iterator->second == y)
													isInPath = true;

											if (!isInPath)
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
									}
		}
		else
		{
			for (int x = currentX - 1; x <= currentX + 1; x++)
				for (int y = currentY - 1; y <= currentY + 1; y++)
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