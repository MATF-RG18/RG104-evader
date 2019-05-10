#include<stdio.h>
#include<GL/glut.h>
#include "funkcije.h"

#define TIMER_ID 0
#define TIMER_INTERVAL 20

/* Promenljive */
float ugao = 0;
float ugao_pocetni = 45;

int animation_ongoing = 0;
int animation_ongoing_skok = 0;
int animation_ongoing_dole = 0;
int animation_ongoing_ubrzanje = 0;
int animation_ongoing_levo = 0;
int animation_ongoing_desno = 0;

float y_osa = 0;
float x_osa = 0;
float z_osa = 0;

int sekunde = 0;
int ind = 0;
int crvena = 0;
int plava = 1;
int zelena = 0;
int crvenaObj = 0;
int zelenaObj = 0;
int plavaObj = 0;

float x_osaObj = 0;
float y_osaObj = 0;
float z_osaObj = 10;

float x_osaObj2 = 0;
float y_osaObj2 = 3;
float z_osaObj2 = 15;

float x_osaCollect = 0;
float y_osaCollect = 1;
float z_osaCollect = 8;

int skor = 0;

int lower3 = -3;
int upper3 = 3;
int count3 = 1;

int lower2 = -2;
int upper2 = 2;
int count2 = 1;

int num;


void draw_road() {
    glPushMatrix();
	    glColor3f(1,0,0);
	    glRotatef(45, 0, 1, 0);
	    glScalef(2.0, .05, 25);
	    glutSolidCube(4);
    glPopMatrix();
}

void draw_object(){

	glPushMatrix();
		if(num == -3){
			crvenaObj = 1;
			zelenaObj = 0;
			plavaObj = 0;
			glPushMatrix();
				glColor3f(crvenaObj, zelenaObj, plavaObj);
				glTranslatef(x_osaObj, y_osaObj, z_osaObj);			
				glutSolidCube(2);
			glPopMatrix();
					
		}else if(num == 0){
			crvenaObj = 1;
			zelenaObj = 1;
			plavaObj = 0;
			glPushMatrix();
				glColor3f(crvenaObj, zelenaObj, plavaObj);
				glTranslatef(x_osaObj, y_osaObj, z_osaObj);		
				glutSolidCube(2);
			glPopMatrix();
		}else{
			crvenaObj = 0;
			zelenaObj = 1;
			plavaObj = 0;
			glPushMatrix();
				glColor3f(crvenaObj, zelenaObj, plavaObj);
				glTranslatef(x_osaObj, y_osaObj, z_osaObj);
				glutSolidCube(2);
			glPopMatrix();
		}

	glPopMatrix();
}

void draw_ball(){
        
	//glPushMatrix();

	glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);

	glRotatef(ugao_pocetni, 0, 1, 0);
	
	//glPushMatrix();		

		glPushMatrix();
			glColor3f(crvena, 0, plava);
			glTranslatef(x_osa, y_osa+1, z_osa);
			glRotatef(ugao, 1, 0, 0);		
			glutSolidSphere(1, 30, 30);
	      	glPopMatrix();

	//glPopMatrix();	

        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      
	//glPopMatrix();

}

void draw_collect(){
        


	glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);

	glPushMatrix();
		glColor3f(1, 0, 1);
		glTranslatef(x_osaCollect, y_osaCollect, z_osaCollect);
		glRotatef(ugao, 1, 0, 0);		
		glutSolidSphere(0.25, 30, 30);
	glPopMatrix();

		

        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      

}
/* Funkcija za generisanje random broja zbog pojavljivanja objekata */
int generate_random3(){ 
    int i; 
    for (i = 0; i < count3; i++) { 
       num = ((rand() % 3) - 1)*3; 

    } 
    return num;
}


/* Regulisanje komandi */
      
void on_keyboard(unsigned char key, int x, int y){
	
	switch(key){
		case 27:
			exit(0);
			break;
		case 13:
			if(animation_ongoing == 0){
				z_osaObj = 10;
				z_osaObj2 = 12;
				x_osa = 0;
				skor = 0;
				animation_ongoing = 1;
				glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
			}
			break;
		case 32:
			if(y_osa == 0){
				sekunde = 0;
				if(animation_ongoing_ubrzanje == 0){
					animation_ongoing_ubrzanje = 1;
					glutTimerFunc(TIMER_INTERVAL, ubrzanje, TIMER_ID);
				}		
			}
			break;
		case 'w':
			animation_ongoing_dole = 0;
			if(animation_ongoing_skok == 0){
				animation_ongoing_skok = 1;
				glutTimerFunc(TIMER_INTERVAL, skok, TIMER_ID);
				break;
			}
			break;	
		case 's':
			animation_ongoing_skok = 0;
			if(animation_ongoing_dole == 0){
				animation_ongoing_dole = 1;
				glutTimerFunc(TIMER_INTERVAL, dole, TIMER_ID);
			}
			break;
		case 'a':
			if(y_osa == 0.0){
				animation_ongoing_desno = 0;
				if(animation_ongoing_levo == 0){
					animation_ongoing_levo = 1;
					glutTimerFunc(TIMER_INTERVAL, levo, TIMER_ID);
				}
			}
			break;
		case 'd':
			if(y_osa == 0.0){
				animation_ongoing_levo = 0;
				if(animation_ongoing_desno == 0){
					animation_ongoing_desno = 1;
					glutTimerFunc(TIMER_INTERVAL, desno, TIMER_ID);
				}
			}
			break;
	}
      
}
      
