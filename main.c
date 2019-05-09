/* 

RG104-evader

	Projekat iz Racunarske Grafike

		Lazar Ristic 150/2016
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<GL/glut.h>

    
/* Deklaracije callback funkcija. */

static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int);
static void draw_debug_coosys();
static void skok(int);
static void dole(int);
static void ubrzanje(int);
static void levo(int);
static void desno(int);
static void pojavljivanje_objekata(int);

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
float z_osaObj2 = 10;

float x_osaCollect = 0;
float y_osaCollect = 1;
float z_osaCollect = 8;

int generisanje_objekta;
int lower3 = -3;
int upper3 = 3;
int count3 = 1;

int lower2 = -2;
int upper2 = 2;
int count2 = 1;

int num;

int skor = 0;

/* Funkcije za crtanje puta, prepreka i loptica */

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

void draw_ball(double r){
        
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

void draw_collect(double r){
        


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
      
static void on_keyboard(unsigned char key, int x, int y){
	
	switch(key){
		case 27:
			exit(0);
			break;
		case 13:
			if(animation_ongoing == 0){
				z_osaObj = 10;
				z_osaObj2 = 12;
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
      
static void on_display(void){
        
        GLfloat light_position[] = {0,1,0, 0 };
              
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
              
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
                
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	/* pogled kamere */
	gluLookAt(-7, 6, -7, 0, 0, 0, 0, 1, 0);

	draw_road();
	draw_ball(1);
	draw_object();
	draw_collect(0.5);
	

        glutSwapBuffers();
}
      
      
int main(int argc, char **argv){

         GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
         GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
         GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };
      
         GLfloat ambient_coeffs[] = { 0.3, 0.7, 0.3, 1 };
         GLfloat diffuse_coeffs[] = { 0.2, 1, 0.2, 1 };
         GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
         GLfloat shininess = 30;
     

         glutInit(&argc, argv);
         glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
      

         glutInitWindowSize(1000, 1000);
         glutInitWindowPosition(500, 500);
         glutCreateWindow(argv[0]);
      

         glutKeyboardFunc(on_keyboard);
         glutReshapeFunc(on_reshape);
         glutDisplayFunc(on_display);
      

         glClearColor(0, 0, 0, 0);
         glEnable(GL_DEPTH_TEST);
     
         glEnable(GL_LIGHTING);
      

         glEnable(GL_LIGHT0);
      
         glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
         glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
         glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
      

         glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
         glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
         glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
         glMaterialf(GL_FRONT, GL_SHININESS, shininess);
         glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);
         glEnable(GL_COLOR_MATERIAL);

         glutMainLoop();
	

         return 0;
}
      
static void on_timer(int id){
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
			z_osaObj = 10;
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

/* Funkcija za ubrzanje */

static void ubrzanje(int id){
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
 
static void skok(int id_skok){

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

static void dole(int id_dole){
	if(id_dole != TIMER_ID)
		return;

	if(y_osa > 0)
		y_osa -= 0.25;
	
	if(animation_ongoing_dole)
		glutTimerFunc(TIMER_INTERVAL, dole, TIMER_ID);

	glutPostRedisplay();
}

/* Kretanje levo */

static void levo(int id_dole){
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

static void desno(int id_dole){
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
     
static void on_reshape(int width, int height){

         glViewport(0, 0, width, height);
      

         glMatrixMode(GL_PROJECTION);
         glLoadIdentity();
         gluPerspective(60, (float) width / height, 1, 100);
}
      

      
static void draw_debug_coosys(){
         glDisable(GL_LIGHTING);
         glBegin(GL_LINES);
         glColor3f (1, 0, 0);
         glVertex3f(-10, 0, 0);
         glVertex3f(0, 0, 0);
      
         glColor3f (0, 1, 0);
         glVertex3f(0, 10, 0);
         glVertex3f(0, 0, 0);
      
         glColor3f (0, 0, 1);
         glVertex3f(0, 0, -10);
         glVertex3f(0, 0, 0);
         glEnd();
         glEnable(GL_LIGHTING);
}
