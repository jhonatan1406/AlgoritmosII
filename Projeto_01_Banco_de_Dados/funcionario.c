#include "funcionario.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <time.h>

// Imprime funcionario
void imprime(TFunc *func) {
    printf("**********************************************");
    printf("\nFuncionario de cÃ³digo ");
    printf("%d", func->cod);
    printf("\nNome: ");
    printf("%s", func->nome);
    printf("\nCPF: ");
    printf("%s", func->cpf);
    printf("\nData de Nascimento: ");
    printf("%s", func->data_nascimento);
    printf("\nSalÃ¡rio: ");
    printf("%4.2f", func->salario);
    printf("\n**********************************************");
}

// Cria funcionario. Lembrar de usar free(func)
TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, double salario) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    //inicializa espaÃ§o de memÃ³ria com ZEROS
    if (func) memset(func, 0, sizeof(TFunc));
    //copia valores para os campos de func
    func->cod = cod;
    strcpy(func->nome, nome);
    strcpy(func->cpf, cpf);
    strcpy(func->data_nascimento, data_nascimento);
    func->salario = salario;
    return func;
}

// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(TFunc *func, FILE *out) {
    fwrite(&func->cod, sizeof(int), 1, out);
    //func->nome ao invÃ©s de &func->nome, pois string jÃ¡ Ã© ponteiro
    fwrite(func->nome, sizeof(char), sizeof(func->nome), out);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), out);
    fwrite(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), out);
    fwrite(&func->salario, sizeof(double), 1, out);
}

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
TFunc *le(FILE *in) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    if (0 >= fread(&func->cod, sizeof(int), 1, in)) {
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    fread(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), in);
    fread(&func->salario, sizeof(double), 1, in);
    return func;
}
void limpa() {
    char *inputFilenames[]= {"p1.dat","p2.dat","p3.dat","p4.dat","p5.dat","p6.dat","p7.dat","p8.dat"};
    int numFiles = sizeof(inputFilenames) / sizeof(inputFilenames[0]);
    for (int i = 0; i < numFiles; i++) {
        int status = remove(inputFilenames[i]);
        if (status != 0) {
            printf("Erro ao remover o arquivo %s.\n", inputFilenames[i]);
        }
    }
}
void IntercalaOtima( FILE *arq  , int maxss ,char *nome_ordenado ){
//declara ponteiro para arquivo
clock_t inicio = clock();
     maxss=0;

    FILE *out;
    //abre arquivo
    if ((out = fopen(nome_ordenado, "wb+")) == NULL) {
        printf("Erro ao abrir arquivo\n");
    }
    else{
   clock_t inicio = clock();

    fseek(arq, 0, SEEK_END);
    long size = ftell(arq);
    rewind(arq);
    char *buffer = malloc(size);
    fread(buffer, size, 1, arq);
    fwrite(buffer, size, 1, out);
    free(buffer);

	int i;
	int j;
    int tam = tamanho_arquivo(out);
	for (j = 2; j <= tam; j++) {

    fseek(out, (j-1) * tamanho_registro(), SEEK_SET);
    TFunc *fj = le(out);

    i = j - 1;

    fseek(out, (i-1) * tamanho_registro(), SEEK_SET);
    TFunc *fi = le(out);
    while ((i > 0) && (fi->cod > fj->cod)) {

        fseek(out, i * tamanho_registro(), SEEK_SET);

        salva(fi, out);
        i = i - 1;

        fseek(out, (i-1) * tamanho_registro(), SEEK_SET);
        fi = le(out);

    }

    fseek(out, (i) * tamanho_registro(), SEEK_SET);
    salva(fj, out);
	}

	fflush(out);
    limpa();

    clock_t fim = clock();
	double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
	printf("Tempo gasto: %f segundos\n", tempo);




    }
}


