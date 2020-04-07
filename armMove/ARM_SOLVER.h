#ifndef ARM_SOLVER_H
#define ARM_SOLVER_H

#include <windows.h>
#include<iostream>
#include<stdio.h>
#include <cmath>
#include <commctrl.h>
#include"resource.h"

#define PI 3.1415926535
#define X 470
#define Y 450

class Arm_solver
{
private:
    float cosB = 0;
    float sinB = 0;
    float xc = 0;
    float yc = 0;
    float radianA;
    float radianV;

public:
    float tangle1=0,tangle2=0,tangle3=0,radian1=0,radian2=0,radian3=0;
    float xe = 0;
    float ye = 0;
    float tangleE = 0;
    float radianE = 0;
    float location_x = X;
    float location_y = Y;
    float length1 = 100;
    float length2 = 90;
    float length3 = 60;

    Arm_solver(float xe_t,float ye_t,float tangleE_t);
    void solver(int flag);
    void setLength(float length1_t,float length2_t,float length3_t);
    void tangleDraw(HDC hdc, float& location_x, float& location_y, float radian, float length_temp);
};

#endif
