//tentei de todo o jeito que encontrei fazer com que o programa aceitasse espaço no nome, mas de nenhum jeito funcionava corretamente

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct elemento {
    char nome[30];
    char email[30];
    int tel;
    elemento *prox;
};

typedef struct {
    elemento *inicio;
} Lista;

Lista lista;

int inicializar(Lista *lista){
  lista->inicio=NULL;
  return -1;
}

int inserirInicio(Lista *lista, char nome[], int tel, char email[]) {
  elemento *novo = (elemento *) malloc(sizeof(elemento));
  if(novo == NULL) {
    printf("Erro ao adicionar.");
    return 0;
  }
  novo->tel = tel;
  strcpy(novo->nome, nome);
  strcpy(novo->email, email);
  novo->prox = lista->inicio;
  lista->inicio = novo;
  return 1;
}

int inserirFim(Lista *lista, char nome[], int tel, char email[]){
  elemento *novo = (elemento *) malloc(sizeof(elemento));
  if(novo == NULL){
    printf("Memoria cheia");
    return 0;
  }
  novo->tel = tel;
  strcpy(novo->nome, nome);
  strcpy(novo->email, email);
  novo->prox = NULL;
  if (lista->inicio == NULL){
    lista->inicio = novo;
    return 1;
  }
  elemento *aux = lista->inicio;
  while(aux->prox != NULL){
    aux = aux->prox;
  }
  aux->prox = novo;
  return 1;
}

int listar (Lista*lista){
  elemento *aux = lista->inicio;
  int numero = 1;
  if(aux == NULL){
    printf("\nLista vazia.\n");
    return 0;
  }
  while(aux != NULL){
    printf("\n%d\nNome: %s\nTelefone: %d\nE-mail: %s\n", numero, aux->nome, aux->tel, aux->email);
    aux = aux->prox;
    numero++;
  }
  return 1;
}

int pesquisar(Lista *lista, char nome[]) {
    elemento *aux = lista->inicio;
    int numero = 1;
    int encontrou = 0;

    while(aux != NULL) {
        if(strcmp(aux->nome, nome) == 0) {
            printf("\n%d\nNome: %s\nTelefone: %d\nE-mail: %s\n", numero, aux->nome, aux->tel, aux->email);
            encontrou = 1;
        }
        aux = aux->prox;
        numero++;
    }

    if (!encontrou) {
        printf("\nContato não encontrado.\n");
    }
  return 0;
}

int remover(Lista *lista, char nome[]) {
    elemento *anterior = NULL;
    elemento *atual = lista->inicio;
    int encontrou = 0;
    int numero = 0;
    int opcao;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("\n%d\nNome: %s\nTelefone: %d\nE-mail: %s\n", ++numero, atual->nome, atual->tel, atual->email);
            encontrou = 1;
        }
        atual = atual->prox;
    }

    if (!encontrou) {
        printf("\nContato não encontrado.\n");
        return 0;
    }

    printf("\nO(s) contato(s) acima foi/foram encontrado(s). Digite o número correspondente ao contato que deseja remover:\n");
    scanf("%d", &opcao);

    atual = lista->inicio;
    numero = 0;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            numero++;
            if (numero == opcao) {
                if (anterior == NULL) {
                    lista->inicio = atual->prox;
                } else {
                    anterior->prox = atual->prox;
                }
                printf("\n%s removido com sucesso.\n", atual->nome);
                free(atual);
                return 1;
            }
        }
        anterior = atual;
        atual = atual->prox;
    }

    return 0;
}

