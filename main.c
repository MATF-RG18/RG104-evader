#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

static int angle = 0;
static int b = 0;
static unsigned char taster;
static void on_display(void);
static void animacija(int val);
static void ubrzanje(unsigned char taster);
int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("Evader");

    glutDisplayFunc(on_display);

    glClearColor(1,1,1, 0);

    glutTimerFunc(25, animacija, 0);
    glutKeyboardFunc(ubrzanje);
    glutMainLoop();

    return 0;
}

static void on_display(void){

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,0,1);

    glPushMatrix();

    glTranslatef(0,-0.5,0);
    glRotatef(angle, 1, 0, 0);

    glutWireSphere(0.4, 10, 10);

    glPopMatrix();

    glutSwapBuffers();

}

static void animacija(int val){

        angle+=b;

    glutPostRedisplay();

    glutTimerFunc(25, animacija, 0);
}

static void ubrzanje(unsigned char taster){

    switch(taster){
        case 'w':
            b+=2;
            break;
        case 32:
            b+=15;
            break;
        case 's':
            if(b > 15) {
                b -= 15;
            }
            break;
        case 27:
            exit(1);
    }
}