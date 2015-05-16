/*
 * =====================================================================================
 *
 *       Filename:  frameRate.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/16/2015 08:05:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Navid Khazaee (nkh), navid.khazaee@gmail.com
 *        Company:  nkhdiscovery
 *
 * =====================================================================================
 */

#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

#include <chrono>
#include <thread>
#include <functional>

Display                 *dpy;
Window                  root;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;

void DrawColor(double R, double G, double B, double A) {
    printf("Draw color %f \n", R);
    glClearColor(R, G, B, A);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1., 1., -1., 1., 1., 20.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);
} 

bool lastOn = false;
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
    if(lastOn)
    {
        DrawColor(0.0, 0.0, 0.0, 0.0);
    }
    else
    {
        DrawColor(1.0, 1.0, 1.0, 1.0);
    }
    lastOn = !lastOn ;
}

int main(int argc, char *argv[]) {

    dpy = XOpenDisplay(NULL);

    if(dpy == NULL) {
        printf("\n\tcannot connect to X server\n\n");
        exit(0);
    }

    root = DefaultRootWindow(dpy);

    vi = glXChooseVisual(dpy, 0, att);

    if(vi == NULL) {
        printf("\n\tno appropriate visual found\n\n");
        exit(0);
    } 
    else {
        printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
    }


    cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;

    win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

    XMapWindow(dpy, win);
    XStoreName(dpy, win, "VERY SIMPLE APPLICATION");

    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);

    glEnable(GL_DEPTH_TEST); 

    timer_start(updateImage, 2000);
    while(1) {
        XNextEvent(dpy, &xev);

        if(xev.type == Expose) {
            XGetWindowAttributes(dpy, win, &gwa);
            glViewport(0, 0, gwa.width, gwa.height);
            //DddrawColor( 0, 0, 0, 0); 
            updateImage();
            glXSwapBuffers(dpy, win);
        }

        else if(xev.type == KeyPress) {
            glXMakeCurrent(dpy, None, NULL);
            glXDestroyContext(dpy, glc);
            XDestroyWindow(dpy, win);
            XCloseDisplay(dpy);
            exit(0);
        }
    } /* this closes while(1) { */
} /* this is the } which closes int main(int argc, char *argv[]) { */
