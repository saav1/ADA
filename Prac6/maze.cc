#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;



bool readFile(string fileName, int matrix[][100], int &filas, int &columnas){

  ifstream myFile (fileName.c_str());

  if( myFile.is_open() ){
    myFile >> filas;
    myFile >> columnas;

    for(int i = 0; i < filas; i++){
    	for(int j = 0; j < columnas; j++){
    		myFile >> matrix[i][j];
    	}
    }

    myFile.close();
    return true;
  
  }else{

  cout << "ERROR: can't open file: " << fileName << "." << endl;
  cout << "Usage:\nmaze [-p] [-t] [--ignore-recursive] -f file"<<endl;
  return false;  	
  
  }
}

int recursivoSinAlmcn(int array[][100],int i, int j, int filas, int columnas){

	unsigned long long cR = 0;
	if(array[0][0] == 0) return 0;
	if(i == filas-1 && j == columnas-1) return ++cR; //Caso Base
	if(array[i][j+1] == 1) cR += recursivoSinAlmcn(array, i, j+1,filas,columnas); //Derecha
	if(array[i+1][j] == 1) cR += recursivoSinAlmcn(array, i+1, j,filas,columnas); //Abajo
	if(array[i+1][j+1] == 1) cR += recursivoSinAlmcn(array, i+1, j+1,filas, columnas); //Diagonal

	return cR;
}

int recursivoConAlmcn(int array[][100], int auxArray[][100], int filas, int columnas, bool imprimir){

	unsigned long long cR = 0;
	if(auxArray[filas][columnas] == -1){
		if(array[0][0] == 0 && array[filas][columnas] == 0){
			 auxArray[filas][columnas] = cR;
			 	
			 return auxArray[filas][columnas];
		} 
		if(filas == 0 && columnas == 0){
 			auxArray[filas][columnas] = ++cR; 	
 			
			return auxArray[filas][columnas];
		} 
		 

		if(array[filas][columnas-1] == 1) cR += recursivoConAlmcn(array, auxArray, filas, columnas-1,false);
		if(array[filas-1][columnas] == 1) cR += recursivoConAlmcn(array, auxArray, filas-1, columnas,false);
		if(array[filas-1][columnas-1] == 1) cR += recursivoConAlmcn(array, auxArray, filas-1, columnas-1,false);

		auxArray[filas][columnas] = cR;

		return cR;
	}else{

		return auxArray[filas][columnas];
	}
}

int iterativo(int array[][100], int auxArray[][100], int filas, int columnas){
	
	unsigned long long camino = 0;

	for(int i = 0; i < filas; i++){

		for(int j = 0; j < columnas;j++){
			//Evitamos entrar en la primera casilla [0][0]
			if( (i != 0) || (j != 0) ){
				
				if(array[i][j] == 0) camino = 0;
				else{

					if(i-1 > -1) camino = auxArray[i-1][j]; //Arriba
					if(j-1 > -1) camino += auxArray[i][j-1]; //Izquierda					
					if(i-1 > -1 && j-1 > -1) camino += auxArray[i-1][j-1]; //Diagonal
					
					auxArray[i][j] = camino;
				
				}

				camino = 0;
			}

		}
	}



	return auxArray[filas-1][columnas-1];
}

int main(int argc, char* argv[] ){
	int array[100][100];
	int auxArray[100][100];
	int auxIT[100][100];
	unsigned long long resRSA = 0, resRCA = 0, resIT = 0, resIV = 0;
	bool argsOK = true, table = false, path = false, ignore = false;
	int rows = -1, columns = -1, i = 0, j = 0;
	
	string fileName = "null";


	if(argc >= 3 && argc <= 6){
		for(int i = 1; i < argc; i++){
			if(strcmp(argv[i],"-f") == 0) fileName = argv[++i];
			else if(strcmp(argv[i],"-p")==0) path = true;
			else if(strcmp(argv[i],"-t")==0) table = true;
			else if(strcmp(argv[i],"--ignore-recursive")==0) ignore = true;
			else{
				argsOK = false;
				cout << "ERROR: unknow option " << argv[i] << "." << endl;
				cout << "Usage:\nmaze [-p] [-t] [--ignore-recursive] -f file" << endl;
			}
		}

		if(fileName == "null") argsOK = false;
		if(argsOK && readFile(fileName, array, rows, columns)){
			if(!ignore){
				resRSA = recursivoSinAlmcn(array, i, j, rows, columns);	
			}
				//...................................................//
					for(int i = 0 ; i < rows; i++){
						for(int j = 0; j < columns; j++){

							auxIT[i][j] = 0;
							auxArray[i][j] = -1;
						}
					}
				//...................................................//


			resRCA = recursivoConAlmcn(array, auxArray, rows-1, columns-1,false);
	

					


			if(array[0][0] != 0){ //Si la posicion array[0][0] es igual a cero, nos evitamos hacer el algoritmo.
				auxIT[0][0] = 1;			 //Si es diferente ponemos un uno.
				resIT = iterativo(array, auxIT, rows, columns);	

			}

			//resIV = iterativoVector();
			
			cout << "Recursive ........ :   " << resRSA << endl;
			cout << "Memoization ...... :   " << resRCA << endl;
			cout << "Iterative ........ :   " << resIT  << endl;
			cout << "Iterative (vectors):   " << resIV << endl;
			cout << endl;
			
			if(table){
				cout << "Memoization table:" << endl;
				for(int i = 0; i < rows; i++){
					for(int j = 0; j < columns; j++){
						if(auxArray[i][j] == -1 || auxArray[i][j] == 0) cout << " - ";
						else cout << " " << auxArray[i][j] << " "; 
					}
					cout << endl;
				}
				cout << endl;
				cout << "Iterative table:" << endl;
				for(int i = 0; i < rows; i++){
					for(int j = 0; j < columns; j++){
						cout << " " << auxIT[i][j] << " ";
					}
					cout << endl;
				}
				cout << endl;
			}
			if(path){
				cout << "A possible path:" << endl;
			}
		}


	}


return 0;
}









