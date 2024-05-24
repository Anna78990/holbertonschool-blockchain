#include "cli.h"


/**
 * _print_unspent - Print an unspent transaction output
 *
 * @unspent: Pointer to the unspent transaction output to print
 * @idx:	 Unused
 * @indent:  Indentation
 *
 * Return: 0
 */
int print_unspent(unspent_tx_out_t const *unspent, unsigned int idx,
	char const *indent)
{
	printf("%s{\n", indent);

	printf("%s\tblock_hash: ", indent);
	_print_hex_buffer(unspent->block_hash, SHA256_DIGEST_LENGTH);
	printf("\n");

	printf("%s\ttx_id: ", indent);
	_print_hex_buffer(unspent->tx_id, SHA256_DIGEST_LENGTH);
	printf("\n");

	printf("%s}\n", indent);
	_tx_out_print(&unspent->out, 0, indent);

	(void)idx;
	return (0);
}

/**
 * print_all_unspent - Print a list of unspent transaction outputs
 *
 * @unspent: List of unspent transaction outputs to print
 */
void print_all_unspent(llist_t *unspent)
{
	printf("Unspent transaction outputs [%u]: [\n", llist_size(unspent));

	llist_for_each(unspent, (node_func_t)print_unspent, "\t");

	printf("]\n");
}

/**
 * isarg - checks if arg is part of input line argv
 * @info: line input info struct
 * @arg: the argument to find
 * Return: 1 if true else 0
 */
int isarg(info_t *info, char *arg)
{
	int i = 0;

	for (i = 0; i < info->argc; i++)
		if (!strcmp(info->argv[i], arg))
			return (1);
	return (0);
}

/**
 * cmd_info - displays info about blockchain
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: always 0
 */
int cmd_info(info_t *info)
{
	if (isarg(info, "-u"))
	{
		print_all_unspent(info->blockchain_data->blockchain->unspent);
		return (0);
	}
	if (isarg(info, "-p"))
	{
		printf("----------- TX Pool:\n");
		llist_for_each(info->blockchain_data->tx_pool,
		(node_func_t)_transaction_print_loop, "\t\t");
		printf("----------- END TX Pool:\n");
		return (0);
	}
	if (isarg(info, "-b"))
		_blockchain_print_brief(info->blockchain_data->blockchain);
	else
		_blockchain_print(info->blockchain_data->blockchain);
	printf("%s\n", "------------------------------------------------------");
	printf("Blocks: %d\tUTXOs: %d\tTX Pool: %d\n",
		llist_size(info->blockchain_data->blockchain->chain),
		llist_size(info->blockchain_data->blockchain->unspent),
		llist_size(info->blockchain_data->tx_pool));
	return (0);
}

