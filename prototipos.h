#ifndef PROTOTIPOS_H
#define  PROTOTIPOS_H

/* algoritmo.c */
t_lista *  correprograma(char *** dicionario, char * filename);
t_lista * procura_caminho(char *** dicionario, char * inicial, char* final, int quant);

/* file.c */
FILE *AbreFicheiro ( char *nome, char *mode );
char *LePalavra ( FILE * f );
int LeParametros(FILE * f, char ** inicial, char ** final, int *quant);
t_lista * AlocaDicionario (FILE * f,short numchars[MAX_STR]);
void PreencheDicionario(FILE * f, t_lista * dicionario, short numchars[MAX_STR]);
char* ConstroiNome ( char*  nomeantigo );
t_lista * ProcuraExercicios(FILE* ficheiro, short numchars[MAX_STR],short *nmutmax);
void EscreveFicheiro(char* nome, t_lista * exercicios, t_lista * dicionario);


/* libertador.c */
void Freedoom ( t_lista* dicionario, t_lista * caminhos);
void freepldicionario( Item  aaa );
void free_exercicios( Item  aaa );

/* ordenador.c */
void ArrumaDicionario(t_lista * dicionario);
void mergesort(Type * table, int low, int high, int comparer(Type, Type) );
void merge(Type * table, int low, int mid, int high, int comparer(Type, Type) );
int stringcompare ( char* a, char* b );
int binarysearch(Type* table, int l, int r, Type item, int comparer(Type, Type) );
void encontraposicao( t_lista * exercicios, t_lista * dicionariocabeca );
int compfunc( const void * a, const void * b );
void quicksort(Item a[], int l, int r);
int partition(Item a[], int l, int r);

/*grafo.c*/
void cria_todos_grafos(t_lista * dicionario,short nmutmax[] );
void cria_grafo( payload_dicionario * payld, short nmutmax );
int comparer2( char * p1, char* p2, short n);
void encontracaminhos( t_lista * dicionario, t_lista * exercicios, char* nomeficheiro );
void printcaminho(FILE*fp, short* st, int n, char** palavras);
void dijkstra( int ini, int fini, lista_adjs** lista , int num_v, short max_mut, int ** _st, int ** _wt );



/*fila_prioritaria.c*/
FilaP * FPriorIni(int);		    /*Aloca e inicializa uma fila prioritaria*/
void FInsere(FilaP * fp, int item, int weight[]);
int FRemove(FilaP * fp, int weight[]);
void FixUp(int queue[] , int idx, int weight[] );
void FixDown( int queue[], int idx, int n, int weight[] );



#endif
