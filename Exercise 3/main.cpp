#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main(int argc,char** argv)
{
    string s;
    ifstream out(argv[1]);
    if (!out)
    {
     cout<<"File not found";
    }
    else
    getline (out,s,'\n');
    string s1 = argv[2];
    int pos1 = s.find(s1+" ");
    int pos2 = s.find(" "+s1);
    int pos3 = s.find(" "+s1+" ");
    if (pos1 != -1 || pos2 != -1 || pos3 != -1)
    cout<<"The word is in the file";
    else
    cout<<"The word is not in the file";
    out.close();
    return 0;
}
