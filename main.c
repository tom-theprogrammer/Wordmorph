#include "estrt_const_bibliot.h"
#include "prototipos.h"

/*
	> Se palavras so diferem numa letra nao fazer dikstra
	> Se a source for a mesma para 2 problemas nao faz dikstra
	> Usar item no dikstra (??)
	> Tipo abstrato é so declarar estruturas no .c e tyedef no .h e funções no .c e prototipos no .h
*/
int main(int argc, char *argv[])
{
	t_lista *dicionario, *exercicios;
	short numchars[MAX_STR]={0}, nmutmax[MAX_STR]= {0};
	char* nomesaida;

	if ( argc < 3 ) {
    	exit ( 0 );
  	}


	dicionario=iniLista();

	exercicios = ProcuraExercicios(AbreFicheiro(argv[2],"r"),numchars, nmutmax);

	exercicios = InverteLista(exercicios);

	dicionario = AlocaDicionario(AbreFicheiro(argv[1],"r"),numchars);

	PreencheDicionario(AbreFicheiro(argv[1],"r"), dicionario, numchars);

	ArrumaDicionario(dicionario);

	encontraposicao( exercicios, dicionario );

	cria_todos_grafos(dicionario,nmutmax);

	nomesaida = ConstroiNome( argv[2] );

	encontracaminhos( dicionario, exercicios, nomesaida );

	Freedoom(dicionario, exercicios);

	return 0;
}
