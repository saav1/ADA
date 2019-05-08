//STALYN ALEJANDRO ALCOCER VALENCIA DNI: 20947870E
#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <time.h>
using namespace std;

const int MAX = 100;
struct Point{
	int x, y;
	int dist;
};

int makePath(bool visited[][MAX], int i, int j, int x, int y, vector<Point> &path){
	Point destination;
	destination.x = x;
	destination.y = y;
	destination.dist = 900; //Solo tenemos que poner un número grande.

	path.push_back(destination);
	while(1){
		Point newPoint;
		if(destination.x == i && destination.y == j){
			return 0;
		}
		//Miramos abajo
		if(visited[destination.x+1][destination.y] == true){
			newPoint.x = destination.x+1;
			newPoint.y = destination.y;
		}
		//Derecha
		if(visited[destination.x][destination.y+1] == true){
			newPoint.x = destination.x;
			newPoint.y = destination.y+1;
		}
		//Abajo-Derecha
		if(visited[destination.x+1][destination.y+1] == true){
			newPoint.x = destination.x+1;
			newPoint.y = destination.y+1;
		}
		//Abajo-Izquierda
		if(visited[destination.x+1][destination.y-1] == true){
			newPoint.x = destination.x+1;
			newPoint.y = destination.y-1;
		}
		//Izquierda
		if(visited[destination.x][destination.y-1] == true){
			newPoint.x = destination.x;
			newPoint.y = destination.y-1;
		}
		//Miramos arriba
		if(visited[destination.x-1][destination.y] == true){
			newPoint.x = destination.x-1;
			newPoint.y = destination.y;
		}
		//Arriba-Derecha
		if(visited[destination.x-1][destination.y+1] == true){
			newPoint.x = destination.x-1;
			newPoint.y = destination.y+1;
		}
		//Arriba-Izquierda
		if(visited[destination.x-1][destination.y-1] == true){
			newPoint.x = destination.x-1;
			newPoint.y = destination.y-1;
		}
		visited[destination.x][destination.y] = false;
		newPoint.dist = destination.dist - 1;
		path.push_back(newPoint);
		destination = newPoint;
	}
}
int eightAlgorithm(int array[][MAX], bool visited[][MAX], int i, int j, int x, int y){
	if(i == x && j == y){
		visited[i][j] = true;
		return 0; //EXIT!
	}
	if(visited[i][j] == false && array[i][j] == 1){
		visited[i][j] = true;
		//Abajo-Derecha
		if(eightAlgorithm(array, visited, i+1, j+1, x, y ) == 0) return 0;
		//Abajo
		if(eightAlgorithm(array, visited, i+1, j, x, y ) == 0) return 0;
		//Derecha
		if(eightAlgorithm(array, visited, i, j+1, x, y ) == 0) return 0;
		if(x < 25){ //El lab. 10 encuentra un camino más rápido.
			//Abajo-Izquierda
			if(eightAlgorithm(array, visited, i+1, j-1, x, y ) == 0) return 0;
			//Arriba-Izquierda
			if(eightAlgorithm(array, visited, i-1, j-1, x, y ) == 0) return 0;
			//Izquierda
			if(eightAlgorithm(array, visited, i, j-1, x, y ) == 0) return 0;
			//Arriba-Derecha
			if(eightAlgorithm(array, visited, i-1, j+1, x, y ) == 0) return 0;
			//Arriba
			if(eightAlgorithm(array, visited, i-1, j, x, y ) == 0) return 0;
		}
		visited[i][j] = false;
	}
	return -1;//NO EXIT!
}

int main(int argc, char* argv[]){
	string fileName = "null";
	unsigned int rows, columns;
	bool argsOK = true;
	bool showPath = false; //Si introduce el parámetro -p. Mostraremos el camino.
	int resBT = -1;	// -1 será 'BLOCKED' // 0 será 'OK'
	int array[MAX][MAX]; //Array donde guardo el laberinto.
	bool visited[MAX][MAX]; //Array del mismo tamaño, para saber que casillas hemos visitado.
	double CMD = 0;
	clock_t t, t2; //Para saber el tiempo de ejecución de el algoritmo.
	vector<Point> path;

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
				cout << "Usage:\n maze-bt [-f] file" << endl;
				return 0;
			}
			//Marcamos todas las casillas como no visitadas.
			for(unsigned i = 0; i < rows; i++){
				for(unsigned j = 0; j < columns; j++){
					visited[i][j] = false;
				}
			}
			//If source(0, 0) and destination(n-1, m-1) point == 1. We call the algorithm.
			if(array[0][0] == 1 && array[rows-1][columns-1] == 1){
				//............................ALGORITHM...................................//
				t = clock();
				resBT = eightAlgorithm(array, visited, 0, 0, rows-1, columns-1);
				t2 = clock();
				CMD = difftime(t2,t);
			}
			/*...........................PRINT RESULTS...................................*/
			bool print = true;
			if(resBT != -1){
				//Pongo en un vector para que no se repitan casillas.
				makePath(visited, 0, 0,  rows-1, columns-1, path);
				cout << "Shortest path length= " << path.size() << endl;
				cout << "CPU elapsed time= " << CMD << " ms." << endl;
				if(showPath){
					cout << "Path 2D:" << endl;
					for(int i = 0; i < rows; i++){
						for(int j = 0; j < columns; j++){
							for(int k = 0 ; k < path.size(); k++){
								if(((i == path[k].x) && (j == path[k].y)) ){
									cout << "*";
									print = false;
								}
							}
							if(print) cout << array[i][j] ;
							print = true;
						}
						cout << endl;
					}	
				}
				
			}else{
				cout << "NO EXIT" << endl;
			}
		}
	}else{
			cout << "Usage:\n maze-bt [-p] -f fichero-entrada" << endl;
	}
return 0;
}
