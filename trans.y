%{
#include"graphviz.h"
#include <string.h>

TIPO_1 * t1;
TIPO_2 * t2;

GHashTable * tabela;
GSList * lista1 = NULL;
GSList * lista2 = NULL;
GSList * horarios_ = NULL;

GSList * v1;
GSList * temp;
GSList * v2;

VIAGEM_1 * viagem_1;
VIAGEM_2 * viagem_2;

DESC * descr;

char * trans;


%}


%union {
		char *str;
		char *erro;
       }

%token <str> distancia horas custo cidade aviao comboio camioneta inicio fim virg 


%start ROOT

%%

ROOT			: TIPO
			| ROOT virg TIPO
			;
TIPO			: TIPO1					
                        | TIPO2
			;
TIPO1			: cidade cidade LstViagens		{
									/*Inserir as cidades na Hash Table*/
									
									g_hash_table_insert(tabela, $1, $1);
									g_hash_table_insert(tabela, $2, $2);

									t1 = inicializa_tipo1();
									t1->origem = strdup($1);
									t1->destino = strdup($2);
									//temp = g_slist_alloc();
									temp = v1;
									t1->viagem_1 = temp;
									v1 = NULL;
									
									lista1 = g_slist_prepend(lista1, t1);

								}
			;
TIPO2			: Transporte LstT			{
									t2 = inicializa_tipo2();
									t2->transporte = strdup(trans);
									trans[0] = '\0';

									//temp = g_slist_alloc();
									temp = v2;
									t2->viagem_2 = temp;
									v2 = NULL;

									lista2 = g_slist_prepend(lista2, t2);
								}
			;
LstT			: LstT Elem				{
									v2 = g_slist_prepend(v2, viagem_2);
									
								}
			|
			;
Elem			: cidade cidade Info			{
									/*Inserir as cidades na Hash Table*/
									
									g_hash_table_insert(tabela, $1, $1);
									g_hash_table_insert(tabela, $2, $2);

									viagem_2 = inicializa_viagem2();
									viagem_2->origem = strdup($1);
									viagem_2->destino = strdup($2);
									viagem_2->descricao = descr;
									descr = inicializa_descr();
								}
			;
Info			: distancia horas custo HORARIOS	{
									descr = inicializa_descr();

									descr->distancia_ = strdup($1);
									descr->custo_ = strdup($3);
									descr->duracao_ = strdup($2);
									temp = horarios_;
									descr->horarios = horarios_;
									horarios_ = g_slist_alloc();
								}
			;
LstViagens		: LstViagens Viagem			{
									v1 = g_slist_prepend(v1, viagem_1);
									
								}
			|
			;
Transporte		: aviao					{
									trans = strdup($1);
								}
                        | comboio				{
									trans = strdup($1);
								}
                        | camioneta				{
									trans = strdup($1);
								}
			;
Viagem			: Transporte Info			{
									viagem_1 = inicializa_viagem1();
									viagem_1->transporte = strdup(trans);
									trans[0] = '\0';
									viagem_1->descricao = descr;
									descr = inicializa_descr();
									
								}
			;
HORARIOS                : horas					{
									horarios_ = g_slist_prepend(horarios_, $1);
								}
			| HORARIOS horas			{
									horarios_ = g_slist_prepend(horarios_, $2);
								}
			;

%%

void ajuda()
{
	printf("\n\tTrabalho de PL\n\t  2005-2006\n\n");
	printf("\tRealizado por:\n");
	printf("\tAdriana ... ...\n");
	printf("\tCarlos Vilhena ...\n");
	printf("\tSérgio Novo º35860\n\n");
	printf("\tSintaxe de execução:\n\n");
	printf("\tModo Gráfico:\n");
	printf("\t ./plgui................................Abertura em modo gráfico\n");
	
	printf("\n\tModo Texto:\n");
	printf("\t ./plgui -o output.gif..................Leitura do stdin e resultado de execução escrito em output.gif\n");
	printf("\t ./plgui -o output.gif -i input.txt.....Leitura de input.txt e resultado em output.gif\n\n");

}


