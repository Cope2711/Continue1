#include <iostream>
#include <vector>
#include <random>
#include <conio.h>

using namespace std;

// Enumeración para representar direcciones
enum class Direction { LEFT, RIGHT, UP, DOWN };

// Función para obtener un número aleatorio en un rango
int getRandomInt(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

// Función para obtener un carácter aleatorio de un conjunto dado
char getRandomChar(const vector<char>& characters) {
    int randomIndex = getRandomInt(0, characters.size() - 1);
    return characters[randomIndex];
}

// Función para crear un mapa con un símbolo de pared dado
vector<vector<string>> createMap(const vector<int>& mapSize, const string& wallSymbol) {
    vector<vector<string>> map;
    for (int x = 0; x < mapSize[0]; x++) {
        vector<string> row(mapSize[1], wallSymbol);
        map.push_back(row);
    }
    return map;
}

// Función para imprimir el mapa en la consola
void printMap(const vector<vector<string>>& map) {
    for (const auto& row : map) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

// Función para modificar un índice específico en el mapa
void modifyMapIndex(vector<vector<string>>& map, const vector<int>& position, const string& symbol) {
    int x = position[0];
    int y = position[1];
    map[y][x] = symbol;
}

// Función para verificar si el próximo movimiento del jugador es una pared
bool isNextMoveWall(const vector<vector<string>>& map, const vector<int>& playerPosition, const string& wallSymbol, Direction direction) {
    int x = playerPosition[0];
    int y = playerPosition[1];
    switch (direction) {
    case Direction::LEFT:
        return (x > 0 && map[y][x - 1] == wallSymbol);
    case Direction::RIGHT:
        return (x < map.size() - 1 && map[y][x + 1] == wallSymbol);
    case Direction::UP:
        return (y > 0 && map[y - 1][x] == wallSymbol);
    case Direction::DOWN:
        return (y < map[0].size() - 1 && map[y + 1][x] == wallSymbol);
    default:
        return false;
    }
}

// Función para colocar una zona de movimiento en una posición aleatoria
void spawnMoveZone(vector<vector<string>>& map, const vector<int>& playerPosition, const string& routeSymbol, const string& wallSymbol) {
    char key = getRandomChar({ 'a', 'w', 's', 'd' });
    int x = playerPosition[0];
    int y = playerPosition[1];

    switch (tolower(key)) {
    case 'a':
        if (x > 0) {
            map[y][x - 1] = routeSymbol;
        }
        break;
    case 'd':
        if (x < map.size() - 1) {
            map[y][x + 1] = routeSymbol;
        }
        break;
    case 'w':
        if (y > 0) {
            map[y - 1][x] = routeSymbol;
        }
        break;
    case 's':
        if (y < map[0].size() - 1) {
            map[y + 1][x] = routeSymbol;
        }
        break;
    default:
        break;
    }
}


// Función para mover al jugador en una dirección dada
void movePlayer(vector<vector<string>>& map, vector<int>& playerPosition, const string& playerSymbol, const string& routeSymbol, const string& wallSymbol, Direction direction) {
    int x = playerPosition[0];
    int y = playerPosition[1];
    switch (direction) {
    case Direction::LEFT:
        if (x > 0 && isNextMoveWall(map, playerPosition, wallSymbol, Direction::LEFT) == false) {
            modifyMapIndex(map, playerPosition, wallSymbol);
            playerPosition[0] -= 1;
            modifyMapIndex(map, playerPosition, playerSymbol);
            spawnMoveZone(map, playerPosition, routeSymbol, wallSymbol);
        }
        break;
    case Direction::RIGHT:
        if (x < map.size() - 1 && isNextMoveWall(map, playerPosition, wallSymbol, Direction::RIGHT) == false) {
            modifyMapIndex(map, playerPosition, wallSymbol);
            playerPosition[0] += 1;
            modifyMapIndex(map, playerPosition, playerSymbol);
            spawnMoveZone(map, playerPosition, routeSymbol, wallSymbol);
        }
        break;
    case Direction::UP:
        if (y > 0 && isNextMoveWall(map, playerPosition, wallSymbol, Direction::UP) == false) {
            modifyMapIndex(map, playerPosition, wallSymbol);
            playerPosition[1] -= 1;
            modifyMapIndex(map, playerPosition, playerSymbol);
            spawnMoveZone(map, playerPosition, routeSymbol, wallSymbol);
        }
        break;
    case Direction::DOWN:
        if (y < map[0].size() - 1 && isNextMoveWall(map, playerPosition, wallSymbol, Direction::DOWN) == false) {
            modifyMapIndex(map, playerPosition, wallSymbol);
            playerPosition[1] += 1;
            modifyMapIndex(map, playerPosition, playerSymbol);
            spawnMoveZone(map, playerPosition, routeSymbol, wallSymbol);
        }
        break;
    default:
        break;
    }
}



int main() {
    string playerSymbol = "i";
    string wallSymbol = "#";
    string routeSymbol = " ";

    vector<int> mapSize{ 10 , 10 };
    vector<vector<string>> map = createMap(mapSize, wallSymbol);

    vector<int> playerPosition{ getRandomInt(1, 8), getRandomInt(1, 8) };

    modifyMapIndex(map, playerPosition, playerSymbol);

    spawnMoveZone(map, playerPosition, routeSymbol, wallSymbol);

    while (true) {
        system("cls");
        printMap(map);

        // Obtener entrada del usuario
        char key = _getch();
        Direction direction;
        switch (tolower(key)) {
        case 'a':
            direction = Direction::LEFT;
            break;
        case 'd':
            direction = Direction::RIGHT;
            break;
        case 'w':
            direction = Direction::UP;
            break;
        case 's':
            direction = Direction::DOWN;
            break;
        default:
            continue; // Ignorar entradas no válidas
        }

        movePlayer(map, playerPosition, playerSymbol, routeSymbol, wallSymbol, direction);
    }

    return 0;
}
