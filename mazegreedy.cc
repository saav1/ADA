//20947870E
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;

const int MAX = 100;

struct Point{
	int x;
	int y;
};


struct Path{
	vector<Point> points;
};

bool isValid(int row, int col, int Trows, int Tcol){
	bool valid = ((row >= 0) && (row < Trows) && (col >= 0) && (col < Tcol)) ? true : false;
	return valid;
}

int greedyFunction(int array[MAX][MAX], bool vistArray[][MAX] ,Point source, Point destination, Path &shortPath){

	//Comprobar que las posiciones 'source' y 'destination' tiene valor 1.
	if( (array[source.x][source.y] != 1) || (array[destination.x][destination.y] != 1)) return -1; //-1 es 'BLOCKED'

	//Marcamos la primera casilla como visitada.
	vistArray[source.x][source.y] = true;

	//Agregamos la primera casilla al camino mas corto 'shortPath'.
	shortPath.points.push_back(source);

	//Asignamos al nodo el primer nodo del camino que tenemos en ese momento.
	shortPath.points.front();


	while(1){
		Point currentPoint = shortPath.points.back();

		//Caso Base: Cuando llegamos a la casilla de destino, terminamos.
		if(currentPoint.x == destination.x && currentPoint.y == destination.y) return 0; //0 es 'OK'.

		//Primero miramos en diagonal.
		if(array[currentPoint.x+1][currentPoint.y+1] == 1 && !vistArray[currentPoint.x+1][currentPoint.y+1]){
			Point nextPoint = {currentPoint.x+1, currentPoint.y+1}; //Le damos los valores del siguiente nodo, en diagonal.
			shortPath.points.push_back(nextPoint);
			//Ponemos la actual posicion como visiatada.
			vistArray[nextPoint.x][nextPoint.y] = true;
		}
		//Miramos hacia abajo.
		else if(array[currentPoint.x+1][currentPoint.y] == 1 && !vistArray[currentPoint.x+1][currentPoint.y]){
			Point nextPoint = {currentPoint.x+1, currentPoint.y}; //Le damos los valores del siguiente nodo, en diagonal.
			shortPath.points.push_back(nextPoint);
			//Ponemos la actual posicion como visiatada.
			vistArray[nextPoint.x][nextPoint.y] = true;
		}
		//Miramos hacia derecha.
		else if(array[currentPoint.x][currentPoint.y+1] == 1 && !vistArray[currentPoint.x][currentPoint.y+1]){
			Point nextPoint = {currentPoint.x, currentPoint.y+1}; //Le damos los valores del siguiente nodo, en diagonal.
			shortPath.points.push_back(nextPoint);
			//Ponemos la actual posicion como visiatada.
			vistArray[nextPoint.x][nextPoint.y] = true;
		}
		//Si llegamos aquí esque el camino está bloqueado.
		else{
			return -1;
		}


	}

	return 0;
}


int main(int argc, char* argv[]){
	string fileName = "null";
	unsigned int filas, columnas;
	bool argsOK = true;
	int array[MAX][MAX]; //Array donde guardo el laberinto.
	int resGreedy = -1;	// -1 será 'BLOCKED' // 0 será 'OK'
	bool vistArray[MAX][MAX]; //Array del mismo tamaño, para saber que casillas hemos visitado.

	Path shortPath;

	if(argc == 3){

		if(strcmp(argv[1],"-f") == 0) fileName = argv[2];
		else{
			argsOK = false;
			cout << "ERROR: unknow option " << argv[1] << "." << endl;
		}

		if(argsOK){
			ifstream myFile(fileName.c_str());
			if(myFile.is_open()){
				myFile >> filas;
				myFile >> columnas;
				for(unsigned i = 0; i < filas; i++){
					for(unsigned j = 0; j < columnas; j++){
						myFile >> array[i][j];
					}
				}
				myFile.close();
			}else{
				cout << "ERROR: can't open file: " << fileName << "." << endl;
				cout << "Usage:\n maze-greedy [-f] file" << endl;
				return 0;
			}

			for(unsigned i = 0; i < filas; i++){
				for(unsigned j = 0; j < columnas; j++){
					vistArray[i][j] = false; //Marcamos todas las casillas como no-visitadas.
				}
			}

		//.............................GREEDY ALGORITHM.............................................//
			Point source, destination;
			source.x = 0;
			source.y = 0;
			destination.x = filas-1;
			destination.y = columnas-1;
			resGreedy = greedyFunction(array, vistArray, source, destination, shortPath);
		//..........................................................................................//

		//..............................PRINT RESULTS...............................................//
			cout << "A possible greedy path:" << endl;

			for(int i = 0 ; i < (int)shortPath.points.size() ; i++){
				cout << "(" << shortPath.points[i].x << "," << shortPath.points[i].y << ")";
			}
			if(resGreedy == -1)cout << "BLOCKED" << endl;
			else cout << endl;

			cout << "Length= ";
			if(resGreedy == -1) cout << "0" << endl;
			else cout << shortPath.points.size() << endl;
			cout << endl;

			cout << "Path 2D:" << endl;
			for(unsigned i = 0; i < filas; i++){
				for(unsigned j = 0; j < columnas; j++){
					if(vistArray[i][j] == true) cout << "*";
					else cout << array[i][j];
				}
				cout << endl;
			}


		//..........................................................................................//

		}
	}else{
			cout << "ERROR: Invalid number of arguments." << endl;
	}
	return 0;
}

/*El problema del laberinto 2

	 Se presenta un laberinto con 1 o 0. Un valor 0 en una casilla significa que es inaccesible, por el contrario, con el valor 1 se
	simbolizan las casillas accesibles.
	 Se pide aplicar el 'método voraz' para tratar de encontrar el camino de longitud mínima, que conduzca a la salida del laberinto.
	El punto de partida es la casilla [0][0] y el de llegada la casilla [filas-1][columas-1].
	 Movimientos:
	 	1. Derecha: (i, j+1)
	 	2. Abajo:   (i+1, j)
	 	3. Diagonal: (i+1, j+1)

	La orden tendrá la siguiente sintaxi: 'maze-greedy -f fichero_entrada'
	Salida del programa.

		1. Mediante una enumeración de las casillas que lo componen y a continuación la longitud de dicho camino. En el caso
		de que el criterio voraz no conduzca a la salida (o que no exista un camino de salida) se mostrará las casillas que
		se han visitado seguido del literl 'BLOCKED'. En este caso la longitud del camino deberá ser 0.
		2. Mediante una superposición del camino en la matriz que representa el laberinto. Se mostrará el carácter '*' en cada
		una de las casillas que componen el camino. 	*/
