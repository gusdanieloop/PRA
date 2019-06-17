#include <bits/stdc++.h>

using namespace std;

#define TAM 10000

class Pagina1No
{
    //indice codigo
    pair<long long, long long> *keys;
    int num_keys;
    Pagina1No **filhos;
    int current_num_keys;
    bool isFolha;

    public:
        Pagina1No(int num_keys, bool isFolha);

        void insertNonFull(long long key, long long pos);

        void splitChild(int i, Pagina1No *y);

        void traverse();

        long long search(long long key);

        friend class Pagina1;
};

class Pagina1
{
    Pagina1No *raiz;
    int num_keys;
    
    public:
        Pagina1(int nk)
        {
            raiz = NULL;
            num_keys = nk;
        }

        void traverse()
        {
            if( raiz != NULL)
                raiz->traverse();
        }

        long long search(long long key)
        {
            return (raiz == NULL)? (long long)-1: raiz->search(key);
        }

        void insert(long long key, long long pos);
};

typedef struct Cod
{
    long long codigo;
    long long posicao;
}Cod;

typedef struct Cepnumero
{
    long long cepnumero;
    long long posicao;
}Cepnumero;

typedef struct Casa
{
    long long cepnumero, codigo;
    int n_quartos, n_banheiros, metros_quadrados;
    char cor[10], imobiliaria[30], genero[15];
}Casa;

Pagina1No::Pagina1No(int _num_keys, bool _isFolha)
{
    num_keys = _num_keys;
    isFolha = _isFolha;

    keys = new pair<long long, long long> [2 * (num_keys - 1)];
    filhos = new Pagina1No * [2 * num_keys];

    current_num_keys = 0;
}

void Pagina1No::traverse()
{
    int i;
    for(i = 0; i < current_num_keys; i++)
    {
        if( isFolha == false)
            filhos[i]->traverse();
        cout << " [" << keys[i].first << "," << keys[i].second << "]";
    }

    if( isFolha == false)
        filhos[i]->traverse();
}

long long Pagina1No::search(long long key)
{
    int i = 0;
    while( i < current_num_keys && key > keys[i].first)
        i++;

    if (keys[i].first == key)
        return keys[i].second;
    
    if( isFolha == true)
        return (long long)-1;
    
    return filhos[i]->search(key);
}

void Pagina1::insert(long long key, long long pos)
{
    if( raiz == NULL)
    {
        raiz = new Pagina1No(num_keys, true);
        raiz->keys[0].first = key;
        raiz->keys[0].second = pos;
        raiz->current_num_keys = 1;
    }
    else
    {
        //puts("a");
        if( raiz->current_num_keys == 2 * ( num_keys - 1))
        {
            Pagina1No *s = new Pagina1No(num_keys, false);

            s->filhos[0] = raiz;
            //puts("b");
            s->splitChild(0, raiz);
            //puts("c");
            int i = 0;
            if( s->keys[0].first < key)
                i++;
            s->filhos[i]->insertNonFull(key, pos);
            //puts("d");
            raiz = s;
            //puts("f");
        }
        else
        {
            //puts("e");
            raiz->insertNonFull(key, pos);
        }
        
    }
    
}

void Pagina1No::insertNonFull(long long key, long long pos)
{
    int i = current_num_keys - 1;

    if( isFolha == true)
    {
        while( i >= 0 && keys[i].first > key)
        {
            keys[i+1].first = keys[i].first;
            keys[i+1].second = keys[i].second;
            i--;
        }

        keys[i+1].first = key;
        keys[i+1].second = pos;
        current_num_keys+=1;
    }
    else
    {
        while( i >= 0 && keys[i].first > key)
        {
            i--;
        }

        if(filhos[i+1]->current_num_keys == 2 * (num_keys-1))
        {
            splitChild(i+1, filhos[i+1]);

            if( keys[i+1].first < key)
                i++;
        }

        filhos[i+1]->insertNonFull(key, pos);
    } 
}

