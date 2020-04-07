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

const char g_szClassName[] = "myWindowClass";//�����洢�����Ǵ���������֣����ϻ�������ϵͳע�Դ����࣮
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
        if((HWND)lParam==button1)//�ж���Ϣ�Ƿ����԰���
        {
            nTextLength=GetWindowTextLength(textBox1);//��ȡedit����
            GetWindowText(textBox1,sztextC,nTextLength+1);//��ȡedit text
            arm.tangle1 = atof(sztextC);
            arm.radian1 = arm.tangle1*PI/180;
        }
        if((HWND)lParam==button2)//�ж���Ϣ�Ƿ����԰���
        {
            nTextLength=GetWindowTextLength(textBox2);//��ȡedit����
            GetWindowText(textBox2,sztextC,nTextLength+1);
            arm.tangle2 = atof(sztextC);
            arm.radian2 = arm.tangle2*PI/180;
        }
        if((HWND)lParam==button3)//�ж���Ϣ�Ƿ����԰���
        {
            nTextLength=GetWindowTextLength(textBox3);//��ȡedit����
            GetWindowText(textBox3,sztextC,nTextLength+1);
            arm.tangle3 = atof(sztextC);
            arm.radian3 = arm.tangle3*PI/180;
        }
        if((HWND)lParam==button4)//�ж���Ϣ�Ƿ����԰���
        {
            nTextLength=GetWindowTextLength(textBox4);//��ȡedit����
            GetWindowText(textBox4,sztextC,nTextLength+1);
            arm.xe = atof(sztextC);
            nTextLength=GetWindowTextLength(textBox5);//��ȡedit����
            GetWindowText(textBox5,sztextC,nTextLength+1);
            arm.ye = atof(sztextC);
            nTextLength=GetWindowTextLength(textBox6);//��ȡedit����
            GetWindowText(textBox6,sztextC,nTextLength+1);
            arm.tangleE = atof(sztextC);
            flag = 1;
            arm.solver(flag);
        }
        if((HWND)lParam==button5)//�ж���Ϣ�Ƿ����԰���
        {
            nTextLength=GetWindowTextLength(textBox4);//��ȡedit����
            GetWindowText(textBox4,sztextC,nTextLength+1);
            arm.xe = atof(sztextC);
            nTextLength=GetWindowTextLength(textBox5);//��ȡedit����
            GetWindowText(textBox5,sztextC,nTextLength+1);
            arm.ye = atof(sztextC);
            nTextLength=GetWindowTextLength(textBox6);//��ȡedit����
            GetWindowText(textBox6,sztextC,nTextLength+1);
            arm.tangleE = atof(sztextC);
            arm.radianE = arm.tangleE*PI/180;
            flag = 2;
            arm.solver(flag);
        }
        if((HWND)lParam==button6)//�ж���Ϣ�Ƿ����԰���
        {
            arm.radian1 = 0;
            arm.radian2 = 0;
            arm.radian3 = 0;
        }
        break;

    case WM_CLOSE://WM_CLOSE�������ǰ��¹رհ�ť����Alt+F4���ʱ�����ģ���Ĭ�ϻ�ʹ��������������ϲ����ʽ����������Ϊ�����ڳ����˳�֮ǰ�������飬��ѯ���Ñ��Ƿ񱣴��ļ�������ľ��ѵ�λ��
        DestroyWindow(hwnd);//�����ǵ���DestoryWindow()ϵͳ��Ҫ�����Ĵ����ͳ�WM_DESTORY��Ϣ�����������ǵĴ��ڣ����ڴ�ϵͳ�Ƴ����ǵĴ���֮ǰɾ����ʣ�µ����е��Ӵ���
        break;

    case WM_DESTROY:
        PostQuitMessage(0);//��Ϊ�������ǵĳ�����Ψһ�Ĵ��ڣ����ǜʱ����˲�ϣ�������˳����������ǵ�����PostQuitMessage()
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
    WNDCLASSEX wc;//ע�����ǵĴ�����Ĵ���
    HWND hwnd;//��������
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);//�ṹ��Ĵ�С
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;//Ӧ�ó���ʵ���ľ��
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);//�������Ǵ��ڱ����ɫ�ı���ˢ�ӣ�
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;//�������
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
               WS_EX_CLIENTEDGE,//��һ��������WS_EX_CLIENTEDGE������չ�Ĵ���ʽ������������������õ�һ���Ȳ����ݵı߿�Ч����
               g_szClassName,//������������֣�g_szClassName��������ϵͳ����Ҫ����ʲô���Ĵ��ڣ���Ϊ����Ҫ�Ӹո�ע�Ե��ഴ�����ڣ�����ʹ���˸��������
               "3R armMove",//ָ�������Ǵ��ڵ����ֻ��Ǳ��⣬������ʾ�����Ǵ��ڵ���ۻ��Ǳ������ϣ�
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,//���ڵ����Ͻǵ�X��Y��������Ⱥ͸߶ȣ��Ұ�X��Y������ΪCW_USEDEFAULT����ϵͳ�Լ�ѡ������Ļ���ĸ��ط������ô��ڣ���ס��Ļ������ߵ�X����Ϊ0�����Ҽӣ���Ļ�Ķ�����Y����Ϊ0����׼�.��λ������
               NULL, NULL, hInstance, NULL);//�քe�Ǹ����ڵľ�����˵������Ӧ�ó���ʵ��������ʹ��ڴ������ݵ�ָ��

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    button1=CreateWindow("BUTTON","�ؽڽ�1(�Ƕ�)",WS_VISIBLE|WS_CHILD|WS_BORDER|BS_PUSHBUTTON,10,50,100,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//��������
    button2=CreateWindow("BUTTON","�ؽڽ�2(�Ƕ�)",WS_VISIBLE|WS_CHILD|WS_BORDER|BS_PUSHBUTTON,10,140,100,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//��������
    button3=CreateWindow("BUTTON","�ؽڽ�3(�Ƕ�)",WS_VISIBLE|WS_CHILD|WS_BORDER|BS_PUSHBUTTON,10,230,100,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//��������
    button4=CreateWindow("BUTTON","Ŀ��(x,y,��)-��һ",WS_VISIBLE|WS_CHILD|WS_BORDER|BS_PUSHBUTTON,10,320,150,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//��������
    button5=CreateWindow("BUTTON","Ŀ��(x,y,��)-���",WS_VISIBLE|WS_CHILD|WS_BORDER|BS_PUSHBUTTON,10,360,150,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//��������
    button6=CreateWindow("BUTTON","��λ",WS_VISIBLE|WS_CHILD|WS_BORDER|BS_PUSHBUTTON,10,400,50,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//��������

    textBox1=CreateWindow("EDIT","0",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_WANTRETURN,10,10,100,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//�����ı���
    textBox2=CreateWindow("EDIT","0",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_WANTRETURN,10,100,100,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//�����ı���
    textBox3=CreateWindow("EDIT","0",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_WANTRETURN,10,190,100,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//�����ı���
    textBox4=CreateWindow("EDIT","0",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_WANTRETURN,10,280,30,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//�����ı���
    textBox5=CreateWindow("EDIT","0",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_WANTRETURN,60,280,30,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//�����ı���
    textBox6=CreateWindow("EDIT","0",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_WANTRETURN,110,280,30,30,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//�����ı���
    textBox7=CreateWindow("EDIT","��ʵ�ֹ���:\t1.�����е�۽ǶȽ��б任\t2.����Ŀ�����꼰�ǶȽ��б任\t3.��е���˶��������λ��",WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE|ES_WANTRETURN,10,440,140,100,hwnd,NULL,(HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),NULL);//�����ı���

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}


