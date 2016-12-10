#include "estrt_const_bibliot.h"
#include "prototipos.h"


FilaP * FPriorIni(int size){
    FilaP * fp = (FilaP *)x_malloc(sizeof(FilaP));
    fp->queue = (unsigned short *)x_malloc(sizeof(unsigned short)*size);
    fp->size = size;
    fp->free = 0;
    return fp;
}




void FInsere(FilaP * fp, int item, unsigned short weight[]){
    if(fp->free < fp->size ){
        fp->queue[fp->free] = item;
        FixUp(fp,fp->free,weight);
        fp->free++;
        return;
    }
    /*printf("A fila prioritaria está cheia, por isso há aqui um prob\n");*/
}

void FInsereDirec(FilaP * fp, int item) {
    if(fp->free < fp->size) {
        fp->queue[fp->free] = item;
        fp->free++;
        return;
    }
    /*printf("A fila prioritaria está cheia, por isso há aqui um prob\n");*/
}



int FRemove(FilaP * fp,unsigned short weight[]){
    int aux;

    /* executar a troca */
    aux = fp->queue[0];
    fp->queue[0] = fp->queue[fp->free -1];

    /* fazer fixdown do trocado */
    fp->free--;

    FixDown(fp,0,fp->free, weight);


    return aux;

}





void FixUp(FilaP *fp , int idx, unsigned short weight[] ){
    int aux;
    while( (idx > 0) && ( weight[ fp->queue[(idx-1)/2] ] > weight[ fp->queue [idx] ]) ){
        aux = fp->queue[(idx-1)/2];
        fp->queue[(idx-1)/2] = fp->queue[idx];
        fp->queue[idx] = aux;
        idx=(idx-1)/2;
    }
}


/**
 * idx é a posição na tabela do nó que queremos acertar
 * n é a primeira posição não ocupada
 */
void FixDown( FilaP *fp, int idx, int n, unsigned short weight[] ){
    int child;
    int aux;

    while( 2 * idx < n -1){
        /* comparamos os 2 filhos */
        child = 2*idx+1; /* filho 1 */
        if( (child < n-1) &&  weight[fp->queue[child] ] >  weight[fp->queue[child+1] ] )
            child++;

        /* verificamos se o filho cuja prioridade é maior tem maior prioridade que o pai */
        if(weight[fp->queue[idx] ] <  weight[fp->queue[child] ])
            break;

        aux = fp->queue[idx];
        fp->queue[idx] = fp->queue[child];
        fp->queue[child] = aux;

        idx = child;
    }
}

void FPfree(FilaP *  fp){
    free(fp->queue);
    free(fp);
}



int FPDiscover(FilaP *fp, int v) {
  int i;
  for(i=0;i<fp->free;i++) {
    if( fp->queue[i] == v ) return i;
  }
  /*printf("Erro crasso\n" );*/
  exit(0);
}
