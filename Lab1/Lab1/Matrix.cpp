//
// Created by Vladislav Babkin on 2/4/14.
// Copyright (c) 2014 noorg. All rights reserved.
//


#include <exception>
#include <iostream>
#include <thread>
#include <ctime>
#include <cstdlib>
#include "config.h"
#include "Matrix.h"

#define myabs(a) (((a)<0)?(-(a)):(a))

Matrix::Matrix(int n, bool gen)
{
    size = n;
    a = NULL;
    if(gen) generate();
}

Matrix::~Matrix()
{
    for(int i = 0; i<size; ++i)
        delete[] a[i];
    delete[] a;
}

Matrix *Matrix::buildInverted()
{
    double** temp_a = new double*[size];
    for(int i = 0; i<size; ++i)
        temp_a[i] = new double[size*2];

    for(int i = 0; i<size; ++i)
    {
        for(int j = 0; j<size; ++j)
            temp_a[i][j] = a[i][j];

        for(int j = size; j<2*size; ++j)
            if(i == j-size)
                temp_a[i][j] = 1;
            else
                temp_a[i][j] = 0;
    }

    //Make 0-s under main diagonal;
    for(int i = 0; i<size; ++i)
    {
        for(int j = i+1; j<size; ++j)
            swapRows(temp_a[i],temp_a[j], i);

        if(myabs(temp_a[i][i]) < 0.0000001)
        {
            for(int i = 0; i<size; ++i)
                delete[] temp_a[i];
            delete[] temp_a;

            return NULL;
        }
        for(int k = i+1; k<size; ++k)
            subtractRows(temp_a[k], temp_a[i], size*2, temp_a[k][i]/temp_a[i][i]);
    }

    //Make 1-s over main diagonal
    for(int i = size-1; i>=0; --i)
        for(int k = i-1; k>=0; --k)
            subtractRows(temp_a[k], temp_a[i], size*2, temp_a[k][i]/temp_a[i][i]);

    //division
    for(int i = 0; i<size; ++i)
        for(int j = size; j<size*2; ++j)
            temp_a[i][j]/=temp_a[i][i];


    Matrix* m = new Matrix(size,false);

    m->a = new double*[size];
    for(int i = 0; i<size; ++i)
    {
        m->a[i] = new double[size];
        for(int j = 0; j<size; ++j)
            m->a[i][j] = temp_a[i][j+size];
    }

    for(int i = 0; i<size; ++i)
        delete[] temp_a[i];
    delete[] temp_a;

    return m;
}

double Matrix::operator ()(int i, int j)
{
    if(i >= 0 && i<size && j>=0 && j<size)
        return a[i][j];
    throw std::exception();
}

void Matrix::generate()
{
    srand(time(NULL));
    if(a!=NULL)
    {
        for(int i = 0; i<size; ++i)
            delete[] a[i];
        delete[] a;
    }

    a = new double*[size];
    for(int i = 0; i<size; ++i)
        a[i] = new double[size];

    for(int i = 0; i<size; ++i)
        for(int j = 0; j<size; ++j)
            a[i][j] = rand()%3000;
}

void Matrix::subtractRows(double *row1, double *row2, int len, double k)
{
    for(int i = 0; i<len; ++i)
        row1[i] -= row2[i] * k;

}

void Matrix::swapRows(double*& row1, double*& row2, int c)
{
    if(myabs(row2[c]) > myabs(row1[c]))
    {
        double* tr = row1;
        row1 = row2;
        row2 = tr;
    }
}
