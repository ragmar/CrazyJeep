#pragma once
#include "jeep.h"

		jeep::jeep(){
			traslacionX=0.0f;
			traslacionZ=0.0f;
			activo=true;
		}

		jeep::~jeep(){
			vertex.clear();
			cara_vertice.clear();
			cara_normal.clear();
			cara_textura.clear();
			texturas.clear();
			origen.clear();
			norma_point.clear();
		}

		void jeep::Iniciar(){
			traslacionX=0.0f;
			traslacionZ=0.0f;
		}

		void jeep::mover(short eje){ //x = 1 -x = -1 z= 2 -z=-2
			if(eje==1){ // +x
				traslacionX+=VELOCIDAD;
				bounding_box.min.x+=VELOCIDAD;
				bounding_box.max.x+=VELOCIDAD;
				rotacion=0.0f;
			}else if(eje==-1){ // -x
				traslacionX+=-VELOCIDAD;
				bounding_box.min.x-=VELOCIDAD;
				bounding_box.max.x-=VELOCIDAD;
				rotacion=180.0f;
			}else if(eje==2){ // z
				traslacionZ+=VELOCIDAD;
				bounding_box.min.z+=VELOCIDAD;
				bounding_box.max.z+=VELOCIDAD;
				rotacion=270.0f;
			}else if(eje==-2){ // -z
				traslacionZ+=-VELOCIDAD;
				bounding_box.min.z-=VELOCIDAD;
				bounding_box.max.z-=VELOCIDAD;
				rotacion=90.0f;
			}

		}

		void jeep::FilesToLoad(){
			string archivo="";
			string archivo_textura="";
			archivo="./files/Modelos/jeep.obj";
			archivo_textura="./files/Texturas/jeep_army.jpg";
			CargarModelo(archivo);
			texture.Init(archivo_textura);
			texture.CargarTextura();
			MaxOriginal=bounding_box.max;
			MinOriginal=bounding_box.min;
		}

		void jeep::Dibujar(){
			glTranslatef(0.0f,-15.0f,0.0f);
			for(unsigned int i=0;i<cara_vertice.size();i++){
				glBegin(GL_TRIANGLES);
					glTexCoord2f(texturas[cara_textura[i].V[0]].T[0], texturas[cara_textura[i].V[0]].T[1]);
					glNormal3f(norma_point[cara_normal[i].V[0]].x,norma_point[cara_normal[i].V[0]].y,norma_point[cara_normal[i].V[0]].z);
					vertex[cara_vertice[i].V[0]].Pintar();
					
					glTexCoord2f(texturas[cara_textura[i].V[1]].T[0], texturas[cara_textura[i].V[1]].T[1]);
					glNormal3f(norma_point[cara_normal[i].V[1]].x,norma_point[cara_normal[i].V[1]].y,norma_point[cara_normal[i].V[1]].z);
					vertex[cara_vertice[i].V[1]].Pintar();
					
					glTexCoord2f(texturas[cara_textura[i].V[2]].T[0], texturas[cara_textura[i].V[2]].T[1]);
					glNormal3f(norma_point[cara_normal[i].V[2]].x,norma_point[cara_normal[i].V[2]].y,norma_point[cara_normal[i].V[2]].z);
					vertex[cara_vertice[i].V[2]].Pintar();

				glEnd();
			}
		}

		void jeep::Pintar(GLuint car){

			texture.Bind();
			glPushMatrix();
			point medio=bounding_box.Medio();
				glTranslatef(medio.x,medio.y,medio.z);
					glScalef(0.4f,0.4f,0.4f);
					glRotatef(rotacion,0.0f,1.0f,0.0f);
				glTranslatef(-medio.x-centro.x,-medio.y-centro.y,-medio.z-centro.z);

			glTranslatef(traslacionX,0.0f,traslacionZ);
			glCallList(car);
			glPopMatrix();
		}
		

		void jeep::Posicionar(point Pos){
			bounding_box.max=MaxOriginal;
			bounding_box.min=MinOriginal;

			centro=bounding_box.Medio()-Pos;
			bounding_box.max=bounding_box.max-centro;
			bounding_box.min=bounding_box.min-centro;
		}