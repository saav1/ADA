#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
using namespace std;

const int MAX = 1000;

struct Point{
	int x;
	int y;
};

struct Path{
	vector<Point> points;
};

int eightAlgorithm(int array[][MAX], bool visitArray[][MAX], Point source, Point destination, Path &shortPath){
	//Check if source and destination has value 1.
	if( (array[source.x][source.y] != 1) || (array[destination.x][destination.y] != -1)) return -1; //NO EXIT!

	//Put source point as visited.
	visitArray[source.x][source.y] = true;

	//Add source point to the '&shortPath'.
	shortPath.points.push_back(source);

	while(1){
		Point currentPoint = shortPath.points.back();

		//Base.
		if(currentPoint.x == destination.x && currentPoint.y == destination.y) return 0; //EXIT!

		//Directions. We have 8 movements, as long as they are available. '1'.
		/*if(){}
		else if(){}
		else if(){}
		else{
			//If we arrived here, it means the paht has no exit!
			return -1; //NO EXIT!	
		}*/

	}

	return 0;
}

int main(int argc, char* argv[]){
	
	string fileName = "null";
	unsigned int rows, columns;
	bool argsOK = true;
	bool showPath = false; //Si introduce el parámetro -p. Mostraremos el camino.
	int resBT = -1;	// -1 será 'BLOCKED' // 0 será 'OK'
	int array[MAX][MAX]; //Array donde guardo el laberinto.
	bool visitArray[MAX][MAX]; //Array del mismo tamaño, para saber que casillas hemos visitado.
	Path shortPath;


	if(argc >= 3){
		for(int i = 1; i < argc; i++){
			if(strcmp(argv[i],"-f") == 0) fileName = argv[++i];
			else if(strcmp(argv[i], "-p") == 0) showPath = true; 
			else{
				argsOK = false;
				cout << "ERROR: unknow option " << argv[1] << "." << endl;
			}
		}

		if(argsOK){
			ifstream myFile(fileName.c_str());
			if(myFile.is_open()){
				myFile >> rows;
				myFile >> columns;
				for(unsigned i = 0; i < rows; i++){
					for(unsigned j = 0; j < columns; j++){
						myFile >> array[i][j];
					}
				}
				myFile.close();
			}else{
				cout << "ERROR: can't open file: " << fileName << "." << endl;
				cout << "Usage:\n maze-greedy [-f] file" << endl;
				return 0;
			}

		/*...........................ALGORITHM.......................................*/
			//Marcamos todas las casillas como no visitadas.
			for(unsigned i = 0; i < rows; i++){
				for(unsigned j = 0; j < columns; j++){
					visitArray[i][j] = false;
				}
			}

			Point source, destination;
			source.x = 0;
			source.y = 0;
			destination.x = rows-1;
			destination.y = columns-1;
			resBT = eightAlgorithm(array, visitArray, source, destination, shortPath);
		/*...........................................................................*/
		

		/*...........................PRINT RESULTS...................................*/
			cout << "" << endl;
		/*...........................................................................*/

		
		}

	}else{
			cout << "ERROR: Invalid number of arguments." << endl;
			cout << "Usage:\n maze-bt [-p] -f fichero-entrada" << endl;
	}

return 0;
}
/*
........................LABERINTO CON 8 MOVIMIENTOS........................
 	El laberinto con ocho movimientos: Se permite visitar cualquier casilla 
colindante siempre que sea accesible.
 
	Se pide aplicar el el método vueltra atrás para encontrar el camino de 
longitud mínima que conduzca a la salida del laberinto suponiendo, a diferencia
de las prácticas anteriores, que desde una posición cualquiera (i, j) puede
visitarse cualquiera de sus ocho casillas adyacentes siempre que sea accesible.
El punto de partida es la casilla (0, 0) y el de llegada la casilla (n-1, m-1).

1.NOMBRE DEL PROGRAMA, OPCIONES Y SINTAXIS DE LA ORDEN.
	La orden tendrá la singuiente sintaxis:
			maze-bt [-p] -f fichero-entrada

	El fichero con el laberinto a resolver se suministraa través de la opcion -f.
Si se hace uso del parámetro opcional -p, el programa mostrará el camino de 
longitud mínima encontrado (no tiene por qué ser único), en dos dimensiones
superpuesto a la matriz que codifica el laberinto, escribiendo el carácter '*'.
*/