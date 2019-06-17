#include <bits/stdc++.h>

using namespace std;

typedef struct Casa
{
    long long cepnumero, codigo;
    int n_quartos, n_banheiros, metros_quadrados;
    char cor[10], imobiliaria[30], genero[15];
}Casa;

typedef struct Cepnumero
{
    long long cepnumero;
    long long posicao;
}Cepnumero;

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
    fstream cepnumero;
    cepnumero.open("indice_cepnumero.dat", ios::out | ios::app | ios::binary);
    if(cepnumero.fail())
    {
        cout << "Erro ao abrir o arquivo para o indice cepnumero" << endl;
        return 1;
    }
    Casa* casa = new Casa();
    Cepnumero* cn = new Cepnumero();
    binario.seekg(0, ios::beg);
    for(int i = 0; i < 10000; i++)
    {
        posicao = binario.tellg();
        binario.read((char*)casa, sizeof(Casa));
        cn->cepnumero = casa->cepnumero;
        cn->posicao = posicao;
        cout << "posicao: " << cn->posicao << " cepnumero: " << cn->cepnumero << endl;
        cepnumero.write((char*)cn, sizeof(Cepnumero));
        binario.seekg(sizeof(Casa)*(i+1));
    }
    binario.close();
    cepnumero.close();

    return 0;
    
}