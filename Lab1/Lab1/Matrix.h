//
// Created by Vladislav Babkin on 2/4/14.
// Copyright (c) 2014 noorg. All rights reserved.
//



#ifndef __Matrix_H_
#define __Matrix_H_

#include "config.h"
class Matrix
{
private:
    int size;
    double** a;

public:
    Matrix(int n, bool generate = true);
    ~Matrix();
    void generate();
    Matrix* buildInverted();
    double& operator()(int i, int j);
    static void subtractRows(double* row1, double* row2, int len, double k);
    static void swapRows(double*& row1, double*& row2, int c);
};


#endif //__Matrix_H_
