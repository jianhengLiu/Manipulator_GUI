#include "MATRIX_4.h"
#include <iostream>
#include <cmath>

#define PI 3.1415926535

using namespace std;

Matrix_4x4::Matrix_4x4()
{
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            if (i==j)
                matrix[i][j]=1;
            else
                matrix[i][j]=0;
        }
    }
}

Matrix_4x4::Matrix_4x4(const double (&mat)[4][4])
{
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            matrix[i][j]=mat[i][j];
        }
    }
}

Matrix_4x4::Matrix_4x4(const Matrix_4x4 &mat)
{
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            matrix[i][j]=mat.matrix[i][j];
        }
    }
}

Matrix_4x4::Matrix_4x4(double tangle,double length)
{
    double radian = tangle*PI/180;
    double cos_tangle = cos(radian);
    double sin_tangle = sin(radian);
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            if ((i==j)&&(i<2))
                matrix[i][j]=cos_tangle;
            else if (i==j)
                matrix[i][j]=1;
            else if ((i==1)&&(j==0))
                matrix[i][j]=sin_tangle;
            else if ((i==0)&&(j==1))
                matrix[i][j]=-sin_tangle;
            else if ((i==0)&&(j==3))
                matrix[i][j]=length;
            else
                matrix[i][j]=0;
        }
    }
}

Matrix_4x4::Matrix_4x4(double x,double y, double z)
{
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            if((i==0)&&(j==0))
                matrix[i][j]=x;//x
            else if ((i==1)&&(j==0))
                matrix[i][j]=y;//y
            else if ((i==2)&&(j==0))
                matrix[i][j]=z;
            else if ((i==3)&&(j==0))
                matrix[i][j]=1;
            else
                matrix[i][j]=0;
        }
    }
}

Matrix_4x4 operator+ (const Matrix_4x4 &m1, const Matrix_4x4 &m2)
{
    Matrix_4x4 m0;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            m0.matrix[i][j]=m1.matrix[i][j] + m2.matrix[i][j];
        }
    }
    return m0;
}

Matrix_4x4 operator- (const Matrix_4x4 &m1, const Matrix_4x4 &m2)
{
    Matrix_4x4 m0;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            m0.matrix[i][j]=m1.matrix[i][j] - m2.matrix[i][j];
        }
    }
    return m0;
}

Matrix_4x4 operator* (const Matrix_4x4 &m1, const Matrix_4x4 &m2)
{
    double m[4][4]= {0};
    Matrix_4x4 m0(m);
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            for (int p=0; p<4; p++)
            {
                m0.matrix[i][j]+=m1.matrix[i][p] * m2.matrix[p][j];
            }
        }
    }
    return m0;
}

double Matrix_4x4::det()
{
    double DET=1;
    double temp;
    Matrix_4x4 t(matrix);
    Matrix_4x4 s(matrix);
    for (int i=0; i<3; i++)
    {
        int cnt=1;
        while((t[i][i]==0)&&(i+cnt<4))
        {
            for(int k=i; k<4; k++)
            {
                temp=t[i][k];
                t[i][k]=t[i+cnt][k];
                t[i+cnt][k]=(-1)*temp;
            }
            cnt++;
        }
        s = t;
        for (int j=i; j<4; j++)
        {
            for (int p=1; p<4; p++)
            {
                if((i+p<4)&&(t[i][i]!=0))
                {
                    //cout<<"["<<i<<"]["<<j<<"] : "<<t[i][j]<<endl;
                    //cout<<"["<<i+p<<"]["<<i<<"] : "<<s[i+p][i]<<endl;
                    //cout<<"["<<i<<"]["<<i<<"] : "<<t[i][i]<<endl;
                    //cout<<"["<<i+p<<"]["<<j<<"] -= "<<t[i][j]*(s[i+p][i]/t[i][i])<<endl;
                    t[i+p][j]-=t[i][j]*(s[i+p][i]/t[i][i]);
                    if(abs(t[i+p][j])<1e-14)
                        t[i+p][j]=0;
                    //cout<<"t : "<<t<<endl;
                }
            }
        }
    }
    for (int i=0; i<4; i++)
        DET *= t.matrix[i][i];
    return DET;
}

