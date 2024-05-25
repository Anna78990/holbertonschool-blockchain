CC = gcc

CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu90 -ggdb3 -g -I. -I../blockchain/v0.3/ -I../blockchain/v0.3/transaction/ -I../blockchain/v0.3/provided/ -I../crypto

LDFLAGS = -L../blockchain/v0.3 -lhblk_blockchain -L../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

PROVIDED_SRC = $(wildcard ../blockchain/v0.3/provided/*.c)
CLI_SRC = $(wildcard *.c)
TRANSACTION_SRC = $(wildcard ../blockchain/v0.3/transaction/*.c)

PROVIDED_OBJ = $(PROVIDED_SRC:.c=.o)
CLI_OBJ = $(CLI_SRC:.c=.o)
TRANSACTION_OBJ = $(TRANSACTION_SRC:.c=.o)

TARGET = cli

all: $(TARGET)

$(TARGET): $(PROVIDED_OBJ) $(CLI_OBJ) $(TRANSACTION_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROVIDED_OBJ) $(CLI_OBJ) $(TRANSACTION_OBJ) $(TARGET)

.PHONY: all clean

