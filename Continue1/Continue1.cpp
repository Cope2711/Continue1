#include <iostream>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include "Parameters.h" 
#include "Map.h"
#include "Player.h"

using namespace std;

int main() {
    
    Player player1;
    Player player2;

    player1.setKeys('w', 's', 'a', 'd');
    player2.setKeys('i', 'k', 'j', 'l');
    

    Parameters::mapSize = { 3, 3 };

    player1.playerPosition = { 1,1 };
    player2.playerPosition = { 0, 0 };

    vector<Player> players = { player1, player2 };

    Map::createMap();

    player1.playerName = "Diego";
    player1.drawPlayer();
    player1.spawnRoute();
    

    player2.playerName = "Tadeo";
    player2.drawPlayer();
    player2.spawnRoute();


    Map::printMap();

    while (true)
    {
        char keyPressed = _getch();
        
        for (size_t i = 0; i < players.size(); ++i){
            Player& player = players[i];
            if (player.keyToDirection.find(keyPressed) != player.keyToDirection.end()) {
                player.keyToDirection[keyPressed]();
            }
        }
        system("cls");
        Map::printMap();

    }

    return 0;
}