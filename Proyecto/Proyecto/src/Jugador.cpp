#pragma once
#include "Jugador.h"


		Jugador::Jugador(){
				activo=true;
		}

		Jugador::~Jugador(){
			vertex.clear();
			cara_vertice.clear();
			cara_normal.clear();
			cara_textura.clear();
			texturas.clear();
			origen.clear();
			norma_point.clear();
		}

