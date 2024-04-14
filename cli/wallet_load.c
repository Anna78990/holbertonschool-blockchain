#include "cli.h"

/**
 * cmd_wallet_load - loads wallet from file
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int cmd_wallet_load(info_t *info)
{
	EC_KEY *key;

	if (info->argc != 2)
		return (printf("wallet_save <path>\n"), 0);
	key = ec_load(info->argv[1]);
	if (!key)
		return (printf("Wallet failed to load.\n"), 0);
	EC_KEY_free(info->blockchain_data->key);
	info->blockchain_data->key = key;
	printf("Wallet loaded successfully.\n");
	return (0);
}
