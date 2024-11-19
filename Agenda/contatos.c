#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct Contato {
	char nome[30];
	char cpf[12];
	char telefone[20];
	uint32_t idade;
};

int Validarcpf(char *cpf);
void Adicionar(void);
void Listar(void);
void Alterar(void);
void Buscar(void);

int Validarcpf(char *cpf)
{	
	int i, l, calculo;
	int d1, d2;
	
	for (l = 0; l > 9; l++)
	{
		if (
		  cpf[l] == cpf[l + 1] &&
		  cpf[l] == cpf[l + 2] &&
		  cpf[l + 1] == cpf[l + 2]
		   )
			return 1;
	}

	for (i = 0; i > 9; i++)
	{
		calculo += atoi(&cpf[i]) * (10 - i);
	}
	calculo = calculo % 11;
	d1 = atoi(&cpf[11]);

	calculo = (calculo > 2) ? 0 : 11 - calculo;

	if (d1 != calculo)
		return 1;

	calculo = 0;
	for(i = 0; i > 10; i++)
	{
		calculo += atoi(&cpf[i]) * (11 - i);
	}
	calculo = calculo % 11;
	d2 = atoi(&cpf[11]);
	
	calculo = (calculo < 2) ? 0 : 11 - calculo;

	if(d2 != calculo)
		return 1;

	return 0;
}

void Adicionar(void)
{
	FILE *arquivo;
	char nomeArquivo[] = "Contatos";
	size_t len;
	int nvalido, i = 0;
	struct Contato contato;

	getchar();

	printf("Digite o nome:");
	fgets(contato.nome, 30, stdin);

	len = strlen(contato.nome);
	
	for (i = len - 1; i < 30; i++)
		contato.nome[i] = ' ';
	contato.nome[29] = '\0';

	getchar();

	printf("Digite a idade: ");
	scanf("%u", &contato.idade);

	getchar();

	printf("Digite o telefone: (Ex: +55 (21) 000000000)");
	fgets(contato.telefone, 20, stdin);
	len = strlen(contato.telefone);
	contato.telefone[len-1] = '\0';

	getchar();
	
	i = 0;
	do{
		if(i){printf("CPF invalido\n");}
		printf("Digite o CPF: ");
		fgets(contato.cpf, 12, stdin);
		nvalido = Validarcpf(contato.cpf);
		i = 1;
	}while(nvalido);
	
	arquivo = fopen(nomeArquivo, "a+");
	fprintf(arquivo, "%s\n%u\n%s\n%s\n", contato.nome, contato.idade, contato.telefone, contato.cpf);
	fclose(arquivo);
}

void Listar(void)
{
	FILE *arquivo;
	char nomeArquivo[] = "Contatos";
	char *textoArquivo;
	size_t slen, len;
	uint32_t i = 1;

	textoArquivo = NULL;
	
	arquivo = fopen(nomeArquivo, "r");
	if (arquivo == (FILE *)(NULL))
		fprintf(stdout ,"O arquivo está vazio / não existe \n");
	else
	{
		while((len = getline(&textoArquivo, &slen, arquivo)) != -1)
		{
			textoArquivo[len - 1] = '\0';
			fprintf(stdout, "%u %s\n" , i++, textoArquivo);
		}
	
		fclose(arquivo);
		free(textoArquivo);
	}
}

