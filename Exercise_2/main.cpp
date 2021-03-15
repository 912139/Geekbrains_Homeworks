#include <fstream>
#include <iostream>
#include <string>
using std::cin;
using std::cout;

int main()
{
    std::string s1;
    std::string s2;
    std::ifstream out_1("out_1.txt");
    if (!out_1)
    cout << "Failed to create out_1!";
    std::ifstream out_2("out_2.txt");
    if (!out_2)
    cout << "Failed to create out_1!";
    std::getline(out_1,s1,'\n');
    std::getline(out_2,s2,'\n');
    std::ofstream out_3("out_3.txt");
    if (!out_3)
    cout << "Failed to create out_3!";
    out_3<<s1<<'\n';
    out_3<<s2;
    out_1.close ();
    out_2.close ();
    out_3.close ();
    return 0;
}
