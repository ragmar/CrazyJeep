#pragma once
#include "point.h"
#include "box.h"
#include "textura.h"
#include <vector>
#define ANCHO 2
#define INICIO 2
#define ALTO 0

using namespace std;

class Muro
{
public:
	Muro();
	~Muro();
	unsigned int cantidad;
	textura texture;
	bool activo;
	struct piso{
		point p1,p2,p3,p4,p5,p6,p7,p8;
		int dir;
	};
	vector<piso> pisos;
	void limpiar();
	void Pintar();
	void FilesToLoad();
	void GenerarMuro(point C,int dir);
	void Actualizar(point C);
};