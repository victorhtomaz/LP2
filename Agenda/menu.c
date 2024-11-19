#include <stdio.h>
#include <stdlib.h>
#include "contatos.h"

int main (void);

int main (void)
{
	int opcao;
	do{
		do
		{
			printf("------------------\n");
			printf("Escolha uma opção \n");
			printf("1- Adicionar contato \n");
			printf("2- Listar contatos \n");
			printf("3- Alterar contato \n");
			printf("4- Buscar contato \n");
			printf("5- Sair \n");
			scanf("%d", &opcao);
			getchar();


		}while(opcao < 1 || opcao > 5);

		switch(opcao)
		{
			case 1:
				Adicionar();
				break;
			case 2:
				Listar();
				break;
			case 3:
				Alterar();
				break;
			case 4: 
				Buscar();
				break;
		}
	}while(opcao != 5);
	return 0;
}
