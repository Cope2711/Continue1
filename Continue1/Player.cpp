#include "Player.h"


void Player::drawPlayer() {
	Map::modifyMapIndex(playerPosition, playerSymbol);
}

void Player::setKeys(char keyUp, char keyDown, char keyLeft, char keyRight) {
	keyToDirection[keyUp] = [this]() { moveUp(); };
	keyToDirection[keyDown] = [this]() { moveDown(); };
	keyToDirection[keyLeft] = [this]() { moveLeft(); };
	keyToDirection[keyRight] = [this]() { moveRight(); };
}

void Player::moveUp() {
	if (playerPosition[1] == 0) { return; } // Si es 0 el movimiento es invalido por lo que se rompe la ejecucion antes de hacer el movimiento
	if (isMoveValidSymbol({playerPosition[0], playerPosition[1] - 1}) == false) { return; } // su es un simbolo de movimiento invalido termina
	Map::modifyMapIndex(playerPosition, Parameters::wallSymbol); // Borrar la posicion actual
	playerPosition[1] = playerPosition[1] - 1; // Modificar la posicion acorde al movimiento
	spawnRoute();
	drawPlayer(); // Dibujar la nueva posicion
} // Aplica la misma logica al resto de movimientos

void Player::moveDown() {
	if (playerPosition[1] == Parameters::mapSize[0] - 1) { return; }
	if (isMoveValidSymbol({ playerPosition[0], playerPosition[1] + 1 }) == false) { return; }
	Map::modifyMapIndex(playerPosition, Parameters::wallSymbol);
	playerPosition[1] = playerPosition[1] + 1;
	spawnRoute();
	drawPlayer();
}

void Player::moveLeft() {
	if (playerPosition[0] == 0) { return; }
	if (isMoveValidSymbol({ playerPosition[0] - 1, playerPosition[1] }) == false) { return; }
	Map::modifyMapIndex(playerPosition, Parameters::wallSymbol);
	playerPosition[0] = playerPosition[0] - 1;
	spawnRoute();
	drawPlayer();
}

void Player::moveRight() {
	if (playerPosition[0] == Parameters::mapSize[1] - 1) { return; }
	if (isMoveValidSymbol({ playerPosition[0] + 1, playerPosition[1] }) == false) { return; }
	Map::modifyMapIndex(playerPosition, Parameters::wallSymbol);
	playerPosition[0] = playerPosition[0] + 1;
	spawnRoute();
	drawPlayer();
}

void Player::spawnRoute() {
	vector<string> routes = { "UP", "DOWN", "LEFT", "RIGHT" };
	if (playerPosition[0] == 0 || isSpawnRouteValidSymbol({playerPosition[0] - 1, playerPosition[1]}) == false) { routes.erase(remove(routes.begin(), routes.end(), "LEFT"), routes.end()); }
	else if (playerPosition[0] == Parameters::mapSize[0] - 1 || isSpawnRouteValidSymbol({ playerPosition[0] + 1, playerPosition[1] }) == false) { routes.erase(remove(routes.begin(), routes.end(), "RIGHT"), routes.end()); }
	if (playerPosition[1] == 0 || isSpawnRouteValidSymbol({ playerPosition[0], playerPosition[1] - 1 }) == false) { routes.erase(remove(routes.begin(), routes.end(), "UP"), routes.end()); }
	else if (playerPosition[1] == Parameters::mapSize[1] - 1 || isSpawnRouteValidSymbol({ playerPosition[0], playerPosition[1] + 1 }) == false) { routes.erase(remove(routes.begin(), routes.end(), "DOWN"), routes.end()); }
	srand(time(0));
	string route = routes[rand() % routes.size()];
	if (route == "UP") { Map::modifyMapIndex({playerPosition[0], playerPosition[1] - 1}, Parameters::routeSymbol); }
	else if (route == "DOWN") { Map::modifyMapIndex({ playerPosition[0], playerPosition[1] + 1 }, Parameters::routeSymbol); }
	else if (route == "LEFT") { Map::modifyMapIndex({ playerPosition[0] - 1, playerPosition[1] }, Parameters::routeSymbol); }
	else if (route == "RIGHT") { Map::modifyMapIndex({ playerPosition[0] + 1, playerPosition[1] }, Parameters::routeSymbol); }
}

bool Player::isSpawnRouteValidSymbol(vector<int> position) {
	if (Map::map[position[1]][position[0]] == Parameters::wallSymbol) { return true; }
	return false;
}

bool Player::isMoveValidSymbol(vector<int> position) {
	if (Map::map[position[1]][position[0]] == playerSymbol) {
		cout << playerName << " Ha gando" << endl;
		exit(EXIT_SUCCESS); }
	if (Map::map[position[1]][position[0]] == Parameters::routeSymbol) { return true; }
	return false;
}



