test:
	gcc code.h
	bison -d bison.y
	flex flex.l
	gcc bison.tab.c lex.yy.c -o processor_simulator -lpthread
