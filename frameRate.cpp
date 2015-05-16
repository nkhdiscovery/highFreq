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
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

#include <cv.h>
#include <highgui.h>

using namespace cv;

Mat offImg(Mat(700, 1000, CV_32F));
Mat onImg(Mat(700, 1000, CV_32F));
bool lastOn = false;
char windowName[]="Frame";
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


void do_something()
{
    if(lastOn)
    {
        imshow( windowName, offImg);
        cvWaitKey(1/10000);
    }
    else
    {
        imshow( windowName, onImg);
        cvWaitKey(1/10000);
    }
    lastOn = !lastOn ;
}

int main() {
    namedWindow( windowName, WINDOW_OPENGL);
    offImg = cv::Scalar(0,0,0);
    onImg = cv::Scalar(255,255,255);

    imshow( windowName, offImg);
    cvWaitKey();
    timer_start(do_something, 1000);
    while(true);
}
