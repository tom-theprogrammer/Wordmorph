#include "estrt_const_bibliot.h"
#include "prototipos.h"
#include "fila_prioritaria.h"


/******************************************************************************
 * cria_todos_grafos()
 *
 * Argumentos:dicionario - Ponteiro para a lista que contêm o dicionario
 *			  nmutmax - Array que contêm o maior número maximo de mutações para cada tamanho de palavra
 * Retorna: ---
 * Efeitos-colaterais: ----
 *
 * Descrição:
 *
 *****************************************************************************/
void cria_todos_grafos(t_lista * dicionario,short nmutmax[] ){
	t_lista * iterador = NULL;
	payload_dicionario * payld = NULL;

	for( iterador=dicionario ;iterador != NULL; iterador = getProxElementoLista(iterador) ){
		payld = getItemLista(iterador);
		cria_grafo(payld, nmutmax[payld->num_char-1]);
	}
	
}



/******************************************************************************
 * cria_grafo()
 *
 * Argumentos:payld - 
 *			  nmutmax - Array que contêm o maior número maximo de mutações para cada tamanho de palavra
 * Retorna: ---
 * Efeitos-colaterais: ----
 *
 * Descrição:
 *
 *****************************************************************************/
void cria_grafo( payload_dicionario * payld, short nmutmax ) {
	int counter1=0, counter2=0, diff=0;
	lista_adjs ** adj2 = NULL;
	lista_adjs * aux  = NULL;

	payld->adj = (lista_adjs **) x_malloc( sizeof(lista_adjs*) * payld->num_palavras );
	adj2 = payld->adj;

	for( counter1=0; counter1<payld->num_palavras; counter1++ ){
		adj2[counter1] = NULL;
	}

	for( counter1 = 0; counter1 < payld->num_palavras; counter1++) {

		for( counter2 = counter1+1; counter2 < payld->num_palavras; counter2++) {
			diff = comparer2(payld->palavras[counter1], payld->palavras[counter2], nmutmax);
			if(diff > nmutmax) continue;

			aux= (lista_adjs *) x_malloc( sizeof(lista_adjs) );
			aux->v_adj=counter2;
			aux->peso=diff*diff;
			aux->prox=adj2[counter1];
			adj2[counter1]= aux;

			aux= (lista_adjs *) x_malloc( sizeof(lista_adjs) );
			aux->v_adj=counter1;
			aux->peso=diff*diff;
			aux->prox=adj2[counter2];
			adj2[counter2]= aux;

		}
	}
}

/******************************************************************************
 * comparer2()
 *
 * Argumentos:p1 - Uma das strings que queremos comparar
 *			  p2 - Uma das strings que queremos comparar
 *			  n -  Número máximo de mutações
 * Retorna: Número de caracteres diferentes entre as 2 strings
 * Efeitos-colaterais: ----
 *
 * Descrição:
 *
 *****************************************************************************/
int comparer2( char * p1, char* p2, short n) {
	int diff=0, i=0;
	for( i=0; p1[i] != '\0'; i++ )
		if(p1[i]!=p2[i]) diff++;

	return diff;
}

/******************************************************************************
 * encontracaminhos()
 *
 * Argumentos: dicionario - Ponteiro para a lista que contêm o dicionario
 			   exercicios - Ponteiro para a lista que contêm os Problemas a resolver
			   nomeficheiro - Nome do ficheiro de escrita
 * Retorna: ---
 * Efeitos-colaterais: ----
 *
 * Descrição:
 *
 *****************************************************************************/
