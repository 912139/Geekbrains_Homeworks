#include <iostream>
#include "functions.h"
using namespace std;

int main()
{
    int (*fx1)(int*);
    int (*fx2)(int*);
    bool (*fx3)(int*);
    int (*fx4)(int*, int);
    void (*fx5)(int, ...);
    fx1 = functions::change;
    fx2 = functions::change1;
    fx3 = functions::function1;
    fx4 = functions::function2;
    fx5 = functions::change2;
    int array1[10] = {1, 1, 0, 0, 1, 0, 1, 1, 0, 0};
    int array2[8] {0};
    int array3[5] {10, 1, 2, 3, 4};
    int n = 2;
    int array4[5] {10, 1, 2, 3, 4};
    int m = 5;
    int array5[5] = {1, 1, 0, 0, 1};
    (*fx1)(array1);
    (*fx2)(array2);
    bool b = (*fx3)(array3);
    (*fx4)(array4, n);
    cout<<"Exercise 1: ";
    for (int i=0;i<10;i++)
    cout<<*(array1 + i)<<' ';
    cout<<"Exercise 2: ";
    for (int i=0;i<8;i++)
    cout<<*(array2 + i)<< ' ';
    cout<<"Exercise 3: ";
    cout<<boolalpha<<b<<' ';
    cout<<"Exercise 4: ";
    for (int i=0;i<5;i++)
    cout<<*(array4 + i)<<' ';
    cout<<"Exercise 5: ";
    cout<<noboolalpha;
    (*fx5)(m, array5[0], array5[1], array5[2], array5[3], array5[4]);
}
