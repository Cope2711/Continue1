#include "Map.h"

vector<vector<string>> Map::map;

void Map::createMap() {
    for (int x = 0; x < Parameters::mapSize[0]; x++) {
        vector<string> row(Parameters::mapSize[1], Parameters::wallSymbol); // Se crea un vector del tamaño x y se rellena con el simbolo de pared
        map.push_back(row);
    }
}

void Map::printMap() {
    for (const auto& row : map) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

void Map::modifyMapIndex(vector<int> position, string symbol) {
    Map::map[position[1]][position[0]] = symbol;
}