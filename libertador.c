#include "estrt_const_bibliot.h"
#include "prototipos.h"


/******************************************************************************
 * freepldicionario()
 *
 * Argumentos:aaa- Ponteiro para a estrutura que contêm os campos a libertar
 * Retorna: ---
 * Efeitos-colaterais: ---
 *
 * Descrição:
 *
 *****************************************************************************/
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


/******************************************************************************
 * free_exercicios()
 *
 * Argumentos:aaa- Ponteiro para a estrutura a libertar
 * Retorna: ---
 * Efeitos-colaterais: ---
 *
 * Descrição:
 *
 *****************************************************************************/
void free_exercicios( Item aaa ) { 
    payload_exercicios * payl = (payload_exercicios * ) aaa;
    free(payl);
}


/******************************************************************************
 * Freedoom()
 *
 * Argumentos:dicionario - Ponteiro para a lista que contêm o dicionario
 *            exercicios - Ponteiro para a lista que contêm os Problemas a resolver
 * Retorna: ---
 * Efeitos-colaterais: ---
 *
 * Descrição:Liberta toda a memoria alocada para as listas  de dicionario e exercicos.
 *
 *****************************************************************************/
void Freedoom ( t_lista * dicionario, t_lista * exercicios) {
    libertaLista(dicionario, freepldicionario);
    libertaLista(exercicios, free_exercicios);
}


/******************************************************************************
 * x_malloc()
 *
 * Argumentos:size - Tamanho do espaço a alocar
 * Retorna: Ponteiro para o espaço alocado
 * Efeitos-colaterais: Sai do programa se não for possivel alocar mais memoria
 *
 * Descrição: Aloca memoria e verifica se foi alocada com sucesso.
 *
 *****************************************************************************/
void * x_malloc(size_t size){
    void * p = NULL;
    p = malloc(size);
    if(p==NULL) 
        exit(0);
    return p;
}

