#include "estrt_const_bibliot.h"
#include "prototipos.h"



 /******************************************************************************
 * AbreFIcheiro()
 *
 * Argumentos: nome - Nome do ficheiro a abrir
               mode - Modo de abertura do ficheiro
 * Retorna: Ponteiro para ficheiro aberto
 * Efeitos-colaterais: Exit se o ficheiro passado não poder ser aberto
 *
 * Descrição:
 *
 *****************************************************************************/
FILE *AbreFicheiro ( char *nome, char *mode ) {
  FILE *f;
  f = fopen ( nome, mode );
  if ( f == NULL ) 
    exit (0);
  return (f);
}


/******************************************************************************
 * LePalavra()
 *
 * Argumentos:f - Ponteiro para o ficheiro de onde vamos extrair informação
 * Retorna: Ponteiro para a palavra lida
 * Efeitos-colaterais: Return NUll se nao conseguir ler a palavra
 *
 * Descrição:
 *
 *****************************************************************************/
char* LePalavra( FILE * f ) {
  char temp[MAX_STR] = {'\0'}, *pal=NULL;

  if( fscanf(f,"%s", temp) == 0 )
    return NULL;

  if (!strcmp(temp, "\0"))
    return NULL;

  pal = (char*) x_malloc(strlen(temp) + 1);
  if(pal != NULL)
    strcpy(pal,temp);

  return pal;
}



/******************************************************************************
 * LeParametros()
 *
 * Argumentos:f - Ponteiro para o ficheiro de onde vamos extrair informação
 *            inicial - Ponteiro para a string que vai conter a palavra inicial do problema
 *            final - Ponteiro para a string que vai conter a palavra final do problema
 *            quant - Ponteiro para o inteiro que vai conter o número maximo de mutações para o problema
 * Retorna:   3 se tudo correr como esperado
              0,1 ou 2 se existir um erro na leitura do ficheiro
 * Efeitos-colaterais: ---
 *
 * Descrição:
 *
 *****************************************************************************/
int LeParametros(FILE * f, char ** inicial, char ** final, int *quant){
  char *strint = NULL;

  *inicial = LePalavra(f);
  if(*inicial == NULL ) return 0;
  *final = LePalavra(f);
  if(*final == NULL)	return 1;
  *quant = atoi(strint = LePalavra(f));
  if(strint == NULL)	return 2;

  free(strint);

  return 3;
}




/******************************************************************************
 * AlocaDicionario()
 *
 * Argumentos:f - Ponteiro para o ficheiro de onde vamos extrair informação
 *            numchars - Array que indica quais a quantidade de palavras por tamanho de palavra 
 * Retorna:   Ponteiro para a cabeça da lista que é o dicionario
 * Efeitos-colaterais: ---
 *
 * Descrição: 
 *
 *****************************************************************************/
t_lista * AlocaDicionario (FILE * f,short numchars[MAX_STR]){
	int ocorrencias[MAX_STR] = {0};
	char * nova_palavra = NULL;
	int i, erro;
	t_lista * cabeca = iniLista();
	payload_dicionario * payloaddicionario = NULL;

    while((nova_palavra=LePalavra(f)) != (char *)NULL){
		  ocorrencias[strlen(nova_palavra)-1] +=1;
		  free(nova_palavra);
    }


	for(i=0;i<MAX_STR;i++){
		if(ocorrencias[i]==0 || numchars[i]==0) continue;
        payloaddicionario = (payload_dicionario * ) x_malloc ( sizeof(payload_dicionario) );
        payloaddicionario->palavras =  (char ** ) x_malloc ( sizeof(char*) * ocorrencias[i] );
        payloaddicionario->num_palavras = ocorrencias[i];
        payloaddicionario->num_char = i+1;
        cabeca = criaNovoNoLista ( cabeca, (Item) payloaddicionario,&erro);
        if (erro) {exit(0);}
	}
	fclose(f);
	return cabeca;
}




/******************************************************************************
 * PreencheDicionario()
 *
 * Argumentos:f - Ponteiro para o ficheiro de onde vamos extrair informação
 *            dicionario - Ponteiro para a lista que contêm o dicionario
 *            numchars - Array que indica quais a quantidade de palavras por tamanho de palavra
 * Retorna:  ---
 * Efeitos-colaterais: ---
 *
 * Descrição:
 *
 *****************************************************************************/
