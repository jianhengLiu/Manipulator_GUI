#ifndef MATRIX_4_H
#define MATRIX_4_H

#include <iostream>
using namespace std;

class Matrix_4x4
{
private:
    double matrix[4][4];

public:

    Matrix_4x4();//Ĭ�Ϲ��캯������ʼ������Ϊ��λ��
    Matrix_4x4(const double (&mat)[4][4]);//��һ��4x4�Ķ�ά�����ʼ��
    Matrix_4x4(const Matrix_4x4 &mat);//��һ��Matrix_4x4�����ʼ��
    Matrix_4x4(double tangle,double length);
    Matrix_4x4(double x,double y, double z);

    //�������������������������
    friend Matrix_4x4 operator+ (const Matrix_4x4 &m1, const Matrix_4x4 &m2);
    friend Matrix_4x4 operator- (const Matrix_4x4 &m1, const Matrix_4x4 &m2);
    friend Matrix_4x4 operator* (const Matrix_4x4 &m1, const Matrix_4x4 &m2);
    //Matrix_4x4& operator= (const Matrix_4x4 &m);

    double *const operator[] (const int i){return matrix[i];}//˫�±귽ʽ���ʾ���Ԫ��
    //double & get_data(int i, int j) const {return matrix[i][j];} //��ȡ����Ԫ��
    double const& operator() (int i, int j) const {return matrix[i][j];}

    friend ostream& operator <<(ostream& out_put, const Matrix_4x4 &m);//�������������
    friend istream& operator >>(istream& in_put, const Matrix_4x4 &m);//������������

    Matrix_4x4 inverse();
    Matrix_4x4 transpose();
    double det();
};

#endif // MATRIX_4


