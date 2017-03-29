#pragma once
#include "Muro.h"



		Muro::Muro(){
			
		}

		Muro::~Muro(){
			pisos.clear();
		}

		void Muro::limpiar() {
			cantidad=-1;
			activo=true;
			pisos.clear();
		}
		
		void Muro::GenerarMuro(point C,int dir){
			if(activo){
				piso Aux;
				Aux.dir=dir;
				C.y=ALTO;
				if(dir==1){//llendo a la derecha
					Aux.p1 = C;
					Aux.p2 = C;
					Aux.p1.z = C.z-ANCHO;
					Aux.p2.z = C.z+ANCHO;
					Aux.p1.x = C.x -INICIO;
					Aux.p2.x = C.x -INICIO;
					Aux.p3= Aux.p2;
					Aux.p4=Aux.p1;
				}else if(dir==-1){//llendo a la izquerda
					Aux.p4 = C;
					Aux.p3 = C;
					Aux.p4.z = C.z-ANCHO;
					Aux.p3.z = C.z+ANCHO;
					Aux.p4.x = C.x +INICIO;
					Aux.p3.x = C.x +INICIO;
					Aux.p1= Aux.p4;
					Aux.p2=Aux.p3;
				}else if(dir==2){//llendo hacia abajo
					Aux.p1 = C;
					Aux.p4 = C;
					Aux.p1.x = C.x-ANCHO;
					Aux.p4.x = C.x+ANCHO;
					Aux.p1.z = C.z -INICIO;
					Aux.p4.z = C.z -INICIO;
					Aux.p2= Aux.p1;
					Aux.p3=Aux.p4;
				}else{//llendo hacia arriba
					Aux.p2 = C;
					Aux.p3 = C;
					Aux.p2.x = C.x-ANCHO;
					Aux.p3.x = C.x+ANCHO;
					Aux.p2.z = C.z +INICIO;
					Aux.p3.z = C.z +INICIO;
					Aux.p1= Aux.p2;
					Aux.p4=Aux.p3;
				}
				Aux.p5=Aux.p1;
				Aux.p6=Aux.p2;
				Aux.p7=Aux.p3;
				Aux.p8=Aux.p4;

				Aux.p5.y=-4;
				Aux.p6.y=-4;
				Aux.p7.y=-4;
				Aux.p8.y=-4;

				pisos.push_back(Aux);
				cantidad++;

			}
		}

		void Muro::Actualizar(point C){
			if(activo&&cantidad>=0){
				int dir=pisos[cantidad].dir;
				if(dir==1){
					pisos[cantidad].p3.x=C.x-INICIO;
					pisos[cantidad].p4.x=C.x-INICIO;
					pisos[cantidad].p7.x=C.x-INICIO;
					pisos[cantidad].p8.x=C.x-INICIO;

				}else if(dir==-1){
					pisos[cantidad].p1.x=C.x+INICIO;
					pisos[cantidad].p2.x=C.x+INICIO;
					pisos[cantidad].p5.x=C.x+INICIO;
					pisos[cantidad].p6.x=C.x+INICIO;

				}else if(dir==2){
					pisos[cantidad].p2.z=C.z-INICIO;
					pisos[cantidad].p3.z=C.z-INICIO;
					pisos[cantidad].p6.z=C.z-INICIO;
					pisos[cantidad].p7.z=C.z-INICIO;
				}else{
					pisos[cantidad].p1.z=C.z+INICIO;
					pisos[cantidad].p4.z=C.z+INICIO;
					pisos[cantidad].p5.z=C.z+INICIO;
					pisos[cantidad].p8.z=C.z+INICIO;
				}
			}
		}

		void Muro::Pintar(){
			if(activo&&cantidad>=0){
				texture.Bind();
				for(unsigned int i=0;i<=cantidad;i++){
					glPushMatrix();

					glBegin(GL_QUADS);	
						//CARA 1 (ARRIBA)
							glTexCoord2f(0,0);
							glNormal3f(0.0f,1.0f,0.0f);
							pisos[i].p1.Pintar();
							
							glTexCoord2f(1,0);
							glNormal3f(0.0f,1.0f,0.0f);
							pisos[i].p2.Pintar();
							
							glTexCoord2f(1,1);
							glNormal3f(0.0f,1.0f,0.0f);
							pisos[i].p3.Pintar();

							glTexCoord2f(0,1);
							glNormal3f(0.0f,1.0f,0.0f);
							pisos[i].p4.Pintar();



						//CARA 2 (frente)

							glTexCoord2f(0,0);
							glNormal3f(0.0f,0.0f,-1.0f);
							pisos[i].p8.Pintar();
							
							glTexCoord2f(1,0);
							glNormal3f(0.0f,0.0f,-1.0f);
							pisos[i].p5.Pintar();
							
							glTexCoord2f(1,1);
							glNormal3f(0.0f,0.0f,-1.0f);
							pisos[i].p1.Pintar();

							glTexCoord2f(0,1);
							glNormal3f(0.0f,0.0f,-1.0f);
							pisos[i].p4.Pintar();

						//CARA 3 (atras)

							glTexCoord2f(0,0);
							glNormal3f(0.0f,0.0f,1.0f);
							pisos[i].p6.Pintar();
							
							glTexCoord2f(1,0);
							glNormal3f(0.0f,0.0f,1.0f);
							pisos[i].p7.Pintar();
							
							glTexCoord2f(1,1);
							glNormal3f(0.0f,0.0f,1.0f);
							pisos[i].p3.Pintar();

							glTexCoord2f(0,1);
							glNormal3f(0.0f,0.0f,1.0f);
							pisos[i].p2.Pintar();

						//Cara 4 (izquierda)

							glTexCoord2f(0,0);
							glNormal3f(-1.0f,0.0f,0.0f);
							pisos[i].p5.Pintar();
							
							glTexCoord2f(1,0);
							glNormal3f(-1.0f,0.0f,0.0f);
							pisos[i].p6.Pintar();
							
							glTexCoord2f(1,1);
							glNormal3f(-1.0f,0.0f,0.0f);
							pisos[i].p2.Pintar();

							glTexCoord2f(0,1);
							glNormal3f(-1.0f,0.0f,0.0f);
							pisos[i].p1.Pintar();

						//Cara 5 (Derecha)

							glTexCoord2f(0,0);
							glNormal3f(1.0f,0.0f,0.0f);
							pisos[i].p7.Pintar();
							
							glTexCoord2f(1,0);
							glNormal3f(1.0f,0.0f,0.0f);
							pisos[i].p8.Pintar();
							
							glTexCoord2f(1,1);
							glNormal3f(1.0f,0.0f,0.0f);
							pisos[i].p4.Pintar();

							glTexCoord2f(0,1);
							glNormal3f(1.0f,0.0f,0.0f);
							pisos[i].p3.Pintar();


					glEnd();

					glPopMatrix();
				}
			}
		}



		void Muro::FilesToLoad(){
				string archivo_textura="./files/Texturas/muro.jpg";
				texture.Init(archivo_textura);
				texture.CargarTextura();

	}
