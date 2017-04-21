test:
	gcc code.h
	bison -d bison.y
	flex flex.l
	gcc bison.tab.c lex.yy.c -o processor_simulator -lpthread
clean:
	rm bison.tab.c bison.tab.h code.h.gch lex.yy.c processor_simulator.exe *.svg