void on_display(void){
        
        GLfloat light_position[] = {0,1,0, 0 };
              
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
              
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
                
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	/* pogled kamere */
	gluLookAt(-7, 6, -7, 0, 0, 0, 0, 1, 0);

	draw_road();
	draw_ball();
	draw_object();
	draw_collect();
	

        glutSwapBuffers();
}

void on_timer(int id){
	if(id != TIMER_ID)
		return;

	if(ugao < 100000)
		ugao += 2.5;	

	/* Priblizavanje prepreka */

	if(z_osaObj > -20){
		if(ind == 1){
			z_osaObj -= 0.55;
		}else{
			z_osaObj -= 0.25;
		}
		if(z_osaObj == 0){
			if(x_osaObj == x_osa && y_osaObj == y_osa){
				if(crvenaObj == 1 && zelenaObj == 0 && plavaObj == 0){
					animation_ongoing = 0;
					printf("Izgubili ste, vas rezultat je: %d\n", skor);
				}else if(ind != 1 && (crvenaObj == 1 && zelenaObj == 1)){
					animation_ongoing = 0;
					printf("Izgubili ste, vas rezultat je: %d\n", skor);			
				}
			}
		}		

		if(z_osaObj <= -5){
			z_osaObj = 15;
			x_osaObj = generate_random3(lower2, upper2, count2);
			//y_osaObj = abs(generate_random2(lower3, upper3, count3));
			draw_object();		
		}
		
	}

	/* Priblizavanje loptica koje se skupljaju */
	
	if(z_osaCollect > -20){
		z_osaCollect -= 0.10;
		
		if(z_osaCollect <= 0){
			if(x_osaCollect == x_osa){
				skor++;	
				z_osaCollect = 8;
				x_osaCollect = generate_random3(lower2, upper2, count2);
				draw_collect(0.25);		
			}else{
				z_osaCollect = 8;
				x_osaCollect = generate_random3(lower2, upper2, count2);
				draw_collect(0.25);		
			}	
		}	
		
	}


	if(animation_ongoing)
		glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);

	glutPostRedisplay();

}

void on_reshape(int width, int height){

         glViewport(0, 0, width, height);
      

         glMatrixMode(GL_PROJECTION);
         glLoadIdentity();
         gluPerspective(60, (float) width / height, 1, 100);
}

/* Funkcija za ubrzanje */

void ubrzanje(int id){
	if(id != TIMER_ID)
		return;
		
	if(sekunde < 50){
		ind = 1;
		ugao += 10.5;
		sekunde++;
		crvena = 1;
		plava = 0;
	}else{
		crvena = 0;
		plava = 1;
		ind = 0;
	}

	if(animation_ongoing_ubrzanje)
		glutTimerFunc(TIMER_INTERVAL, ubrzanje, TIMER_ID);

	glutPostRedisplay();

}

/* Funkcija za skok */
 
void skok(int id_skok){

	if(id_skok != TIMER_ID)
		return;

	if(y_osa < 2){
		y_osa += 0.25;		
	}

	if(animation_ongoing_skok)
		glutTimerFunc(TIMER_INTERVAL, skok, TIMER_ID);


	glutPostRedisplay();
	
}

/* Funkcija za spustanje loptice dole */

void dole(int id_dole){
	if(id_dole != TIMER_ID)
		return;

	if(y_osa > 0)
		y_osa -= 0.25;
	
	if(animation_ongoing_dole)
		glutTimerFunc(TIMER_INTERVAL, dole, TIMER_ID);

	glutPostRedisplay();
}

/* Kretanje levo */

void levo(int id_dole){
	if(id_dole != TIMER_ID)
		return;

	if(x_osa < 3)
		x_osa += 0.25;
	if(x_osa == 0)
		animation_ongoing_levo = 0;
	
	if(animation_ongoing_levo)
		glutTimerFunc(TIMER_INTERVAL, levo, TIMER_ID);

	glutPostRedisplay();
}

/* Kretanje desno */

void desno(int id_dole){
	if(id_dole != TIMER_ID)
		return;

	if(x_osa > -3)
		x_osa -= 0.25;

	if(x_osa == 0)
		animation_ongoing_desno = 0;
	
	if(animation_ongoing_desno)
		glutTimerFunc(TIMER_INTERVAL, desno, TIMER_ID);

	glutPostRedisplay();
}
