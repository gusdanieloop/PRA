#include <bits/stdc++.h>

using namespace std;

typedef struct Casa
{
    long long cepnumero, codigo;
    int n_quartos, n_banheiros, metros_quadrados;
    char cor[10], imobiliaria[30], genero[15];
}Casa;

typedef struct Cod
{
    long long codigo;
    long long posicao;
}Cod;

int main()
{
    streampos posicao;
    fstream binario;
    binario.open("banco_binario.dat", ios::in | ios::binary);
    if(binario.fail())
    {
        cout << "Erro ao abrir o arquivo binario" << endl;
        return 1;
    }
    fstream codigo;
    codigo.open("indice_codigo.dat", ios::out | ios::app | ios::binary);
    if(codigo.fail())
    {
        cout << "Erro ao abrir o arquivo para o indice código" << endl;
        return 1;
    }
    Casa* casa = new Casa();
    Cod* cod = new Cod();
    binario.seekg(0, ios::beg);
    for(int i = 0; i < 10000; i++)
    {
        posicao = binario.tellg();
        binario.read((char*)casa, sizeof(Casa));
        cod->codigo = casa->codigo;
        cod->posicao = posicao;
        cout << "posicao: " << cod->posicao << " codigo: " << cod->codigo << endl;
        codigo.write((char*)cod, sizeof(Cod));
        binario.seekg(sizeof(Casa)*(i+1));
    }
    binario.close();
    codigo.close();

    return 0;
    
}