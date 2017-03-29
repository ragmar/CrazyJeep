
#pragma comment(lib, "../lib/freeglut.lib")
#pragma comment(lib, "../lib/SDL2.lib")
#pragma comment(lib, "../lib/SDL2main.lib")
#pragma comment(lib, "../lib/SDL2_mixer.lib")
#include "../tools/GL/freeglut.h"
#include "../tools/SDL2/SDL.h"
#include "../tools/SDL2/SDL_mixer.h"
#include <string>
#include <ctime>
#include "objeto.h"
#include "jeep.h"
#include "textura.h"
#include "Jugador.h"
#include "muro.h"
#include "Colision.h"
#include "VariablesGlobales.h"

GLvoid drawQuad(float p, float q, float r, float s, float t, float u, float v, float w, int sigma) {
	point a,b,c,d;
	a.x = p; a.y = q;
	b.x = r; b.y = s;
	c.x = t; c.y = u;
	d.x = v; d.y = w;
	texturitas[sigma].Bind();
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		a.Pintar();
		glTexCoord2f(0, 0);
		c.Pintar();
		glTexCoord2f(1, 0);
		d.Pintar();
		glTexCoord2f(1, 1);
		b.Pintar();
	glEnd();
}

GLvoid restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

GLvoid setOrthographicProjection() {

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0,-1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

GLvoid inicializarMusica() {
	if(Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) < 0)
		exit(-1);
	atexit(Mix_CloseAudio);
	sdlMenu = Mix_LoadMUS("./files/Sonidos/Venus.wav");
	sdlJuego = Mix_LoadMUS("./files/Sonidos/BossMain.wav");
	sdlAceleracion = Mix_LoadWAV("./files/Sonidos/Aceleracion.wav");
	sdlChoque = Mix_LoadWAV("./files/Sonidos/Choque.wav");
	Mix_AllocateChannels(2);
}

void Reiniciar() {

	ManejadorMenu=0;
	stringSeleccionado=0;
	EstadoJuego=0;
	Enter=false;
	xMir = yMir = 0.0;
	movimientoJugador = -2;
	lastKey='w';

	for(int a = 0; a < 7; ++a){
		if(a<EnemigosActivos){
			choque[a] = false;
		}else{
			choque[a]=true;
		}
	}
	choque[7]=false;

	tiempo=true;

	Colisionar.limpiar();
	for(int a = 0; a < 8; ++a) {
		pared[a].limpiar();
	}

	point aux;
	for(int i=0;i<7;i++){
		if(i>=EnemigosActivos){
			Enemigos[i].activo=false;
			pared[i].activo=false;
		}else{
			Enemigos[i].activo=true;
			Enemigos[i].Iniciar();
			aux=Enemigos[i].bounding_box.Medio();
			aux.x=XInicial[i];
			aux.z=ZInicial[i];
			Enemigos[i].Posicionar(aux);
			Colisionar.Posiciones(Enemigos[i].bounding_box.Medio(),i);
			pared[i].GenerarMuro(Enemigos[i].bounding_box.Medio(),movimientoEnemigo[i]);
		}
	}
	player.activo=true;
	player.Iniciar();
	aux=player.bounding_box.Medio();
	aux.x=XInicial[7];
	aux.z=ZInicial[7];
	player.Posicionar(aux);

	Colisionar.Posiciones(player.bounding_box.Medio(),7);
	pared[7].GenerarMuro(player.bounding_box.Medio(),movimientoJugador);



}
#include "CamaraTeclas.h"


