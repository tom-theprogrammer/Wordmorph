#include "estrt_const_bibliot.h"
#include "prototipos.h"

/*
	>Se palavras so diferem numa letra nao fazer dikstra
	>Se a source for a mesma para 2 problemas nao faz dikstra
	>Usar item no dikstra (??)
*/
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

	encontraposicao( exercicios, dicionario );

	cria_todos_grafos(dicionario,nmutmax);

	/* debugging 
	payload_exercicios * payld_ex;t_lista*iterador;
	for(iterador = exercicios ; iterador != NULL; iterador = getProxElementoLista(iterador)) {
		payld_ex = getItemLista(iterador);
		printf("Inicial: %d\n", payld_ex->pos_inicial);
		printf("Final: %d\n", payld_ex->pos_final );
		printf("numchar: %d\n", payld_ex->num_char );	
	}
	*/


	nomesaida = ConstroiNome( argv[2] );

	encontracaminhos( dicionario, exercicios, nomesaida );

	printf("About to free \n");
	Freedoom(dicionario, exercicios);

	return 0;
}
