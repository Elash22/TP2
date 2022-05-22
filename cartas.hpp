#ifndef CARTAS_H_
#define CARTAS_H_

enum TipoDeCarta{
    misil,
    avion, 
    barco,
    somnifero,
    robo,
    harakiri
}

class Cartas{
private:
    TipoDeCarta tipo;
};

#endif