#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    static float angle = 0;
    angle += 1.0f;
    glRotatef(angle, 0, 0, 1);

    glColor3ub(255,0,0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0,0);
    glVertex2f(10,0);
    glVertex2f(10,10);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

void timer(int extra)
{
    glutPostRedisplay();
    glutTimerFunc(0, timer, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("Timer");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
