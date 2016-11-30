#include "estrt_const_bibliot.h"
#include "prototipos.h"

void cria_todos_grafos(t_lista * dicionario,short nmutmax[] ){
    t_lista * iterador = NULL;
    payload_dicionario * payld = NULL;
    short i = 0;

    for(iterador=dicionario, i =0 ;iterador != NULL; iterador = getProxElementoLista(iterador),i++){
        payld = getItemLista(iterador);
        cria_grafo(payld, nmutmax[payld->num_char]);
    }
}




void cria_grafo( payload_dicionario * payld, short nmutmax ) {
    int counter1=0, counter2=0, diff=0;
    lista_adjs ** adj2 = NULL;
    lista_adjs * aux  = NULL;

    payld->adj = (lista_adjs **) malloc( sizeof(lista_adjs*) * payld->num_palavras );
    adj2 = payld->adj;

    for( counter1=0; counter1<payld->num_palavras; counter1++ ){
        adj2[counter1] = NULL;
    }

    for( counter1 = 0; counter1 < payld->num_palavras; counter1++) {

        for( counter2 = counter1+1; counter2< payld->num_palavras; counter2++) {

            diff = comparer2(payld->palavras[counter1], payld->palavras[counter2], nmutmax);
            if(diff > nmutmax) continue;

            aux= (lista_adjs *) malloc( sizeof(lista_adjs) );
            aux->v_adj=counter2;
            aux->peso=diff*diff;
            aux->prox=adj2[counter1];
            adj2[counter1]= aux;

            aux= (lista_adjs *) malloc( sizeof(lista_adjs) );
            aux->v_adj=counter1;
            aux->peso=diff*diff;
            aux->prox=adj2[counter2];
            adj2[counter1]= aux;

        }

    }

}

/* assumimos que as palavras têm o mesmo comprimento */
int comparer2( char * p1, char* p2, short n) {
    int diff=0, i=0;
    for( i=0; p1[i] != '\0' && diff<=n; i++ )
        if(p1[i]!=p2[i]) diff++;

    return diff;
}


void encontracaminhos( t_lista * dicionario, t_lista * exercicios, char* nomeficheiro ) {
    t_lista * it_ex = exercicios, * it_dic = NULL;
    payload_exercicios * payld_ex = NULL;
    payload_dicionario * payld_dic = NULL;
    int * st;
    int i;
	/*FILE* fp = AbreFicheiro(nomeficheiro, "w");*/

    for(; it_ex != NULL; it_ex = getProxElementoLista(it_ex) ) {
        payld_ex = (payload_exercicios *)getItemLista( it_ex );

        for(it_dic=dicionario;it_dic!=NULL;it_dic=getProxElementoLista(it_dic)) {
            payld_dic = (payload_dicionario *) getItemLista( it_dic );
            if( payld_dic->num_char == payld_ex->num_char )
                break;
        }

        printf("Iniciar Dijkstra \n");
        st = dijkstra( payld_ex->pos_inicial, payld_ex->pos_final, payld_dic->adj, payld_dic->num_palavras, payld_ex->max_mutacoes );
		printf("Dijkstra terminado \n");

        for(i=0;i<10;i++){
            printf("%d=%d\n",i,st[i]);
        }
        for(i=payld_ex->pos_inicial;i != payld_ex->pos_final; i = st[i]){
            printf("%d - %s \n",i, payld_dic->palavras[i]);
        }
	}

	/*fclose(fp);*/
}


/* http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/  */
int* dijkstra( int ini, int fini, lista_adjs** lista , int num_v, short max_mut ){
    int prio, v;
    int *st=NULL, *wt=NULL;
	FilaP * fp = NULL;
    int item;
    lista_adjs * iterador = NULL;
	st = (int *) malloc( sizeof(int) * num_v);
	wt = (int *) malloc( sizeof(int) * num_v);

    fp =FPriorIni(num_v);

    printf("Inicializar variaveis \n");
    for( v = 0; v < num_v-1; v ++ ){
		st[v] = -1;
		wt[v] = INFINITE;
        if(v == ini) {printf("ini=%d\n",ini); wt[v]=0;}
		FInsere(fp, v, wt);
	}

    printf("Iniciar algoritmo \n");
    while( fp->free != 0 ) {
        prio = FRemove(fp,wt);
        printf("%d retirado da lista de prioridade: \n",prio);
        printf("peso(%d)=%d\n",prio,wt[prio]);
        for(iterador = lista[prio]; iterador != NULL; iterador = iterador->prox){
            printf("distancia=%d\n",(int)iterador->peso);
            printf("%d\n",wt[iterador->v_adj]);
             if(wt[prio] + (int)iterador->peso < wt[iterador->v_adj]){
                 wt[iterador->v_adj] = wt[prio] + iterador->peso;
                 FixUp(fp->queue,iterador->v_adj,wt);
                 st[iterador->v_adj]=prio;  /*Not sure*/
             }
        }

    }
    return st;
}
