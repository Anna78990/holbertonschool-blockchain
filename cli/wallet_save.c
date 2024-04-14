#include "cli.h"

/**
 * cmd_wallet_save - saves wallet to file
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int wallet_save(info_t *info)
{
	if (info->argc != 2)
		return (printf("wallet_save <path>\n"), 0);
	if (ec_save(info->blockchain_data->key, info->argv[1]))
		printf("Wallet saved successfully.\n");
	else
		printf("Wallet failed to save.\n");
	return (0);
}
