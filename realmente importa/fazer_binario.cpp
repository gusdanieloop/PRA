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
    ifstream file;
    file.open("banco_dados.txt");
    fstream binario;
    binario.open("banco_binario.dat", ios::app | ios::binary);
    if(binario.fail())
    {
        cout << "falha ao abrir o arquivo binário!" << endl;
        return 1;
    }
    Casa* casa = new Casa();
    string buffer;
    while(!file.eof())
    {
        getline(file, buffer, ' ');
        casa->codigo = stoll(buffer);
        getline(file, buffer, ' ');
        casa->cepnumero = stoll(buffer);
        getline(file, buffer, ' ');
        casa->n_quartos = atoi(buffer.c_str());
        getline(file, buffer, ' ');
        casa->n_banheiros = atoi(buffer.c_str());
        getline(file, buffer, ' ');
        strcpy(casa->cor, buffer.c_str());
        getline(file, buffer, ' ');
        strcpy(casa->imobiliaria, buffer.c_str());
        getline(file, buffer, ' ');
        casa->metros_quadrados = atoi(buffer.c_str());
        getline(file, buffer);
        strcpy(casa->genero, buffer.c_str());
        
        //cout << "codigo: " << casa->codigo << " cepnumero: " << casa->cepnumero << " n_quartos: " << casa->n_quartos << " n_banheiros: " << casa->n_banheiros << " cor: " << casa->cor << " imobiliaria: " << casa->imobiliaria << " metros_q: " << casa->metros_quadrados << " genero: " << casa->genero << endl;

        binario.write((char *)casa, sizeof(Casa));
    }
    file.close();
    binario.close();
}