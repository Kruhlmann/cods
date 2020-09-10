CC = gcc
RM = rm -rf

CXXFLAGS = -Wall -Wextra -Werror -O2 -g -ggdb -lrt -lm -Iinc/
CXX_TEST_FLAGS =

SRC = $(wildcard src/*.c)
SRC_OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
TST = $(wildcard tst/*.c)
TST_OBJ = $(patsubst tst/%.c, tst/%.o, $(TST))
PROGRAM = test

all: $(PROGRAM)

obj/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CXXFLAGS) -c -o $@ $<

tst/%.o: tst/%.c $(OBJ)
	@mkdir -p $(@D)
	@$(CC) $(CXXFLAGS) -c -o $@ $< $(SRC_OBJ)

$(PROGRAM): $(SRC_OBJ) $(TST_OBJ) Makefile
	@$(CC) $(CXXFLAGS) -o $@ $(TST_OBJ) $(SRC_OBJ)

compile_commands.json: Makefile
	@make clean
	@bear make

clean:
	@$(RM) $(SRC_OBJ) $(TST_OBJ) $(PROGRAM)

.PHONY: clean
