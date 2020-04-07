#include <windows.h>
#include<iostream>
#include<stdio.h>
#include <cmath>
#include <commctrl.h>
#include"resource.h"
#include"ARM_SOLVER.h"

#define PI 3.1415926535
#define X 470
#define Y 450

using namespace std;

const char g_szClassName[] = "myWindowClass";//变量存储了我们窗口类的名字，马上会用来向系统注冊窗口类．
int x,y,key;
int draw;

int flag;

HWND button1,button2,button3,button4,button5,button6,textBox1,textBox2,textBox3,textBox4,textBox5,textBox6,textBox7;

Arm_solver arm(0,0,0);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int nTextLength;
    TCHAR sztextC[1024];
    arm.setLength(100,90,60);

    switch(msg)
    {

    case WM_CREATE:
        SetTimer(hwnd,1,200,NULL);
        draw=1;
        break;

    case WM_COMMAND:
        if((HWND)lParam==button1)//判断消息是否来自按键
        {
            nTextLength=GetWindowTextLength(textBox1);//读取edit长度
            GetWindowText(textBox1,sztextC,nTextLength+1);//读取edit text
            arm.tangle1 = atof(sztextC);
            arm.radian1 = arm.tangle1*PI/180;
        }
        if((HWND)lParam==button2)//判断消息是否来自按键
        {
            nTextLength=GetWindowTextLength(textBox2);//读取edit长度
            GetWindowText(textBox2,sztextC,nTextLength+1);
            arm.tangle2 = atof(sztextC);
            arm.radian2 = arm.tangle2*PI/180;
        }
        if((HWND)lParam==button3)//判断消息是否来自按键
        {
            nTextLength=GetWindowTextLength(textBox3);//读取edit长度
            GetWindowText(textBox3,sztextC,nTextLength+1);
            arm.tangle3 = atof(sztextC);
            arm.radian3 = arm.tangle3*PI/180;
        }
        if((HWND)lParam==button4)//判断消息是否来自按键
        {
            nTextLength=GetWindowTextLength(textBox4);//读取edit长度
            GetWindowText(textBox4,sztextC,nTextLength+1);
            arm.xe = atof(sztextC);
            nTextLength=GetWindowTextLength(textBox5);//读取edit长度
            GetWindowText(textBox5,sztextC,nTextLength+1);
            arm.ye = atof(sztextC);
            nTextLength=GetWindowTextLength(textBox6);//读取edit长度
            GetWindowText(textBox6,sztextC,nTextLength+1);
            arm.tangleE = atof(sztextC);
            flag = 1;
            arm.solver(flag);
        }
        if((HWND)lParam==button5)//判断消息是否来自按键
        {
            nTextLength=GetWindowTextLength(textBox4);//读取edit长度
            GetWindowText(textBox4,sztextC,nTextLength+1);
            arm.xe = atof(sztextC);
            nTextLength=GetWindowTextLength(textBox5);//读取edit长度
            GetWindowText(textBox5,sztextC,nTextLength+1);
            arm.ye = atof(sztextC);
            nTextLength=GetWindowTextLength(textBox6);//读取edit长度
            GetWindowText(textBox6,sztextC,nTextLength+1);
            arm.tangleE = atof(sztextC);
            arm.radianE = arm.tangleE*PI/180;
            flag = 2;
            arm.solver(flag);
        }
        if((HWND)lParam==button6)//判断消息是否来自按键
        {
            arm.radian1 = 0;
            arm.radian2 = 0;
            arm.radian3 = 0;
        }
        break;

    case WM_CLOSE://WM_CLOSE是在我们按下关闭按钮或按下Alt+F4组合时产生的．这默认会使窗口销毀，但我喜欢显式处理它，因为这是在程序退出之前做清除检查，或询问用戶是否保存文件等事情的绝佳的位置
        DestroyWindow(hwnd);//当我们调用DestoryWindow()系统向要销毀的窗口送出WM_DESTORY消息，这里是我们的窗口，并在从系统移除我们的窗口之前删除它剩下的所有的子窗口
        break;

    case WM_DESTROY:
        PostQuitMessage(0);//因为这是我们的程序中唯一的窗口，我们準备好了并希望程序退出，所以我们调用了PostQuitMessage()
        break;

    case WM_LBUTTONDOWN:
        arm.xe=LOWORD(lParam)-X;
        arm.ye=Y-HIWORD(lParam);
        arm.radianE = atan2(arm.ye,arm.xe);
        flag = 1;
        arm.solver(flag);
        break;

    case WM_TIMER:
        if(draw)
        {
            static float radian1_ind=0;
            static float radian2_ind=0;
            static float radian3_ind=0;

            if (abs(radian1_ind-arm.radian1)>1e-15)
            {
                radian1_ind+=(arm.radian1-radian1_ind)/3;
            }
            if (abs(radian2_ind-arm.radian2)>1e-15)
            {
                radian2_ind+=(arm.radian2-radian2_ind)/3;
            }
            if (abs(radian3_ind-arm.radian3)>1e-15)
            {
                radian3_ind+=(arm.radian3-radian3_ind)/3;
            }

            HDC hdc=GetDC(hwnd);
            HBRUSH hBrush;
            RECT rect;
            SetRect(&rect, 200, 0,800,800);
            hBrush = CreateSolidBrush(RGB(112, 112, 112));
            FillRect(hdc, &rect, hBrush);
            hBrush = NULL;

            MoveToEx(hdc,X,Y,NULL);
            arm.location_x = X;
            arm.location_y = Y;

            hBrush = CreateSolidBrush(RGB(200,200,200));
            SelectObject(hdc, hBrush);
            HPEN pen = CreatePen(PS_SOLID,5,RGB(200,200,200));
            HPEN old = (HPEN) SelectObject(hdc,pen);
            arm.tangleDraw(hdc,arm.location_x,arm.location_y,radian1_ind,arm.length1);

            hBrush = CreateSolidBrush(RGB(164,220,236));
            SelectObject(hdc, hBrush);
            pen = CreatePen(PS_SOLID,5,RGB(164,220,236));
            old = (HPEN) SelectObject(hdc,pen);
            arm.tangleDraw(hdc,arm.location_x,arm.location_y,radian2_ind,arm.length2);

            hBrush = CreateSolidBrush(RGB(255,255,255));
            SelectObject(hdc,hBrush);
            pen = CreatePen(PS_SOLID,5,RGB(255,255,255));
            old = (HPEN) SelectObject(hdc,pen);
            arm.tangleDraw(hdc,arm.location_x,arm.location_y,radian3_ind,arm.length3);

            ReleaseDC(hwnd,hdc);
        }
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;//注冊我们的窗口类的代码
    HWND hwnd;//创建窗口
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);//结构体的大小
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;//应用程序实例的句柄
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);//设置我们窗口背景顏色的背景刷子．
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;//类的名字
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
               WS_EX_CLIENTEDGE,//第一个参数（WS_EX_CLIENTEDGE）是扩展的窗口式样，这里我设置它想得到一个內部下陷的边框效果．
               g_szClassName,//设置了类的名字（g_szClassName），告诉系统我们要创建什么样的窗口．因为我们要从刚刚注冊的类创建窗口，我们使用了该类的名字
               "3R armMove",//指定了我们窗口的名字或是标题，用来显示在我们窗口的外观或是标题栏上．
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,//窗口的左上角的X，Y坐标和其宽度和高度．我把X，Y坐标设为CW_USEDEFAULT来让系统自己选择在屏幕的哪个地方来放置窗口．记住屏幕的最左边的X坐标为0并向右加；屏幕的顶部的Y坐标为0并向底加.单位是像素
               NULL, NULL, hInstance, NULL);//分別是父窗口的句柄，菜单句柄，应用程序实例句柄，和窗口创建数据的指针

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    button1=CreateWindow("BUTTON","关节角1(角度)",WS_VISIBLE|WS_CHILD|WS_BORDER|BS_PUSHBUTTON,10,50,100,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//创建按键
    button2=CreateWindow("BUTTON","关节角2(角度)",WS_VISIBLE|WS_CHILD|WS_BORDER|BS_PUSHBUTTON,10,140,100,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//创建按键
    button3=CreateWindow("BUTTON","关节角3(角度)",WS_VISIBLE|WS_CHILD|WS_BORDER|BS_PUSHBUTTON,10,230,100,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//创建按键
    button4=CreateWindow("BUTTON","目标(x,y,φ)-解一",WS_VISIBLE|WS_CHILD|WS_BORDER|BS_PUSHBUTTON,10,320,150,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//创建按键
    button5=CreateWindow("BUTTON","目标(x,y,φ)-解二",WS_VISIBLE|WS_CHILD|WS_BORDER|BS_PUSHBUTTON,10,360,150,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//创建按键
    button6=CreateWindow("BUTTON","归位",WS_VISIBLE|WS_CHILD|WS_BORDER|BS_PUSHBUTTON,10,400,50,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//创建按键

    textBox1=CreateWindow("EDIT","0",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_WANTRETURN,10,10,100,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//创建文本框
    textBox2=CreateWindow("EDIT","0",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_WANTRETURN,10,100,100,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//创建文本框
    textBox3=CreateWindow("EDIT","0",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_WANTRETURN,10,190,100,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//创建文本框
    textBox4=CreateWindow("EDIT","0",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_WANTRETURN,10,280,30,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//创建文本框
    textBox5=CreateWindow("EDIT","0",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_WANTRETURN,60,280,30,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//创建文本框
    textBox6=CreateWindow("EDIT","0",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_WANTRETURN,110,280,30,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//创建文本框
    textBox7=CreateWindow("EDIT","可实现功能:\t1.输入机械臂角度进行变换\t2.输入目标坐标及角度进行变换\t3.机械臂运动到鼠标点击位置",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_WANTRETURN,10,440,140,100,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//创建文本框

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}


