#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

static int angle = 0;

static void on_display(void);
static void animacija(int val);

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("Evader");

    glutDisplayFunc(on_display);

    glClearColor(1,1,1, 0);

    glutTimerFunc(25, animacija, 0);

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

    angle+=2;
    glutPostRedisplay();

    glutTimerFunc(25, animacija, 0);
}