#include "estrt_const_bibliot.h"
#include "prototipos.h"


FilaP * FPriorIni(int size){
    FilaP * fp = (FilaP *)malloc(sizeof(FilaP));
    fp->queue = (int *)malloc(sizeof(int)*size);
    fp->size = size;
    fp->free = 0;
    return fp;
}




void FInsere(FilaP * fp, int item, short weight[]){
    if(fp->free +1 < fp->size ){
        fp->queue[fp->free] = item;
        FixUp(fp->queue,fp->free,weight);
        fp->free++;
        return;
    }
    printf("A fila prioritaria está cheia, por isso há aqui um prob\n");
}





int FRemove(FilaP * fp,short weight[]){
    int aux;

    /* executar a troca */
    aux = fp->queue[0];
    fp->queue[0] = fp->queue[fp->free -1];

    /* fazer fixdown do trocado */
    fp->free--; 

    FixDown(fp->queue,0,fp->free, weight);


    return aux;

}





void FixUp(int queue[] , int idx, short weight[] ){
    int aux;
    while( (idx > 0) && ( weight[ queue[(idx-1)/2] ] > weight[ queue [idx] ]) ){
        aux = queue[(idx-1)/2];
        queue[(idx-1)/2] = queue[idx];
        queue[idx] = aux;
        idx=(idx-1)/2;
    }
}


/**
 * idx é a posição na tabela do nó que queremos acertar
 * n é a primeira posição não ocupada
 */
void FixDown( int queue[], int idx, int n, short weight[] ){
    int child;
    int aux;

    while( 2 * idx < n -1){
        /* comparamos os 2 filhos */
        child = 2*idx+1; /* filho 1 */
        if( (child < n-1) &&  weight[queue[child] ] >  weight[queue[child+1] ] )
            child++;

        /* verificamos se o filho cuja prioridade é maior tem maior prioridade que o pai */
        if(weight[queue[idx] ] <  weight[queue[child] ])
            break;

        aux = queue[idx];
        queue[idx] = queue[child];
        queue[child] = aux;

        idx = child;
    }
}
