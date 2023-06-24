#include <stdio.h>
#include <stdlib.h>
#include "func.h"
Elemento* novoElemento(int chave, TFunc *valor) {
    Elemento *e = (Elemento*) malloc( sizeof(Elemento));
    e->chave = chave;
    e->valor = valor;
    e->prox = NULL;
    return e;
}

THash* novaTabelaHash(int tamanho) {
    THash *t = (THash*) malloc(sizeof(THash));
    t->tabela = (Elemento**) calloc(tamanho, sizeof(Elemento*));
    t->tamanho = tamanho;
    return t;
}

int hash(int chave) {
    return chave % MAX_SIZE;
}

void inserir(THash *t, int chave, TFunc *valor) {
    int indice = hash(chave);
    Elemento *e = novoElemento(chave, valor);
    Elemento *atual = t->tabela[indice];
    if (atual == NULL) {
        t->tabela[indice] = e;
    } else {
        while (atual->prox != NULL && atual->chave != chave) {
            atual = atual->prox;
        }
        if (atual->chave == chave) {
            if (atual->valor != NULL) {
                free(atual->valor);
                atual->valor = NULL;
            }
        } else {
            atual->prox = e;
        }
    }
}

TFunc* buscar(THash *t, int chave) {
    int indice = hash(chave);
    Elemento *atual = t->tabela[indice];
    while (atual != NULL && atual->chave != chave) {
        atual = atual->prox;
    }
    if (atual == NULL || atual->valor == NULL) {
        return NULL;
    } else {
        inserirBusca(atual->valor, "buscas.dat");
        return atual->valor;
    }
}

void imprimir(THash *t) {
    printf("Tabela de hash:\n");
    for (int i = 0; i < t->tamanho; i++) {
        Elemento *atual = t->tabela[i];
        printf("%d: ", i);
        while (atual != NULL) {
            printf("(%d, %s, %.2f) ", atual->valor->cod, atual->valor->nome, atual->valor->salario);
            atual = atual->prox;
        }
        printf("\n");
    }
}

void inserir_funcionarios(THash *t) {
    for(int i = 0; i < MAX_TAM; i++){
        TFunc* func = (TFunc*) malloc(sizeof(TFunc));
        func->cod = i;
        func->salario = rand() % 15000;
        sprintf(func->nome, "Funcionario %d", func->cod);
        inserir(t, func->cod, func);
    }

}

void buscar_funcionario(THash *t, int cod) {
    TFunc *funcionario = buscar(t, cod);
    if (funcionario != NULL) {
        printf("\nFUNCIONARIO ENCONTRADO COM SUCESSO!\n");
        printf("CODIGO: %d\n", funcionario->cod);
        printf("NOME: %s\n", funcionario->nome);
        printf("SALARIO: %.2f\n", funcionario->salario);
    } else {
        printf("\nFUNCIONARIO NAO ENCONTRADO.\n");
    }
}

void remover_funcionario(THash *t, int cod) {
    int indice = hash(cod);
    Elemento *atual = t->tabela[indice];
    Elemento *anterior = NULL;

    while (atual != NULL && atual->chave != cod) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("FUNCIONARIO NAO ENCONTRADO.\n");
        return;
    }

    if (anterior == NULL) {
        t->tabela[indice] = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    if (atual->valor != NULL) {
        free(atual->valor);
        atual->valor = NULL;
    }
    free(atual);
    printf("\nFUNCIONARIO REMOVIDO COM SUCESSO!\n");

}

void limpar_tabela(THash *t) {
    for (int i = 0; i < t->tamanho; i++) {
        Elemento *atual = t->tabela[i];
        while (atual != NULL) {
            Elemento *prox = atual->prox;
            if (atual->valor != NULL) {
                free(atual->valor);
            }
            free(atual);
            atual = prox;
        }
        t->tabela[i] = NULL;
    }
}

void salvarHash(THash *t, FILE *arquivo) {
    if (arquivo == NULL) {
        printf("Erro: arquivo não foi aberto.\n");
        return;
    }
    fwrite(t, sizeof(THash), 1, arquivo);
}

void inserirBusca(TFunc *valor, char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return;
    }
    fwrite(valor, sizeof(TFunc), 1, arquivo);
    fclose(arquivo);
}
