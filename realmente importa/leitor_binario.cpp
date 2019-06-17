#include <bits/stdc++.h>

using namespace std;

typedef struct Casa
{
    long long cepnumero, codigo;
    int n_quartos, n_banheiros, metros_quadrados;
    char cor[10], imobiliaria[30], genero[15];
}Casa;

int main()
{
    fstream binario;
    binario.open("banco_binario.dat", ios::in | ios::binary);
    if(binario.fail())
    {
        cout << "Erro ao abrir o arquivo binario" << endl;
        return 1;
    }
    Casa* casa = new Casa();
    binario.seekg(0, ios::beg);
    for(int i = 0; i <= 10000; i++)
    {
        binario.read((char*)casa, sizeof(Casa));
        cout << "codigo: " << casa->codigo << " cepnumero: " << casa->cepnumero << " n_quartos: " << casa->n_quartos << " n_banheiros: " << casa->n_banheiros << " cor: " << casa->cor << " imobiliaria: " << casa->imobiliaria << " metros_q: " << casa->metros_quadrados << " genero: " << casa->genero << endl;
        //binario.write((char*)&casa, sizeof(Casa));
        binario.seekg(sizeof(Casa)*i);
    }
    binario.close();

    return 0;
    
}