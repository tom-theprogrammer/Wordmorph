#ifndef PROTOTIPOS_H
#define  PROTOTIPOS_H

/* algoritmo.c */
t_lista * correprograma(char *** dicionario, char * filename);
t_lista * procura_caminho(char *** dicionario, char * inicial, char* final, int quant);

/* file.c */
FILE   *AbreFicheiro ( char *nome, char *mode );
char   *LePalavra ( FILE * f );
int     LeParametros(FILE * f, char ** inicial, char ** final, int *quant);
t_lista*AlocaDicionario (FILE * f,short numchars[MAX_STR]);
void    PreencheDicionario(FILE * f, t_lista * dicionario, short numchars[MAX_STR]);
char   *ConstroiNome ( char*  nomeantigo );
t_lista*ProcuraExercicios(FILE* ficheiro, short numchars[MAX_STR],short *nmutmax);
void    EscreveFicheiro(char* nome, t_lista * exercicios, t_lista * dicionario);


/* libertador.c */
void Freedoom ( t_lista* dicionario, t_lista * caminhos);
void freepldicionario( Item  aaa );
void free_exercicios( Item  aaa );
void * x_malloc(size_t size);

/* ordenador.c */


/*grafo.c*/
void cria_todos_grafos(t_lista * dicionario,short nmutmax[] );
void cria_grafo( payload_dicionario * payld, short nmutmax );
int  comparer2( char * p1, char* p2, short n);
void encontracaminhos( t_lista * dicionario, t_lista * exercicios, char* nomeficheiro );
void printcaminho(FILE*fp, unsigned short* st, unsigned short n, char** palavras);
int  dijkstra( int ini, int fini, lista_adjs** lista , int num_v, short max_mut, unsigned short ** _st, unsigned short ** _wt );


#endif
