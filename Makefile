CC = gcc
RM = rm -rf

CXXFLAGS = -Wall -Wextra -O2 -g -ggdb

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
PROGRAM = ttt

obj/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CXXFLAGS) -c -o $@ $<

$(PROGRAM): $(OBJ) Makefile
	@$(CC) $(CXXFLAGS) -o $@ $(OBJ)

clean:
	@$(RM) $(OBJ) $(PROGRAM)

.PHONY: clean
