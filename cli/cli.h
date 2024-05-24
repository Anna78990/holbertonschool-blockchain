#ifndef CLI_H
#define CLI_H

#include <stddef.h>
#include <stdlib.h>
#include "../crypto/hblk_crypto.h"

#include "blockchain.h"
#include <transaction.h>
#include <llist.h>
#include "provided.h"


typedef struct blockchain_data
{
	EC_KEY *key;
	blockchain_t *blockchain;
	llist_t *tx_pool;
} blockchain_data_t;

/**
 *struct Info - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@status: the return status of the last exec'd command
 *@readfd: the fd from which to read line input
 *@blockchain_data: stored data about current blockchain
 */
typedef struct Info
{
	char *arg;
	char **argv;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;

	int status;
	int readfd;

	blockchain_data_t *blockchain_data;
} info_t;

ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
char **strtow(char *str, char *d);
int wallet_save(info_t *info);
int cmd_wallet_load(info_t *info);
int cmd_info(info_t *info);
int cmd_send(info_t *info);

#endif
