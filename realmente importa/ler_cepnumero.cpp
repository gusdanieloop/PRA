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
    /*fstream binario;
    binario.open("banco_binario.dat", ios::in | ios::binary);
    if(binario.fail())
    {
        cout << "Erro ao abrir o arquivo binario" << endl;
        return 1;
    }*/
    fstream ind_cn;
    ind_cn.open("indice_cepnumero.dat", ios::in | ios::binary);
    Cepnumero* cn = new Cepnumero();
    Casa* casa = new Casa();
    ind_cn.seekg(0, ios::beg);
    for(int i = 0; i < 10000; i++)
    {
        ind_cn.read((char*)cn, sizeof(Cepnumero));
        cout << cn->cepnumero << " na pos " << cn->posicao << endl;
        //cout << "codigo: " << casa->codigo << " cepnumero: " << casa->cepnumero << " n_quartos: " << casa->n_quartos << " n_banheiros: " << casa->n_banheiros << " cor: " << casa->cor << " imobiliaria: " << casa->imobiliaria << " metros_q: " << casa->metros_quadrados << " genero: " << casa->genero << endl;
        //binario.write((char*)&casa, sizeof(Casa));
        ind_cn.seekg(sizeof(Cepnumero)*(i+1));
    }
    ind_cn.close();
    //binario.close();

    return 0;
    
}