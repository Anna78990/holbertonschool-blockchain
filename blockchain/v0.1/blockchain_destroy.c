#include "blockchain.h"

/**
 * blockchain_destroy - destroy blockchain
 * @blockchain: pointer to the Blockchain structure to delete
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	if (blockchain)
	{
		llist_destroy(blockchain->chain, 1, (node_dtor_t)block_destroy);
		free(blockchain);
	}
}
