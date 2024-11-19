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

void Adicionar(void);

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
