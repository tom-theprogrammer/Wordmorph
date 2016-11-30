#include "estrt_const_bibliot.h"
#include "prototipos.h"



void cria_todos_grafos(t_lista * dicionario,short nmutmax[] ){
    t_lista * iterador = NULL;
    payload_dicionario * payld = NULL;

    for( iterador=dicionario ;iterador != NULL; iterador = getProxElementoLista(iterador) ){
        payld = getItemLista(iterador);
        printf("tamanho das palavras deste grafo: %d\n",(int)payld->num_char);
        printf("num max mut teste grafo: %d", (int)nmutmax[payld->num_char-1]);        
        cria_grafo(payld, nmutmax[payld->num_char-1]);
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

        for( counter2 = counter1+1; counter2 < payld->num_palavras; counter2++) {

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
            adj2[counter2]= aux;

        }

    }

    for( counter1 = 0; counter1 < payld->num_palavras; counter1++){
        printf(">>>NÓ: %d --->     ",counter1);
        for(aux = adj2[counter1];aux != NULL;aux=aux->prox) {
            printf("%d--",aux->v_adj);
        }
        printf("\n");
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
    short * st = NULL, * wt = NULL, temp;
    int i;
	FILE* fp = AbreFicheiro(nomeficheiro, "w");

    for(; it_ex != NULL; it_ex = getProxElementoLista(it_ex) ) {
        payld_ex = (payload_exercicios *)getItemLista( it_ex );

        for(it_dic=dicionario;it_dic!=NULL;it_dic=getProxElementoLista(it_dic)) {
            payld_dic = (payload_dicionario *) getItemLista( it_dic );
            if( payld_dic->num_char == payld_ex->num_char )
                break;
        }

        dijkstra( payld_ex->pos_inicial, payld_ex->pos_final, payld_dic->adj, payld_dic->num_palavras, payld_ex->max_mutacoes , &st, &wt);

                
        for(i=0;i<payld_dic->num_palavras;i++){
            printf("%d=%d -- %s \n",i, st[i], payld_dic->palavras[i]);
        }


        fprintf(fp, "%s %d\n", payld_dic->palavras[payld_ex->pos_inicial] , (int) wt[ payld_ex->pos_final ] );
        printcaminho(fp, st, payld_ex->pos_final, payld_dic->palavras);

        /*for(i=payld_ex->pos_final; i != payld_ex->pos_inicial; i = st[i]){
            printf("i= %d\n",i);
            printf("next_i= %d\n",st[i]);
            printf("%d - %s \n",i, payld_dic->palavras[i]);
        }*/
	}

	fclose(fp);
}


void printcaminho(FILE*fp, short* st, int n, char** palavras) {
    
    if( st [ st[n] ] != -1 )
        printcaminho(fp, st, st[n], palavras);

    fprintf(fp,"%s\n", palavras[n]);

}




void dijkstra( int ini, int fini, lista_adjs** lista , int num_v, short max_mut, short ** _st, short ** _wt ){
    int prio, v;
    short *st=NULL, *wt=NULL;
	FilaP * fp = NULL;
    int item;
    lista_adjs * iterador = NULL;
	st = (short *) malloc( sizeof(short) * num_v);
	wt = (short *) malloc( sizeof(short) * num_v);

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
        if( wt[prio = FRemove(fp,wt)] != INFINITE ){
            
            for(iterador = lista[prio]; iterador != NULL; iterador = iterador->prox){
                 
                 if(iterador->peso > max_mut*max_mut)break;
                 
                 if( wt[iterador->v_adj] > wt[prio] + (int)iterador->peso ){
                     printf("--    ");
                     wt[iterador->v_adj] = wt[prio] + iterador->peso;
                     /*FixDown(fp->queue,iterador->v_adj, fp->free -1 ,wt );*/                     
                     FixUp(fp->queue,iterador->v_adj,wt);
                     st[iterador->v_adj]=prio;  
                 }
            }
        }
    }

    *_st = st;
    *_wt = wt;
}
