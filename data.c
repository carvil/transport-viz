#include"data.h"

DESC * inicializa_descr() {
	
	DESC * d;
	d = (DESC *) malloc(sizeof(DESC));
	d->distancia_ = NULL;
	d->custo_ = NULL;
	d->duracao_ = NULL;
	return d;
}

VIAGEM_1 * inicializa_viagem1() {

	VIAGEM_1 * v1;
	v1 = (VIAGEM_1 *) malloc(sizeof(VIAGEM_1));
	v1->transporte = NULL;
	v1->descricao = inicializa_descr();
	return v1;
}

VIAGEM_2 * inicializa_viagem2() {
	
	VIAGEM_2 * v2;
	v2 = (VIAGEM_2 *) malloc(sizeof(VIAGEM_2));
	v2->origem = NULL;
	v2->destino = NULL;
	v2->descricao = inicializa_descr();
	return v2;
}

TIPO_1 * inicializa_tipo1() {

	TIPO_1 * t = (TIPO_1 *) malloc(sizeof(TIPO_1));
	t->origem = NULL;
	t->destino = NULL;
	return t;

}

TIPO_2 * inicializa_tipo2() {

	TIPO_2 * t = (TIPO_2 *) malloc(sizeof(TIPO_2));
	t->transporte = NULL;
	return t;

}

/*libertar uma g2list do tipo1*/
GSList * freeGslistT1(GSList *g)
{
	if(g != NULL)
	{
		g_slist_foreach(g,(void *) freeTipo1, NULL);
		
		g_slist_free(g);
		
		g = NULL;
		
		return g;
	}
	else return NULL;
}

void freeTipo1(TIPO_1 *t)
{
	free(t->origem);
	free(t->destino);
	
	g_slist_foreach(t->viagem_1, (void *) freeViagem_1, NULL);
	
	g_slist_free(t->viagem_1);
	
	free(t);
}

void freeViagem_1(VIAGEM_1 *v)
{
	free(v->transporte);
	
	freeDescricao(v->descricao);
	
	free(v);
}

void freeDescricao(DESC *d)
{
	free(d->distancia_);
	free(d->custo_);
	free(d->duracao_);
	
	g_slist_foreach(d->horarios, (void *) free, NULL);
	
	g_slist_free(d->horarios);

	free(d);
}

/*libertar uma gslist do tipo2*/
GSList * freeGslistT2(GSList *g)
{

	if(g != NULL)
	{
		g_slist_foreach(g, (void *) freeTipo2, NULL);
		
		g_slist_free(g);
		
		g = NULL;
		
		return g;
	}
	else return NULL;
}

void freeTipo2(TIPO_2 *t)
{
	free(t->transporte);
	
	g_slist_foreach(t->viagem_2, (void *) freeViagem_2, NULL);
	
	g_slist_free(t->viagem_2);
	
	free(t);
}

void freeViagem_2(VIAGEM_2 *v)
{	
	free(v->origem);
	free(v->destino);
	
	freeDescricao(v->descricao);
	
	free(v);
}
