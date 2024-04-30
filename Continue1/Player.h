#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <map>
#include <functional>
#include <cstdlib>
#include <ctime>

#include "Map.h"

using namespace std;

class Player
{
public:
	vector<int> playerPosition = { 0,0 };
	map<char, function<void()>> keyToDirection;
	string playerSymbol = "i";
	string playerName = "";
	void drawPlayer();
	void setKeys(char keyUp, char keyDown, char keyLeft, char keyRight);
	void spawnRoute();
	
private:
	bool isSpawnRouteValidSymbol(vector<int> position);
	bool isMoveValidSymbol(vector<int> position);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();


};

#endif // PLAYER_H
