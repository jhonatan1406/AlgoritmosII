#include "funcionario.h"

typedef struct ListaFuncionarios {
	TFunc **lista;
	int qtd;
} TListaFunc;

// Imprime pizzas
void imprime_funcionarios(TListaFunc *l);

// Cria lista de pizzas. Lembrar de usar libera_pizzas(lista_pizzas)
TListaFunc *cria_funcionarios(int qtd, ...);

// Salva lista de pizzas no arquivo nome_arquivo
void salva_funcionarios(char *nome_arquivo, TListaFunc *l);

// Le lista de pizzas do arquivo nome_arquivo
TListaFunc *le_funcionarios(char *nome_arquivo);

// Compara duas listas de pizzas
// Retorna 1 se as pizzas das duas listas forem iguais
// e 0 caso contrario
int cmp_funcionarios(TListaFunc *l1, TListaFunc *l2);

// Desaloca lista de pizzas
void libera_Funcionarios(TListaFunc *l);
