#include "functions.h"
#include <iostream>
#include <stdarg.h>

namespace functions{
int change (int *arr)
{
    for (int i=0;i<10;i++)
    *(arr + i) = !*(arr + i);
    return *arr;
}
int change1 (int *arr)
{
    int ChangeArray [8] = {1, 4, 7, 10, 13, 16, 19, 22};
    for (int i=0;i<8;i++)
    *(arr+i) = ChangeArray[i];
    return *arr;
}
bool function1 (int *arr)
{
    int left = 0;
    int right = 0;
    bool b = false;
    for (int i=0;i<4;i++)
     {
       for (int j=0;j<=i;j++)
       left += *(arr+j);
       for (int k=i;k<4;k++)
       right += *(arr+k+1);
       if (left==right)
       {
       b=true;
       }
       left = 0;
       right = 0;
     }
     return b;
}
int function2 (int *arr, int n)
{
    int array1[5] {0};
    int j = 0;
    if (n<0)
    {
    int k=-n;
    for(int i=0;i<5-k;i++)
    array1[i] = *(arr+i+k);
    for(int i=5-k;i<5;i++)
    {
    array1[i] = *(arr + j);
    j++;
    }
    }
    else
    {
    for(int i=0;i<5-n;i++)
    array1[i+n] = *(arr+i);
      for(int i=0;i<n;i++)
      {
      array1[i] = *(arr + 5 + i - n);
      }
    }
    for(int i=0;i<5;i++)
    *(arr +i) = array1[i];
return *arr;
}
void change2 (int n, ...)
{
int r;
va_list ap;
int j;
va_start(ap, n);
for (j = 0; j < n; j++)
{
r=va_arg(ap, int);
std::cout<<!r<<' ';
}
}
}