// Retorna tamanho do funcionario em bytes
int tamanho_registro() {
    return sizeof(int)  //cod
           + sizeof(char) * 50 //nome
           + sizeof(char) * 15 //cpf
           + sizeof(char) * 11 //data_nascimento
           + sizeof(double); //salario
}
// Retorna o tamanho do arquivo
int tamanho_arquivo(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / tamanho_registro());
    return tam;
}
void salvar_resultados_BS(TFunc *func, int comp, float tempo) {
    FILE *fp = fopen("DadosBS.txt","a");
    if (fp) {
        fprintf(fp, "Informações do funcionário:\n");
        fprintf(fp, "Código: %d\n", func->cod);
        fprintf(fp, "Nome: %s\n", func->nome);
        fprintf(fp, "CPF: %s\n", func->cpf);
        fprintf(fp, "Data de Nascimento: %s\n", func->data_nascimento);
        fprintf(fp, "Salário: %f\n", func->salario);
        fprintf(fp, "Número de comparações: %d\n", comp);
        fprintf(fp, "Tempo gasto: %f\n", tempo);
        fprintf(fp, "\n");
        fclose(fp);
    }
	else {
        printf("Não foi possível abrir o arquivo %s\n");
    }
}
void salvar_resultados_Bin(TFunc *func, int comp, float tempo) {
    FILE *fp = fopen("DadosBin.txt","a");
    if (fp) {
        fprintf(fp, "Informações do funcionário:\n");
        fprintf(fp, "Código: %d\n", func->cod);
        fprintf(fp, "Nome: %s\n", func->nome);
        fprintf(fp, "CPF: %s\n", func->cpf);
        fprintf(fp, "Data de Nascimento: %s\n", func->data_nascimento);
        fprintf(fp, "Salário: %f\n", func->salario);
        fprintf(fp, "Número de comparações: %d\n", comp);
        fprintf(fp, "Tempo gasto: %f\n", tempo);
        fprintf(fp, "\n");
        fclose(fp);
    }
	else {
        printf("Não foi possível abrir o arquivo %s\n");
    }
}



void insere_5_funcionarios(FILE *out) {
    printf("Inserindo 5 funcionÃ¡rios no arquivo...");

    TFunc *f1 = funcionario(1, "Ana", "000.000.000-00", "01/01/1980", 3000);
    salva(f1, out);
    free(f1);
    TFunc *f2 = funcionario(3, "Carlos", "111.111.111-11", "01/01/1990", 500);
    salva(f2, out);
    free(f2);
    TFunc *f3 = funcionario(2, "FÃ¡tima", "222.222.222-22", "02/02/1980", 1000);
    salva(f3, out);
    free(f3);
    TFunc *f4 = funcionario(5, "Marcelo", "333.333.333-33", "03/03/1990", 1500);
    salva(f4, out);
    free(f4);
    TFunc *f5 = funcionario(4, "Silvia", "444.444.444-44", "04/04/1980", 900);
    salva(f5, out);
    free(f5);
}
void Insere_5000_funcio (FILE *out){
	//Para evitar a repetição de códigos, uma solução é adicionar um controle de verificação de existência de um
	//código gerado antes de a3r os códigos já gerados e verificar antes de adicionar um novo código
	printf ("Inserindo funcionario no arquivo....\n");
	int max_funcionario=90;
	int codigos[max_funcionario] ;
	int numFuncionarios = 90;
	int count = 0;
	while (count < numFuncionarios) {
		int cod = rand() % numFuncionarios;
		int j;

		for (j = 0; j < count; j++) {
			if (cod == codigos[j]) {
				break;
			}
		}
    	if (j == count) {
			codigos[count++] = cod;
			char nome[50];
			sprintf(nome, "Funcionario %d", count);
			char cpf[15];
			sprintf(cpf, "CPF %d", count);
			char data_nascimento[11];
			sprintf(data_nascimento, "01/01/%d", 1900 + (count % 100));
			double salario = (double)rand() / RAND_MAX * 10000;

    		TFunc *func = funcionario(cod, nome, cpf, data_nascimento, salario);
	    	imprime(func);
	    	salva(func, out);
    		free(func);
  		}
	}
}
TFunc *busca_sequencial_CT(int chave, FILE *in, int tamanho_arquivo) {
	int compara = 0;

    clock_t inicio_tempo = clock();
	rewind(in);
	TFunc *f = le(in);
	while (f != NULL && f->cod != chave) {
		compara++;
		f = le(in);
	}
    clock_t fim_tempo = clock();
    float tempo_gasto = (float)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC;

	if (f != NULL) {
		salvar_resultados_BS(f, compara, tempo_gasto);
		return f;
	}
	else printf("nullkkkkk "); return NULL;
	}

