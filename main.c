#include "estrt_const_bibliot.h"
#include "prototipos.h"


int main(int argc, char *argv[])
{
	t_lista *dicionario, *exercicios;
	short numchars[MAX_STR]={0}, nmutmax[MAX_STR]= {0};
	char* nomesaida;

	if ( argc < 3 ) {
    	exit ( 0 );
  	}


	dicionario=iniLista();

	/* Começamos por carregar os exercícios para a memória */
	exercicios = ProcuraExercicios(AbreFicheiro(argv[2],"r"),numchars, nmutmax);

	/* Coloca os exercícios pela ordem certa */
	exercicios = InverteLista(exercicios);

	/* Aloca o que é necessário do dicionário para a memória */
	dicionario = AlocaDicionario(AbreFicheiro(argv[1],"r"),numchars);

	/* Coloca as palavras do dicionário no espaço alocado */
	PreencheDicionario(AbreFicheiro(argv[1],"r"), dicionario, numchars);

	/* Aplica o algorítmo quick sort no dicionário */
	ArrumaDicionario(dicionario);

	/* Aplica o algorítmo Binary Search para encontrar as palavras no dicionário */
	encontraposicao( exercicios, dicionario );

	/* Cria os grafos implementados por lista de adjacências */
	cria_todos_grafos(dicionario,nmutmax);

	/* Coloca a extensão .path no ficheiro */
	nomesaida = ConstroiNome( argv[2] );

	/* Aplica o algorítmo de Dijkstra para cada um dos exercícios */
	encontracaminhos( dicionario, exercicios, nomesaida );

	/* Liberta para a memória o dicionário e os exercícios */
	Freedoom(dicionario, exercicios);

	return 0;
}
