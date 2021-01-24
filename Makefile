main: 0.c
	cc -g $? -o $@

.PHONY: clean
clean:
	rm ./main
