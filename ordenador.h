#ifndef ORDENADOR_H
#define  ORDENADOR_H

#include "estrt_const_bibliot.h"


typedef char* Type;

void ArrumaDicionario(t_lista * dicionario);
void mergesort(Type * table, int low, int high, int comparer(Type, Type) );
void merge(Type * table, int low, int mid, int high, int comparer(Type, Type) );
int  stringcompare ( char* a, char* b );
int  binarysearch(Type* table, int l, int r, Type item, int comparer(Type, Type) );
void encontraposicao( t_lista * exercicios, t_lista * dicionariocabeca );
int  compfunc( const void * a, const void * b );
void quicksort(Item a[], int l, int r);
int  partition(Item a[], int l, int r);

#endif
