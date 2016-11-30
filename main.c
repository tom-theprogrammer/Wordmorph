#include "estrt_const_bibliot.h"
#include "prototipos.h"


int main(int argc, char *argv[])
{
	t_lista *dicionario, *exercicios;
	short numchars[MAX_STR]={0}, nmutmax[MAX_STR]= {0};
	char* nomesaida;

	t_lista * tmp = NULL;

	if ( argc < 3 ) {
    	fprintf ( stderr, "ERROR: Usage: %s [filename].dic [filename].pal\n", argv[0] );
    	exit ( 0 );
  	}

	dicionario=iniLista();

	exercicios = ProcuraExercicios(AbreFicheiro(argv[2],"r"),numchars, nmutmax);

	exercicios = InverteLista(exercicios);

	dicionario = AlocaDicionario(AbreFicheiro(argv[1],"r"),numchars);

	PreencheDicionario(AbreFicheiro(argv[1],"r"), dicionario, numchars);

	ArrumaDicionario(dicionario);

	printf(">Iniciar construção de grafos: \n");
	cria_todos_grafos(dicionario,nmutmax);

	printf(">Iniciar construção de grafos: \n");
	encontraposicao( exercicios, dicionario );

	/*nomesaida = ficheiroout( argv[2] );*/

	printf(">Procura caminhos: \n");
	encontracaminhos( dicionario, exercicios, nomesaida );

	printf(">Fim \n");
	Freedoom(dicionario, exercicios);

	return 0;
}
