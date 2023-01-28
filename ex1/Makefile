MAIN = main.c
UTIL = ponto.c caminho.c util.c
BINARY = programa

all:
	gcc -Wall -g ${MAIN} ${UTIL} -o ${BINARY} -lm

run:
	./${BINARY}

go: all run

debug:
	gcc -DDEBUG -Wall ${MAIN} ${UTIL} -o ${BINARY}

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./${BINARY}

clean:
	@rm *.o