Matrix_4x4 Matrix_4x4::inverse()
{
    if (this->det()!=0)
    {
        double temp;
        double n[4][8];
        double s[4][8];

        //初始化数组
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<8; j++)
            {
                if(j<4)
                    n[i][j]=matrix[i][j];
                else if (i+4==j)
                    n[i][j]=1;
                else
                    n[i][j]=0;
            }
        }

        //下三角化0
        for (int i=0; i<3; i++)
        {
            int cnt=1;

            //检测是否为0
            while((n[i][i]==0)&&(i+cnt<4))
            {
                for(int k=i; k<8; k++)
                {
                    temp=n[i][k];
                    n[i][k]=n[i+cnt][k];
                    n[i+cnt][k]=temp;
                }
                cnt++;
            }

            for (int i=0; i<4; i++)
            {
                for (int j=0; j<8; j++)
                {
                    s[i][j]=n[i][j];
                }
            }

            for (int j=i; j<8; j++)
            {
                for (int p=1; p<4; p++)
                {
                    if((i+p<4)&&(n[i][i]!=0))
                    {
                        //cout<<"["<<i<<"]["<<j<<"] : "<<n[i][j]<<endl;
                        //cout<<"["<<i+p<<"]["<<i<<"] : "<<s[i+p][i]<<endl;
                        //cout<<"["<<i<<"]["<<i<<"] : "<<n[i][i]<<endl;
                        //cout<<"["<<i+p<<"]["<<j<<"] -= "<<n[i][j]*(s[i+p][i]/n[i][i])<<endl;
                        n[i+p][j]-=n[i][j]*(s[i+p][i]/n[i][i]);
                        if(abs(n[i+p][j])<1e-14)
                            n[i+p][j]=0;
                    }
                }

            }
            /*//cout
            cout<<" n : "<<endl;
            for (int i=0; i<4; i++)
            {
                for (int j=0; j<8; j++)
                {
                    cout<<n[i][j]<<"    ";
                }
                cout<<endl;
            }*/
        }

        //上三角化0
        for (int i=3; i>=0; i--)
        {
            //复制数组
            for (int q=0; q<4; q++)
            {
                for (int w=0; w<8; w++)
                {
                    s[q][w]=n[q][w];
                }
            }

            for (int j=i; j<8; j++)
            {
                for (int p=1; p<4; p++)
                {
                    if((i-p>=0)&&(n[i][i]!=0))
                    {
                        //cout<<"["<<i<<"]["<<j<<"] : "<<n[i][j]<<endl;
                        //cout<<"["<<i+p<<"]["<<i<<"] : "<<s[i+p][i]<<endl;
                        //cout<<"["<<i<<"]["<<i<<"] : "<<n[i][i]<<endl;
                        //cout<<"["<<i+p<<"]["<<j<<"] -= "<<n[i][j]*(s[i+p][i]/n[i][i])<<endl;
                        n[i-p][j]-=n[i][j]*(s[i-p][i]/n[i][i]);
                        if(abs(n[i-p][j])<1e-14)
                            n[i-p][j]=0;
                    }
                }


            }
        }

        //化左为单位矩阵
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<8; j++)
                n[i][j]=n[i][j]/s[i][i];
        }
        /*
                //cout
                cout<<" n : "<<endl;
                for (int q=0; q<4; q++)
                {
                    for (int w=0; w<8; w++)
                    {
                        cout<<n[q][w]<<"    ";
                    }
                    cout<<endl;
                }
                */

        Matrix_4x4 tempIn;
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<4; j++)
            {
                tempIn[i][j]=n[i][j+4];
            }
        }
        //cout<<"tempIn : "<<tempIn<<endl;
        return tempIn;
    }
    else
    {
        cout<<"不可逆！"<<endl;
        return Matrix_4x4(matrix);
    }
}

Matrix_4x4 Matrix_4x4::transpose()
{
    Matrix_4x4 temp;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            temp[j][i] = matrix[i][j];
        }
    }
    return temp;
}

ostream& operator <<(ostream& out_put, const Matrix_4x4 &m)
{
    out_put<<endl;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            out_put<<m.matrix[i][j]<<" ";
        }
        out_put<<endl;
    }
    return out_put;
}


