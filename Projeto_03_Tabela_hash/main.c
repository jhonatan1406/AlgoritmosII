#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


#include "cliente.h"
#include "compartimento_hash.h"
#include "encadeamento_exterior.h"
#include "lista_clientes.h"
#include "lista_compartimentos.h"
#include <assert.h>
#include <stdlib.h>
#include "func.h"

int menu(){
    int opt;
    printf("\nOpcoes:\n");
    printf("0. Sair\n");
    printf("1. Inserir\n");
    printf("2. Remover um funcionario\n");
    printf("3. Inserir 1000 funcionario\n");
    printf("4. cria Hash.\n");
    printf("5. Buscar funcionario.\n");
    printf("6. imprimi na tela.\n");
    printf(" \t Digite sua opcao:\n");
    scanf("%d", &opt);

    return opt;
}


void tarefa(int opt, char *nome_arquivo_metadados, char *nome_arquivo_dados, int d,  THash *t) {

    if (opt == 0){

        printf("Saindo...\n");

    }else if(opt == 1){//Inserir
        int cod;
        char nome[50];
        printf("\nInformacoes do funcionario:\n");
        printf("Codigo:\n");
        scanf("%d", &cod);
        printf("Nome\n");
        scanf(" %[^\n]", nome);
        if(insere(cod, nome,nome_arquivo_metadados, nome_arquivo_dados, d) != -1){
            printf("Inserido com Sucesso\n");
        }else printf("Codigo ja exitente\n");

    }else if(opt == 2){//Remover

        int cod;
        printf("Codigo:\n");
        scanf("%d", &cod);
        remover_funcionario(t, cod);
        if(exclui(cod, nome_arquivo_metadados, nome_arquivo_dados)!=-1){
        printf("removido com sucesso\n");
        }
        else{
            printf("\n********************\n");
        }

    }else if(opt == 3){//Inserir
    printf ("Inserindo funcionarios no arquivo....\n");
    cria_hash(nome_arquivo_metadados,d);
    inserir_funcionarios(t);
	int max_funcionario=20;
	int numFuncionarios = 20;
	int count = 0;
	int cod=0;
	/*while (count < numFuncionarios) {
			cod=count;
			char nome[50];
			sprintf(nome, "Funcionario %d", count);
        if(insere(cod, nome,nome_arquivo_metadados, nome_arquivo_dados, d) != -1){
            printf("Inserido com Sucesso\n");
            }else printf("Codigo ja exitente\n");
            count++;
        }*/
       // imprimir(t);

    }else if(opt == 4){//Imprimir arvore

       cria_hash (nome_arquivo_metadados ,d);

    }else if(opt == 5){//Buscar Funcionario

        int cod;
        printf("Codigo:\n");
        scanf("%d", &cod);
        buscar_funcionario(t,cod);
        if(busca(cod, nome_arquivo_metadados, nome_arquivo_dados)!=-1){
            printf("funcionario enocntrado \n");
        }
        else {
            printf("\n*************8\n");
        }

    }
    else if(opt == 6){//Buscar Funcionario

        imprimir(t);
    }

    else{
        printf("Tarefa invalida.\n");
    }
}
int main()
{
    int opt;
    int d;
    THash *t = novaTabelaHash(MAX_SIZE);
    char nome_arquivo_metadados[20];// = "metadados.dat";
    char nome_arquivo_dados[20];// = "pizzas.dat";
    printf("Digite a ordem da tabela hash.\n");
    scanf(" %d", &d);
    printf("Nome do arquivo da tabela hash (com .txt ou .dat).\n");
    scanf(" %s", nome_arquivo_metadados);
    printf("Nome do arquivo do funcionario (com .txt ou .dat).\n");
    scanf(" %s", nome_arquivo_dados);

    int flag;
    printf("\nDigite 1 caso deseje apagar o conteudo existente nesses arquivos e 0 se desejar manter.\n");

    scanf(" %d", &flag);
    if(flag){
        fclose(fopen(nome_arquivo_dados, "wb"));//Apaga o conteudo do arquivo.
        fclose(fopen(nome_arquivo_metadados, "wb"));
    }

    do{

        opt = menu();
        tarefa(opt, nome_arquivo_metadados, nome_arquivo_dados, d,t);

    }while(opt);

    return 0;

}
