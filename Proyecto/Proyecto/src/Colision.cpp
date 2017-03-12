#pragma once
#include "Colision.h"

	Colision::Colision(){
		
	}

	Colision::~Colision(){
		
	}

	void Colision::limpiar() {
		for(int i=0;i<TAMANO;i++)
			for(int j=0;j<TAMANO;j++)
				Matriz[i][j]=-1;

		rango_x=LIM_SUP_X+LIM_INF_X;
		rango_z=LIM_SUP_Z+LIM_INF_Z;
		srand ( (unsigned int)time(NULL) );
		for(int i=0;i<7;i++){
			Peso[i]=0;
		}
	}

	void Colision::Iniciar(int Jugadores){
		jugadores=Jugadores;
		for(int i=0;i<8;i++){
			Pos_jugadores[i][0]=-400;
			Pos_jugadores[i][1]=-400;
		}
	}
	
	void Colision::Posiciones(point Centro,int ID){
		float infx=(Centro.x+LIM_INF_X)*(TAMANO-1)/rango_x;
		float infz=(Centro.z+LIM_INF_Z)*(TAMANO-1)/rango_z;
		Pos_jugadores[ID][0]=(int)infx;
		Pos_jugadores[ID][1]=(int)infz;
	}
	
	bool Colision::SetJugador(point Centro,int ID){
		float infx,infz;
		infx=(Centro.x+LIM_INF_X)*(TAMANO-1)/rango_x;
		infz=(Centro.z+LIM_INF_Z)*(TAMANO-1)/rango_z;
		int x,z;
		x=(int)infx;
		z=(int)infz;



		if(x<0||x>=TAMANO||z<0||z>=TAMANO){
			return false;
		}

		if(x!=Pos_jugadores[ID][0]||z!=Pos_jugadores[ID][1]){
			Matriz[Pos_jugadores[ID][0]][Pos_jugadores[ID][1]]=-2;
			Pos_jugadores[ID][0]=x;
			Pos_jugadores[ID][1]=z;
			
		}

		if(Matriz[Pos_jugadores[ID][0]][Pos_jugadores[ID][1]]==-1||Matriz[Pos_jugadores[ID][0]][Pos_jugadores[ID][1]]==ID){
			Matriz[Pos_jugadores[ID][0]][Pos_jugadores[ID][1]]=ID;
			return true;
		}else if(Matriz[Pos_jugadores[ID][0]][Pos_jugadores[ID][1]]!=-2){
			Matriz[Pos_jugadores[ID][0]][Pos_jugadores[ID][1]]=-2;
			return false;
		}else{
			return false;
		}
	

	}

	int Colision::Decision(int ID, int Movimiento){
		int dirI,dirD,dirF;
		int muro=0;
		int probabilidad=1;
		bool ladoI,ladoD,frente;
		dirI=0,dirD=0,dirF=0;
		ladoI=true,ladoD=true,frente=true;
		if(Movimiento==-1){//A
			dirF=-1;
			dirI=2;
			dirD=-2;

			for(int i=1;i<10;i++){
				if(Pos_jugadores[ID][0]-i<0||Matriz[Pos_jugadores[ID][0]-i][Pos_jugadores[ID][1]]!=-1){
					muro=i;
					frente=false;
					break;
				}
			}

			if(Pos_jugadores[ID][1]+1>=TAMANO||Matriz[Pos_jugadores[ID][0]][Pos_jugadores[ID][1]+1]!=-1){
				ladoI=false;
			}
			if(Pos_jugadores[ID][1]-1<0||Matriz[Pos_jugadores[ID][0]][Pos_jugadores[ID][1]-1]!=-1){
				ladoD=false;
			}
		}

		if(Movimiento==1){//D
			dirF=1;
			dirI=-2;
			dirD=2;
			for(int i=1;i<10;i++){
				if(Pos_jugadores[ID][0]+i>=TAMANO||Matriz[Pos_jugadores[ID][0]+i][Pos_jugadores[ID][1]]!=-1){
					muro=i;
					frente=false;
					break;
				}
			}
			if(Pos_jugadores[ID][1]+1>=TAMANO||Matriz[Pos_jugadores[ID][0]][Pos_jugadores[ID][1]+1]!=-1){
				ladoD=false;
			}
			if(Pos_jugadores[ID][1]-1<0||Matriz[Pos_jugadores[ID][0]][Pos_jugadores[ID][1]-1]!=-1){
				ladoI=false;
			}
		}

		if(Movimiento==2){//S
			dirF=2;
			dirI=1;
			dirD=-1;
			for(int i=1;i<10;i++){
				if(Pos_jugadores[ID][1]+i>=TAMANO||Matriz[Pos_jugadores[ID][0]][Pos_jugadores[ID][1]+i]!=-1){
					muro=i;
					frente=false;
					break;
				}
			}
			if(Pos_jugadores[ID][0]+1>=TAMANO||Matriz[Pos_jugadores[ID][0]+1][Pos_jugadores[ID][1]]!=-1){
				ladoI=false;
			}
			if(Pos_jugadores[ID][0]-1<0||Matriz[Pos_jugadores[ID][0]-1][Pos_jugadores[ID][1]]!=-1){
				ladoD=false;
			}
		}

		if(Movimiento==-2){//W
			dirF=-2;
			dirI=-1;
			dirD=1;
			for(int i=1;i<10;i++){
				if(Pos_jugadores[ID][1]-i<0||Matriz[Pos_jugadores[ID][0]][Pos_jugadores[ID][1]-i]!=-1){
					muro=i;
					frente=false;
					break;
				}
			}
			if(Pos_jugadores[ID][0]+1>=TAMANO||Matriz[Pos_jugadores[ID][0]+1][Pos_jugadores[ID][1]]!=-1){
				ladoD=false;
			}
			if(Pos_jugadores[ID][0]-1<0||Matriz[Pos_jugadores[ID][0]-1][Pos_jugadores[ID][1]]!=-1){
				ladoI=false;
			}
		}

		probabilidad=rand()%PROBABILIDAD;
		if(muro!=0&&probabilidad<PROBABILIDAD/muro){
			if(ladoI&&ladoD){
				if(probabilidad<(PROBABILIDAD-(Peso[ID]*300))/muro/2){
					Peso[ID]=1;
					return dirI;
				}else{
					Peso[ID]=-1;
					return dirD;
				}
			}else{
				if(ladoI){
					Peso[ID]=1;
					return dirI;
				}else if(ladoD){
					Peso[ID]=0;
					return dirD;
				}else
					return Movimiento;
			}
		}else{
			if(probabilidad<4){
				if(ladoI&&ladoD){
					if(probabilidad<2-Peso[ID]){
						Peso[ID]=1;
						return dirI;
					}else{
						Peso[ID]=-1;
						return dirD;
					}
				}else{
					if(ladoI){
						return dirI;
						Peso[ID]=1;
					}else if(ladoD){
						return dirD;
						Peso[ID]=-1;
					}else
						return Movimiento;
				}

			}else{
				return Movimiento;	
			}
		}
	}
