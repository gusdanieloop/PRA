#include <bits/stdc++.h>

using namespace std;

#define CHAR_SIZE 58

typedef struct Trie
{
    bool folha;
    Trie *chave[CHAR_SIZE];
    string *significado;
}trie;

trie* getNovoNo()
{
    trie *no = new trie;//(trie*) malloc(sizeof(trie));
    no->folha = false;
    for(auto i = 0; i < CHAR_SIZE; ++i)
    {
        no->chave[i] = NULL;
    }
    no->significado = new string();
    //puts("no criado");
    return no;
}

void insertTrie(trie *head, string str, string significado)
{
    int flag = 1;
    //começa da raiz
    trie *atual = new trie;
    atual = head;
    for(char& c : str)
    {
        //cout <<"letra " << c << endl;
        if( atual->chave[c - 'A'] == NULL)
        {   
            //puts("chave ainda nao existe");
            atual->chave[c - 'A'] = getNovoNo();
            flag = 1;
        }
        else
        {
            //printf("%i tem %s\n", c - 'A',atual->chave[c - 'A']);
            //puts("ja existe");
            flag = 0;
        }
        
        //cout << atual->chave[c - 'a'] << endl;
        atual = atual->chave[c - 'A'];
    }
    if(flag == 1)
    {
        //cout << "chave inserida" << endl;
        //cout << significado << endl;
        atual->significado = new string();
        *atual->significado = significado;
        //cout << *atual->significado << endl;
        //cout<< "significado inserido" << endl;
        //no momento de inserção, é folha
        atual->folha = true;
        //puts("eh folha");
    }
}

//procurar pela chave
string procurar(trie *head, string str)
{
    //retorna 0 se a trie tiver vazia
    if(head == NULL)
        return NULL;
    trie *atual = head;
    for(char& c : str)
    {
        atual = atual->chave[c - 'A'];
        if(atual == NULL)
            return NULL;
    }
    return *atual->significado;
}

bool temFilhos(trie *atual)
{
    for(auto i = 0; i < CHAR_SIZE; ++i)
    {
        if(atual->chave[i])
            return true;
    }
    return false;
}

bool deletando(trie *atual, char *str)
{
    if(atual == NULL)
        return false;
    if(*str)
    {
        if(atual != NULL && atual->chave[*str - 'A'] != NULL && deletando(atual->chave[*str - 'A'], str + 1) && atual->folha == false)
        {
            if(!temFilhos(atual))
            {
                free(atual);
                atual = NULL;
                return true;
            }
            else
            {
                return false;
            }
            
        }
    }

    if(*str == '\0' && atual->folha)
    {
        if(!temFilhos(atual))
        {
            free(atual);
            atual = NULL;
            return true;
        }
        else
        {
            atual->folha = false;
            return false;
        }
        
    }
    return false;
}

int main()
{
    trie *no = getNovoNo();
    ifstream oxford("AT15.Oxford.txt");
    string significado;
    string chavinha;
    string lixo;
    int flag = 1;
    while((getline(oxford, chavinha, ' ')) && (getline(oxford, significado)))
    {   
        flag = 1;
        //puts("inicio");
        regex regex("\n");
        vector<string> palavrinhas(
            sregex_token_iterator(chavinha.begin(), chavinha.end(), regex, -1),
            sregex_token_iterator()
        );
        string chave = palavrinhas.back();
        //cout << significado << " eh o significado " << endl;
        //cout << chavinha << " eh a chave" << endl;
        //cout << chave << endl;
        if(significado.find(".") != std::string::npos)
        {
            //cout << significado << endl;
            for(char& c : chave)
            {
                //cout << c << " eh a letra" << endl;
                if( !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
                {
                    flag = 0;
                }
            }
            if(flag == 1)
            {
                //cout << chave << ' ' << significado << endl;
                insertTrie(no, chave, significado);
                //puts("inserido");
            }    
        }
        
    }
    puts("acabou a insercao");
    printf("Procurando por Paratyphoid!\n");
    cout << procurar(no, "Paratyphoid") << endl;
    //insertTrie(no,(char*)"abacate", "fruta");
    //insertTrie(no,(char*)"abacatinho", "frutinha");
    //insertTrie(no,(char*)"abacatao", "frutao");
    //cout << no->significado << endl;
    return 0;
}
