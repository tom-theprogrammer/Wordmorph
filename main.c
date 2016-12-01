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

	/* debugging
	int i;
	payload_dicionario * p = getItemLista(dicionario);
	for(i = 0; i< p->num_palavras; i++ ) {
		printf("%s-", p->palavras[i] );
	}
	*/

	cria_todos_grafos(dicionario,nmutmax);

	encontraposicao( exercicios, dicionario );

	nomesaida = ConstroiNome( argv[2] );

	encontracaminhos( dicionario, exercicios, nomesaida );

	Freedoom(dicionario, exercicios);

	return 0;
}
