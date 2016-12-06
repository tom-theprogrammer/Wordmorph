#include "estrt_const_bibliot.h"
#include "prototipos.h"


/******************************************************************************
 * AbreFicheiro()
 *
 * Arguments: nome - pointer to string holding name of file to open
 *            mode - pointer to string holding mode to use for opening file
 * Returns: pointer to opened file
 * Side-Effects: exits if given file cannot be opened with given mode
 *
 * Description:
 *
 *****************************************************************************/
FILE *AbreFicheiro ( char *nome, char *mode ) {
  FILE *f;
  f = fopen ( nome, mode );
  if ( f == NULL ) {
    exit (0);
    /* Error messages are sent to the stderr channel.
       Use an exit number different from 0 (zero) in case of error.*/
  }
  return (f);
}



/******************************************************************************
 * LePalavra()
 *
 * Arguments: f - pointer to file where word will be read
 * Returns: pointer to word just read
 * Side-Effects: none
 *
 * Description:
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

  /* fscanf(f, "%s %s %d", inicial, final, quant); */
}





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



char* ConstroiNome ( char*  nomeantigo ) {
    char*  ficheirooutput = (char*) x_malloc( sizeof(char) * ( strlen(nomeantigo) + 2 ) );
    strcpy(ficheirooutput, nomeantigo);
    strcpy(ficheirooutput + (strlen(nomeantigo) - 1) , "th" );
    return ficheirooutput;
}





t_lista * ProcuraExercicios(FILE* ficheiro, short numchars[MAX_STR], short nummutmax[MAX_STR]) {
  char *inicial=NULL, *final=NULL;
  int n_mutacoes=0, erro, tamanho;
  payload_exercicios * exercicio;
  t_lista * cabeca = NULL;

  while( LeParametros(ficheiro, &inicial, &final, &n_mutacoes) == 3 ){
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
