#include <iostream>
#include <ctime>

using namespace std;
const int tam = 9;

struct Jugador
{
    string nombre;
    char alfombra;
    int nAlfombras;
    int monedas;
};


void iniciartablero(char tablero[][tam], int fil, int col)
{
    char nuevoTablero[9][9] = {
        {'E','1','3','4','3','4','3','4','E'},
        {'2','0','0','0','0','0','0','0','5'},
        {'5','0','0','0','0','0','0','0','6'},
        {'6','0','0','0','0','0','0','0','5'},
        {'5','0','0','0','H','0','0','0','6'},
        {'6','0','0','0','0','0','0','0','5'},
        {'5','0','0','0','0','0','0','0','6'},
        {'6','0','0','0','0','0','0','0','2'},
        {'E','3','4','3','4','3','4','1','E'}
    };

    for (int i = 0; i < fil; ++i) {
        for (int j = 0; j < col; ++j) {
            tablero[i][j] = nuevoTablero[i][j];
        }
    }
}
void mostrartablero(char tablero[][tam], int fil, int col)
{
    for(int i = 0; i < fil; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(tablero[i][j] == 'E')
            {
                cout << "-" << " ";
            }
            else if(tablero[i][j] == '1')
            {
                if(i == 8)
                {
                    cout << "(" << " ";    
                }
                else{
                    cout << ")" << " ";
                }
            }
            else if(tablero[i][j] == '2')
            {
                if(i == 7)
                {
                    cout << ")" << " ";    
                }
                else{
                    cout << "(" << " ";
                }
            }
            else if(tablero[i][j] == '3')
            {
                cout << "(" << " ";
            }
            else if(tablero[i][j] == '4')
            {
                cout << ")" << " ";
            }
            else if(tablero[i][j] == '5')
            {
                cout << "_" << " ";
            }
            else if(tablero[i][j] == '6')
            {
                cout << '_' << " ";
            }
            else{
                cout << tablero[i][j] << " ";
            } 
        }
        cout << endl;
    }
    return;
}

void girarDerecha(char &direccion) {
    // Definimos las direcciones en un ciclo circular
    if (direccion == 'N') {
        direccion = 'E';
    } else if (direccion == 'E') {
        direccion = 'S';
    } else if (direccion == 'S') {
        direccion = 'O';
    } else if (direccion == 'O') {
        direccion = 'N';
    }
}

void girarIzquierda(char &direccion) {
    // Definimos las direcciones en un ciclo circular
    if (direccion == 'N') {
        direccion = 'O';
    } else if (direccion == 'O') {
        direccion = 'S';
    } else if (direccion == 'S') {
        direccion = 'E';
    } else if (direccion == 'E') {
        direccion = 'N';
    }
}

void moverHassam(char tablero[][tam], int fil, int col, int &posHassamFila, int &posHassamColumna, char &direccion, int dado, char &ant) {
    // Definimos cómo cambiar la posición dependiendo de la dirección
    int cambioFila = 0, cambioColumna = 0;
    if (direccion == 'N') {
        cambioFila = -1;
    } else if (direccion == 'S') {
        cambioFila = 1;
    } else if (direccion == 'E') {
        cambioColumna = 1;
    } else if (direccion == 'O') {
        cambioColumna = -1;
    }

    // Calculamos la nueva posición multiplicando el cambio por el valor del dado
    int nuevaFila = posHassamFila + (cambioFila * dado);
    int nuevaColumna = posHassamColumna + (cambioColumna * dado);

    // Verificamos si la nueva posición está dentro del tablero
    if (nuevaFila >= 1 && nuevaFila < fil-1 && nuevaColumna >= 1 && nuevaColumna < col-1) {
        tablero[posHassamFila][posHassamColumna] = ant;  // Borramos la posición anterior de Hassam
        posHassamFila = nuevaFila;
        posHassamColumna = nuevaColumna;
        ant = tablero[posHassamFila][posHassamColumna];
        tablero[posHassamFila][posHassamColumna] = 'H';  // Colocamos a Hassam en su nueva posición
        
    } else {
        int posaf = nuevaFila;
        int posac = nuevaColumna;
        tablero[posHassamFila][posHassamColumna] = ant;
        // Si la nueva posición está fuera del tablero, movemos a Hassam en espiral
        // alrededor del borde del tablero
        if (nuevaFila <= 0) {
            posHassamFila = 0;
            posaf = -posaf;
            posaf++;
        } else if (nuevaFila >= fil-1) {
            posaf = posHassamFila - posaf;
            posHassamFila = fil - 1;
        }
        if (nuevaColumna <= 0) {
            posHassamColumna = 0;
            posac = -posac;
            posac++;
        } else if (nuevaColumna >= col-1) {
            posac = posHassamColumna - posac;
            posHassamColumna = col - 1;
        }
        switch (tablero[posHassamFila][posHassamColumna])
        {
        case '1':
            posHassamFila = posaf;
            girarDerecha(direccion);
            break;
        case '2':
            posHassamColumna = posac;
            girarIzquierda(direccion);
            break;
        case '3':
            cout << "Hola" << endl;
            posHassamFila  += posaf;
            posHassamColumna++;
            girarDerecha(direccion);
            girarDerecha(direccion);
            break;
        case '4':
            posHassamFila += posaf;
            posHassamColumna--;
            girarDerecha(direccion);
            girarDerecha(direccion);
            break;
        case '5':
            posHassamFila++;
            posHassamColumna += posac;
            girarDerecha(direccion);
            girarDerecha(direccion);  
            break;
        case '6':
            posHassamFila--;
            posHassamColumna += posac;
            girarDerecha(direccion);
            girarDerecha(direccion); 
            break;
        default:
            break;
        }
        ant = tablero[posHassamFila][posHassamColumna];
        tablero[posHassamFila][posHassamColumna] = 'H';
    }
}

