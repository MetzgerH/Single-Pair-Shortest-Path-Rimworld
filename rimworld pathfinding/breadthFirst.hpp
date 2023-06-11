#include <vector>
#include "tiles.hpp"
#include <iostream>;

class PathNode
{
private:
	void kill();
	//deallocates path and sets isDead to yes
	bool isAcceptableTile(int x, int y, double minDist);
public:
	std::vector<std::pair<int, int>> path;
	std::pair <int, int> destination;
	double cost;
	PathNode* children[8];
	int childrenCount;
	Map* graph;
	double speed;
	bool isDead;
	int currentX;
	int currentY;
	PathNode(int x , int y, Map *newGraph, double oldSpeed, double oldCost, int destX, int destY, std::vector<std::pair<int, int>>* oldPath=nullptr)
	{
		currentX = x;
		currentY = y;
		childrenCount = 0;
		isDead = false;
		graph = newGraph;
		speed = oldSpeed;
		destination = std::make_pair(destX, destY);
		if (oldPath == nullptr)
		{
			path = std::vector<std::pair<int, int>>();
			cost = 0;
		}
		else
		{
			path = *oldPath;
			cost = oldCost + graph->travelTime(speed, (--path.end())->first, (--path.end())->second, x, y);
		}
		path.push_back(std::make_pair(x, y));
		for (int count = 0; count < 5; count++)
			children[count] = nullptr;
	}
	int proceed(double minDist, PathNode** target);
	void killCheck();
	
	~PathNode()
	{
		for (int count = 0; count < childrenCount; count++)
			delete children[childrenCount];
	}
	
};