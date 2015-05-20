#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>

#include <chrono>
#include <thread>
#include <unistd.h> 
using namespace std;
 
float CL=0;
float CR=1;

int UPDATE_FREQ = 1000 ; 
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
 
    glColor3f(CL,0.0,CR);
    glutSolidTeapot(0.5);
    glutSwapBuffers(); // for GLUT_DOUBLE
}
 
void myIdle(void)
{
    CL= (int)!CL ;
    CR= (int)!CR ;
    myDisplay();
    usleep((double)1000000.0/UPDATE_FREQ);
}

int main(int argc, char *argv[])
{
    printf("Enter delay: \n");
    scanf("%d", &UPDATE_FREQ) ;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Time");

    glutDisplayFunc(&myDisplay);

    glutIdleFunc(&myIdle);


    glutMainLoop();
    return 0;
}