void LucesDir(){
	
	float v[4]; //auxiliar de 4 posiciones
	v[3]=1.0f;
	for(int i=0;i<2;i++){
			v[0]=-Direccion[i][0] ;v[1]= -Direccion[i][1] ;v[2]=-Direccion[i][2];
			glLightfv(GL_LIGHT0+i, GL_POSITION, v);
	}



	
	//luz 0

	v[0] = ambiental[0][0]; v[1]= ambiental[0][1]; v[2]= ambiental[0][2]; 
	glLightfv(GL_LIGHT0, GL_AMBIENT, v);
	v[0] = especular[0][0]; v[1] = especular[0][1]; v[2] = especular[0][2];
	glLightfv(GL_LIGHT0, GL_SPECULAR, v);
	v[0] = difusa[0][0]; v[1] = difusa[0][1]; v[2] = difusa[0][2];
	glLightfv(GL_LIGHT0, GL_DIFFUSE, v);

	/***********************************/
	//luz 1

	v[0] = ambiental[1][0]; v[1]= ambiental[1][1]; v[2]= ambiental[1][2]; 
	glLightfv(GL_LIGHT1, GL_AMBIENT, v);
	v[0] = especular[1][0]; v[1] = especular[1][1]; v[2] = especular[1][2];
	glLightfv(GL_LIGHT1, GL_SPECULAR, v);
	v[0] = difusa[1][0]; v[1] = difusa[1][1]; v[2] = difusa[1][2];
	glLightfv(GL_LIGHT1, GL_DIFFUSE, v);


}




void DrawJuego(){

	
	glCallList(Scene);
	glPushMatrix();
		glCallList(Scene+1);
		glRotatef(180.0f,0.0f,1.0f,0.0f);
		glCallList(Scene+1);
		glRotatef(90.0f,0.0f,1.0f,0.0f);
		glCallList(Scene+1);
		glRotatef(180.0f,0.0f,1.0f,0.0f);
		glCallList(Scene+1);
	glPopMatrix();

	if(player.activo){
		player.Pintar(Car);

	}else{
		glBindTexture( GL_TEXTURE_2D, 0);
	}
	pared[7].Pintar();
	for(int i=0;i<EnemigosActivos;i++){
		if(pared[i].activo)
			pared[i].Pintar();
		if(Enemigos[i].activo){
			Enemigos[i].Pintar(Car);
		}else{
			glBindTexture( GL_TEXTURE_2D, 0);
		}
	}

	glLoadIdentity();
}
void DrawEnemigos(){
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	GLfloat b;
	b = 0;
	int Dibujar;
	for(GLint a = 0; a < EnemigosActivos; ++a) {
		if(!choque[a])
			Dibujar=0;
		else
			Dibujar=1;
		drawQuad(-0.95f + b, 0.95f, -0.75f + b, 0.95f, -0.95f + b, 0.75f, -0.75f + b, 0.75f, Dibujar);
		b += 0.25;
	}
	glEnable(GL_LIGHTING);
	glPopMatrix();
	restorePerspectiveProjection();
}

