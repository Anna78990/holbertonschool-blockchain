CC = gcc
CFLAGS = gcc *.c -L../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread -g transaction/*.c

SRC0 = $(wildcard *.c)
OBJ0 = $(SRC0:.c=.o)
NAME0 = cli

.PHONY: clean oclean flcean cli

clean:
	$(RM) *~ $(NAME0)

oclean:
	$(RM) $(OBJ0)

fclean: clean oclean

cli: cli.h $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0) $(LIBS)
