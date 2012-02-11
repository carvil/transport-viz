#include"graphviz.h"

/*Funções de inserção dos nodos*/

void insere_um_nodo(char * key, char * value, FILE * fp) {

	fprintf(fp, "%s [shape=circle, label=%s, color=black];\n ", value, value);

}

void insere_nodos(GHashTable * tabela, FILE *fp) {

	g_hash_table_foreach(tabela, (void *) insere_um_nodo, fp);
}

/********************************************************************************/

/*
 * Funções que concatenam os horarios numa so string
 */

char * concat(char * h, char * tmp) {
	int h_len, tmp_len;
	
	char * t_tmp;
	
	if(h != NULL && tmp != NULL)
	{
		h_len = (h == NULL)?0:strlen(h);
		
		tmp_len = (tmp == NULL)?0:strlen(tmp);
		
		/* + 3(2 para \n e 1 para \0)*/
		t_tmp = (char *) malloc( h_len + tmp_len + 3);
			
		sprintf(t_tmp,"%s%s\\n",tmp,h);
		
		//strcat(tmp, h);
		//strcat(tmp, "\\n");
		
		free(tmp);
		tmp = NULL;
		
		return t_tmp;
	}
	else 
	{
		return NULL;
	}
}

char * concatHorarios(GSList * horar) {

	int i;
	char * tmp;
	tmp = strdup("");
	i = g_slist_length(horar);
	for(i = i-2; i >= 0; i--)
	{
		tmp = concat((char *) g_slist_nth_data(horar,i), tmp);
	}
	return tmp;
}

/*
 * Função que insere uma ligação (viagem) referente a tipo 1
 */

void insere_uma_ligacao_1(TIPO_1 * t1, FILE * fp) {

	int i, v;
	char * h, *cor;
	h = NULL;
	
	VIAGEM_1 * tmp;
	i = g_slist_length(t1->viagem_1);
	
	if(t1 != NULL)
	{
		for(i = i-1; i >= 0; i--) 
		{
			tmp = (VIAGEM_1 *) g_slist_nth_data(t1->viagem_1, i);
			h = concatHorarios((tmp->descricao)->horarios);
			v = strlen(tmp->transporte);
			switch(v) {
				case 5: {
						//aviao
						cor = strdup("red");
						break;
					}
				case 7: {
						//comboio
						cor = strdup("blue");
						break;
					}
				case 9: {
						//camioneta
						cor = strdup("green");
						break;
					}
				default:{
						cor = strdup("black");
						break;
					}
			}
			fprintf(fp, "%s -> %s [label=\"Custo: %s\\nDistancia: %s\\nDuracao: %s\\n Horarios:\\n%s\", color=%s];\n ", 
					t1->origem, 
					t1->destino, 
					(tmp->descricao)->custo_,
					(tmp->descricao)->distancia_,
					(tmp->descricao)->duracao_, 
					h,
					cor);
		}
		
	}
}

/*
 * Função que insere todas as ligações referentes ao tipo 1
 */

void insere_ligacoes1(GSList * l, FILE * fp) {

	g_slist_foreach(l, (void *) insere_uma_ligacao_1, fp);
}

/*
 * Função que insere uma ligação (viagem) referente a tipo 2
 */

void insere_uma_ligacao_2(TIPO_2 * t2, FILE * fp) {

	int i, v;
	char * h, *cor;
	h = NULL;//(char *) malloc(sizeof(char));
	VIAGEM_2 * tmp;
	i = g_slist_length(t2->viagem_2);
	for(i = i-1; i >= 0; i--)
	{
		tmp = (VIAGEM_2 *) g_slist_nth_data(t2->viagem_2, i);
		h = concatHorarios((tmp->descricao)->horarios);
		v = strlen(t2->transporte);
		switch(v) {
			case 5: {
					//aviao
					cor = strdup("red");
					break;
				}
			case 7: {
					//comboio
					cor = strdup("blue");
					break;
				}
			case 9: {
					//camioneta
					cor = strdup("green");
					break;
				}
			default:{
					cor = strdup("black");
					break;
				}
		}
		fprintf(fp, "%s -> %s [label=\"Custo: %s\\nDistancia: %s\\nDuracao: %s\\n Horarios:\\n%s\", color=%s];\n ", 
				tmp->origem, 
				tmp->destino, 
				(tmp->descricao)->custo_,
				(tmp->descricao)->distancia_,
				(tmp->descricao)->duracao_, 
				h,
				cor
				);
	}
}

/*
 * Função que insere todas as ligações referentes ao tipo 1
 */

void insere_ligacoes2(GSList * l, FILE * fp) {

	g_slist_foreach(l, (void *) insere_uma_ligacao_2, fp);	
}

void insere_legenda(FILE * fp) {

	fprintf(fp, "legenda [shape=box,label=\"Legenda:\\nAviao - Vermelho\\nComboio - Azul\\nCamioneta - Verde\", color=black];\n ");
}


/********************************************************************************/

void gera_ficheiro(GHashTable * tabela, GSList * lista1, GSList * lista2, FILE * fp) {

	fprintf(fp,"digraph mapa {\n ");
	insere_legenda(fp);
	insere_nodos(tabela, fp);
	if(lista1 != NULL) {
	
		insere_ligacoes1(lista1, fp);
	}
	if(lista2 != NULL) {
		insere_ligacoes2(lista2, fp);
	}
	fprintf(fp, "}\n");
}
