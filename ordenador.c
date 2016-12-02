#include "ordenador.h"
#include "prototipos.h"


void ArrumaDicionario(t_lista * dicionario) {
    payload_dicionario * payloaddicionario;

    for( ; dicionario!= NULL ; dicionario = getProxElementoLista(dicionario) ) {
        payloaddicionario = (payload_dicionario * ) getItemLista(dicionario);

        quicksort((void*)payloaddicionario->palavras, 0 ,payloaddicionario->num_palavras-1);
    }
}

void quicksort(Item a[], int l, int r)

{
int i;
if (r <= l) return;
i = partition(a, l, r);
quicksort(a, l, i-1);
quicksort(a, i+1, r);
}

int partition(Item a[], int l, int r)
{
int i, j;
Item v;
v = a[r]; i = l-1; j = r;
for (;;) {
    while (less(a[++i], v)) ;
    while (less(v, a[--j]))
    if (j == l) break;
    if (i >= j) break;
    exch(a[i], a[j]);
}
exch(a[i], a[r]);
return i;
}


int compfunc( const void * a, const void * b ) {
    return stringcompare( (char*) a , (char* )b );
}

/* assume-se que as palavras têm o mesmo tamanho e são todas de minúsculas */
int stringcompare ( char* a, char* b ) {
    int i;
    for(i=0;a[i]!='\0';i++) {
        if(a[i]>b[i]) return 1;
        else if(a[i]<b[i]) return -1;
    }
    return 0;
}


void encontraposicao( t_lista * exercicios, t_lista * dicionariocabeca ) {
    payload_exercicios *payloadexercicios= NULL;
    payload_dicionario *payloaddicionario=NULL;
    t_lista * iterador= NULL;
    int posicaostart, posicaolast, numchars;
    
    for( ; exercicios != NULL; exercicios=getProxElementoLista(exercicios) ) {
        payloadexercicios = (payload_exercicios *) getItemLista(exercicios);
        numchars=payloadexercicios->num_char;
        for(iterador=dicionariocabeca;iterador!=NULL;iterador=getProxElementoLista(iterador)) {
            payloaddicionario=(payload_dicionario*) getItemLista(iterador);
            if(payloaddicionario->num_char==numchars) break;
        }
        posicaostart = binarysearch(payloaddicionario->palavras,0,payloaddicionario->num_palavras-1,payloadexercicios->palavra_inicial,stringcompare);
        payloadexercicios->pos_inicial = posicaostart;
        posicaolast = binarysearch(payloaddicionario->palavras,0,payloaddicionario->num_palavras-1,payloadexercicios->palavra_final,stringcompare);
        payloadexercicios->pos_final = posicaolast;
        free(payloadexercicios->palavra_inicial);
        free(payloadexercicios->palavra_final);
    }
}




/* https://www.tutorialspoint.com/data_structures_algorithms/binary_search_program_in_c.htm */
int binarysearch(Type* table, int l, int r, Type item, int comparer(Type, Type) ) {
    int mid,  compareresult;

    while ( l <= r ) {
        mid = l + ( r - l ) / 2;

        compareresult = comparer( table[mid], item );

        /* if the data to compare is equal to table[mid] */
        if( compareresult == 0 )
            return mid;
        /* if the data do compare is larger   */
        else if ( compareresult < 0 )
            l = mid + 1;
        /* if the data do compare is smaller */
        else
            r = mid -1;
    }

    /* at this point something went wrong so -1 is returned */
    return -1;

}
