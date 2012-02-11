%{
#include"y.tab.h"
#include<stdlib.h>

int yycolno = 1, tamanho = 0, flag = 1;


%}

distancia	[0-9]+k
horas		[0-2]?[0-9]h[0-5][0-9]
custo		[0-9]+e
aviao		[aA][vV][iI][aA][oO]
camioneta	[cC][aA][mM][iI][oO][nN][eE][tT][aA]
comboio		[cC][oO][mM][bB][oO][iI][oO]
cidade		[A-Z][aA-zZ]*
tab_ou_esp	[\t ]
enter		\n
virg		\,


%%

{horas}		{
			tamanho = yyleng;
			yycolno = yycolno + yyleng;
			yylval.str = strdup(yytext);
			return horas;
		}
{custo}		{
			yycolno = yycolno + yyleng;
			tamanho = yyleng;
			yylval.str = strdup(yytext);
			return custo;
		}
{distancia}	{
			tamanho = yyleng;
			yycolno = yycolno + yyleng;
			yylval.str = strdup(yytext);
			return distancia;
		}
{aviao}		{
			tamanho = yyleng;
			yycolno = yycolno + yyleng;
			yylval.str = strdup(yytext);
			return aviao;
		}
{camioneta}	{
			tamanho = yyleng;
			yycolno = yycolno + yyleng;
			yylval.str = strdup(yytext);
			return camioneta;
		}
{comboio}	{
			tamanho = yyleng;
			yycolno = yycolno + yyleng;
			yylval.str = strdup(yytext);
			return comboio;
		}
{cidade}	{
			tamanho = yyleng;
			yycolno = yycolno + yyleng;
			yylval.str = strdup(yytext);
			return cidade;
		}
{virg}		{
			tamanho = yyleng;
			yycolno = 1;
			return virg;
		}
{enter}		{
			tamanho = yyleng;
			if(flag == 1)
				yylineno++;
			yycolno = 1;
		}
{tab_ou_esp}	{
			tamanho = yyleng;
			yycolno = yycolno + yyleng;
		}
.		{
			return 0;
		}

%%

int yyerror(char *str) {
	
	char *temp = strdup("Erro de sintaxe na linha ");
	char *temp2 = strdup(" a partir da coluna ");

	char * msm = (char *) malloc(strlen(temp) + strlen(temp2) + 15);
	sprintf(msm, "%s%d%s%d!", temp,yylineno,temp2, yycolno-tamanho);
	yylval.erro = msm;

	free(temp);
	free(temp2);
	return 1;
}


int yywrap() {

	return 1;
}