TFunc *busca_binaria_CT(int chave, FILE *in, int inicio, int fim) {
    TFunc *f = NULL;
    int cod = -1;
    int comparacoes = 0;
    clock_t inicio_tempo = clock();
    while (inicio <= fim && cod != chave) {
        int meio = trunc((inicio + fim) / 2);
        printf("Inicio: %d; Fim: %d; Meio: %d\n", inicio, fim, meio);
        fseek(in, (meio -1) * tamanho_registro(), SEEK_SET);
        f = le(in);
        cod = f->cod;
        comparacoes++;
        if (f) {
            if (cod > chave) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
	}
    clock_t fim_tempo = clock();
    float tempo_gasto = (float)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC;
    if (cod == chave) {
        // Grava informações no arquivo
        FILE *out = fopen("resultados.txt", "a");
        fprintf(out, "Funcionário encontrado: %d\n", f->cod);
        fprintf(out, "Quantidade de comparações: %d\n", comparacoes);
        salvar_resultados_Bin(f,comparacoes,fim_tempo);
        fclose(out);
        return f;
    }
    else return NULL;
}

void insertion_sort_disco(FILE *arq, int tam)
 {

	clock_t inicio = clock();
	int i;
	int j;
    //faz o insertion sort
	for (j = 2; j <= tam; j++) {
    //posiciona o arquivo no registro j
    fseek(arq, (j-1) * tamanho_registro(), SEEK_SET);
    TFunc *fj = le(arq);
    printf("\n********* Funcionario atual: %d\n", fj->cod);
    i = j - 1;
    //posiciona o cursor no registro i
    fseek(arq, (i-1) * tamanho_registro(), SEEK_SET);
    TFunc *fi = le(arq);
    printf("fi = %d\n", fi->cod);
    while ((i > 0) && (fi->cod > fj->cod)) {
        //posiciona o cursor no registro i+1
        fseek(arq, i * tamanho_registro(), SEEK_SET);
        printf("Salvando funcionario %d na posicao %d\n", fi->cod, i+1);
        salva(fi, arq);
        i = i - 1;
        //lê registro i
        fseek(arq, (i-1) * tamanho_registro(), SEEK_SET);
        fi = le(arq);
        printf("fi = %d; i = %d\n", fi->cod, i);
    }
    //posiciona cursor no registro i + 1
    fseek(arq, (i) * tamanho_registro(), SEEK_SET);
    printf("* Salvando funcionario %d na posicao %d\n", fj->cod, i+1);
    //salva registro j na posição i
    salva(fj, arq);
	}
		    	imprime(arq);

//descarrega o buffer para ter certeza que dados foram gravados
	fflush(arq);

	clock_t fim = clock();
	double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
	printf("Tempo gasto: %f segundos\n", tempo);

}












void intercalateFiles(char *inputFilenames[], int numFiles, char *outputFilename) {
    FILE **files = malloc(numFiles * sizeof(FILE*));
    int *fileSizes = malloc(numFiles * sizeof(int));
    int *indices = calloc(numFiles, sizeof(int));
    int *numReads = calloc(numFiles, sizeof(int));
    int totalSize = 0;
    int minIndex, i;

    FILE *outputFile = fopen(outputFilename, "w");

    if (files == NULL || fileSizes == NULL || indices == NULL || numReads == NULL || outputFile == NULL) {
        printf("Erro ao alocar memória ou ao abrir arquivos\n");
        exit(1);
    }

    for (i = 0; i < numFiles; i++) {
        files[i] = fopen(inputFilenames[i], "r");
        if (files[i] == NULL) {
            printf("Erro ao abrir arquivo %s\n", inputFilenames[i]);
            exit(1);
        }
        fseek(files[i], 0L, SEEK_END);
        fileSizes[i] = ftell(files[i]);
        totalSize += fileSizes[i];
        fseek(files[i], 0L, SEEK_SET);
    }

    while (totalSize > 0) {
        minIndex = -1;
        for (i = 0; i < numFiles; i++) {
            if (indices[i] < numReads[i]) {
                fseek(files[i], (indices[i] * sizeof(int)), SEEK_SET);
                fread(&numReads[i], sizeof(int), 1, files[i]);
            }
            if (numReads[i] != -1) {
                if (minIndex == -1 || numReads[i] < numReads[minIndex]) {
                    minIndex = i;
                }
            }
        }

        fprintf(outputFile, "%d ", numReads[minIndex]);
        indices[minIndex]++;
        if (indices[minIndex] * sizeof(int) >= fileSizes[minIndex]) {
            numReads[minIndex] = -1;
            totalSize -= fileSizes[minIndex];
        }
    }

    fclose(outputFile);
    for (i = 0; i < numFiles; i++) {
        fclose(files[i]);
    }
    free(files);
    free(fileSizes);
    free(indices);
    free(numReads);
}

