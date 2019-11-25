all:
	flex -o lexer.c lexer.l
	gcc -o compiler lexer.c 

fibo:
	./compiler < ./test/fibo.c

copy:
	./compiler < ./test/copy.c

cmt:
	./compiler < ./test/comment.c

clean:
	rm lexer.c compiler 