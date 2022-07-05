dev: bin
	gcc -Wall -Wextra -o bin/gut.dev.exe src/gut.c

prod: bin
	gcc -Wall -Wextra -O3 -o bin/gut.exe src/gut.c

bin:
	mkdir bin
