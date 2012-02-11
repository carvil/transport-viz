#include<stdio.h>
#include<glib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include"data.h"

void insere_um_nodo(char * key, char * value, FILE * fp);

void insere_nodos(GHashTable * tabela, FILE * fp);

char * concat(char * h, char * tmp);

char * concatHorarios(GSList * horar);

void insere_uma_ligacao_1(TIPO_1 * t1, FILE * fp);

void insere_uma_ligacao_2(TIPO_2 * t2, FILE * fp);

void insere_ligacoes1(GSList * l, FILE * fp);

void insere_ligacoes2(GSList * l, FILE * fp);

void insere_legenda(FILE * fp);

void gera_ficheiro(GHashTable * tabela, GSList * lista1, GSList * lista2, FILE * fp);
