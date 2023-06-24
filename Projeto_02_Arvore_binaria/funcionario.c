#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdlib.h>

#include "funcionario.h"


void imprime_func(TFunc *p)
{
	printf("%d, %s , R$ %.2f\n", p->cod, p->nome, p->preco);
}

TFunc *funcionario(int cod, char *nome, float preco)
{
	TFunc *p = (TFunc *) malloc(sizeof(TFunc));
	if (p) memset(p, 0, sizeof(TFunc));
	p->cod = cod;
	strcpy(p->nome, nome);
	p->preco = preco;
	return p;
}

void salva_funcionario(TFunc *p, FILE *out)
{
	fwrite(&p->cod, sizeof(int), 1, out);
	fwrite(p->nome, sizeof(char), sizeof(p->nome), out);
	fwrite(&p->preco, sizeof(float), 1, out);
}

TFunc *le_func(FILE *in)
{
	TFunc *p = (TFunc *) malloc(sizeof(TFunc));
	if (0 >= fread(&p->cod, sizeof(int), 1, in)) {
		free(p);
		return NULL;
	}
	fread(p->nome, sizeof(char), sizeof(p->nome), in);
	fread(&p->preco, sizeof(float), 1, in);
	return p;
}

int cmp_func(TFunc *p1, TFunc *p2)
{
	if (p1 == NULL) {
		return (p2 == NULL);
	}
	if (p1->cod != p2->cod) {
		return 0;
	}
	if (strcmp(p1->nome, p2->nome) != 0) {
		return 0;
	}
	if (p1->preco != p2->preco) {
		return 0;
	}
	return 1;
}

int tamanho_func_bytes()
{
	return sizeof(int) + // cod
		sizeof(char) * 50 + // nome
		sizeof(float); // preço
}
