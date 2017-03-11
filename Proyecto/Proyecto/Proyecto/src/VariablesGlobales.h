
using namespace std;

GLuint Scene;
GLuint Car;

Mix_Music *sdlMenu;
Mix_Music *sdlJuego;
Mix_Chunk *sdlAceleracion;
Mix_Chunk *sdlChoque;

GLboolean choque[8];
GLboolean tiempo;
GLboolean Enter;
GLboolean comenzoMusicaMenu;
GLboolean comenzoMusicaJuego;
GLint EstadoJuego;
GLint w=1000;
GLint h=1000;
GLint channelBoatOutBoard;
GLint movimientoJugador;
GLfloat xMir;
GLfloat yMir;
time_t start,end2;
float XInicial[]={-240,-750,750,230,-750,750,-240,230};
float ZInicial[]={-745,-240,230,-745,230,-240,745,745};
objeto Escenario[10];
Jugador player;
jeep Enemigos[7];
int EnemigosActivos;
int movimientoEnemigo[]={2,1,-1,2,1,-1,-2};

Muro pared[8];
Colision Colisionar;


float material[]={1.0f,1.0f,1.0f,1.0f};
float ambiental[2][3];
float difusa[2][3];
float especular[2][3];
float Direccion[2][3];
int shiny=30;
short stringSeleccionado;
short lastKey=0;
short ManejadorMenu;
string MenuInicial[]={"Comenzar","Instrucciones","Cantidad Jugadores 7","Salir"};
string MenuInstrucciones[]={"Evita chocar con los muros y demas jeeps,\ncada jeep genera un muro atras, asi que cuidado\nGanas si todos los jeeps chocan\nPierdes si tu chocas\nw: gira hacia arriba\ns: gira hacia abajo\nd: gira hacia la derecha\na: gira hacia la izqueirda\nFlechas: para rotar la camara ","Regresar"};
textura texturitas[2];