void renderBitmapString(
		float x,
		float y,
		void *font,
		string algo,bool seleccionado) {

  if(seleccionado)
	glColor3f(1.0f, 0.0f, 0.0f); 
  else
	glColor3f(0.0f, 1.0f, 0.0f); 
  glBindTexture(GL_TEXTURE_2D,0);
  glRasterPos3f(x, y,0.1f);
  unsigned char *imprimir=(unsigned char*)algo.c_str();
  glutBitmapString(GLUT_BITMAP_HELVETICA_18,imprimir);
}
void DrawMenu(){
		glCallList(Scene+2);
		if(ManejadorMenu==0){
			float y=0.9f;
			for(int i=0;i<4;i++){
				y=y-0.15f;
				if(stringSeleccionado==i){
					renderBitmapString(-0.90f,y,GLUT_BITMAP_HELVETICA_18,MenuInicial[i],true);
				}else{
					renderBitmapString(-0.90f,y,GLUT_BITMAP_HELVETICA_10,MenuInicial[i],false);
				}
			}
		}else if(ManejadorMenu==1){
			float y=0.85f;
			for(int i=0;i<2;i++){
				if(stringSeleccionado==i){
					renderBitmapString(-0.90f,y,GLUT_BITMAP_HELVETICA_18,MenuInstrucciones[i],true);
				}else{
					renderBitmapString(-0.90f,y,GLUT_BITMAP_HELVETICA_10,MenuInstrucciones[i],false);
				}
				y=y-0.55f;
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f); 

}


void renderScene(void) {//renderizar
	glClearColor(0.0, 0.0, 0.0, 0.0);	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





	if(EstadoJuego==-1){
		camara();
		glEnable(GL_LIGHTING);
		DrawJuego();
		DrawEnemigos();
	}else{
		glDisable(GL_LIGHTING);
		setOrthographicProjection();
		glPushMatrix();
		glLoadIdentity();
			if(EstadoJuego==0){
				DrawMenu();
			}else if(EstadoJuego==1){
				glCallList(Scene+3);
			}else if(EstadoJuego==2){
				glCallList(Scene+4);
			}
		glPopMatrix();
		restorePerspectiveProjection();
	}


	glutSwapBuffers();
}

void IddleJuego() {
		if(!comenzoMusicaJuego) {
			Mix_VolumeMusic(100);
			Mix_PlayMusic(sdlJuego, -1);
			channelBoatOutBoard = Mix_PlayChannel(0, sdlAceleracion, -1);
			comenzoMusicaJuego = true;
		}
		int aux;
		for(int i=0;i<EnemigosActivos;i++){//enemigos
			if(pared[i].activo)
				pared[i].Actualizar(Enemigos[i].bounding_box.Medio());
			if(Enemigos[i].activo){
				aux=Colisionar.Decision(i,movimientoEnemigo[i]);
				if(aux!=movimientoEnemigo[i]){
					movimientoEnemigo[i]=aux;
					pared[i].GenerarMuro(Enemigos[i].bounding_box.Medio(),movimientoEnemigo[i]);
				}
				if(Colisionar.SetJugador(Enemigos[i].bounding_box.Medio(),i)) {
					Enemigos[i].mover(movimientoEnemigo[i]);
				} else {
					Enemigos[i].activo=false;
					if(!choque[i]) {
						Mix_PlayChannel(1, sdlChoque, 0);
						choque[i] = true;
					}
				}
			}
		}
		
		//jugador
		pared[7].Actualizar(player.bounding_box.Medio());
		if(player.activo&&Colisionar.SetJugador(player.bounding_box.Medio(),7)) {
			player.mover(movimientoJugador);
		} else {
			player.activo=false;
			if(!choque[7]) {
				Mix_PlayChannel(1, sdlChoque, 0);
				choque[7] = true;
			}
		}

		if(choque[0]&&choque[1]&&choque[2]&&choque[3]&&choque[4]&&choque[5]&&choque[6]) {
			Mix_FadeOutChannel(0, 0);
			EstadoJuego = 1;	// Si todos murieron, ganaste!
		}
		if(choque[7]) {
			Mix_FadeOutChannel(0, 0);
			EstadoJuego = 2;	// Si moriste, perdiste...
		}
}

void IddleFin(){
	if(tiempo){
		time(&start);
		tiempo=false;
	}
	time (&end2);
	double dif;
	dif=difftime (end2,start);
	if(dif>3.0f){
		tiempo=true;
		EstadoJuego=0;
		Reiniciar();
	}
}

void IddleMenu(){
	if(!comenzoMusicaMenu) {
		Mix_VolumeMusic(MIX_MAX_VOLUME);
		Mix_PlayMusic(sdlMenu, -1);
		comenzoMusicaMenu = true;
	}
	if(ManejadorMenu==0){
		if(stringSeleccionado>3){
			stringSeleccionado=3;
		}
	}else if(ManejadorMenu==1){
		stringSeleccionado=1;
	}
	if(Enter){
		if(ManejadorMenu==0){
			if(stringSeleccionado==0){
				Reiniciar();
				EstadoJuego=-1;
			}
			if(stringSeleccionado==1)
				ManejadorMenu=1;
			if(stringSeleccionado==2){
				EnemigosActivos++;
				MenuInicial[2][19]++;
				if(EnemigosActivos>7){
					EnemigosActivos=1;
					MenuInicial[2][19]=49;
				}
			}
			if(stringSeleccionado==3)
				exit(0);
		}else if(ManejadorMenu==1){
			ManejadorMenu=0;
			stringSeleccionado=0;
		}
		Enter=false;
	}
}

void idle() {

	if(EstadoJuego==0){//pantalla principal
		comenzoMusicaJuego = false;
		IddleMenu();
	}else if(EstadoJuego==-1){//logica del jeugo
		comenzoMusicaMenu = false;
		IddleJuego();
	}else if(EstadoJuego==1){//ganar
		IddleFin();
	}else if(EstadoJuego==2){//perder
		IddleFin();
	
	}

	glutPostRedisplay();
}


void click_izquierdo(int boton, int estado, int x, int y) 
{
	float x1 =2.0f*(float)x/(float)w-1.0f;//redimenciono los puntos al tamaño de mi ventana
	float y1= - (2.0f*(float)y/h - 1.0f);
	glutPostRedisplay();
}

void reshape(int x, int y){//redimensiono la pantalla
	
	w = x;
	h = y;
	glViewport(0, 0, w, h);	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, ((GLfloat) w) / ((GLfloat) h), 1.0f, 19000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void Init_Light(){ //LUZ -x

    glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);

	ambiental[0][0] =  ambiental[0][1] = ambiental[0][2] = 1.0f;
	especular[0][0] =1.0f; especular[0][1] =0.5f; especular[0][2]  =0.0f;
	difusa[0][0] = 0.0f; difusa[0][1] = 0.5f; difusa[0][2] =0.5f;

	Direccion[0][0] = 15000.0f;
	Direccion[0][1] =  800.0f;
	Direccion[0][2] = -20000.0f;


	glEnable(GL_LIGHT1);

	ambiental[1][0] = ambiental[1][1] = ambiental[1][2] =0.0f;
	especular[1][0] = especular[1][1] = 0.0f; especular[1][2] = 1.0f;
	difusa[1][0] = 1.0f; difusa[1][1] = 0.5f; difusa[1][2] =0.0f;

	Direccion[1][0] =	34000.0f;
	Direccion[1][1] =	-25000.0f;
	Direccion[1][2] =	-25000.0f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material);
	glMaterialiv(GL_FRONT_AND_BACK,GL_SHININESS,&shiny);
	LucesDir();

}

