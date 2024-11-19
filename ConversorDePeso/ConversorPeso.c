#include <stdio.h>
#include <stdlib.h>

#include "libpeso.h"

int main (void);

int main (void)
{
	int opcao, i;
	float peso;
	float (*p)(float);
	char medidas[3][3] = {"kg", "lb", "oz"};

	do{
		printf("Digite o número para escolher uma opção de conversão\n");
		printf("1- KG para LIBRA\n");
		printf("2- LIBRA para KG\n");
		printf("3- KG para ONÇA\n");
		printf("4- ONÇA para KG\n");
		scanf("%d", &opcao);
	}while (!(opcao > 0 && opcao <= 4));

	printf("Digite o valor a ser convertido: ");
	scanf("%f", &peso);

	switch(opcao)
	{
		case 1:
			p = kgtolibra;
			i = 1;	
			break;
		case 2:
			p = libratokg;
			i = 0;
			break;
		case 3:
			p = kgtoonca;
			i = 2;
			break;
		case 4:
			p = oncatokg;
			i = 0;
			break;
	}
	printf("O valor da conversão é %.8f %s \n", (*p)(peso), medidas[i]);

	return 0;
}
