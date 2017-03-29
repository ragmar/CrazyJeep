#pragma once
#include "objeto.h"



		objeto::objeto(){
		}

		objeto::~objeto(){
			vertex.clear();
			cara_vertice.clear();
			cara_normal.clear();
			cara_textura.clear();
			texturas.clear();
			origen.clear();
			norma_point.clear();
		}

		void objeto::agregarVertice(point vertice){
			vertex.push_back(vertice);
			if(vertex.size()==1){
				bounding_box.inicializar(vertice);
			}else{
				bounding_box.asignar_menor(vertice);
				bounding_box.asignar_mayor(vertice);
			}
		}

		void objeto::agregarCara(int *C,int *T,int *N){
			cara Aux;
			Aux.V[0]=C[0];
			Aux.V[1]=C[1];
			Aux.V[2]=C[2];
			cara_vertice.push_back(Aux);
			if(T[0]!=-1){
				Aux.V[0]=T[0];
				Aux.V[1]=T[1];
				Aux.V[2]=T[2];
				cara_textura.push_back(Aux);
			}

			if(N[0]!=-1){
				Aux.V[0]=N[0];
				Aux.V[1]=N[1];
				Aux.V[2]=N[2];
				cara_normal.push_back(Aux);
			}
		}
		
		void objeto::agregarNormal(point punto){
			norma_point.push_back(punto);
			
		}

		void objeto::agregarTextura(float x, float y){
			text pos_text;
			pos_text.T[0]=x;
			pos_text.T[1]=y;
			texturas.push_back(pos_text);
		}

		void objeto::normalizar(){ //poner todo entre 0 y 1
			float norm=bounding_box.normalizar();

			bounding_box.max=bounding_box.max/norm;
			bounding_box.min=bounding_box.min/norm;
			for(unsigned int i=0;i<vertex.size();i++){
				vertex[i]=vertex[i]/norm;
			}
		}


		void objeto::CalcularNorma(){//sacar la norma
			if(cara_normal.size()==0){
				float unitario;
				origen.clear();
				norma_point.clear();
				cara_normal.clear();

				origen.resize(cara_vertice.size());
				cara_normal.resize(cara_vertice.size());
				norma_point.resize(vertex.size());
				
				for(unsigned int i=0;i<norma_point.size();i++){
					norma_point[i].x=0.0f;
					norma_point[i].y=0.0f;
					norma_point[i].z=0.0f;
				}

				point u,v,norma;
				for(unsigned int i=0;i<cara_vertice.size();i++){
					cara_normal[i]=cara_vertice[i];
					u=vertex[cara_vertice[i].V[1]]-vertex[cara_vertice[i].V[0]];
					v=vertex[cara_vertice[i].V[2]]-vertex[cara_vertice[i].V[0]];
					//sacar produto cruz
					norma=productoCruz(u,v);
					unitario=norma.norma2();
					norma=norma/unitario; 

					origen[i]=(vertex[cara_vertice[i].V[0]]+vertex[cara_vertice[i].V[1]]+vertex[cara_vertice[i].V[2]])/3.0f;

					norma_point[cara_vertice[i].V[0]]=norma_point[cara_vertice[i].V[0]]+norma;
					norma_point[cara_vertice[i].V[1]]=norma_point[cara_vertice[i].V[1]]+norma;
					norma_point[cara_vertice[i].V[2]]=norma_point[cara_vertice[i].V[2]]+norma;
				}
				for(unsigned int i=0;i<norma_point.size();i++){
					unitario=norma_point[i].norma2();
					norma_point[i]=norma_point[i]/unitario; 
				}
			}
		}

		point objeto::productoCruz(point u, point v){
			point A;
			A.x=u.y*v.z-u.z*v.y;
			A.y=u.z*v.x-u.x*v.z;
			A.z=u.x*v.y-u.y*v.x;
			return A;
		}

		void objeto::centrar(){
			point PM;
			PM=bounding_box.Medio();
			bounding_box.max=bounding_box.max-PM;
			bounding_box.min=bounding_box.min-PM;
			for(unsigned int i=0;i<vertex.size();i++){
				vertex[i]=vertex[i]-PM;
			}
		}

		void objeto::Pintar(){
			texture.Bind();
			glPushMatrix();
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
			glPopMatrix();
		}


		void objeto::clear(){
			vertex.clear();
			cara_vertice.clear();
			cara_normal.clear();
			cara_textura.clear();
			texturas.clear();
			origen.clear();
			norma_point.clear();
		}

		void objeto::Pintar_box(){
			bounding_box.Pintar();
		}


		void  objeto::lecturaOBJ(string OBJ){
			clear();
			ifstream entrada(OBJ.c_str(),ios::in);
			point XYZ;
			string letra,aux_letra;
			string slash ("/");
			size_t found;

			int T,C,N;
			int cara[3];
			int c_normal[3];
			int textura[3];

			if(entrada.is_open()){
				entrada>>letra;
				while(!entrada.eof()){
					if(letra=="v"){
						entrada>>XYZ.x>>XYZ.y>>XYZ.z;
						agregarVertice(XYZ);
					}
					if(letra=="vt"){
						entrada>>XYZ.x>>XYZ.y;
						agregarTextura(XYZ.x,XYZ.y);
					}
					if(letra=="vn"){
						entrada>>XYZ.x>>XYZ.y>>XYZ.z;
						agregarNormal(XYZ);
					}
					if(letra=="f"){
						int i=0;
						while((entrada>>letra)&&(letra[0]>=48&&letra[0]<=57)){
							C=0;T=0;N=0;

							found=letra.find_first_of(slash);
							if (found!=string::npos){
								aux_letra=letra.substr(0,found);
								C=atoi(aux_letra.c_str());

								letra=letra.substr(found+1);

								found=letra.find_first_of(slash);
								if(letra[0]=='/'){
									//vertice y norma
									letra=letra.substr(1);
									N=atoi(letra.c_str());

								}else if (found!=string::npos){
									//vertice textura y norma
									aux_letra=letra.substr(0,found);
									T=atoi(aux_letra.c_str());
									letra=letra.substr(found+1);
									N=atoi(letra.c_str());

								}else{
									//vertice y textura
									aux_letra=letra.substr(found+1,letra.size());
									T=atoi(aux_letra.c_str());
								}
							}else{
								//solo el vertice
								C=atoi(letra.c_str());
							}
							//agregar cara
							if(i==0){
								cara[0]=C-1;
								textura[0]=T-1;
								c_normal[0]=N-1;
								i++;
							}else if(i==1){
								cara[1]=C-1;
								textura[1]=T-1;
								c_normal[1]=N-1;
								i++;
							}else{
								cara[2]=C-1;
								textura[2]=T-1;
								c_normal[2]=N-1;
								agregarCara(cara,textura,c_normal);

								cara[1]=cara[2];
								textura[1]=textura[2];
								c_normal[1]=c_normal[2];
							}
						}
						continue;
					}
					entrada>>letra;
				}

			}else{
				cout<<"no se pudo abrir el archivo"<<endl;	
			}
			CalcularNorma();


		}

		void objeto::CargarModelo(string archivo){
			if(archivo!=""){
				lecturaOBJ(archivo);
			}
		}

		void objeto::FilesToLoad(int Modelo){
			string archivo="";
			string archivo_textura="";
			if(Modelo==0){
				archivo="./files/Modelos/abajo.obj";
				archivo_textura="./files/Texturas/Skybox/Down.tga";
			}else if(Modelo==1){
				archivo="./files/Modelos/adelante.obj";
				archivo_textura="./files/Texturas/Skybox/Front.jpg";
			}else if(Modelo==2){
				archivo="./files/Modelos/atras.obj";
				archivo_textura="./files/Texturas/Skybox/Back.jpg";
			}else if(Modelo==3){
				archivo="./files/Modelos/derecha.obj";
				archivo_textura="./files/Texturas/Skybox/Right.jpg";
			}else if(Modelo==4){
				archivo="./files/Modelos/izquierda.obj";
				archivo_textura="./files/Texturas/Skybox/Left.jpg";
			}else if(Modelo==5){
				archivo="./files/Modelos/arriba.obj";
				archivo_textura="./files/Texturas/Skybox/Up.jpg";
			}else if(Modelo==6){
				archivo="./files/Modelos/borde.obj";
				archivo_textura="./files/Texturas/Skybox/borde.jpg";
			}else if(Modelo>=7){
				archivo="./files/Modelos/menu.obj";
				if(Modelo == 7){
					archivo_textura="./files/Texturas/Menu1.jpg";
				}if(Modelo == 8)
					archivo_textura="./files/Texturas/Menu2.jpg";
				if(Modelo == 9)
					archivo_textura="./files/Texturas/Menu3.jpg";
			}

			CargarModelo(archivo);
			texture.Init(archivo_textura);
			texture.CargarTextura();

	}