void init() {
	Scene = glGenLists(5);
	Car = glGenLists(1);
	inicializarMusica();
	EnemigosActivos=7;
	//CARGAR
	for(int a = 0; a < 2; ++a) {
		if(a==0){
			texturitas[a].Init("./files/Texturas/Enemigo.jpg");
		}else{
			texturitas[a].Init("./files/Texturas/Enemigo_Crash.jpg");
		}
		texturitas[a].CargarTextura();
	}
	for(unsigned int i=0;i<7;i++){
		Enemigos[i].FilesToLoad();
		pared[i].FilesToLoad();
	}
	for(int i=0;i<10;i++){
		Escenario[i].FilesToLoad(i);
	}

	player.FilesToLoad();
	pared[7].FilesToLoad();
	Reiniciar();
	//DL	
		//ESCENARIO
	glNewList(Scene, GL_COMPILE);
		for(int i=0;i<6;i++){
				Escenario[i].Pintar();
		}
	glEndList();
	glNewList(Scene+1, GL_COMPILE);
				Escenario[6].Pintar();
	glEndList();
	glNewList(Scene+2, GL_COMPILE);
				Escenario[7].Pintar();
	glEndList();
	glNewList(Scene+3, GL_COMPILE);
				Escenario[8].Pintar();
	glEndList();
	glNewList(Scene+4, GL_COMPILE);
				Escenario[9].Pintar();
	glEndList();

		//CAR
	glNewList(Car,GL_COMPILE);
		player.Dibujar();
	glEndList();



	//OPENGL PROPIEDADES
	glEnable (GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);//zbuffer
	glEnable(GL_CULL_FACE);//BACK FACE
	glEnable(GL_NORMALIZE);
	glDepthFunc(GL_LEQUAL);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);//rellena la figura

	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(teclado_especiales);
	glutMouseFunc(click_izquierdo);
	Init_Light();

}

//Main Principal
int main(int argc, char **argv) {
	FreeConsole();
	w = 800;
	h = 600;
	comenzoMusicaMenu = false;
	comenzoMusicaJuego = false;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	/*glutGameModeString("640x480:32@60");
	if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)){
		glutEnterGameMode();
		init();
	}else {*/
		glutInitWindowPosition(0,0);
		glutInitWindowSize(w,h);
		glutCreateWindow("I.C.G. - Proyecto - Alejandro Sans y Victor Felipe");
		init();
	//}

	glutMainLoop();
	return 0;
}
