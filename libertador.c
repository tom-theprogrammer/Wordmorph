#include "estrt_const_bibliot.h"
#include "prototipos.h"



void freepldicionario( Item aaa ) {
    payload_dicionario * payloaddicionario = (payload_dicionario * ) aaa;
    int i;
    for(i = 0; i<payloaddicionario->num_palavras; i++) {
        free(payloaddicionario->palavras[i]);
        free(payloaddicionario->adj[i]);

        for(iterador=payloaddicionario->adj[i]; payloaddicionario->adj[i]!=NULL; payloaddicionario->adj[i]=payloaddicionario->adj[i]->prox )
            free(iterador);

    }
    free(payloaddicionario->palavras);
    free(payloaddicionario->adj);
    free(payloaddicionario);
}


void free_exercicios( Item aaa ) {
    payload_exercicios * payl = (payload_exercicios * ) aaa;
    /*free(payl->palavra_inicial);*/
    /*free(payl->palavra_final);*/
    free(payl);
}


void Freedoom ( t_lista * dicionario, t_lista * exercicios) {
    libertaLista(dicionario, freepldicionario);
    libertaLista(exercicios, free_exercicios);
}
