#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "classificao_externa.h"

/*
Compilação : gcc ED2_ex2_.h ED2_ex2_.c -lm -o <Nome Executavel>
*/

NoVenc* ajustarArvVenc(NoVenc **vetor_no,int max,int indice){

NoVenc *aux = vetor_no[indice];
int 	primeira = 1;

	aux->vencedor = SENTINELA;
	while(aux->pai != NULL){

		(aux->pai)->vencedor = SENTINELA;
		aux = aux->pai;
	}

	aux = vetor_no[indice];


	while(aux->pai != NULL){

		(aux->pai)->vencedor     = ((aux->pai)->dir)->vencedor < ((aux->pai)->esq)->vencedor ? ((aux->pai)->dir)->vencedor:((aux->pai)->esq)->vencedor;
		(aux->pai)->indice       = ((aux->pai)->dir)->vencedor < ((aux->pai)->esq)->vencedor ? ((aux->pai)->dir)->indice:((aux->pai)->esq)->indice;
		(aux->pai)->end_vencedor = ((aux->pai)->dir)->vencedor < ((aux->pai)->esq)->vencedor ? ((aux->pai)->dir)->end_vencedor:((aux->pai)->esq)->end_vencedor;

		aux = aux->pai;
	}

	if(aux->vencedor == SENTINELA) return NULL;

	return aux;

}

NoVenc* arvoreVencedora(NoVenc **arv_venc,NoVenc **vetor_no,int max,int indice)
{
NoVenc *aux,*no;
int    log,tam_nos,salva;

	aux = *arv_venc;

	if(indice == -1){

		log     = (int) log2((double) max);
		salva   = tam_nos =  max == pow(2,log) ? pow(2,log):pow(2,log+1);
		NoVenc **vetor_nos_folhas =  (NoVenc**) malloc(sizeof(NoVenc*)*(tam_nos));
		NoVenc **auxiliar         =  (NoVenc**) malloc(sizeof(NoVenc*)*(tam_nos));

		for(int k = 0; k < tam_nos;k++){

			vetor_nos_folhas[k] = (NoVenc*) malloc(sizeof(NoVenc));
			auxiliar[k]         = (NoVenc*) malloc(sizeof(NoVenc));
		}

		for(int k = 0; k < tam_nos; k++){

			if(k < max) vetor_nos_folhas[k]           = vetor_no[k];
			else        vetor_nos_folhas[k]->vencedor = SENTINELA;

			auxiliar[k] = vetor_nos_folhas[k];
		}
		tam_nos *= 2;
		while(tam_nos != 2){


			tam_nos/=2;
			vetor_nos_folhas = (NoVenc**) malloc(sizeof(NoVenc*)*(tam_nos/2));
			for(int k = 0; k < tam_nos;k++) vetor_nos_folhas[k] = (NoVenc*) malloc(sizeof(NoVenc));

			for(int a = 0; a < tam_nos/2;a++){

				vetor_nos_folhas[a]->esq 	  = auxiliar[a*2];
				auxiliar[a*2]->pai 		 	  = vetor_nos_folhas[a];
				vetor_nos_folhas[a]->dir 	  = auxiliar[(a*2)+1];
				auxiliar[(a*2)+1]->pai 	 	  = vetor_nos_folhas[a];

				vetor_nos_folhas[a]->vencedor     = auxiliar[a*2]->vencedor < auxiliar[(a*2)+1]->vencedor ? auxiliar[a*2]->vencedor:auxiliar[(a*2)+1]->vencedor;
				vetor_nos_folhas[a]->end_vencedor = auxiliar[a*2]->vencedor < auxiliar[(a*2)+1]->vencedor ? auxiliar[a*2]->end_vencedor:auxiliar[(a*2)+1]->end_vencedor;
				vetor_nos_folhas[a]->indice       = auxiliar[a*2]->vencedor < auxiliar[(a*2)+1]->vencedor ? a*2:(a*2)+1;
			}

			auxiliar = (NoVenc**) malloc(sizeof(NoVenc*)*(tam_nos));
			for(int k = 0; k < tam_nos;k++) auxiliar[k] = (NoVenc*) malloc(sizeof(NoVenc));

			for(int k = 0; k < tam_nos; k++){

				auxiliar[k] = vetor_nos_folhas[k];
			}
		}

		*arv_venc = *vetor_nos_folhas;
		aux = *vetor_nos_folhas;
		return aux;
	}

	return ajustarArvVenc(vetor_no,max,indice);
}

