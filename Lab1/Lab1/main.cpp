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

int main(int argc, const char * argv[])
{

    int N;
    cin >> N;
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

    return 0;
}
