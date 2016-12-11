#ifndef ECB_H
#define ECB_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

#define key(A) (A)
#define less(A, B)  (strcmp(A,B) < 0)
#define exch(A, B)  {char* t = A; A = B; B = t; }

#define MAX_STR 40
#define INFINITE MAX_STR*MAX_STR

#define ItemFP void *

typedef struct {
	short num_char;
	short max_mutacoes;		/*Parametro recebido com o número maximo de caracteres que se podem alterar de 1 vez*/
	char * palavra_inicial;
	char * palavra_final;
	int pos_inicial; 		/* posicao da palavra inicial no dicionario */
	int pos_final; 			/* posicao da palavra final no dicionario */
}payload_exercicios;		/*Lista que vai conter ponteiros para todos os caminhos*/

typedef struct _lista_adjs {
	int v_adj;
	short peso;
	struct _lista_adjs * prox;
} lista_adjs;

typedef struct{
	int num_char;
	int num_palavras;
	char ** palavras;
	lista_adjs** adj;
}payload_dicionario;

typedef struct{
	unsigned short *queue;
	int free;
	int size;
}FilaP;
#endif
