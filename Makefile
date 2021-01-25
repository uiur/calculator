objects = main.c parse.o tokenize.o
main: $(objects)
parse.o: parse.c
tokenize.o: tokenize.c

.PHONY: clean
clean:
	rm -rf *.o ./main
