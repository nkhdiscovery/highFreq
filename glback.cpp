
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>

#include <chrono>
#include <thread>
#include <functional>

GLint TIMER_DELAY = 1;

bool lastOn = false;
void setup() { /* empty function  nothing to setup yet */ }
void display() {
    printf("updated\n"); 
    if(lastOn)
    {
         glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    else
    {
         glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    glutSwapBuffers();
}

void myTimer(int id) {                          // timer callback
    printf("Timer just went off.  Reversing colors.\n");
    lastOn = !lastOn;
    glutPostRedisplay();         
    glutTimerFunc(TIMER_DELAY, myTimer, 0);
}
void timer_start(std::function<void(void)> func, unsigned int interval)
{
    std::thread([func, interval]() {
        while (true)
        {
            func();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }).detach();
}

void updateImage()
{
    printf("Updating image\n");
    lastOn = !lastOn ;
    glutPostRedisplay(); 
}

int main(int argc, char *argv[])
{
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
       glutInitWindowSize(800,600);
       glutCreateWindow("Hello World");

       setup();
       glutDisplayFunc(display);

       glutTimerFunc(TIMER_DELAY, myTimer, 0);
//       timer_start(updateImage, 1000);
       glutMainLoop();
       
       
       return 0;
}
