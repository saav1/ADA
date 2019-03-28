#include <iostream>
#include <string.h>
#include <vector>
using namespace std;


//
typedef struct celda{
  bool accesible;
};


void imprimirC(vector<string> line){
  for(int i = 0 ; i < line.size() ; i++){
    cout << line[i] << endl;
  }
}

void imprimirC(string line){
  cout << "File name: " << line << endl;
}

//Los argumentos son -f -p --ignore-recursive -f
int main(int argc, char* argv[])
{
  vector<string> line;
  string fileName;

  cout << "argc: " << argc << endl;


  if(argc <= 6){
    for(int i = 1; i < argc; ++i){
      if(i + 1 < argc){
        line.push_back(argv[i]);
      }else{
        fileName = argv[i];
      }
    }
  }else{

  }

  imprimirC(line);
  imprimirC(fileName);

  return 0;
}

//PROGRAMACIÓN DINÁMICA
/*
  EL PROBLEMA DEL LABERINTO.
  Se dispone de una cuadrícula 'n x m' de valoes {0, 1} que representa un laberinto. Un valor 0 en una casilla cualquiera de la cuadrícula
indica una posición inaccesible, por el contrario, con el valor 1 se simbolizan las casillas accesibles

          1 1 0 1
          0 0 1 0 << (1, 3)   (Fila, Columna)

  Se pide aplicar el método divide y vencerás y su extensión a programación dinámica para calcular el número de caminos distintos que hay desde
el origen (0, 0) hasta el destino (n-1, m-1) asumiendo que solo son válidos tres tipos de movimientos desde una casilla cualquiera (i, j):
  1. Derecha >> (i, j + 1). (Fila, Columna + 1 ).
  2. Abajo >> (i + 1, j).   (Fila + 1, Columna).
  3. Diagonal >> (i + 1, j + 1).

  *nota = Dos caminos, con el mismo origen y el mismo destino, son distintos si varían en al menos una de las casillas intermedias.

  Como es evidente, tampoco son válidos los movimientos que llevan al exterior del laberinto ni los que conducen a casillas inaccesibles.

  Para resolver este ejercicio se debe implentar los siguientes algoritmos:
    1. Recursivo sin almacén (ineficiente).
    2. Recursivo con almacén (memoización).
    3. Iterativo con almacén (tabla).
    4. Iterativo con almacén (vector - versión con complejidad espacial mejorada - )
    5. Además deberá mostrarse un camino de salida cualquiera.
..............................................................................................................................
1. NOMBRE DEL PROGRAMA, OPCIONES Y SINTAXIS DE LA ORDEN.
  El programa a realizar se debe llamar >> maze. La orden tendrá la siguiente sintaxis:
        maze [-t] [-p] [--ignore-recursive] -f fichero_entrada

  En el siguiente apartado se describe el significado de las opciones.

2. SALIDA DEL PROGRAMA Y DESCRIPCIÓN DE LAS OPCIONES.
  En todas las formas posibles de utilizar la mencionada orden, la salida del programa será en primer lugar
la solución obtenida mediante los cuatro algoritmos anteriormente citados: 1.Recursivo sin almacén, 2.Memorizaicón
3.Iterativo con tabla y 4.Iterativo con complejidad espacial mejorada.
  No obstante si se incorpora a la orden la opción [--ignore-recursive] se deberá excluir de la salida del programa
la solución recursiva sin almacén.
  En cuanto al resto de opciones:
  · [-t] se mostrará, a continuación de lo escrito anteriormente, las tablas que almacenan los resultados intermedios
en las versiones memorización e iterativa con matriz (en este orden). Asimismo, para los subproblemas que no han sido
resueltos en la versión recursiva se mostrará el carácter guión ('-').
  · [-p] se mostrará además un camio cualquiera que conduzca a la casilla (n-1, m-1) (la última) desde la casilla (0,0).
Si no existe ningún camino se imprimirá el literal 'NO EXIT'.
  · Las opciones no son excluyentes entre sí, ninguna de ellas. Además podrán aparecer en cualquier orden.
  · Si se hace uso simultáneo de las opciones [-p] y [-t] (da igual el orden) se mostrará primero las tablas y a continuación
el camino.
  · En cualquier de las formas posibles de utilizar la orden, si se incorpora la opción [--ignore-recursive] se debe
excluir únicamente la solución recursiva sin almacén.
  · La opción -f (la única de uso obligado), se utiliza para suministrar el nombre del fichero donde está el laberinto a resolver
En el caso de que se suministre un fichero inexistente se advertira con un mensaje de error. No es necesario controlar posibles
errores en el contenido del fichero de entrada ya que siempre se ajustará fielmente al formato establecido.
  ·En el caso de que se haga uso de una sintaxis disntinta a la descrita se emitirá un mensaje de error adviertiendolo, y
a continuación se mostrará la sintaxis correcta. Considerar en este caso únicamente las opciones inexistentes. La duplicidad de
opciones puede ser ignorada y tratada por tanto como si se hubiera escrito solo una vez. No es necesario indicar todos los errores
sintácticos que pueda contener la orden, basta con hacerlo sólo con el primero que se detecte.

3.ENTRADA DE DATOS AL PROGRAMA. FORMATO DEL FICHERO DE ENTRADA.
Formato y contenido del fichero.
  1. Línea 1 del fichero: valores n y m separados mediante un único espacio en blanco.
  2. Línea 2 (y siguientes): m valores {0,1} que componen la primera fila (y siguientes) del laberinto, separados mediante un único
espacio en blanco.

  Por lo tanto, el fichero contendrá n+1 líneas que finalizarán con un salto de línea, salvo, en todo caso, la última línea.









*/
