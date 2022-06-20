#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
struct cliente{ //Estrutura de dados de um cliente
    char *primeiro_nome;
    char *ultimo_nome;
    int idade;
    char *morada;
    struct cliente *proximo; // link para o proximo cliente
};
struct cliente * inicializar_cliente();// Inicializa o cliente com dados zerados
int inserir_cliente(struct cliente *, int);// Insere um cliente 
void imprimir_clientes(struct cliente *);// Imprime os nomes de todos os clientes
void imprimir_cliente(struct cliente *, int );// Imprime todos os dados de um cliente
int alterar_cliente(struct cliente *,int );// Altera os dados de um cliente
struct cliente * deletar_cliente(struct cliente *,int * );// Deleta um cliente
int menu();
int main(int argc,char *argv[]){
    menu();
    return 0;
}

struct cliente * inicializar_cliente(){
    struct cliente *ptr=(struct cliente *) malloc(sizeof(struct cliente));
    if (ptr==NULL){
        fprintf(stderr,"Erro ao criar cliente\nErro: %s\nSaindo agora...",strerror(errno));
        return NULL;
    }
    ptr->primeiro_nome=NULL;
    ptr->ultimo_nome=NULL;
    ptr->idade=0;
    ptr->morada=NULL;
    ptr->proximo=NULL;
    return ptr;
}

int inserir_cliente(struct cliente *ptr, int total_clientes){
    printf("Registro do cliente numero: %d\nPor favor, introduza o primeiro e o ultimo nome (primeiro ultimo): ", total_clientes+1);
    char primeiro[20];char ultimo[20],morada[20];
    int idade;
    scanf("%s %s",primeiro,ultimo);
    ptr->primeiro_nome=(char *)malloc(sizeof(char)*strlen(primeiro));
    ptr->ultimo_nome=(char *)malloc(sizeof(char)*strlen(ultimo));
    strcpy(ptr->primeiro_nome,primeiro);strcpy(ptr->ultimo_nome,ultimo);
    printf("Por favor introduza a idade do cliente: ");
    scanf("%d",&idade);
    ptr->idade=idade;
    printf("Por favor introduza a morada do cliente: ");
    scanf("%s",morada);
    ptr->morada=(char *)malloc(sizeof(char)*strlen(morada));
    strcpy(ptr->morada,morada);
    return ++total_clientes;
}

void imprimir_clientes(struct cliente *cabeca){
    struct cliente *atual=cabeca;
    printf("Imprimindo clientes: \n");
    int i=0;
    while(atual!=NULL){
        printf("%d - %s %s\n",1+i++,atual->primeiro_nome,atual->ultimo_nome);
        atual=atual->proximo;
    }
}

void imprimir_cliente(struct cliente *cabeca, int total_clientes){
    int i;
    struct cliente *atual=cabeca;
    imprimir_clientes(cabeca);
    printf("Qual cliente deseja imprimir?\n--> ");
    scanf("%d",&i);
    if (i<1 || i>total_clientes){
        printf("Erro. Valor fora do range.");
        return;
    }
    while(i-->1){
        atual=atual->proximo;
    }
    printf("Cliente numero %d: \n",i+1);
    printf("---Nome: %s %s\n",atual->primeiro_nome,atual->ultimo_nome);
    printf("---Idade: %d\n",atual->idade);
    printf("---Morada: %s\n",atual->morada);
}

int alterar_cliente(struct cliente * cabeca,int total_clientes){
    struct cliente * atual=cabeca;
    int i;
    imprimir_clientes(cabeca);
    printf("Qual cliente deseja alterar: ");
    scanf("%d",&i);
    if (i<1 || i>total_clientes){
        printf("Erro. Valor fora do range.");
        return total_clientes;
    }
    while(i-->1){
        atual=atual->proximo;
    }
    printf("Registro do cliente numero: %d\nPor favor, introduza o primeiro e o ultimo nome (primeiro ultimo): ", total_clientes);
    char primeiro[15];char ultimo[15],morada[20];
    int idade;
    scanf("%s %s",primeiro,ultimo);
    strcpy(atual->primeiro_nome,primeiro);strcpy(atual->ultimo_nome,ultimo);
    printf("Por favor introduza a idade do cliente: ");
    scanf("%d",&idade);
    atual->idade=idade;
    printf("Por favor introduza a morada do cliente: ");
    scanf("%s",morada);
    strcpy(atual->morada,morada);
    return total_clientes;
}

struct cliente * deletar_cliente(struct cliente *cabeca,int *total_clientes){
    int i;
    struct cliente *atual=cabeca;
    imprimir_clientes(cabeca);
    printf("Qual cliente deseja deletar: ");
    scanf("%d",&i);
    if (i<1 || i>*total_clientes){
        printf("Erro. Valor fora do range.");
        return cabeca;
    } else if (i==1){
        cabeca=atual->proximo;
        free(atual);
        --*total_clientes;
        return cabeca;
    }
    while(i-->2){
        atual=atual->proximo;
    }
    struct cliente *anterior=atual;
    atual=atual->proximo;
    anterior->proximo=atual->proximo;
    free(atual);
    --*total_clientes;
    return cabeca;
}

int menu(){
    struct cliente * cabeca=NULL;
    struct cliente * atual=NULL;
    int escolha=0,clientes=0;
    while(escolha!=6){
        printf("Menu:\n1- Criar cadastro\n2- Alterar cadastro\n3- Excluir cadastro\n4- Mostrar cadastro\n5- Mostrar cadastros\n6- Sair\n\nInsira uma escolha\n--> ");
        scanf("%d",&escolha);
        switch (escolha)
        {
            case 1:
                if(cabeca==NULL)
                    if((cabeca=inicializar_cliente())==NULL)
                        return 0;
                    else{
                        clientes=inserir_cliente(cabeca,clientes);
                        atual=cabeca;
                        break;
                    }
                else{
                    atual->proximo=inicializar_cliente();
                    atual=atual->proximo;
                    clientes=inserir_cliente(atual,clientes);
                }
                break;
            case 2:
                if(cabeca==NULL){
                    printf("Nao existem cadastros ainda.\n");
                    break;
                }
                else{
                    alterar_cliente(cabeca,clientes);
                    break;
                }
            case 3:
                if(cabeca==NULL){
                    printf("Nao existem cadastros ainda.\n");
                    break;
                }
                else{
                    cabeca=deletar_cliente(cabeca,&clientes);
                }
                break;
            case 4:
                imprimir_cliente(cabeca,clientes);
                break;
            case 5:
                imprimir_clientes(cabeca);
                break;
            case 6:
                break;
            default:
                printf("Opcao Errada.\n");
                break;
        }
    }
    return 0;
}