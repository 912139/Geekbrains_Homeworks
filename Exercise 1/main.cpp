#include <fstream>
#include <iostream>
#include <string>
using std::cin;
using std::cout;

int main()
{
    char c1[] = "Streams are handled in the cstdio library as pointers to FILE objects";
    char c2[] = "This indicator is set when an error has occurred in an operation related to the stream";
    std::ofstream out_1("out_1.txt");
    if (!out_1)
    cout << "Failed to create out_1!";
    std::ofstream out_2("out_2.txt");
    if (!out_2)
    cout << "Failed to create out_2!";
    out_1<<c1;
    out_2<<c2;
    out_1.close ();
    out_2.close ();
    return 0;
}
