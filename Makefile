gui:	callbacks.c interface.c support.c main.c callbacks.h interface.h support.h _lex _yacc
	gcc -g `pkg-config --cflags --libs gtk+-2.0` callbacks.c interface.c support.c main.c lex.yy.c y.tab.c data.c graphviz.c  -o plgui

_lex: trans.l
	lex trans.l
	
_yacc: trans.y
	yacc -d -v trans.y

clean:
	rm lex.yy.c y.tab.* plgui y.output

clear: clean
	rm *.gif *.*~ *.bak *.o
