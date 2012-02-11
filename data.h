#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>


/*Estrutura de descrição*/

typedef struct desc {
	char * distancia_;
	char * custo_;
	char * duracao_;
	GSList * horarios;
}DESC;

typedef struct tipo_1 {
	
	char * origem;
	char * destino;
	GSList * viagem_1;
}TIPO_1;

typedef struct viagem_1 {

	char * transporte;
	DESC * descricao;
}VIAGEM_1;

/******************************************/

typedef struct tipo_2 {
	
	char * transporte;
	GSList * viagem_2;
}TIPO_2;

	
typedef struct viagem_2 {

	char * origem;
	char * destino;
	DESC * descricao;
}VIAGEM_2;

DESC * inicializa_descr();

VIAGEM_1 * inicializa_viagem1();

VIAGEM_2 * inicializa_viagem2();

TIPO_1 * inicializa_tipo1();

TIPO_2 * inicializa_tipo2();

GSList * freeGslistT1(GSList *g);

void freeTipo1(TIPO_1 *t);

void freeViagem_1(VIAGEM_1 *v);

void freeDescricao(DESC *d);

GSList * freeGslistT2(GSList *g);

void freeTipo2(TIPO_2 *t);

void freeViagem_2(VIAGEM_2 *v);
