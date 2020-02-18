SRC=$(wildcard *.c)

all: $(patsubst %.c, %, $(wildcard *.c))

%: %.c
	- mkdir -p out
	- gcc $< -o out/$@ -pthread -lncurses -lrt