#include <bits/stdc++.h>

using namespace std;

int main()
{
    string ola;
    string ola2;
    cout << "digite uma palavra" << endl;
    cin >> ola;
    fstream file("binario.bin", ios::in | ios::out | ios::binary);
    file.write((char*)&ola, sizeof(ola));
    file.read((char*)&ola2, sizeof(string));
    file.close();
    cout << ola2 << endl;
    return 0;
}