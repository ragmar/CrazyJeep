#pragma once
#include "point.h"
#include "box.h"
#include "objeto.h"

#define VELOCIDAD 1.5

class jeep : public objeto{

public:
	jeep();
	~jeep();
	float traslacionX;
	float traslacionZ;
	float rotacion;
	bool activo;
	point MaxOriginal;
	point MinOriginal;
	point centro;

	void mover(short eje);
	void FilesToLoad();
	void Dibujar();
	void Pintar(GLuint car);
	void Posicionar(point Pos);
	void Iniciar();


};

