gcc: bin
	gcc -Wall -Wextra -o bin/gut.exe src/gut.c

tcc: bin
	tcc -Wall -Wextra -o bin/gut.exe src/gut.c

bin:
	mkdir bin
