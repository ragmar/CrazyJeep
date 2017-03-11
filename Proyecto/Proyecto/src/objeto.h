#pragma once
#include "point.h"
#include "box.h"
#include "textura.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class objeto
{
public:
	float traslacionX;
	float traslacionZ;
	objeto();
	~objeto();
	box bounding_box;
	textura texture;
	point productoCruz(point u, point v);
	void agregarVertice(point vertice);
	void agregarCara(int *C,int *T,int *N);
	void normalizar();
	void CalcularNorma();
	void centrar();
	void Pintar();
	void clear();
	void Pintar_box();
	void agregarNormal(point punto);
	void agregarTextura(float x,float y);
	void lecturaOBJ(string OBJ);
	void CargarModelo(string archivo);
	void FilesToLoad(int Modelo);

	struct cara{
		int V[3];
	};
	struct text{
		float T[2];
	};
	vector <point> origen;
	vector <point> vertex;
	vector <text> texturas;
	vector <point> norma_point;

	vector <cara> cara_vertice;
	vector <cara> cara_normal;
	vector <cara> cara_textura;


};