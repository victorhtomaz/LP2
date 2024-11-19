#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void Buscar(void);

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