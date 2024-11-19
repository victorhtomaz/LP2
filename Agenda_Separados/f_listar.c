#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void Listar(void);

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