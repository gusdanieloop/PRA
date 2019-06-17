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
    /*fstream binario;
    binario.open("banco_binario.dat", ios::in | ios::binary);
    if(binario.fail())
    {
        cout << "Erro ao abrir o arquivo binario" << endl;
        return 1;
    }*/
    fstream ind_cod;
    ind_cod.open("indice_codigo.dat", ios::in | ios::binary);
    Cod* cod = new Cod();
    Casa* casa = new Casa();
    ind_cod.seekg(0, ios::beg);
    for(int i = 0; i < 10000; i++)
    {
        ind_cod.read((char*)cod, sizeof(Cod));
        cout << cod->codigo << " na pos " << cod->posicao << endl;
        //cout << "codigo: " << casa->codigo << " cepnumero: " << casa->cepnumero << " n_quartos: " << casa->n_quartos << " n_banheiros: " << casa->n_banheiros << " cor: " << casa->cor << " imobiliaria: " << casa->imobiliaria << " metros_q: " << casa->metros_quadrados << " genero: " << casa->genero << endl;
        //binario.write((char*)&casa, sizeof(Casa));
        ind_cod.seekg(sizeof(Cod)*(i+1));
    }
    //binario.close();

    return 0;
    
}