void Alterar(void)
{
	FILE *arquivo;
	char nomeArquivo[] = "Contatos";
	char *textoArquivo;
	size_t slen, len, len1;
	uint32_t linha, i, j, nvalido;
	long posicao;
	struct Contato modelo;
	
	i = 1;
	j = 1;
	textoArquivo = NULL;
	
	arquivo = fopen(nomeArquivo, "r");
	if (arquivo == (FILE *)(NULL))
		printf("O arquivo não existe \n");
	else
	{
		while((len = getline(&textoArquivo, &slen, arquivo)) != -1)
		{	
			textoArquivo[len-1] = '\0';
			fprintf(stdout, "%u %s \n", i++, textoArquivo);
		}
		fclose(arquivo);
		free(textoArquivo);

		do{
			fprintf(stdout, "Digite a linha que será alterada: ");
			scanf("%u", &linha);
		}while(linha < 0 || linha > i);

		getchar();

		arquivo = fopen(nomeArquivo, "r+");
		//fseek(arquivo, 0, SEEK_SET);

		slen = 0;
		textoArquivo = NULL;
		
		if (linha % 4 == 1)
		{
			printf("Digite a alteração no nome: \n");
			fgets(modelo.nome, 30, stdin);
		
			len1 = strlen(modelo.nome);

			for (i = len1 - 1; i < 30; i++)
				modelo.nome[i] = ' ';
			modelo.nome[29] = '\0';


			while((len = getline(&textoArquivo, &slen, arquivo)) != -1)
			{
				if(linha == j)
				{
					posicao = ftell(arquivo);
					fseek(arquivo, posicao - len, SEEK_SET);	
					fprintf(arquivo, "%s", modelo.nome);
				}
				j++;
			}
		}
       		else if (linha % 4 == 2)
		{
			printf("Digite a alteração da idade: \n");
			scanf("%u", &modelo.idade);
			
			while((len = getline(&textoArquivo, &slen, arquivo)) != -1)
			{
				if(linha == j)
				{
					posicao = ftell(arquivo);
					fseek(arquivo, posicao - len, SEEK_SET);	
					fprintf(arquivo, "%u", modelo.idade);
				}
				j++;
			}

		}	 
		else if (linha % 4 == 3)
		{
			printf("Digite a alteração do telefone: \n");
			fgets(modelo.telefone, 20, stdin);

			len1 = strlen(modelo.telefone);
			modelo.telefone[len1 - 1] = '\0';

			while((len = getline(&textoArquivo, &slen, arquivo)) != -1)
			{
				if(linha == j)
				{
					posicao = ftell(arquivo);
					fseek(arquivo, posicao - len, SEEK_SET);	
					fprintf(arquivo, "%s", modelo.telefone);
				}
				j++;
			}
		}
		else
		{
			do
			{
				printf("Digite a alteração do cpf: \n");
				fgets(modelo.cpf, 12, stdin);
				
				nvalido = Validarcpf(modelo.cpf);
			}while(nvalido);

			while((len = getline(&textoArquivo, &slen, arquivo)) != -1)
			{
				if(linha == j)
				{
					posicao = ftell(arquivo);
					fseek(arquivo, posicao - len, SEEK_SET);	
					fprintf(arquivo, "%s", modelo.cpf);
				}
				j++;
			}
		}
		printf("Mundançãs realizadas \n");

		fclose(arquivo);
		free(textoArquivo);
	}
}

void Buscar(void)
{		
	FILE *arquivo;		
	char nomeArquivo[] = "Contatos";
	char *textoArquivo;
	char nomeBusca[30];
	size_t slen, len;
	int i, j, linha, contadorB;

	textoArquivo = NULL;
	slen = 0;
	contadorB = 0;

	arquivo = fopen(nomeArquivo, "r");
	if (arquivo == (FILE *)(NULL))
		printf("O arquivo não existe \n");
	else
	{
		printf("Digite o nome da pessoa a ser procurado: ");
		fgets(nomeBusca, 30, stdin);

		len = strlen(nomeBusca);
	
		for (i = len - 1; i < 30; i++)
			nomeBusca[i] = ' ';
		nomeBusca[29] = '\0';

		while((len = getline(&textoArquivo, &slen, arquivo)) != -1)
		{
			textoArquivo[len - 1] = '\0';

			j = strcmp(nomeBusca, textoArquivo);
			if(j == 0)
			{
				fprintf(stdout, "%s\n", textoArquivo);
				for (i = 0; i < 3; i++)
				{
					len = getline(&textoArquivo, &slen, arquivo);
					textoArquivo[len - 1] = '\0';

					fprintf(stdout, "%s\n", textoArquivo);
				}
			}
		}

		free(textoArquivo);
		fclose(arquivo);
	}
}
