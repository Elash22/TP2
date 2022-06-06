#include <iostream>
#include "partida.hpp"
#include "unidad.hpp"
#include "jugador.hpp"

using namespace std;

Partida::Partida(){
    this->tablero = NULL;
    this->jugadores = NULL;
    this->mazoDeCartas = NULL;

    this->cantidadDeJugadores = 0;
    this->cantidadDeSoldadosPorJugador = 0;
    this->turno = 1;
    this->nroMapa = 1;
}

void Partida::pedirDatos(int& mapaLargo, int& mapaAncho, int& mapaAlto){
    cout << "Bienvenidos, ingrese la cantidad de jugadores: ";
    this->cantidadDeJugadores = this->ingresarNumeroYValidar(MINIMO_JUGADORES, MAXIMO_JUGADORES);
    cout << endl << "Ingrese la cantidad de soldados por jugador con la que van a jugar: ";
    this->cantidadDeSoldadosPorJugador = this->ingresarNumeroYValidar(MINIMO_SOLDADOS, MAXIMO_SOLDADOS);

    cout << endl << "Ingrese el largo del mapa: ";
    mapaLargo = this->ingresarNumeroYValidar(MINIMO_LARGO_ANCHO_TABLERO,MAXIMO_LARGO_ANCHO_TABLERO);
    cout << endl << "Ingrese el ancho del mapa: ";
    mapaAncho = this->ingresarNumeroYValidar(MINIMO_LARGO_ANCHO_TABLERO,MAXIMO_LARGO_ANCHO_TABLERO);
    cout << endl << "Ingrese el alto del mapa: ";
    mapaAlto = this->ingresarNumeroYValidar(MINIMO_ALTO_TABLERO,MAXIMO_ALTO_TABLERO);

    cout << endl << "En que mapa desea jugar? (1 - " << CANTIDAD_MAPAS<< "): ";
    this->nroMapa = this->ingresarNumeroYValidar(0,CANTIDAD_MAPAS);
}

unsigned int Partida::ingresarNumeroYValidar(unsigned int minimo, unsigned int maximo){
    unsigned int numeroIngresado;
    cin >> numeroIngresado;
    while(numeroIngresado < minimo || numeroIngresado > maximo){
        cout << endl << "Entrada incorrecta. Ingrese una cantidad mayor a " << (minimo-1) << " y menor a " << maximo+1 << ": ";
        cin >> numeroIngresado;
    }
    return numeroIngresado;
}

void Partida::inicializarPartida(){
    int mapaLargo, mapaAncho, mapaAlto;
    this->pedirDatos(mapaLargo, mapaAncho, mapaAlto);

    this->jugadores = new Jugador*[this->getCantidadJugadores()];
    
    for(unsigned int i=0; i<this->getCantidadJugadores(); i++){
        this->jugadores[i] = new Jugador(i);
    }

    this->tablero = new Tablero(mapaLargo, mapaAncho, mapaAlto, this->nroMapa);
    this->inicializarMazo();
    this->inicializarSoldadosAJugadores();
}

// PRE:
// POST: crea punteros a Carta. Agrega cartas en forma aleatoria al vector de punteros a carta.
void Partida::inicializarMazo(){
    // TODO
}

// PRE: haya cartas en el mazo
// POST: saca una carta en orden y coloca el puntero a NULL (libera memoria)
Carta Partida::sacarCartaDelMazo(unsigned int nroJugador){
    // TODO
}

// PRE:
// POST: dependiento el tipo de carta, realizar la accion correspondiente
void Partida::activarCarta(Carta carta){
    // TODO
}

unsigned int Partida::getCantidadJugadores(){
    return this->cantidadDeJugadores;
}

unsigned int Partida::getCantidadJugadoresConSoldados(){
    unsigned int contador = 0;
    for(unsigned int i=0; i<this->cantidadDeJugadores; i++){
        if(this->jugadores[i] != NULL){
            if(this->jugadores[i]->poseeSoldados() == true){
                contador++;
            }else{
                this->jugadorEmprendeRetirada(i);
            }
        }
    }
    return contador;
}

unsigned int Partida::getCantidadDeSoldadosPorJugador(){
    return this->cantidadDeSoldadosPorJugador;
}

int Partida::getTurno(){
    return this->turno;
}

// PRE: 
// POST: Se juega el siguiente turno de la partida, añade uno a la cantidad de turnos
void Partida::siguienteTurno(){
    // TODO
    unsigned int nroJugadorEnTurno = this->getTurno() % this->getCantidadJugadores();
    this->exportarTablero(nroJugadorEnTurno);
    this->realizarDisparosJugador(nroJugadorEnTurno);
    // check si termino el juego (luego de cada disparo?)
    if(this->haTerminado() == true){
        return;
    }
    this->moverUnidad(nroJugadorEnTurno);
    // check si termino el juego
    this->sacarCartaDelMazo(nroJugadorEnTurno);
    // check si termino el juego
    // sumar uno a la cantidad de turnos
}