void Pagina1No::splitChild(int i, Pagina1No *y)
{
    Pagina1No *z = new Pagina1No(y->num_keys, y->isFolha);
    z->current_num_keys = num_keys - 1;

    for( int j = 0; j < num_keys - 1; j++)
    {
        z->keys[j].first = y->keys[j+num_keys].first;
        z->keys[j].second = y->keys[j+num_keys].second;
    }    

    if(y->isFolha == false)
    {
        for(int j = 0 ; j < num_keys ; j++)
        {
            z->filhos[j] = y->filhos[j+num_keys];
        }
    }

    y->current_num_keys = num_keys - 1;
    for( int j = current_num_keys; j >= i; j--)
    {
        filhos[j+1] = filhos[j];
    }

    filhos[i+1] = z;

    for(int j = current_num_keys-1; j >= i; j--)
    {
        keys[j+1].first = keys[j].first;
        keys[j+1].second = keys[j].second;
    }
        

    keys[i].first = y->keys[num_keys - 1].first;
    keys[i].second = y->keys[num_keys - 1].second;

    current_num_keys+=1;
}


int main()
{
    fstream arquivo;
    arquivo.open("banco_binario.dat", ios::in | ios::binary);
    int ordem, identificador;
    //pagina *pag = new pagina();
    int metodo;
    cout << "De qual ordem sera?" << endl;
    cin >> ordem;
    Pagina1 p1(ordem);
    Pagina1 p2(ordem);
    fstream cod;
    cod.open("indice_codigo.dat", ios::in | ios::binary);
    fstream cepn;
    cepn.open("indice_cepnumero.dat", ios::in | ios::binary);
    Cod* ind_cod = new Cod();
    Cepnumero* cn = new Cepnumero();
    Casa* casa = new Casa();
    cod.seekg(0, ios::beg);
    cepn.seekg(0, ios::beg);
    for(int i = 0; i < TAM ; i++)
    {
        cepn.read((char*)cn, sizeof(Cepnumero));
        cod.read((char*)ind_cod, sizeof(Cod));
        //cout << ind_cod->codigo << " " << ind_cod->posicao << endl;
        p1.insert(ind_cod->codigo, ind_cod->posicao);
        p2.insert(cn->cepnumero, cn->posicao);
        //p1.traverse();
        //cout << endl;
        cod.seekg(sizeof(Cod)*(i+1));
        cepn.seekg(sizeof(Cepnumero)*(i+1));
    }
    cod.close();
    cout << "Digite qual o metodo de pesquisa, 0 - CEP + Numero da residencia | 1 - Codigo de Serie" << endl;
    cin >> identificador;

    if(identificador == 0)
    {   
        long long busca;
        cout << "Digite o CEP + Numero da residencia desejada" << endl;
        cin >> busca;
        long long pos = p2.search(busca);
        if(pos != -1)
        {
            arquivo.seekg(pos);
            arquivo.read((char*)casa, sizeof(Casa));
            cout << "codigo: " << casa->codigo << " cepnumero: " << casa->cepnumero << " n_quartos: " << casa->n_quartos << " n_banheiros: " << casa->n_banheiros << " cor: " << casa->cor << " imobiliaria: " << casa->imobiliaria << " metros_q: " << casa->metros_quadrados << " genero: " << casa->genero << endl;
        }
        else
        {
            cout << "nao foi encontrado" << endl;
        }   
    }
    else if(identificador == 1)
    {
        long long busca;
        cout << "Digite o Codigo desejado" << endl;
        cin >> busca;
        long long pos = p1.search(busca);
        cout << pos << endl;
        if(pos != -1)
        {
            cout << "entrou" << endl;
            arquivo.seekg(pos);
            arquivo.read((char*)casa, sizeof(Casa));
            cout << "codigo: " << casa->codigo << " cepnumero: " << casa->cepnumero << " n_quartos: " << casa->n_quartos << " n_banheiros: " << casa->n_banheiros << " cor: " << casa->cor << " imobiliaria: " << casa->imobiliaria << " metros_q: " << casa->metros_quadrados << " genero: " << casa->genero << endl;
        }
        else
        {
            cout << "nao foi encontrado" << endl;
        }   
    }
    else
    {
        puts("opcao invalida");
        return 0;
    }
    //cep + numero
    //codigo aleatorio

    return 0;
}