int atualizar(Lista *lista, char nome[], int tel, char email[]) {
    elemento *aux = lista->inicio;
    int encontrou = 0;
    int numero = 1;
    int opcao;

    while (aux != NULL) {
        if (strcmp(aux->nome, nome) == 0) {
            printf("\n%d\nNome: %s\nTelefone: %d\nE-mail: %s\n", numero, aux->nome, aux->tel, aux->email);
            encontrou = 1;
            numero++; 
        }
        aux = aux->prox;
    }

    if (!encontrou) {
        printf("\nContato não encontrado.\n");
        return 0;
    }

    printf("\nO(s) contato(s) acima foi/foram encontrado(s). Digite o número correspondente ao contato que deseja atualizar:\n");
    scanf("%d", &opcao);

    aux = lista->inicio;
    numero = 1;
    while (aux != NULL) {
        if (strcmp(aux->nome, nome) == 0) {
            if (numero == opcao) {
                int continuar = 1;
                while (continuar) {
                    printf("\nO que deseja atualizar?\n");
                    printf("1 - Nome\n");
                    printf("2 - Telefone\n");
                    printf("3 - Email\n");
                    printf("4 - Terminar de atualizar\n\n");
                    scanf("%d", &opcao);

                    switch (opcao) {
                        case 1:
                            printf("\nDigite o novo nome: ");
                            scanf("%29s", nome);
                            strcpy(aux->nome, nome);
                            printf("\nNome atualizado com sucesso.\n");
                            break;
                        case 2:
                            printf("\nDigite o novo telefone: ");
                            scanf("%d", &tel);
                            aux->tel = tel;
                            printf("\nTelefone atualizado com sucesso.\n");
                            break;
                        case 3:
                            printf("\nDigite o novo e-mail: ");
                            scanf("%29s", email);
                            strcpy(aux->email, email);
                            printf("\nE-mail atualizado com sucesso.\n");
                            break;
                        case 4:
                            printf("\nAtualização concluída.\n");
                            continuar = 0;
                            break;
                        default:
                            printf("\nOpção inválida.\n");
                    }
                }
                return 1;
            }
            numero++;
        }
        aux = aux->prox;
    }

    return 0;
}

int main(void) {
	setlocale(LC_ALL, "Portuguese");
	
    int opcao;
    char nome[30];
    char email[30];
    int tel;
    int resposta;
    int atualizacao;
    int menuFechado = 0;

    while (!menuFechado) {
        printf("\n--------------------------------------");
        printf("\nLista Telefônica\nDigite o número da operação desejada:\n1 - Ver a lista\n2 - Inserir novo contato no início\n3 - Inserir novo contato no fim\n4 - Remover contato\n5 - Pesquisar\n6 - Atualizar\n7 - Fechar o menu\n\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listar(&lista);
                break;

            case 2:
                printf("\nDigite o nome:\n");
                scanf("%29s", nome);
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Digite o telefone:\n");
                scanf("\n%d", &tel);
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Digite o email:\n");
                scanf("%29s", email);
                while ((c = getchar()) != '\n' && c != EOF);
                inserirInicio(&lista, nome, tel, email);
                printf("\n%s cadastrado(a) com sucesso!\n", nome);
                break;

            case 3:
                printf("\nDigite o nome:\n");
                scanf("%29s", nome);
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Digite o telefone:\n");
                scanf("\n%d", &tel);
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Digite o email:\n");
                scanf("%29s", email);
                while ((c = getchar()) != '\n' && c != EOF);
                inserirFim(&lista, nome, tel, email);
                printf("\n%s cadastrado(a) com sucesso!\n", nome);
                break;

            case 4:
                printf("\nDigite o nome do contato que deseja remover:\n");
                scanf("%29s", nome);
                while ((c = getchar()) != '\n' && c != EOF);
                remover(&lista, nome);
                break;

            case 5:
                printf("\nDigite o nome do contato:\n");
                scanf("%29s", nome);
                while ((c = getchar()) != '\n' && c != EOF);
                pesquisar(&lista, nome);
                break;

            case 6:
                printf("\nDigite o nome do contato que deseja atualizar:\n");
                scanf("%29s", nome);
                while ((c = getchar()) != '\n' && c != EOF);
                atualizar(&lista, nome, tel, email);
                break;

            case 7:
                menuFechado = 1;
                printf("\nMenu fechado.\n");
                break;

            default:
                printf("\nComando desconhecido.\n");
        }
    }

    return 0;
}

