#include <iostream>
#include "partida.hpp"
#include "unidad.hpp"
#include "jugador.hpp"
#include "EasyBMP.h"

using namespace std;

Partida::Partida(){
    this->tablero = NULL;
    this->jugadores = NULL;
    this->mazoDeCartas = NULL;

    this->cantidadDeJugadores = 0;
    this->cantidadDeSoldadosPorJugador = 0;
    this->turno = 0;
    this->nroMapa = 1;
}

void Partida::pedirDatos(int& mapaLargo, int& mapaAncho, int& mapaAlto){
    cout << "Bienvenidos, ingrese la cantidad de jugadores: ";
    this->cantidadDeJugadores = this->ingresarNumeroYValidar(MINIMO_JUGADORES, MAXIMO_JUGADORES);
    cout << "Ingrese la cantidad de soldados por jugador con la que van a jugar: ";
    this->cantidadDeSoldadosPorJugador = this->ingresarNumeroYValidar(MINIMO_SOLDADOS, MAXIMO_SOLDADOS);

    cout << "Ingrese el largo del mapa: ";
    mapaLargo = this->ingresarNumeroYValidar(MINIMO_LARGO_ANCHO_TABLERO,MAXIMO_LARGO_ANCHO_TABLERO);
    cout << "Ingrese el ancho del mapa: ";
    mapaAncho = this->ingresarNumeroYValidar(MINIMO_LARGO_ANCHO_TABLERO,MAXIMO_LARGO_ANCHO_TABLERO);
    cout << "Ingrese el alto del mapa: ";
    mapaAlto = this->ingresarNumeroYValidar(MINIMO_ALTO_TABLERO,MAXIMO_ALTO_TABLERO);

    cout << "En que mapa desea jugar? (1 - " << CANTIDAD_MAPAS<< "): ";
    this->nroMapa = this->ingresarNumeroYValidar(0,CANTIDAD_MAPAS);
}