void encontracaminhos( t_lista * dicionario, t_lista * exercicios, char* nomeficheiro ) {
	t_lista * it_ex = exercicios, * it_dic = NULL;
	payload_exercicios * payld_ex = NULL;
	payload_dicionario * payld_dic = NULL;
	unsigned short * st = NULL, * wt = NULL;
	int i, sucesso, tmp;
	FILE* fp = AbreFicheiro(nomeficheiro, "w");


	for(; it_ex != NULL; it_ex = getProxElementoLista(it_ex) ) {
		payld_ex = (payload_exercicios *)getItemLista( it_ex );

		for(it_dic=dicionario;it_dic!=NULL;it_dic=getProxElementoLista(it_dic)) {
			payld_dic = (payload_dicionario *) getItemLista( it_dic );
			if( payld_dic->num_char == payld_ex->num_char )
				break;
		}
		if( (tmp = comparer2(payld_dic->palavras[ payld_ex->pos_inicial],payld_dic->palavras[ payld_ex->pos_final],payld_ex->max_mutacoes)) <=1 ){
			fprintf(fp,"%s %d\n",payld_dic->palavras[ payld_ex->pos_inicial],tmp);
			fprintf(fp,"%s\n\n",payld_dic->palavras[ payld_ex->pos_inicial]);
		}
		else{
			sucesso = dijkstra( payld_ex->pos_inicial, payld_ex->pos_final, payld_dic->adj, payld_dic->num_palavras, payld_ex->max_mutacoes , &st, &wt);
			if( sucesso == 1 ) {
				fprintf(fp, "%s %d\n", payld_dic->palavras[payld_ex->pos_inicial] , wt[ payld_ex->pos_final ] );
				printcaminho(fp, st, payld_ex->pos_final, payld_dic->palavras);
			}
			else {
				fprintf(fp, "%s -1\n", payld_dic->palavras[ payld_ex->pos_inicial] );
				fprintf(fp, "%s\n", payld_dic->palavras[payld_ex->pos_final]);
			}
			fprintf(fp, "\n" );
			free(st);
			free(wt);
		}
	}

	free(nomeficheiro);
	fclose(fp);
}


/******************************************************************************
 * printcaminho()
 *
 * Argumentos:fp - Ponteiro para o ficheiro de escrita
 *			  st - Vetor que contêm a arvore que representam o caminho dos nós à origem
 *			  n - Posição da palavra final do Problema
 *  	      palavras - Array que contêm todas as strings do tamanho desejado
 * Retorna: ----
 * Efeitos-colaterais: ----
 *
 * Descrição:
 *
 *****************************************************************************/
void printcaminho(FILE*fp, unsigned short* st, unsigned short n, char** palavras) {
	if( st [ st[n] ] != 65535 )
		printcaminho(fp, st, st[n], palavras);

	fprintf(fp,"%s\n", palavras[n]);

}

/******************************************************************************
 * dijkstra()
 *
 * Argumentos:ini - Posição da palavra inicial no grafo, no st, e no wt
 *   		  fini - Posição da palavra final no grafo, no st, e no wt
 *			  lista - Tabela de Lista de adjacências
 *			  num_v - Número de vertices
 *			  max_mut - Número máximo de mutações para palavras desse tamanho
 *			  _st - Vetor que contêm a arvore que representam o caminho dos nós à origem
 *			  _wt - array que contêm os pesos das ligações à origem			
 * Retorna:   1 Se há há caminho
 			  0 caso contrário
 * Efeitos-colaterais: ----
 *
 * Descrição:
 *
 *****************************************************************************/
int dijkstra( int ini, int fini, lista_adjs** lista , int num_v, short max_mut, unsigned short ** _st, unsigned short ** _wt ){
	int prio=0, v=0, sucesso=0, item=0;
	unsigned short *st=NULL, *wt=NULL;
	FilaP * fp = NULL;
	lista_adjs * iterador = NULL;
	st = (unsigned short *) x_malloc( sizeof(unsigned short) * num_v);
	wt = (unsigned short *) x_malloc( sizeof(unsigned short) * num_v);

	fp =FPriorIni(num_v);

	for( v = 0; v < num_v ; v ++ ){
		st[v] = -1;
		wt[v] = INFINITE;
		FInsereDirec(fp, v);
	}
	wt[ini] = 0;
	FixUp(fp, ini, wt);

	while( fp->free != 0 ) {
		if( wt[prio = FRemove(fp,wt)] != INFINITE  ){
			for(iterador = lista[prio]; iterador != NULL; iterador = iterador->prox){

				if(iterador->peso > max_mut*max_mut)continue; /* se o peso este adjacente for superior ao estabelecido ignoramos */

				if( wt[iterador->v_adj] > (int)wt[prio] + (int)iterador->peso ){
					wt[iterador->v_adj] = (int)wt[prio] + (int)iterador->peso;
					FixUp(fp,FPDiscover(fp,iterador->v_adj),wt);
					st[iterador->v_adj]=prio;
					if(iterador->v_adj == fini ) sucesso=1;
				}
			}
		}
	}

	*_st = st;
	*_wt = wt;

	FPfree(fp);
	return sucesso;

}