void Partida::setCantidadJugadores(int cantidadNueva){
    this->cantidadDeJugadores = cantidadNueva;
}

Casillero* Partida::pedirCoordenadasAtaque(){
    unsigned int largo, ancho, alto;
    cout << endl << "Ingrese largo: ";
    largo = this->ingresarNumeroYValidar(1,this->tablero->getLargo());
    cout << endl << "Ingrese ancho: ";
    ancho = this->ingresarNumeroYValidar(1,this->tablero->getAncho());    
    cout << "Ingrese altura: ";
    alto = this->ingresarNumeroYValidar(1, this->tablero->getAlto());
    if(this->tablero->getCasillero(largo, ancho, alto) == NULL){
        throw "EL CASILLERO INGRESADO APUNTA A NULL";
    }
    return this->tablero->getCasillero(largo, ancho, alto);
}

Casillero* Partida::pedirCoordenadasUnidad(TipoDeUnidad tipo){
    unsigned int largo, ancho, alto;
    cout << endl << "Ingrese largo: ";
    largo = this->ingresarNumeroYValidar(1,this->tablero->getLargo());
    cout << endl << "Ingrese ancho: ";
    ancho = this->ingresarNumeroYValidar(1,this->tablero->getAncho());
    if(tipo == soldado){
        while(this->tablero->getCasillero(largo, ancho, 1)->getTipoDeTerreno() == agua){
            cout << endl << "Posicion Invalida. La posicion corresponde a agua.";
            cout << endl << "Ingrese largo: ";
            largo = this->ingresarNumeroYValidar(1, this->tablero->getLargo());
            cout << endl << "Ingrese ancho: ";
            ancho = this->ingresarNumeroYValidar(1, this->tablero->getAncho());
        }
    }else if(tipo == barco){
        while(this->tablero->getCasillero(largo, ancho, 1)->getTipoDeTerreno() == tierra){
            cout << endl << "Posicion Invalida. La posicion corresponde a tierra firme.";
            cout << endl << "Ingrese largo: ";
            largo = this->ingresarNumeroYValidar(1, this->tablero->getLargo());
            cout << endl << "Ingrese ancho: ";
            ancho = this->ingresarNumeroYValidar(1, this->tablero->getAncho());
        }
    }
    alto = 1;
    if(tipo == avion){
        cout << "Ingrese altura: ";
        alto = this->ingresarNumeroYValidar(2, tablero->getAlto());
    }
    if(this->tablero->getCasillero(largo, ancho, alto) == NULL){
        throw "EL CASILLERO INGRESADO APUNTA A NULL";
    }
    return this->tablero->getCasillero(largo, ancho, alto);
}

void Partida::asignarUnidadAlCasillero(Jugador* jugador, int nroUnidad, TipoDeUnidad tipo){
    if(jugador==NULL){
        throw "PUNTERO A JUGADOR NULL AL ASIGNAR UNA UNIDAD AL CASILLERO";
    }
    unsigned int largo, ancho, alto;
    cout << endl << "Jugador #" << jugador->getNumeroJugador() << ", ingrese coordenadas para un nuevo " << Unidad::imprimirTipo(tipo)
        << " #" << nroUnidad << "";
    Casillero * casillero= pedirCoordenadasUnidad(tipo);
    while(casillero->getEstado() == inhabilitado){
        cout << endl << "El casillero ingresado se encuentra inhabilitado. Intente nuevamente";
        casillero = pedirCoordenadasUnidad(tipo);
    }
    if(casillero->getEstado() == ocupado){
        cout << endl << "El soldado #" << nroUnidad << " del jugador #" << jugador->getNumeroJugador() << " ha muerto en combate cuerpo a cuerpo";
        if(casillero->getUnidad() == NULL){
            throw "el puntero de la unidad que ocupa el casillero es NULL";
        }
        cout << endl << "El soldado #" << casillero->getUnidad()->getNroUnidad() << " del jugador #" << casillero->getJugador()->getNumeroJugador() << "ha muerto en combate cuerpo a cuerpo";
        casillero->getJugador()->removerUnidad(casillero->getUnidad());
        // delete casillero->getUnidad();
        casillero->inhabilitar();
        return;
    }
    // El casillero esta vacio
    Unidad* unidad = new Unidad(tipo, nroUnidad, casillero->getCoordenada());
    jugador->asignarUnidad(unidad);    
    casillero->setUnidad(unidad);
    casillero->setJugador(jugador);
    casillero->setEstado(ocupado);
}

bool Partida::esSoldado(Unidad unidad){
    return (unidad.getTipoDeUnidad() == soldado);
}

void Partida::inicializarSoldadosAJugadores(){
    for(unsigned int i = 0; i < this->cantidadDeJugadores; i++){
        for(unsigned int j = 1; j <= this->getCantidadDeSoldadosPorJugador(); j++){
            asignarUnidadAlCasillero(this->jugadores[i], j, soldado);
        }
    }   
}

