#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "validadorcpf.h"

struct Contato {
	char nome[30];
	char cpf[12];
	char telefone[20];
	uint32_t idade;
};

void Alterar(void);

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
