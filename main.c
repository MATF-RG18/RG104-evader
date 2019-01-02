#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

    
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

#define TIMER_ID 0
#define TIMER_INTERVAL 20

float ugao = 0;
float ugao_pocetni = 45;
int animation_ongoing = 0;
int animation_ongoing_skok = 0;
int animation_ongoing_dole = 0;
int animation_ongoing_ubrzanje = 0;
int animation_ongoing_levo = 0;
int animation_ongoing_desno = 0;
float y_osa = -3.0;
float x_osa = 0;
float z_osa = 0;
int sekunde = 0;
int crvena = 0;
int plava = 1;

void draw_ball(double r){
        
	glPushMatrix();

	glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);

	glRotatef(ugao_pocetni, 0, 1, 0);
	
	glPushMatrix();		

		glPushMatrix();
			glColor3f(crvena, 0, plava);
			glTranslatef(x_osa, y_osa, z_osa);
			glRotatef(ugao, 1, 0, 0);		
			glutWireSphere(1, 30, 30);
	      	glPopMatrix();

	

	glPopMatrix();

	

        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      
	glPopMatrix();

	
	
}
      
static void on_keyboard(unsigned char key, int x, int y){
	
	switch(key){
		case 27:
			exit(0);
			break;
		case 13:
			if(animation_ongoing == 0){
				animation_ongoing = 1;
				glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
			}
			break;
		case 32:
			if(y_osa == -3.0){
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
			if(y_osa == -3.0){
				animation_ongoing_desno = 0;
				if(animation_ongoing_levo == 0){
					animation_ongoing_levo = 1;
					glutTimerFunc(TIMER_INTERVAL, levo, TIMER_ID);
				}
			}
			break;
		case 'd':
			if(y_osa == -3.0){
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
	gluLookAt(-5, -5, -5, 0, 0, 0, 0, 1, 0);

	draw_ball(1);

	draw_debug_coosys();

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

	if(animation_ongoing)
		glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);

	glutPostRedisplay();

}

static void ubrzanje(int id){
	if(id != TIMER_ID)
		return;
		
	if(sekunde < 50){
		ugao += 10.5;
		sekunde++;
		crvena = 1;
		plava = 0;
	}else{
		crvena = 0;
		plava = 1;
	}

	if(animation_ongoing_ubrzanje)
		glutTimerFunc(TIMER_INTERVAL, ubrzanje, TIMER_ID);

	glutPostRedisplay();

}
 
static void skok(int id_skok){

	if(id_skok != TIMER_ID)
		return;

	if(y_osa < 0){
		y_osa += 0.25;
	}

	if(animation_ongoing_skok)
		glutTimerFunc(TIMER_INTERVAL, skok, TIMER_ID);

	glutPostRedisplay();
	
}

static void dole(int id_dole){
	if(id_dole != TIMER_ID)
		return;

	if(y_osa > -3.0)
		y_osa -= 0.25;
	
	if(animation_ongoing_dole)
		glutTimerFunc(TIMER_INTERVAL, dole, TIMER_ID);

	glutPostRedisplay();
}

static void levo(int id_dole){
	if(id_dole != TIMER_ID)
		return;

	if(x_osa < 2.5)
		x_osa += 0.25;

	if(x_osa == 0)
		animation_ongoing_levo = 0;
	
	if(animation_ongoing_levo)
		glutTimerFunc(TIMER_INTERVAL, levo, TIMER_ID);

	glutPostRedisplay();
}

static void desno(int id_dole){
	if(id_dole != TIMER_ID)
		return;

	if(x_osa > -2.5)
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
