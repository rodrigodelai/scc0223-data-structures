UTIL=Util/FileManager.c Util/StopWatch.c
MAIN=Inverter.c
BINARY=maior

all:
	gcc -Wall $(MAIN) $(UTIL) -o $(BINARY) -I Util/

debug:
	gcc -DDEBUG -Wall $(MAIN) $(UTIL) -o $(BINARY) -I Util/

run:
	./$(BINARY)

plot:
	gnuplot "plotdata" -p

clean:
	@rm *.o
