#pragma once
#include <ctime>
#include "point.h"
using namespace std;
#define TAMANO 250
#define LIM_SUP_Z 796.0f
#define LIM_SUP_X 796.0f
#define LIM_INF_Z 796.0f
#define LIM_INF_X 796.0f
#define PROBABILIDAD 500

class Colision{


public:
	int i;
	float rango_x,rango_z;
	int aux;
	int jugadores;
	short Pos_jugadores[8][2];
	short Peso[7];
	short Matriz[TAMANO][TAMANO];
	Colision();
	~Colision();
	void limpiar();
	void Iniciar(int Jugadores);
	void Posiciones(point Centro,int ID);
	bool SetJugador(point Centro,int ID);
	int Decision(int ID,int Movimiento);
};
