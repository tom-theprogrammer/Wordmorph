#include "estrt_const_bibliot.h"
#include "prototipos.h"



void freepldicionario( Item aaa ) {
    payload_dicionario * payloaddicionario = (payload_dicionario * ) aaa;
   lista_adjs * iterador = NULL;

    int i;
    for(i = 0; i<payloaddicionario->num_palavras; i++) {
        free(payloaddicionario->palavras[i]);

        while(payloaddicionario->adj[i]!=NULL){
            iterador=payloaddicionario->adj[i];
            payloaddicionario->adj[i]=payloaddicionario->adj[i]->prox;
            free(iterador);
        }

    }
    free(payloaddicionario->palavras);
    free(payloaddicionario->adj);
    free(payloaddicionario);
}


void free_exercicios( Item aaa ) {
    payload_exercicios * payl = (payload_exercicios * ) aaa;
    free(payl);
}


void Freedoom ( t_lista * dicionario, t_lista * exercicios) {
    libertaLista(dicionario, freepldicionario);
    libertaLista(exercicios, free_exercicios);
}

void * x_malloc(size_t size){
    void * p = NULL;
    p = malloc(size);
    if(p==NULL) 
        exit(0);
    return p;
}

