#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define ARQUIVO "dados.bin"

typedef struct Casas   
{ 
    long long unsigned cepnumero;
    long long unsigned codigo;
    int num_quartos;
    int num_banheiros;
    char cor[10];
    int metros_quadrados;
    char imobiliaria[50];
    char genero[20]; 
}Casas;

void menu();
int LerString(char *str, int tammax);
int NovaPessoa();
int PedeDadosPessoa(Pessoa *pessoa);
int GravaNovaPessoa(Pessoa *pessoa);
int ConsultarPorID();
int MostraPessoa(Pessoa *pessoa);
Pessoa *LeProximaPessoa(FILE *file);

int main()
{
    menu();
    return 0;
}
 
 void menu()
{
    int escolha;
    do
    {
         printf("\n\nMenu:\n\n");
         printf("0. Sair\n");
         printf("1. Nova Pessoa\n");
         printf("2. Consultar por ID\n");
         scanf("%d",&escolha);
   
         switch (escolha)
        {
            case 0: 
                printf("Fim!\n"); 
                break;
            case 1:
                NovaPessoa();
                break;
            case 2:
                ConsultarPorID();
                break;
            default: printf("Opção invalida. Tente novamente!\n");
                break;
        }    
  
    } while (escolha != 0);     
}

int NovaPessoa()
{
    Pessoa *pessoa = (Pessoa *) malloc (sizeof (Pessoa));
    
    if(!PedeDadosPessoa(pessoa))
    {
        free(pessoa);
        return 0;
    }
    
    if(!GravaNovaPessoa(pessoa))
    {
        free(pessoa);
        return 0;
    }
    
    free(pessoa);
    
    return 1;
}

int PedeDadosPessoa(Pessoa *pessoa)
{
    if(pessoa == NULL)
    {
        printf("\nPessoa invalida para pedir dados!\n");
        return 0;
    }
    
    printf("\nID: ");
    //fflush(stdin);
    scanf("%i", &pessoa->id);
    //fflush(stdin);
    printf("Nome: ");
    //fflush(stdin);
    LerString(pessoa->nome, 20);
    printf("Valor Em Conta: ");
    //fflush(stdin);
    scanf("%f", &pessoa->valorEmConta);
    //fflush(stdin);
    
    return 1;
}

int LerString(char *str, int tammax)
{
    int c, i=0;
    c = getchar();
    while (i==0 || (c != '\n' && c != EOF)) { 
        if(c == '\n' || c == EOF)
        {
            if(i >= 0)
                i--;
        }
        else if(i < tammax - 1)
        {
            str[i] = c;
        }
        c = getchar();
        i++;
        
    }
    if(i >= tammax - 1)
        i = tammax - 1;
    str[i] = '\0';
    fflush(stdin);
    
    return i;
}

int GravaNovaPessoa(Pessoa *pessoa)
{
    FILE *file; 
      
    // open file for writing 
    file = fopen (ARQUIVO, "a"); 
    if (file == NULL) 
    { 
        printf("\nErro ao abrir o arquivo!\n"); 
        return 0;
    } 
    
    if(pessoa == NULL)
    {
        printf("\nPessoa invalida!\n");
        return 0;
    }
      
    if(fwrite (pessoa, sizeof(Pessoa), 1, file) == 0)  
        printf("Erro ao gravar Pessoa %d !\n", pessoa->id); 
  
    // close file 
    fclose (file);
    
    return 1;
}

int ConsultarPorID()
{
    FILE *file;
    int id;
    Pessoa *pessoa = NULL;
    
    printf("\n\nInforme o ID: ");
    fflush(stdin);
    scanf("%d", &id);
    fflush(stdin);
    
    // open file for writing 
    file = fopen (ARQUIVO, "rb"); 
    if (file == NULL) 
    { 
        printf("\nErro ao abrir o arquivo!\n"); 
        return 0;
    }
    
    while(1)
    {
        if(feof(file))
            break;
        
        pessoa = LeProximaPessoa(file);
        
        if(pessoa == NULL || pessoa->id == id)
            break;
        
        free(pessoa);
    }
    
    if(pessoa != NULL)
    {
        printf("\nPessoa encontrada no banco de dados!\n");
        MostraPessoa(pessoa);
        free(pessoa);
    }
    else
    {
        printf("\nPessoa %d nao encontrada!\n",  id);
    }
    
    fclose(file);
    
    return 1;
}

int MostraPessoa(Pessoa *pessoa)
{
    if(pessoa == NULL)
    {
        printf("\nPessoa invalida para mostrar!\n");
        return 0;
    }
    
    printf("\nID: %d\n", pessoa->id);
    printf("Nome: %s\n", pessoa->nome);
    printf("Valor Em Conta: %.2f\n", pessoa->valorEmConta);
    
    return 1;
}

Pessoa *LeProximaPessoa(FILE *file)
{
    Pessoa *pessoa;
    
    if (file == NULL) 
    { 
        printf("\nArquivo invalido!\n"); 
        return 0;
    } 
    
    pessoa = (Pessoa *) malloc (sizeof (Pessoa));
    
    if(fread(pessoa, sizeof(Pessoa), 1, file) == 0)
    {
        printf("Erro ao ler Pessoa !\n");
        free(pessoa);
        pessoa = NULL;
    }
    
    return pessoa;
}