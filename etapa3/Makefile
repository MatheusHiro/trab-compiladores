etapa3: main.o lex.yy.o y.tab.o hash.o ast.o veclist.o
	gcc main.o lex.yy.o y.tab.o hash.o ast.o veclist.o -o etapa3

main.o: main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

ast.o: ast.c
	gcc -c ast.c

veclist.o: veclist.c 
	gcc -c veclist.c 

y.tab.o: y.tab.c
	gcc -c y.tab.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

y.tab.c: parser.y
	yacc -d parser.y 

lex.yy.c: scanner.l
	lex scanner.l

clean: 
	rm lex.yy.c y.tab.c *.o etapa3