#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdarg.h>

#include "lista_func.h"


void imprime_funcionarios(TListaFunc *l)
{
	int i;
	for (i = 0; i < l->qtd; i++) {
		imprime_funcionarios(l->lista[i]);
	}
}

TListaFunc *cria_funcionarios(int qtd, ...)

{
	va_list ap;
	TListaFunc *l = (TListaFunc *)  malloc(sizeof(TListaFunc));
	l->qtd = qtd;
	l->lista = (TFunc **) malloc(sizeof(TFunc *) * (qtd));
	int i;
	va_start(ap, qtd);
	for (i = 0; i < qtd; i++) {
        l->lista[i] = va_arg(ap, TFunc *);
    }
    va_end(ap);
    return l;
}

void salva_funcionarios(char *nome_arquivo, TListaFunc *l)
{
	FILE *out = fopen(nome_arquivo, "wb");
	int i;
	for (i = 0; i < l->qtd; i++) {
		salva_funcionarios(l->lista[i], out);
	}
	fclose(out);
}

TListaFunc *le_funcionarios(char *nome_arquivo)
{
	int qtd = 0;
	TListaFunc *l = (TListaFunc *)  malloc(sizeof(TListaFunc));
	FILE *in = fopen(nome_arquivo, "rb");
	if (in != NULL) {
		TFunc *func = NULL;
		while((func = le_func(in)) != NULL) {
			qtd += 1;
			free(func);
		}
		fseek(in, 0, SEEK_SET);
		l->qtd = qtd;
		l->lista = (TFunc **) malloc(sizeof(TFunc *) * (qtd));
		qtd = 0;
		while((func = le_func(in)) != NULL) {
			l->lista[qtd++] = func;
		}
		fclose(in);
	} else {
		l->qtd = 0;
		l->lista = NULL;
	}
	return l;
}
int cmp_funcionarios(TListaFunc *l1, TListaFunc *l2)
{
	if (l1->qtd != l2->qtd) {
		return 0;
	}
	int i;
	for (i = 0; i < l1->qtd; i++) {
		if (!cmp_func(l1->lista[i], l2->lista[i])) {
			return 0;
		}
	}
	return 1;
}

void libera_Funcionarios(TListaFunc *l)
{
	int i;
	for (i = 0; i < l->qtd; i++) {
		free(l->lista[i]);
	}
	free(l->lista);
	free(l);
}

