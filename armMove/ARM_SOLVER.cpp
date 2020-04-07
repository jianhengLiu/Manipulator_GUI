#include <windows.h>
#include<iostream>
#include<stdio.h>
#include <cmath>
#include <commctrl.h>
#include"resource.h"
#include"ARM_SOLVER.h"

#define PI 3.1415926535

Arm_solver::Arm_solver(float xe_t,float ye_t,float tangleE_t)
{
    xe = xe_t;
    ye =ye_t;
    tangleE = tangleE_t;
    radianE = tangleE*PI/180;
}

void Arm_solver::solver(int flag)
{
    if(flag == 1)
    {
        xc = xe - length3*cos(radianE);
        yc = ye - length3*sin(radianE);

        cosB =(pow(length1,2)+pow(length2,2)-pow(xc,2)-pow(yc,2))/(2*length1*length2);
        sinB = sqrt(1-pow(cosB,2));

        if((length1+length2) >= sqrt(pow(xc,2)+pow(yc,2)))
        {
            radian2 = PI - atan2(sinB,cosB);

            radianA = atan2(yc,xc);
            radianV = atan2(length2*sin(radian2), length1 + length2*cos(radian2));

            radian1 = radianA - radianV;
            radian3 = radianE - radian1 - radian2;

            radian2 += radian1;
            radian3 += radian2;
        }
        else
        {
            MessageBox(NULL,"无解！","提示",MB_OK);
        }

    }
    if(flag == 2)
    {
        xc = xe - length3*cos(radianE);
        yc = ye - length3*sin(radianE);

        cosB =(pow(length1,2)+pow(length2,2)-pow(xc,2)-pow(yc,2))/(2*length1*length2);
        sinB = -sqrt(1-pow(cosB,2));

        if((length1+length2) >= sqrt(pow(xc,2)+pow(yc,2)))
        {
            radian2 = PI - atan2(sinB,cosB);

            radianA = atan2(yc,xc);
            radianV = atan2(length2*sin(radian2), length1 + length2*cos(radian2));

            radian1 = radianA - radianV;
            radian3 = radianE - radian1 - radian2;

            radian2 += radian1;
            radian3 += radian2;
        }
        else
        {
            MessageBox(NULL,"无解！","提示",MB_OK);
        }
    }
}

void Arm_solver::setLength(float length1_t,float length2_t,float length3_t)
{
    length1 = length1_t;
    length2 = length2_t;
    length3 = length3_t;
}

void Arm_solver::tangleDraw(HDC hdc, float& location_x, float& location_y, float radian, float length_temp)
{
    Ellipse(hdc, location_x-10,location_y-10,location_x+10,location_y+10);
    location_x += 10*cos(radian+PI/2);
    location_y -= 10*sin(radian+PI/2);
    LineTo(hdc,location_x,location_y);
    location_x += length_temp*cos(radian);
    location_y -= length_temp*sin(radian);
    LineTo(hdc,location_x,location_y);
    location_x += 20*cos(radian-PI/2);
    location_y -= 20*sin(radian-PI/2);
    LineTo(hdc,location_x,location_y);
    location_x += length_temp*cos(radian-PI);
    location_y -= length_temp*sin(radian-PI);
    LineTo(hdc,location_x,location_y);
    location_x += 10*cos(radian-3*PI/2);
    location_y -= 10*sin(radian-3*PI/2);
    LineTo(hdc,location_x,location_y);

    location_x += length_temp*cos(radian);
    location_y -= length_temp*sin(radian);
    MoveToEx(hdc,location_x,location_y,NULL);
}
