#include "cli.h"

/**
 * cmd_send - sends coins from one wallet to another
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: always 0
 */
int cmd_send(info_t *info)
{
	EC_KEY *receiver;
	transaction_t *tx = NULL;
	uint8_t pub[EC_PUB_LEN] = {0};
	uint32_t amount, i;

	if (info->argc != 3)
		return (printf("send <amount> <address>\n"), 0);
	amount = atoi(info->argv[1]);
	for (i = 0; i < EC_PUB_LEN; i++)
		if (sscanf(&info->argv[2][i * 2], "%2x", (unsigned int *)&pub[i]) < 1)
			break;
	receiver = ec_from_pub(pub);
	if (!receiver)
		return (printf("Invalid receiver public key.\n"), 0);
	tx = transaction_create(info->blockchain_data->key, receiver, amount,
		info->blockchain_data->blockchain->unspent);
	if (!tx)
		printf("Failed to create transaction.\n");
	else
	{
		if (transaction_is_valid(tx,
			info->blockchain_data->blockchain->unspent))
		{
			if (llist_add_node(info->blockchain_data->tx_pool, tx,
				ADD_NODE_REAR) != -1)
				printf("Transaction successfully added to local pool.\n");
			else
			{
				printf("Error adding transaction to local pool.\n");
				transaction_destroy(tx);
			}
		}
		else
		{
			printf("Transaction not validated.\n");
			transaction_destroy(tx);
		}
	}
	EC_KEY_free(receiver);
	return (0);
}

