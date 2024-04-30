#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <iostream>
#include "Parameters.h" // Asegúrate de incluir solo una vez Parameters.h
using namespace std;

class Map
{
public:
    static void createMap();
    static void printMap();
    static void modifyMapIndex(vector<int> position, string symbol);

    static vector<vector<string>> map;
};

#endif // MAP_H
