#include <iostream>
#include <vector>
#include <random>
#include <conio.h>

using namespace std;

// Enumeración para representar direcciones
enum class Direction { LEFT, RIGHT, UP, DOWN }; // Direcciones posibles

// Función para generar un número entero aleatorio dentro del rango [min, max]
int getRandomInt(int min, int max) {
    random_device rd; // Crear un objeto random_device para generar semillas aleatorias
    mt19937 gen(rd()); // Crear un generador de números pseudoaleatorios con la semilla generada por random_device
    uniform_int_distribution<> distr(min, max); // Crear una distribución uniforme de números enteros en el rango [min, max]
    return distr(gen); // Generar y devolver un número entero aleatorio utilizando la distribución uniforme y el generador
}

// Función para obtener un carácter aleatorio de un conjunto dado
char getRandomChar(const vector<char>& characters) {
    int randomIndex = getRandomInt(0, characters.size() - 1); // crea un numero aleatorio entre 0 y la longitud del vector
    return characters[randomIndex];
}

// Función para crear un mapa con un símbolo de pared dado
vector<vector<string>> createMap(const vector<int>& mapSize, const string& wallSymbol) {
    vector<vector<string>> map;
    for (int x = 0; x < mapSize[0]; x++) {
        vector<string> row(mapSize[1], wallSymbol); // Se crea un vector del tamaño x y se rellena con el simbolo de pared
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
        return (x > 0 && map[y][x - 1] == wallSymbol); // Comprueba si estas en el borde o si es un simbolo lo mismo en las demas
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
void spawnMoveZone(vector<vector<string>>& map, vector<int> mapSize, const vector<int>& playerPosition, const string& routeSymbol, const string& wallSymbol) {
    char key;
    vector<char> validMovements = { 'a', 'w', 's', 'd' };
    int x = playerPosition[0];
    int y = playerPosition[1];
    if (x == 0) { // Si x igual a 0 eliminamos el que se pueda posicionar a la izquierda
        validMovements.erase(remove(validMovements.begin(), validMovements.end(), 'a'), validMovements.end()); 
    } 
    else if (x == mapSize[1] - 1) { // Si x igual al mapSize -1 eliminamos el que se pueda posicionar a la izquierda
        validMovements.erase(remove(validMovements.begin(), validMovements.end(), 'd'), validMovements.end());
    }
    if (y == 0) { // Si y es igual a 0 eliminamos el que se pueda posicionar hacia arriba
        validMovements.erase(remove(validMovements.begin(), validMovements.end(), 'w'), validMovements.end());
    }
    else if (y == mapSize[0] - 1) { // Si y es igual a mapSize -1 eliminamos el que se pueda posicionar hacia abajo
        validMovements.erase(remove(validMovements.begin(), validMovements.end(), 's'), validMovements.end());
    }
    key = getRandomChar(validMovements); // Se llama a la funcion para que torne un character random despues de a ver realizado las comprobaciones

    switch (tolower(key)) {
    case 'a':
        if (x > 0) {
            modifyMapIndex(map, { x - 1, y }, routeSymbol); // Se resta uno a x para que se mueva a la derecha la misma logica para el resto
        }
        break;
    case 'd':
        if (x < map.size() - 1) {
            modifyMapIndex(map, { x + 1, y }, routeSymbol);
        }
        break;
    case 'w':
        if (y > 0) {
            modifyMapIndex(map, { x, y - 1}, routeSymbol);
        }
        break;
    case 's':
        if (y < map[0].size() - 1) {
            modifyMapIndex(map, { x, y + 1}, routeSymbol);
        }
        break;
    default:
        break;
    }
}


// Función para mover al jugador en una dirección dada
void movePlayer(vector<vector<string>>& map, vector<int> mapSize, vector<int>& playerPosition, const string& playerSymbol, const string& routeSymbol, const string& wallSymbol, Direction direction) {
    int x = playerPosition[0];
    int y = playerPosition[1];
    switch (direction) {
    case Direction::LEFT: 
        if (x > 0 && isNextMoveWall(map, playerPosition, wallSymbol, Direction::LEFT) == false) { // Se comprueban los bordes y las colisiones
            modifyMapIndex(map, playerPosition, wallSymbol); // La posicion actual se remplaza por un simbolo de pared
            playerPosition[0] -= 1; // se modifica la posicion actual del jugador para que este uno mas a la derecha
            modifyMapIndex(map, playerPosition, playerSymbol); // se actualiza la posicion del jugador
            spawnMoveZone(map, mapSize, playerPosition, routeSymbol, wallSymbol); // se spawnea una nueva zona de movimiento
        } // Misma logica aplica al resto
        break;
    case Direction::RIGHT:
        if (x < map.size() - 1 && isNextMoveWall(map, playerPosition, wallSymbol, Direction::RIGHT) == false) {
            modifyMapIndex(map, playerPosition, wallSymbol);
            playerPosition[0] += 1;
            modifyMapIndex(map, playerPosition, playerSymbol);
            spawnMoveZone(map, mapSize, playerPosition, routeSymbol, wallSymbol);
        }
        break;
    case Direction::UP:
        if (y > 0 && isNextMoveWall(map, playerPosition, wallSymbol, Direction::UP) == false) {
            modifyMapIndex(map, playerPosition, wallSymbol);
            playerPosition[1] -= 1;
            modifyMapIndex(map, playerPosition, playerSymbol);
            spawnMoveZone(map, mapSize, playerPosition, routeSymbol, wallSymbol);
        }
        break;
    case Direction::DOWN:
        if (y < map[0].size() - 1 && isNextMoveWall(map, playerPosition, wallSymbol, Direction::DOWN) == false) {
            modifyMapIndex(map, playerPosition, wallSymbol);
            playerPosition[1] += 1;
            modifyMapIndex(map, playerPosition, playerSymbol);
            spawnMoveZone(map, mapSize, playerPosition, routeSymbol, wallSymbol);
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

    vector<int> mapSize{ 10 , 10 }; // Tamaño del mapa
    vector<vector<string>> map = createMap(mapSize, wallSymbol); // Se crea el mapa

    vector<int> playerPosition{ getRandomInt(0, mapSize[1] - 1), getRandomInt(0, mapSize[0] - 1) }; // La posicion del jugador es aleatoria  y evita q

    modifyMapIndex(map, playerPosition, playerSymbol);

    spawnMoveZone(map, mapSize, playerPosition, routeSymbol, wallSymbol);

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

        movePlayer(map, mapSize, playerPosition, playerSymbol, routeSymbol, wallSymbol, direction);
    }

    return 0;
}

// Tarea:
// Nombre:
// Solucion:


// Tarea: Crear una interfaz (urgente)  :(
// Nombre:
// Solucion:


// Tarea: Crear variable que almacene los movimientos efectivos realizados por el jugador
// Nombre:
// Solucion:


// Tarea: Evitar que el jugador se quede sin movimientos al spawnear un moveZone fuera de los limites del mapa 
// Nombre: Diego
// Solucion: Se comprueban los bordes del mapa antes de retornar el randomCharacter


// Tarea: Crear colisiones
// Nombre: Diego
// Solucion: Se agregaron comprobaciones de limites de coordenadas antes de que se ejecuten los movimientos del jugador



// Tarea: Crear rutas de movimiento aleatorias
// Nombre: Diego
// Solucion: se creo la funcion spawnMoveZone la cual selecciona una direccion aleatoria entorno a las coordenadas del jugador y modifica 
// dicha direccion poniendo un simbolo de ruta, tambien se creo la funcion getRandomChar que recibe un vector de char y retorne un valor aleatorio



// Tarea: Crear una funcion que permita que el jugador se mueva
// Nombre: Diego
// Solucion: Se creo un enum class Direction que corresponde a las direcciones de movimiento
// En el codigo se agrego un bucle el cual recibe las pulsaciones del teclado por consola y estas pulsaciones corresponden a una direccion
// se creo la funcion movePlayer la cual recibe lo necesario y dependiendo de la direccion dada llama a modifyMapIndex e inserta el symbolo
// del jugador en la coordenada modificada con el movimiento


// Tarea: Crear una funcion que permita insertar un symbolo en unas coordenadas dadas en el mapa
// Nombre: Diego
// Solucion: Se creo la funcion recibe, el mapa, el symbolo, y las coordenadas

// Tarea: Crear una funcion que retornde un int dado un rango
// Nombre: Diego
// Solucion: Se autoexplica


// Tarea: Imprimir mapa
// Nombre: Diego
// Solucion: Se creo una funcion que recibe el mapa y lo imprime


// Tarea: Crear mapa de vector por vector de string de n por n
// Nombre: Diego
// Solucion: Se creo una funcion que recibe un vector<int> de 2x2, y un string que corresponde a las paredes, retorna un mapa de NxN en relacion al vector dado