void PreencheDicionario(FILE * f, t_lista * dicionario, short numchars[MAX_STR]){
  t_lista * iterador = NULL;
	int posicoes[MAX_STR] = {0};
	int tamanho;
	char * nova_palavra = NULL;
  payload_dicionario * payd;

	while((nova_palavra=LePalavra(f)) != (char *)NULL){
        tamanho = strlen(nova_palavra);
        for(iterador=dicionario;iterador!=NULL;iterador=getProxElementoLista(iterador)) {

            payd=(payload_dicionario*) getItemLista(iterador);
            if(payd->num_char==tamanho) break;
        }

        if(iterador == NULL ) {
            free(nova_palavra);
            continue;
        }
        payd->palavras[ posicoes[tamanho-1]++ ]= nova_palavra;
	}
  fclose(f);
}





/******************************************************************************
 * EscreveFicheiro()
 *
 * Argumentos:nome - Nome do ficheiro de entrada que nos premitira descobrir o nome do de saída
 *            exercicios - Ponteiro para a lista que contêm os Problemas a resolver
 *            dicionario - Ponteiro para a lista que contêm o dicionario
 * Retorna: ---
 * Efeitos-colaterais: ---
 *
 * Descrição:
 *
 *****************************************************************************/
void EscreveFicheiro(char* nome, t_lista * exercicios, t_lista * dicionario){
    char* ficheirooutput = ConstroiNome(nome);
    FILE * f = AbreFicheiro(ficheirooutput,"w");
    t_lista * iterador = dicionario;
	payload_exercicios * payloadexercicios = NULL;
    payload_dicionario * payloaddicionario = getItemLista(iterador);

	for(;exercicios != NULL; exercicios = getProxElementoLista(exercicios)){
		payloadexercicios = (payload_exercicios *)getItemLista(exercicios);

        if(payloadexercicios->max_mutacoes == 1) {
            iterador = dicionario;
            payloaddicionario = getItemLista(iterador);

            while(payloadexercicios->num_char != payloaddicionario->num_char){
              iterador = getProxElementoLista(iterador);
              payloaddicionario = getItemLista(iterador);
            }


            fprintf(f, "%s %d\n\n",payloadexercicios->palavra_inicial,payloaddicionario->num_palavras);
        }
        else {
            fprintf(f,"%s %d\n%s %d\n\n",payloadexercicios->palavra_inicial,payloadexercicios->pos_inicial,payloadexercicios->palavra_final,payloadexercicios->pos_final);
        }
	}

    fclose(f);
    free(ficheirooutput);

}


/******************************************************************************
 * ConstroiNome()
 *
 * Argumentos:nomeantigo - Nome do ficheiro de entrada
 * Retorna:   Ponteiro para a string que contêm o nome do ficheiro de escrita
 * Efeitos-colaterais: ---
 *
 * Descrição:
 *
 *****************************************************************************/
char* ConstroiNome( char*  nomeantigo ) {
    char*  ficheirooutput = (char*) x_malloc( sizeof(char) * ( strlen(nomeantigo) + 2 ) );
    strcpy(ficheirooutput, nomeantigo);
    strcpy(ficheirooutput + (strlen(nomeantigo) - 1) , "th" );
    return ficheirooutput;
}




/******************************************************************************
 * ProcuraExercicios()
 *
 * Argumentos:ficheiro - Ponteiro para o ficheiro de onde vamos extrair informação
 *            numchars - Array que indica quais a quantidade de palavras por tamanho de palavra
 *            nummutmax - Array que contêm o maior número maximo de mutações para cada tamanho de palavra
 * Retorna:   Ponteiro para a cabeça da lista que contêm os problemas a resolver
 * Efeitos-colaterais: ---
 *
 * Descrição:
 *
 *****************************************************************************/
t_lista * ProcuraExercicios(FILE* ficheiro, short numchars[MAX_STR], short nummutmax[MAX_STR]) {
  char *inicial=NULL, *final=NULL;
  int n_mutacoes=0, erro, tamanho, tmp;
  payload_exercicios * exercicio;
  t_lista * cabeca = NULL;

  while( LeParametros(ficheiro, &inicial, &final, &n_mutacoes) == 3 ){

    if( (tmp = comparer2(inicial,final,n_mutacoes)) < n_mutacoes){
      n_mutacoes=tmp;
    }

    if(n_mutacoes > nummutmax[strlen(inicial)-1]) nummutmax[strlen(inicial)-1] = n_mutacoes;

    exercicio = (payload_exercicios*) x_malloc(sizeof(payload_exercicios));
  	exercicio->palavra_inicial = inicial;
  	exercicio->palavra_final = final;
  	exercicio->max_mutacoes = n_mutacoes;
    tamanho = strlen(inicial);
    if(tamanho > MAX_STR ){exit(0);}
  	exercicio->num_char = tamanho;
  	numchars[tamanho-1]=1;
  	cabeca = criaNovoNoLista (cabeca, (Item) exercicio, &erro);
  	if(erro == 1) { exit(0);}
  }

  fclose(ficheiro);
  return cabeca;
}