int intercalaOtima(Fila **fila,int num_input,int MAX_ARQUIVOS,char *nome_saida_final)
{

 // Declarando variáveis
FILE   *arqs[MAX_ARQUIVOS - 1],*arq_saida;
NoVenc *vencedor,*arv_venc,**num = (NoVenc**) malloc(sizeof(NoVenc*)*(MAX_ARQUIVOS-1));
Fila   *aux;
char   nome_saida[17],*nome_ler_arquivo,*filee; //17 porque são 6 caracteres de 'saida_' + 10 caracteres[maior int representavel em c] + '\0'
int    i,cont_arq,quebra,cont___,cont2___,
       arquivos,acabou_arquivos,indice_menor_numero,indice_substituir,
       contador_nome_arquivo,num_arq_atual;
 // Inicializando variáveis
	i          		= quebra = 0;
	acabou_arquivos = contador_nome_arquivo = 1;
	aux        		= *fila ;
// Alocando memória para o array num
	for(int i = 0;i < MAX_ARQUIVOS-1 ; i++) num[i] = (NoVenc*) malloc(sizeof(NoVenc));
 // Loop principal
	while(1){
// Criando novo arquivo de saída
		sprintf(nome_saida,"saida_%d",++num_input);
		arq_saida  = fopen(nome_saida,"w");
  // Lendo arquivos da fila e armazenando no array num
		for(int l = 0; l < MAX_ARQUIVOS-1; l++){
// Verificando se ainda há arquivos na fila
			filee = popArquivo(&aux);
			if(!filee){
				if(l == 1) quebra = 1;
				break;
			}
			nome_ler_arquivo = strdup(filee);
// Abrindo arquivo e armazenando no array num
			if( (arqs[l] = fopen(nome_ler_arquivo,"r")) ){

				num[l]->end_vencedor = arqs[l];
				arquivos = num_arq_atual = l+1;
				continue;
			}

		}
// Verificando se chegou ao final da fila
		if(quebra) break;
// Loop para intercalar arquivos
		while(1){

			for(int j = 0; j < num_arq_atual; j++) if(feof(arqs[j])) arquivos--;
// Se todos os arquivos chegaram ao final, sai do loop
			if(!arquivos) break;
 // Verificando se ainda não terminou de ler o arquivo com o menor número
			if(acabou_arquivos){
 // Lendo o próximo número de cada arquivo
				for(int k = 0; k < arquivos; k++){
					fread(&num[vencedor->indice]->vencedor, sizeof(int), 1, vencedor->end_vencedor);
					//fscanf(arqs[k],"%d",&num[k]->vencedor);
					cont___+=1;

				}
				 // Reiniciando flag de leitura de arquivos
				acabou_arquivos = 0;
                // Encontrando o vencedor entre os números lidos
				vencedor = arvoreVencedora(&arv_venc,num,num_arq_atual,-1);
				// Escrevendo o vencedor no arquivo de saída
				fwrite(&vencedor->vencedor, sizeof(int), 1, arq_saida);
				//fprintf(arq_saida, "%d ",vencedor->vencedor );
			}
			else{

				if(!feof(vencedor->end_vencedor)) fread(&num[vencedor->indice]->vencedor, sizeof(int), 1, vencedor->end_vencedor);
				//fscanf(vencedor->end_vencedor,"%d",&num[vencedor->indice]->vencedor);

				if(feof(vencedor->end_vencedor)){
					num[vencedor->indice]->vencedor = SENTINELA;
					continue;
				}

				vencedor = arvoreVencedora(&arv_venc,num,num_arq_atual,vencedor->indice);
				if(!vencedor) quebra=1;break;
				fwrite(&vencedor->vencedor, sizeof(int), 1, arq_saida);
				//fprintf(arq_saida, "%d ",vencedor->vencedor );
			}
		}

		acabou_arquivos = 1;
		adicionaArquivo(&aux,nome_saida);
	}
	rewind(arq_saida);
	while(1)
	{
		fread(&num, sizeof(int), 1, arq_saida);
		if(feof(arqs)) break;
		cont2___++;
	}
	return cont___/cont2___;
}


char* popArquivo(Fila **fila)
{
Fila *aux;
char *file_name;

	aux = *fila;
	if(!aux) return NULL;
	*fila = (*fila)->prox;
	file_name = strdup(aux->nome_arquivo);
	if(aux->nome_arquivo) free(aux->nome_arquivo);
	if(aux) free(aux);

	return file_name;

}
//a.txt b.txt c.txt fim aaaa
void adicionaArquivo(Fila **fila,char *arquivo)
{
Fila *aux,*no;

	no = (Fila*) malloc(sizeof(Fila));
	no->nome_arquivo = strdup(arquivo);
	no->prox		 = NULL;

	if(*fila == NULL){

		*fila = no;
	}
	else{

		aux = *fila;

		while(aux->prox != NULL){

			aux = aux->prox;
		}

		aux->prox = no;
	}
}
/*
int main(){
char *nome_arquivo,*nome_saida;
int	 num_de_arquivo,max_arqs,medida;
Fila *fila;

	fila = (Fila*) malloc(sizeof(Fila));
	fila = NULL;
	num_de_arquivo = 0;
	nome_arquivo = strdup("__init__");
    nome_saida   = strdup("__init__");

	fprintf(stderr, "Insira o número máximo de arquivos que podem ser abertos simultaneamente : \n");

	scanf("%d",&max_arqs);

	fprintf(stderr, "Insira o nome os nomes dos arquivos [Após todos os arquivos digite \"fim\"]\n" );

	while(strcmp(nome_arquivo,"fim")){

		scanf("%s",nome_arquivo);
		if(strcmp(nome_arquivo,"fim")) adicionaArquivo(&fila,nome_arquivo);
		num_de_arquivo++;
	}

	if(num_de_arquivo == 1) {fprintf(stderr,"\nVocê não inseriu nenhum arquivo, o programa está sendo terminado ...\n");return 0;}

	fprintf(stderr, "Digite o nome do arquivo de saída : \n");
	scanf("%s",nome_saida);

	medida = intercalaOtima(&fila,num_de_arquivo-1,max_arqs,nome_saida);
	fprintf(stderr, "A medida de desempenho foi : %d\n",medida);
	return 0;
}*/
