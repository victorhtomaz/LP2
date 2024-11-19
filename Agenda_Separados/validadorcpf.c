#include <stdio.h>
#include <stdlib.h>

int Validarcpf (char *cpf);

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