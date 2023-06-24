#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "funcionario.h"
#include "nomes.h"
#include "geracao_particoes.h"
#include "classificao_externa.h"


int main(int argc, char** argv) {

    //declara ponteiro para arquivo
    FILE *out;
    //abre arquivo
    if ((out = fopen("funcionario.dat", "wb+")) == NULL) {
        printf("Erro ao abrir arquivo\n");
    }
    else {
        int opcao;
		while (opcao != 6){
		REFAZ: printf("\n\nEscolha uma opcao entre 1 e 6: \n");
		printf("\n***********************************************************\n");
		printf("1. Para inserir 5000 funcionarios em um 1 arquivo!\n");
		printf("2. Para fazer uma busca sequenncial !\n");
		printf("3. Colocar em ordem os funcionarios !\n");
		printf("4. Tecnica de ordenacao externa!\n");
		printf("5. Busca binaria no arquivo !\n");
		printf("6. Para sair !!\n");
		printf("**************************************************************\n");
		printf("\nDigite sua opcao:");
       		scanf("%d", &opcao);
       		if ((opcao > 6)||(opcao <1)) goto REFAZ;  /* Opcao invalida: volta ao rotulo REFAZ */
       		switch (opcao)
          	{
          		case 1:
               			printf("\n --> Primeira opcao...\n");
               			Insere_5000_funcio(out);
               			fflush(out);
               			goto REFAZ;
          		break;
          		case 2:

               			printf("\n --> Segunda opcao...\n");
               			printf("QUAL FUNCIONARIO DESEJA PESQUIAR?\n");
               			int num1 =0;
               			scanf("%d",&num1);
               			busca_sequencial_CT(num1,out,tamanho_arquivo (out));

						goto REFAZ;
          		break;
          		case 3:
               			printf("\n --> Terceira opcao...\n");
               			insertion_sort_disco (out,tamanho_arquivo (out));

          		break;
         		case 4:
               			printf("\n --> Quarta opcao...\n");
               			int i;
                        selec_sub();
                        printf("\nDeseja fazer intercalacao otima (aperte 1) ? \n");
                        scanf("%d",&i);
                        if (i==1){
                            Fila *fila;

                                fila = (Fila*) malloc(sizeof(Fila));
                                fila = NULL;
                                int max_arqs=0;
                                char *nome_arquivo,*nome_saida;
                                fprintf(stderr, "Insira o numero maximo de arquivos que podem ser abertos simultaneamente : \n");
                                scanf("%d",&max_arqs);
                                fprintf(stderr, "Digite o nome do arquivo de saida : \n");
                                scanf("%s",&nome_saida);
                                IntercalaOtima(out , max_arqs ,"ordenado.dat");
                                goto REFAZ;
                        }


                        goto REFAZ;
          		break;
          		case 5:
               			printf("\n --> Quinta opcao...\n");
               			int num=0;
               			printf("qual funcionario deseja pesquisa ?\n");
               			scanf("%d",&num);
             			busca_binaria_CT (num,out,1,tamanho_arquivo(out));
               			goto REFAZ;
          		break;
          		case 6:
               			printf("\n --> Abandonando..");
               			fclose(out);

          		break;
          	}
       	}

    }
    return 0;
}

