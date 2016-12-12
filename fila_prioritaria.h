#ifndef FILA_PRIORITARIO_H
#define FILA_PRIOTIRARIO_H

#include "estrt_const_bibliot.h"

FilaP *FPriorIni(int);											/*Aloca e inicializa uma fila prioritaria*/
void   FInsere(FilaP * fp, int item, unsigned short weight[]);	/*Insere um elemento na fila prioritáira*/
void   FInsereDirec(FilaP * fp, int item);          			/*Insere um elemento sem se preocupar com concertar a prioridade */ 
int    FRemove(FilaP * fp, unsigned short weight[]);			/*Remove um elemento da fila prioritária*/
void   FixUp(FilaP * , int item, unsigned short weight[] );		/*Ajusta a localização de um elemento cuja prioridade foi aumentada*/
void   FixDown(FilaP *, int item, unsigned short weight[] );	/*Ajusta a localização de um elemento cuja prioridade foi diminuida>*/
void   FPfree(FilaP *  fp);                                 	/*Liberta memoria alocada para o uso da lista prioritária*/

#endif