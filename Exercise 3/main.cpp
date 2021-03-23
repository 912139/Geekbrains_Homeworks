#include <iostream>
using namespace std;

extern const int a;
extern const int b;
extern const int c;
extern const int d;
extern float x;

int main()
{ 
    x = a * (b + (c / d));
    cout<<x;
}