unsigned int Partida::ingresarNumeroYValidar(unsigned int minimo, unsigned int maximo){
    unsigned int numeroIngresado;
    cin >> numeroIngresado;
    while(numeroIngresado < minimo || numeroIngresado > maximo){
        cout << "Entrada incorrecta. Ingrese una cantidad mayor a " << (minimo-1) << " y menor a " << maximo+1 << ": ";
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

void Partida::inicializarMazo(){
    unsigned int cantidadDeCartas= this->getCantidadJugadores() * CANTIDAD_CARTAS_POR_JUGADOR;
    this->mazoDeCartas = new Carta*[cantidadDeCartas]();
    srand((unsigned)time(0));
    int nroAnterior = -1;
    for(unsigned int i=0; i<cantidadDeCartas; i++){
        int randomNumber = (rand() % CANTIDAD_DISTINTA_CARTAS) + 0;
        while(randomNumber == nroAnterior){
            randomNumber = (rand() % CANTIDAD_DISTINTA_CARTAS) + 0;
        }
        nroAnterior = randomNumber;
        TipoDeCarta tipo;
        if(randomNumber==0){
            tipo = Misil;
        }else if(randomNumber==1){
            tipo = NuevoAvion;
        }else if(randomNumber==2){
            tipo = NuevoBarco;
        }else if(randomNumber==3){
            tipo = Somnifero;
        }else if(randomNumber==4){
            tipo = Francotirador;
        }else if(randomNumber==5){
            tipo = Harakiri;
        }
        this->mazoDeCartas[i] = new Carta(tipo);
    }
}

void Partida::sacarCartaDelMazo(unsigned int nroJugador){
    unsigned int turno = this->getTurno();
    unsigned int cantidadDeCartas= this->getCantidadJugadores() * CANTIDAD_CARTAS_POR_JUGADOR;
    Carta* carta = NULL;
    if (turno < cantidadDeCartas){
        carta = this->mazoDeCartas[turno];
        this->activarCarta(carta);
    }
}

void Partida::activarCarta(Carta* carta){
    if(carta == NULL){
        throw "EL PUNTERO A CARTA ES NULO";
    }
    TipoDeCarta tipo = carta->getTipo();
    unsigned int nroJugadorEnTurno = this->getTurno() % this->getCantidadJugadores();
    Jugador* jugadorEnTurno = this->jugadores[nroJugadorEnTurno];
    unsigned int cantidadTotalUnidades = this->jugadores[nroJugadorEnTurno]->getCantidadTotalUnidades();
    if(tipo == Misil){
        cout << endl << "El jugador #" << nroJugadorEnTurno << " saco la carta Misil, en su proximo turno tendra un misil adicional";
        jugadorEnTurno->agregarMisilProximoTurno();
    }else if(tipo == NuevoAvion){
        cout << endl << "El jugador #" << nroJugadorEnTurno << " saco la carta nuevo Avion";
        this->asignarUnidadAlCasillero(jugadorEnTurno, cantidadTotalUnidades+1, avion);
    }else if(tipo == NuevoBarco){
        cout << endl << "El jugador #" << nroJugadorEnTurno << " saco la carta nuevo Barco";
        this->asignarUnidadAlCasillero(jugadorEnTurno, cantidadTotalUnidades+1, barco);
    }else if(tipo == Somnifero){
        cout << endl << "El jugador #" << nroJugadorEnTurno << " saco la carta Somnifero. El jugador #" << (nroJugadorEnTurno+1) % this->getCantidadJugadores()<< " pierde su turno";
        this->activarCartaSomnifero();
    }else if(tipo == Francotirador){
        cout << endl << "El jugador #" << nroJugadorEnTurno << " saco la carta Francotirador.";
        this->realizarDisparosJugador(nroJugadorEnTurno, 1);
    }else if(tipo == Harakiri){
        cout << endl << "El jugador #" << nroJugadorEnTurno << " saco la carta Harakiri. Uno de sus soldados ha muerto";
        activarCartaHarakiri(nroJugadorEnTurno);
    }
}

void Partida::activarCartaSomnifero(){
    this->turno++;
}

void Partida::activarCartaHarakiri(unsigned int nroJugadorEnTurno){
    Unidad* unidad = this->jugadores[nroJugadorEnTurno]->buscarPrimerUnidad();
    if(unidad == NULL){
        throw "PUNTERO A UNIDAD NULO EN CARTA HARAKIRI";
    }
    Coordenada* coordenada = unidad->getPosicion();
    Casillero* casillero = this->tablero->getCasillero(coordenada->getLargo(), coordenada->getAncho(), coordenada->getAlto());
    this->jugadores[nroJugadorEnTurno]->removerUnidad(unidad);
    casillero->inhabilitar();
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

void Partida::siguienteTurno(){
    unsigned int nroJugadorEnTurno = this->getTurno() % this->getCantidadJugadores();
    // cout << endl << "--TEST: exportar tablero";
    // this->exportarTablero(nroJugadorEnTurno);
    this->realizarDisparosJugador(nroJugadorEnTurno, this->jugadores[nroJugadorEnTurno]->getCantidadDisparosDisponibles());
    if(this->haTerminado() == true){
        return;
    }
    this->lanzarMisilesJugador(nroJugadorEnTurno, this->jugadores[nroJugadorEnTurno]->getCantidadMisilesDisponibles());
    if(this->haTerminado() == true){
        return;
    }    
    this->moverUnidad(nroJugadorEnTurno);
    if(this->haTerminado() == true){
        return;
    }
    this->sacarCartaDelMazo(nroJugadorEnTurno);
    if(this->haTerminado() == true){
        return;
    }
    // sumar uno a la cantidad de turnos
    this->turno++;
}

void Partida::setCantidadJugadores(int cantidadNueva){
    this->cantidadDeJugadores = cantidadNueva;
}

Casillero* Partida::pedirCoordenadasAtaque(){
    unsigned int largo, ancho, alto;
    cout << endl << "Ingrese largo: ";
    largo = this->ingresarNumeroYValidar(1,this->tablero->getLargo());
    cout << "Ingrese ancho: ";
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
    cout << "Ingrese ancho: ";
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
    Unidad* unidad = jugador->buscarUnidad(nroUnidad);

    cout << endl << "Jugador #" << jugador->getNumeroJugador() << ", ingrese coordenadas para un " << Unidad::imprimirTipo(tipo)
        << " #" << nroUnidad << "";
    Casillero * casillero= pedirCoordenadasUnidad(tipo);
    Coordenada* coordenadaNueva = casillero->getCoordenada();
    Coordenada* coordenadaVieja;
    if(unidad == NULL){
        coordenadaVieja = NULL;
    }else{
        coordenadaVieja = unidad->getPosicion();
    }
    while(casillero->getEstado() == inhabilitado || !esCoordenadaVecina(coordenadaVieja, coordenadaNueva)){
        cout << endl << "El casillero ingresado se encuentra inhabilitado o no es vecino. Intente nuevamente";
        casillero = pedirCoordenadasUnidad(tipo);
        coordenadaNueva = casillero->getCoordenada();
    }
    if(casillero->getEstado() == ocupado){
        cout << endl << "El soldado #" << nroUnidad << " del jugador #" << jugador->getNumeroJugador() << " ha muerto en combate cuerpo a cuerpo";
        if(unidad != NULL){
            Coordenada* aux =unidad->getPosicion();
            Casillero * viejoCasillero = this->tablero->getCasillero(aux->getLargo(), aux->getAncho(), aux->getAlto());
            viejoCasillero->getJugador()->removerUnidad(casillero->getUnidad());
            viejoCasillero->setEstado(vacio);
            viejoCasillero->setJugador(NULL);
        }

        if(casillero->getUnidad() == NULL){
            throw "el puntero de la unidad que ocupa el casillero es NULL";
        }

        cout << endl << "El soldado #" << casillero->getUnidad()->getNroUnidad() << " del jugador #" << casillero->getJugador()->getNumeroJugador() << " ha muerto en combate cuerpo a cuerpo";
        casillero->getJugador()->removerUnidad(casillero->getUnidad());
        // delete casillero->getUnidad();
        casillero->inhabilitar();
        return;
    }
    // El casillero esta vacio
    if(unidad != NULL){
        Coordenada* aux =unidad->getPosicion();
        Casillero * viejoCasillero = this->tablero->getCasillero(aux->getLargo(), aux->getAncho(), aux->getAlto());
        viejoCasillero->setEstado(vacio);
        viejoCasillero->setJugador(NULL);
    }
    if(unidad == NULL){
        unidad = new Unidad(tipo, nroUnidad, casillero->getCoordenada());
        jugador->asignarUnidad(unidad);    
    }
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

void Partida::realizarDisparosJugador(unsigned int nroJugador, unsigned int disparos){
    while(disparos >0){
        this->exportarTablero(nroJugador);
        cout << "El jugador #" << nroJugador << " posee " << disparos << " disparo(s):";
        cout << endl << "Ingrese una coordenada para atacar:";
        Casillero* casillero = this->pedirCoordenadasAtaque();
        this->realizarDisparoACasillero(casillero);
        // chequeo si el juego ha terminado
        if(this->haTerminado() == true){
            return;
        }
        disparos--;
    }
}

void Partida::realizarDisparoACasillero(Casillero* casillero){
    if(casillero == NULL){
        throw "PUNTERO A CASILLERO NULO AL REALIZAR DISPARO";
    }
    Coordenada* coordenada = casillero->getCoordenada();
    if(casillero->getEstado() == inhabilitado){
        cout << "El casillero ("<<coordenada->getLargo()<<", "<<coordenada->getAncho()<<", "<<coordenada->getAlto()<<") se encontraba inhabilitado";
    }else if(casillero->getEstado() == vacio){
        cout << "El casillero ("<<coordenada->getLargo()<<", "<<coordenada->getAncho()<<", "<<coordenada->getAlto()<<") se encontraba vacio";
        casillero->inhabilitar();
    }else{
        cout << endl << "El "<< Unidad::imprimirTipo(casillero->getUnidad()->getTipoDeUnidad()) << " #" << casillero->getUnidad()->getNroUnidad()
                << " del jugador #" << casillero->getJugador()->getNumeroJugador() << " ha muerto";
        casillero->getJugador()->removerUnidad(casillero->getUnidad());
        // delete casillero->getUnidad();
        casillero->inhabilitar();
    }
}

void Partida::lanzarMisilesJugador(unsigned int nroJugador, unsigned int cantMisiles){
    while(cantMisiles >0){
        this->exportarTablero(nroJugador);
        cout << "El jugador #" << nroJugador << " posee " << cantMisiles << " misil(es):";
        cout << endl << "Ingrese una coordenada para atacar";
        Casillero* casillero = this->pedirCoordenadasAtaque();
        Coordenada* coordenadaObjetivo = casillero->getCoordenada();
        for(int i = coordenadaObjetivo->getLargo() - 1; i <= coordenadaObjetivo->getLargo() + 1; i++){
            for(int j = coordenadaObjetivo->getAncho() - 1; j <= coordenadaObjetivo->getAncho() + 1; j++){
                for(int k = coordenadaObjetivo->getAlto() - 1; k <= coordenadaObjetivo->getAlto() + 1; k++){
                    casillero = this->tablero->getCasillero(i, j, k);
                    if(casillero != NULL){
                        this->realizarDisparoACasillero(casillero);
                    }
                }
            }
        }
        // chequeo si el juego ha terminado
        if(this->haTerminado() == true){
            return;
        }
        cantMisiles--;
    }
}

bool Partida::esCoordenadaVecina(Coordenada* coordenada1, Coordenada* coordenada2){
    bool esVecina = true;
    if( coordenada1 == NULL || coordenada2 == NULL){
        return esVecina;
    }
    esVecina = false;
    if((coordenada2->getLargo() == coordenada1->getLargo() + 1) || (coordenada2->getLargo() == coordenada1->getLargo() - 1) || (coordenada2->getLargo() == coordenada1->getLargo())){
        if((coordenada2->getAncho() == coordenada1->getAncho() + 1) || (coordenada2->getAncho() == coordenada1->getAncho() - 1) || (coordenada2->getAncho() == coordenada1->getAncho())){
            esVecina = true;
        }
    }
    return esVecina;
}

void Partida::moverUnidad(unsigned int nroJugador){
    if(this->jugadores[nroJugador] == NULL){
        throw "NUMERO DE JUGADOR INVALIDO AL MOVER UNA UNIDAD";
    }
    unsigned int nroUnidad;
    cout << endl << "Jugador #"<< nroJugador<<". Inserte el numero de la unidad que desea mover: ";
    cin >> nroUnidad;
    Unidad* unidadAMover = this->jugadores[nroJugador]->buscarUnidad(nroUnidad);
    while(unidadAMover == NULL){
        cout << "El numero es invalido";
        cout << endl << "Inserte el numero de la unidad que desea mover: ";
        cin >> nroUnidad;
        unidadAMover = this->jugadores[nroJugador]->buscarUnidad(nroUnidad);
    }
    this->asignarUnidadAlCasillero(this->jugadores[nroJugador], nroUnidad, soldado);
}

// PRE: 
// POST: se crea un archivo bitmap con el mapa de la partida
// al comenzar el turno para un jugador se exporta el tablero para el solo
void Partida::exportarTablero(unsigned int nroJugador){
    // TODO
    TipoTerreno terreno;
    EstadoDeCasillero estado;
    Unidad* unidad;
    TipoDeUnidad tipo;

    int largo = this->tablero->getLargo();
    int ancho = this->tablero->getAncho();
    int alto = this->tablero->getAlto();

    cout << endl;
    for(int i=1; i<alto+1; i++){
        cout << "ALTURA: "<< i << endl;
        // int tamCasillero = 10;
        // BMP mapa;
        // mapa.SetSize(tamCasillero*largo, tamCasillero*ancho);
        for(int j=1; j<largo+1; j++){
            for(int k=1; k<ancho+1; k++){
                Casillero* casillero = this->tablero->getCasillero(j, k, i);
                // for(int x=0; x<tamCasillero; x++){
                    // for(int y=0; y<tamCasillero; y++){
                        estado = casillero->getEstado();
                        terreno = casillero->getTipoDeTerreno();

                        if(estado == inhabilitado){
                            cout << "X";
                        }else if(estado == ocupado){
                            unidad = casillero->getUnidad();
                            if(unidad != NULL){
                                tipo = unidad->getTipoDeUnidad();
                                if(tipo == soldado){
                                    // cout << nroJugador;
                                    // --TEST
                                    cout << casillero->getJugador()->getNumeroJugador();
                                }else if(tipo == barco){
                                    cout << "B";
                                }else if(tipo == avion){
                                    cout << "A";
                                }
                            }
                        }else{
                            // el casillero esta vacio
                            if(terreno == tierra){
                                // marron
                                cout << "T";
                            }else if(terreno == agua){
                                // azul
                                cout << "~";
                            }else if(terreno == aire){
                                // celeste
                                cout << "@";
                            }
                    // }
                // }
                }
                

            }
            cout << endl;
        }
    }
}

bool Partida::haTerminado(){
    if(this->getCantidadJugadoresConSoldados() <= 1){
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
    return 0;
}

Partida::~Partida(){
    // TODO
}