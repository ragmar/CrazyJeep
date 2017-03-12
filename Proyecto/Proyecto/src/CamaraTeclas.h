#pragma once


GLvoid mirar() {
	if(xMir > 30.0)
		xMir = 30.0;
	else if(xMir < -45.0)
		xMir = -45.0;

	if(yMir >45)
		yMir = 45;
	else if(yMir < -45)
		yMir =-45;
}

GLvoid camara() {
	glLoadIdentity();
	point Pa=player.bounding_box.Medio();


	gluLookAt(Pa.x,Pa.y+125,Pa.z+200,
			Pa.x,Pa.y,Pa.z,
			0.0f,1.0f,0.0f);
	glTranslatef(Pa.x,Pa.y,Pa.z);
	if(Pa.x>0)
		glRotatef(-xMir, Pa.x, 0.0f, 0.0f);
	else
		glRotatef(-xMir, -Pa.x, 0.0f, 0.0f);
	glRotatef(yMir, 0.0f, Pa.y, 0.0f);
	glTranslatef(-Pa.x,-Pa.y,-Pa.z);
}


void teclado(unsigned char key, int x, int y){

	if(EstadoJuego==-1){
		point Medio=player.bounding_box.Medio();
		if(key == 27){
			EstadoJuego=0;
			Reiniciar();
		}else if(key=='w'&&lastKey!='s'&&lastKey!='w'){
			if(player.activo){
				pared[7].GenerarMuro(Medio,-2);
			}
			movimientoJugador=-2;
			lastKey='w';
		}else if(key=='d'&&lastKey!='a'&&lastKey!='d'){
			if(player.activo){
				pared[7].GenerarMuro(Medio,1);
			}
			movimientoJugador=1;
			lastKey='d';
		}else if(key=='s'&&lastKey!='w'&&lastKey!='s'){
			if(player.activo){
				pared[7].GenerarMuro(Medio,2);
			}
			movimientoJugador=2;
			lastKey='s';
		}else if(key=='a'&&lastKey!='d'&&lastKey!='a'){
			if(player.activo){
				pared[7].GenerarMuro(Medio,-1);
			}
			movimientoJugador=-1;
			lastKey='a';
		}

	}
	if(EstadoJuego==0){
		if(key==13){
			Enter=true;
		}
	}
	glutPostRedisplay();
}

void teclado_especiales(int key, int x, int y){
	if(EstadoJuego==-1){
			if(key == GLUT_KEY_UP) {
				xMir -= 2.5;
				mirar();
			}
			if(key == GLUT_KEY_DOWN) {
				xMir += 2.5;
				mirar();
			}
			if(key == GLUT_KEY_RIGHT) {
				yMir +=  2.5;
				mirar();
			}
			if(key == GLUT_KEY_LEFT) {
				yMir -=  2.5;
				mirar();
			}

	}else if (EstadoJuego==0){
		if(ManejadorMenu!=1){
			if(key == GLUT_KEY_UP) {
				stringSeleccionado--;
				if(stringSeleccionado<0)
					stringSeleccionado=0;
			}
			if(key == GLUT_KEY_DOWN) {
				stringSeleccionado++;
			}
		}

	}
	glutPostRedisplay();
}
