//
//  main.cpp
//  Lab1
//
//  Created by Vladislav Babkin on 2/4/14.
//  Copyright (c) 2014 noorg. All rights reserved.
//

#include <iostream>
#import "matrix.h"

using namespace std;
void performTest(int N)
{
    Matrix m1(N);
    cout.setf(ios::fixed);
#if !DISABLE_OUTPUT
    for(int i = 0; i<N; ++i)
    {
        for(int j = 0; j<N; ++j)
            cout << m1(i,j) << ' ';
        cout << endl;
    }
    cout << endl;
#endif

    Matrix* m2 = m1.buildInverted();
    if(m2 == NULL)
    {
        cout << "det M == 0;";
    }
#if !DISABLE_OUTPUT

    else
        for(int i = 0; i<N; ++i)
        {
            for(int j = 0; j<N; ++j)
                cout << (*m2)(i,j) << ' ';
            cout << endl;
        }
    cout << endl;
#endif

    if(m2!=NULL) delete m2;
}
int main(int argc, const char * argv[])
{

    /*int N;
    cin >> N;    */
    for(int i = 2; i<=2048; i*=2)
    {
        int testTotal = 0;
        int testCount = 0;
        while(testTotal < CLOCKS_PER_SEC*3)
        {
            int startTime = clock();
            performTest(i);
            int endTime = clock();
            testTotal += endTime- startTime;
            ++testCount;
        }
        cout << i << "\t" << (((double)testTotal)/testCount) / CLOCKS_PER_SEC;
        cout << endl;

    }

    return 0;
}
