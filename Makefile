build/cli: src/main.c build/lex.yy.c build/cli.tab.c src/commands/commands.c
	gcc -I build -I src -Wall -g src/main.c build/lex.yy.c build/cli.tab.c src/commands/commands.c -o build/cli -lfl

build/lex.yy.c: src/cli.l build/cli.tab.h
	flex -o build/lex.yy.c src/cli.l

build/cli.tab.c build/cli.tab.h: src/cli.y
	bison -d -o build/cli.tab.c src/cli.y

.PHONY: run clean

run: build/cli
	./build/cli

clean:
	rm -rf build/*