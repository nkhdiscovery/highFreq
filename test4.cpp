#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>

#include <chrono>
#include <thread>
#include <functional>
 
using namespace std;
 
float CL=0;
float CR=1;

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
 
    glColor3f(CL,0.0,CR);
    glutSolidTeapot(0.5);
    glutSwapBuffers(); // for GLUT_DOUBLE
}
 
void myIdle(void)
{
     myDisplay();
 
}
 
void timer_start(std::function<void(void)> func, unsigned int interval)
{
    std::thread([func, interval]() {
        while (true)
        {
            func();
            std::this_thread::sleep_for(std::chrono::microseconds(interval));
        }
    }).detach();
}

void updateImage()
{
    CL= (int)!CL ;
    CR= (int)!CR ;
}

int main(int argc, char *argv[])
{
    int TIMER_DELAY = 1000 ; 
    printf("Enter delay: \n");
    scanf("%d", &TIMER_DELAY) ;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Time");

    glutDisplayFunc(&myDisplay);

    glutIdleFunc(&myIdle);

    timer_start(updateImage, TIMER_DELAY);

    glutMainLoop();
    return 0;
}
