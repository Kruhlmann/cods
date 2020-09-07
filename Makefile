CC = gcc
RM = rm -rf

GCCFLAGS = -Wall -Wextra

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
PROGRAM = ttt

obj/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CPPFLAGS) -c -o $@ $<

$(PROGRAM): $(OBJ)
	@$(CC) $(CPPFLAGS) -o $@ $(OBJ)

clean:
	@$(RM) $(OBJ) $(PROGRAM)

.PHONY: clean
