main: 0.c
	gcc -g $? -o $@

.PHONY: clean
clean:
	rm ./main