char * funcao(int argc, char **argv) {
	
	/*Variáveis*/
	FILE * fp;
	char * fich_in, *fich_out, *comando_aux = NULL, *comando = NULL;
	pid_t pid;
	fich_in = NULL; //(char *) malloc(sizeof(char));
	FILE *yin;
	
	char *erro = (char *) malloc(100);
	char *erro_aux = strdup("Foi impossivel abrir o ficheiro:\n");
	
	/*ignorando nome do executavel*/
	char * exec = argv[0];
	
	argc--;
	argv++;
	
	if(argc == 1 && (strcmp(argv[0],"-h") == 0 || strcmp(argv[0],"--help") == 0))
	{
			ajuda();
			return NULL;
	}else if(argc == 2)
	{
		if( strcmp(argv[0],"-o") == 0 || strcmp(argv[0],"-O") == 0 )
		{
			fich_out = strdup(argv[1]);
			if(fich_out == NULL)
			{
				if(strlen(argv[1])+strlen(erro_aux)+3 > 100)
					erro = (char *)realloc(erro,strlen(argv[1])+strlen(erro_aux)+3);
				sprintf(erro,"%s[%s]",erro_aux,argv[1]);
				
				return erro;
			}
		}
		else
		{
			sprintf(erro,"Parâmetro [%s] inválido\nExecute %s --help",argv[0],exec);
			return erro;
		}
	}
	else if(argc == 4)
	{
		if( strcmp(argv[0],"-o") == 0 || strcmp(argv[0],"-O") == 0 )
		{
		
			fich_out = strdup(argv[1]);
		
			
			
			if( strcmp(argv[2],"-i") == 0 || strcmp(argv[2],"-I") == 0 )
			{
				yin = fopen(argv[3],"r");
				if(yin == NULL)
				{
					if(strlen(argv[3])+strlen(erro_aux)+3 > 100)
						erro = (char *)realloc(erro,strlen(argv[3])+strlen(erro_aux)+3);
					sprintf(erro,"%s[%s]",erro_aux,argv[3]);
					
					return erro;
				}
				yyrestart(yin);
			}
			else
			{
				sprintf(erro,"Parâmetro [%s] inválido\nExecute %s --help",argv[2],exec);
				return erro;
			}
		}
		else if( strcmp(argv[0],"-i") == 0 || strcmp(argv[0],"-I") == 0 )
		{
			yin = fopen(argv[1],"r");
			if(yin == NULL)
			{
				if(strlen(argv[1])+strlen(erro_aux)+3 > 100)
					erro = (char *)realloc(erro,strlen(argv[1])+strlen(erro_aux)+3);
				sprintf(erro,"%s[%s]",erro_aux,argv[1]);
				
				return erro;
			}
			yyrestart(yin);
			
			if( strcmp(argv[2],"-o") == 0 || strcmp(argv[2],"-O") == 0 )
			{	
				fich_out = strdup(argv[3]);
			
			}
			else
			{
				sprintf(erro,"Parâmetro [%s] inválido\nExecute %s --help",argv[2],exec);
				return erro;
			}
		}
		else 
		{
			sprintf(erro,"Parâmetros [%s][%s] inválidos\nExecute %s --help",argv[0],argv[2],exec);
			return erro;
		}
	}
	else 
	{
		sprintf(erro,"Sintaxe de excucao incompleta\nExecute %s --help",exec);
		return erro;
	}



	comando_aux = strdup("dot -Tgif /tmp/mapa.dot -o ");

	comando = (char *) malloc(strlen(fich_out) + strlen(comando_aux) + 1);

	sprintf(comando,"%s%s",comando_aux,fich_out);
	
	//inicialização da tabela de Hash
	tabela = g_hash_table_new(g_str_hash, g_str_equal);

	//abertura dos ficheiros
	fich_in = strdup("/tmp/mapa.dot");
	
	yylval.erro = NULL;

	lista1 = freeGslistT1(lista1);
	lista2 = freeGslistT2(lista2);
	horarios_ = NULL;

	yyparse();

	//tratamento da estrutura
	if((lista1 == NULL) && (lista2 == NULL))
	{
		return strdup(yylval.erro);
	}
	else {
		fp = fopen(fich_in, "w");
		
		gera_ficheiro(tabela, lista1, lista2, fp);
		fclose(fp);
		
		
		system(comando);


		if(comando_aux != NULL)
			free(comando_aux);
		if(comando != NULL)
			free(comando);
		
	}

	return NULL;
}

