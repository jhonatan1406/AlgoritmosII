#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "no_folha.h"


void imprime_no_folha(int d, TNoFolha *no)
{
	int i;
	printf("%d, %d, %d (\n", no->m, no->pont_pai, no->pont_prox);
	for (i = 0; i < 2 * d; i++) {
		printf("  ");
		if (no->funcs[i])
			imprime_func(no->funcs[i]);
	}
	printf(")\n");
}

TNoFolha *no_folha(int d, int m, int pont_pai, int pont_prox)
{
	int i;
	TNoFolha *no = (TNoFolha *) malloc(sizeof(TNoFolha));
	if (no) memset(no, 0, sizeof(TNoFolha));
	no->m = m;
	no->pont_pai = pont_pai;
	no->pont_prox = pont_prox;
	no->funcs = (TFunc **) malloc(sizeof(TFunc *) * 2 * d);
	for (i = 0; i < 2 * d; i++) {
		no->funcs[i] = NULL;
	}
	return no;
}

TNoFolha *no_folha_vazio(int d)
{
	return no_folha(d, 0, -1, -1);
}

TNoFolha *cria_no_folha(int d, int pont_pai, int pont_prox, int m, ...)
{
	TNoFolha *n = no_folha(d, m, pont_pai, pont_prox);
	int i;
	va_list ap;
	va_start(ap, m);
	for (i = 0; i < n->m; i++) {
		n->funcs[i] = va_arg(ap, TFunc *);
	}
	va_end(ap);
	return n;
}

void salva_no_folha(int d, TNoFolha *no, FILE *out)
{
	int i;
	fwrite(&no->m, sizeof(int), 1, out);
	fwrite(&no->pont_pai, sizeof(int), 1, out);
	fwrite(&no->pont_prox, sizeof(int), 1, out);
	//garantidamente, sempre havera pelo menos 1 chave no noh
    //portanto, p0 sempre vai existir
	TFunc *vazio = funcionario(-1, "", 0);

	for (i = 0; i < 2 * d; i++) {
		if (no->funcs[i]) {
			salva_funcionario(no->funcs[i], out);
		} else {
			salva_funcionario(vazio, out);
		}
	}
	free(vazio);
}

TNoFolha *le_no_folha(int d, FILE *in)
{
	int i;
	TNoFolha *no = (TNoFolha *) malloc(sizeof(TNoFolha));
	if (0 >= fread(&no->m, sizeof(int), 1, in)) {
		free(no);
		return NULL;
	}
	fread(&no->pont_pai, sizeof(int), 1, in);
	fread(&no->pont_prox, sizeof(int), 1, in);
	no->funcs = (TFunc **) malloc(sizeof(TFunc *) * 2 * d);

	for (i = 0; i < no->m; i++) {
		no->funcs[i] = le_func(in);
	}

	// Termina de ler dados nulos para resolver problema do cursor
	// Dados lidos sao descartados
	TFunc *vazio;
	for (i = no->m; i < 2 * d; i++) {
		no->funcs[i] = NULL;
		vazio = le_func(in);
		free(vazio);
	}
	return no;
}

int cmp_no_folha(int d, TNoFolha *n1, TNoFolha *n2)
{
	int i;
	if (n1 == NULL) {
		return (n2 == NULL);
	}
	if (n1->m != n2->m) {
		return 0;
	}
	if (n1->pont_pai != n2->pont_pai) {
		return 0;
	}
	if (n1->pont_prox != n2->pont_prox) {
		return 0;
	}
	for (i = 0; i < n1->m; i++) {
		if (!cmp_func(n1->funcs[i], n2->funcs[i])) {
			return 0;
		}
	}
	return 1;
}

int tamanho_no_folha(int d)
{
	return sizeof(int) + // m
		sizeof(int) + // pont_pai
		sizeof(int) + // pont_prox
		tamanho_func_bytes() * (2 * d); // funcs
}

void libera_no_folha(int d, TNoFolha *no)
{
	int i;
	for (i = 0; i < 2 * d; i++) {
		free(no->funcs[i]);
	}
	free(no->funcs);
	no->funcs = NULL;
	free(no);
}
