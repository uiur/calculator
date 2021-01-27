objects =  parse.o tokenize.o
main: main.c $(objects)
test: test.c $(objects)
parse.o: parse.c
tokenize.o: tokenize.c

.PHONY: clean
clean:
	rm -rf *.o ./main