void posiblesAlfombras(char tablero[][tam], int phf, int phc, int posis[32][4], int &nposis)
{
    nposis = 0;
    for(int i = phf-1; i <= phf+1; i++)
    {
        for(int j = phc-1; j <= phc+1; j++)
        {
            if(tablero[i][j] == '0')
            {
                if(tablero[i-1][j] == '0' || tablero[i-1][j] == '*' || tablero[i-1][j] == '#')
                {
                    posis[nposis][0] = i;
                    posis[nposis][1] = j;
                    posis[nposis][2] = i-1;
                    posis[nposis][3] = j;
                    nposis++;
                }
                if(tablero[i][j+1] == '0' || tablero[i][j+1] == '*' || tablero[i][j+1] == '#')
                {
                    posis[nposis][0] = i;
                    posis[nposis][1] = j;
                    posis[nposis][2] = i;
                    posis[nposis][3] = j+1;
                    nposis++;
                }
                if(tablero[i+1][j] == '0' || tablero[i+1][j] == '*' || tablero[i+1][j] == '#')
                {
                    posis[nposis][0] = i;
                    posis[nposis][1] = j;
                    posis[nposis][2] = i+1;
                    posis[nposis][3] = j;
                    nposis++;
                }
                if(tablero[i][j-1] == '0' || tablero[i][j-1] == '*' || tablero[i][j-1] == '#')
                {
                    posis[nposis][0] = i;
                    posis[nposis][1] = j;
                    posis[nposis][2] = i;
                    posis[nposis][3] = j-1;
                    nposis++;
                }
            }
        }
    }
    cout << "Numero de opciones para colocar una alfombra: " <<nposis << endl;
    for(int i = 0; i < nposis; i++)
    {
        cout << "Opcion " << i+1 << endl;
        cout << "Primera mitad:" << endl;
        cout << "X: " << posis[i][0] << " ";
        cout << "Y: " << posis[i][1] << endl;
        cout << "Segunda mitad:" << endl;
        cout << "X: " << posis[i][2] << " ";
        cout << "Y: " << posis[i][3] << endl;
        cout << endl;
    }
}

bool esValido(int x, int y, char board[][tam], bool visited[][tam], char simboloJugador) {
    return (x >= 0 && x < tam-1 && y >= 0 && y < tam-1 && board[x][y] == simboloJugador && !visited[x][y]);
}