void Partida::realizarDisparosJugador(unsigned int nroJugador){
    unsigned int disparos = this->jugadores[nroJugador]->getCantidadDisparosDisponibles();
    cout << endl << "El jugador " << nroJugador << "posee " << disparos << "disparos";
    while(disparos >0){
        cout << endl << "Ingrese una coordenada para atacar";
        Casillero* casillero = this->pedirCoordenadasAtaque();
        if(casillero->getEstado() == inhabilitado){
            cout << endl << "El casillero se encontraba inhabilitado";
        }else if(casillero->getEstado() == vacio){
            cout << endl << "El casillero se encontraba vacio";
            casillero->inhabilitar();
        }else{
            // existe una unidad en el casillero
            cout << endl << "El "<< Unidad::imprimirTipo(casillero->getUnidad()->getTipoDeUnidad()) << "#" << casillero->getUnidad()->getNroUnidad()
                 << " del jugador #" << casillero->getJugador() << "ha muerto";
            casillero->getJugador()->removerUnidad(casillero->getUnidad());
            // delete casillero->getUnidad();
            casillero->inhabilitar();
        }
        // chequeo si el juego ha terminado
        if(this->haTerminado() == true){
            return;
        }
        disparos--;
    }
}

// PRE: 
// POST: jugador elije una unidad y realiza un movimiento con ella
// Jugador ingresa el numero de unidad para obtener su posicion, luego
// usar pedirCoordenadasUnidad() y asignarUnidadAlCasillero()
void Partida::moverUnidad(unsigned int nroJugador){
    // TODO
}
/*
bool Partida::esCoordenadaVecina(Coordenada* coordenada1, Coordenada* coordenada2){
    if( coordenada1 == NULL || coordenada2 == NULL){
        throw "PUNTERO A COORDENADA NULO AL DECIDIR SI CASILLEROS SON VECINOS";
    }
    bool esVecina = false;
    if((coordenada2->getLargo() == coordenada1->getLargo() + 1) || (coordenada2->getLargo() == coordenada1->getLargo() - 1) || (coordenada2->getLargo() == coordenada1->getLargo())){
        if((coordenada2->getAncho() == coordenada1->getAncho() + 1) || (coordenada2->getAncho() == coordenada1->getAncho() - 1) || (coordenada2->getAncho() == coordenada1->getAncho())){
            esVecina = true;
        }
    }
    return esVecina;
}

void Partida::moverUnidad(int nroJugador){
    if(this->jugadores[nroJugador]){
        throw "NUMERO DE JUGADOR INVALIDO AL MOVER UNA UNIDAD";
    }
    unsigned int nroUnidad;
    cout << endl << "Inserte el numero de la unidad que desea mover: ";
    cin >> nroUnidad;
    Unidad* unidadAMover = this->jugadores[nroJugador]->buscarUnidad(nroUnidad);
    while(unidadAMover == NULL){
        cout << endl << "El numero es invalido";
        cout << endl << "Inserte el numero de la unidad que desea mover: ";
        cin >> nroUnidad;
        unidadAMover = this->jugadores[nroJugador]->buscarUnidad(nroUnidad);
    }
    Casillero* casilleroNuevo = this->pedirCoordenadasUnidad(soldado);
    while(!esCoordenadaVecina(unidadAMover->getPosicion(), casilleroNuevo->getCoordenada())){
        cout << "La coordenada ingresada no es vecina." << endl;
        casilleroNuevo = this->pedirCoordenadasUnidad(soldado);
    }
    unidadAMover->setPosicionUnidad(casilleroNuevo->getCoordenada());
}
*/
// PRE: 
// POST: se crea un archivo bitmap con el mapa de la partida
// al comenzar el turno para un jugador se exporta el tablero para el solo
void Partida::exportarTablero(unsigned int nroJugador){
    // TODO
}

bool Partida::haTerminado(){
    if(this->getCantidadJugadoresConSoldados()<=1){
        cout << endl << "El juego ha terminado!";
        return true;
    }
    return false;
}

void Partida::jugadorEmprendeRetirada(unsigned int nroJugador){
    if(this->jugadores[nroJugador] == NULL){
        return;
    }
    Unidad* unidad = this->jugadores[nroJugador]->buscarUnidad(1);
    Coordenada* coordenada;
    Casillero* casillero;
    while(unidad != NULL){
        coordenada = unidad->getPosicion();
        if(!coordenada){
            throw "ERROR EN COORDENADA AL EMPRENDER RETIRADA";
        }
        casillero = this->tablero->getCasillero(coordenada->getLargo(), coordenada->getAncho(), coordenada->getAlto());
        if(!casillero){
            throw "ERROR EN CASILLERO AL EMPRENDER RETIRADA";
        }
        this->jugadores[nroJugador]->removerUnidad(unidad);
        casillero->inhabilitar();
    }
    cout << endl << "Al morir todos sus soldados, las unidades del jugador #" << nroJugador << " han emprendido retirada";
}


// PRE:
// POST: devuelve el jugador ganador de la partida, en caso de que haya terminado en empate retorna 0;
unsigned int Partida::jugadorGanador(){
    // TODO
}

Partida::~Partida(){
    // TODO
}