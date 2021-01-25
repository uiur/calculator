main: main.c parse.o tokenize.o
	cc -g $^ -o $@

parse.o: parse.c
	cc -c $? -o $@

tokenize.o: tokenize.c
	cc -c $? -o $@

.PHONY: clean
clean:
	rm -rf *.o ./main