int calculatePago(char tablero[][tam], int x, int y, char simboloJugador) {
    // Dirección de movimientos posibles (arriba, abajo, izquierda, derecha)
    int direcciones[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    bool visitados[tam][tam] = {false};
    int puntos[tam * tam][2];  
    int primero = 0, ultimo = 0;
    
    puntos[ultimo++][0] = x;
    puntos[ultimo++][0] = y;  // Añadir el punto inicial
    visitados[x][y] = true;  // Marcar el punto inicial como visitado
    
    int area = 1;
    while (primero < ultimo) {
        int p[1][2];
        p[0][0] = puntos[primero++][0];  // Extraer el siguiente punto
        p[0][1] = puntos[primero++][1];

        area++;  // Incrementar el area de la alfombra
        
        // Explorar las celdas vecinas
        for (int i = 0; i < 4; ++i) {
            int nx = p[0][0] + direcciones[i][0];
            int ny = p[0][1] + direcciones[i][1];
            
            if (esValido(nx, ny, tablero, visitados, simboloJugador)) {
                puntos[ultimo++][0] = nx;
                puntos[ultimo++][1] = ny;  // Añadir la celda vecina
                visitados[nx][ny] = true;  // Marcar la celda vecina como visitada
            }
        }
    }
    
    int costPerCarpet = 1;  // Costo fijo por cada alfombra
    return area * costPerCarpet;
}


int main() {
    srand(time(nullptr)); // Semilla para la generación de números aleatorios
    Jugador j1, j2;
    int fil = 9, col = 9;
    char tablero[9][tam]; 
    char ant = '0';
    int posHassamFila = 4, posHassamColumna = 4;  // Posición inicial de Hassam
    char direccionActual = 'N';  // Dirección inicial de Hassam ('N' para norte)

    iniciartablero(tablero, fil, col);

    std::cout << "Tablero inicial:" << std::endl;
    mostrartablero(tablero, fil, col);
    cout << "Ingrese el nombre del jugador 1:" << endl;
    cin >> j1.nombre;
    j1.alfombra = '*';
    j1.monedas = 20;
    j1.nAlfombras = 10;
    cout << "Ingrese el nombre del jugador 2:" << endl;
    cin >> j2.nombre;
    j2.alfombra = '#';
    j2.monedas = 20;
    j2.nAlfombras = 10;
    // Simulamos el movimiento de Hassam
    for (int i = 0; i < 10000; ++i) {
        int posis[32][4];
        int nposis;
        int op;
        Jugador main;
        if(i % 2 == 0)
        {
            main = j1;
        }
        else{
            main = j2;
        }

        cout << "Turno del jugador: " << main.nombre << endl;
        // Solicitamos al usuario la dirección a la que Hassam va a mirar
        cout << "Hassam esta mirando hacia el " << direccionActual << ". ¿Hacia donde desea girar Hassam? (D: derecha, I: izquierda, cualquier otra tecla: seguir mirando hacia donde esta): ";
        char opcion;
        cin >> opcion;

        if (opcion == 'D' || opcion == 'd') {
            girarDerecha(direccionActual);
        } else if (opcion == 'I' || opcion == 'i') {
            girarIzquierda(direccionActual);
        }

        int dado = rand() % 3 + 1;  // Simulamos el lanzamiento de un dado
        cin.ignore();
        cout << "\nMovimiento " << i + 1 << " de Hassam: Dado = " << dado << endl;
        moverHassam(tablero, fil, col, posHassamFila, posHassamColumna, direccionActual, dado, ant);
        mostrartablero(tablero, fil, col);
        cout << endl;
        if(main.alfombra != ant && ant != '0')
        {
            int cPagar = calculatePago(tablero,posHassamFila,posHassamColumna,ant);
            cout << "Tiene que pagar: " << cPagar << endl;
            if(main.monedas < cPagar)
            {
                cout << "El jugador: " << main.nombre << " es el perdedor" << endl;
            }
            else{
                if(main.alfombra == '*')
                {
                    j1.monedas -= cPagar;
                    j2.monedas += cPagar;
                }
                else{
                    j2.monedas -= cPagar;
                    j1.monedas += cPagar;
                }

            }
        }
        else{
            posiblesAlfombras(tablero,posHassamFila,posHassamColumna,posis, nposis);
            cout << "Ingrese la opcion de alfombra que desea poner" << endl;
            cin >> op;
            if(op > 0 && op <= nposis)
            {
                tablero[posis[op-1][0]][posis[op-1][1]] = main.alfombra;
                tablero[posis[op-1][2]][posis[op-1][3]] = main.alfombra;
            }
            else{
                cout << "Opcion invalida" << endl;
            }
        }
        cout << endl;
        mostrartablero(tablero, fil, col);
        cout << endl;
    }

    return 0;
}