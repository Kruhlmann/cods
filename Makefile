CC = gcc
RM = rm -rf

CFLAGS = -Wall -Wextra -Wno-unknown-pragmas -pedantic -O2 -g3 -ggdb -I inc/ -I tst/

SRC = $(shell find src/ -type f -name '*.c')
SRC_OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
TST = $(shell find tst/ -type f -name '*.c')
TST_OBJ = $(patsubst tst/%.c, tst/%.o, $(TST))
PROGRAM = test

all: $(PROGRAM)

obj/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $<

tst/%.o: tst/%.c $(OBJ)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $< $(SRC_OBJ)

$(PROGRAM): $(SRC_OBJ) $(TST_OBJ) Makefile
	@$(CC) $(XFLAGS) -o $@ $(TST_OBJ) $(SRC_OBJ)

compile_commands.json: Makefile
	@make clean
	@bear make

clean:
	@$(RM) $(SRC_OBJ) $(TST_OBJ) $(PROGRAM)

.PHONY: clean
