#ifndef ECB_H
#define ECB_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

/* Para utilizar pelo ordenador */
#define key(A) (A)
#define less(A, B)  (strcmp(A,B) < 0)
#define exch(A, B)  {char* t = A; A = B; B = t; }

/* Numero maximo de chars que o programa aceita */
#define MAX_STR 40
#define INFINITE MAX_STR*MAX_STR

#define ItemFP void *

typedef struct {
    short num_char;				/* Numero de chars da palavra */
    short max_mutacoes;			/*Parametro recebido com o número maximo de caracteres que se podem alterar de 1 vez*/
    char * palavra_inicial;		/*A palavra inicial*/
    char * palavra_final;		/*A palavra final*/
    int pos_inicial; 			/* posicao da palavra inicial no dicionario*/
    int pos_final; 				/* posicao da palavra final no dicionario*/
}payload_exercicios;			/*Lista que vai conter ponteiros para todos os caminhos*/

typedef struct _lista_adjs {
    int v_adj;					/*O vertice adjacente*/
    short peso;					/*O peso da ligação*/
    struct _lista_adjs * prox;	/*Ponteiro para o próximo nó*/
} lista_adjs;

typedef struct{
    int num_char;				/*Numero de caracteres das palavras deste dicionário*/
    int num_palavras;			/*Numero de palavras deste dicionário*/
    char ** palavras;			/*O vetor de palavras*/
    lista_adjs** adj;			/*A tabela de listas de adjacências*/
}payload_dicionario;

typedef struct{
    unsigned short *queue;		/*A fila implementada por tabela*/
    unsigned short *pos; 		/*Vetor que auxilia a descoberta dos items na tabela*/
    int free;					/*O numero de itens na tabela*/
    int size;					/*O tamanho da tabela*/
}FilaP;
#endif
