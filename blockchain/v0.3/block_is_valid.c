#include "blockchain.h"


/**
* validate_transactions - Check if all transactions are valid
* @block: Pointer to the Block to check
* @unspent: List of unspent transactions
* Return: 0 if all transactions are valid, otherwise -1
*/
int validate_transactions(block_t const *block, llist_t *unspent)
{
	int i;
	transaction_t *node;

	for (i = 0; i < llist_size(block->transactions); i++)
	{
		node = llist_get_node_at(block->transactions, i);
		if (i == 0 && !coinbase_is_valid(node, block->info.index))
			return (-1);
		if (i > 0 && !transaction_is_valid(node, unspent))
			return (-1);
	}
	if (i == 0)
		return (-1);
	return (0);
}


/**
 * block_is_valid - verifies that a Block is valid
 * @block: pointer to the Block to check
 * @prev_block: pointer to the previous Block in the Blockchain
 * Return: 0 if valid, otherwise 1
 */
int block_is_valid(block_t const *block, block_t const *prev_block, llist_t *all_unspent)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH] = {0};
	block_t genesis = {
		{
			0,	    /* index */
			0,	    /* difficulty */
			1537578000, /* timestamp */
			0,	    /* nonce */
			{0}	    /* prev_hash[SHA256_DIGEST_LENGTH] */
		},
		{
			"Holberton School",	/* buffer */
			16			/* len */
		},
		NULL,
		"\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97"
		"\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f"
		"\x04\x51\x58\x03"
	};

	if (!block || (!prev_block && block->info.index != 0))
		return (1);
	if (block->info.index == 0)
		return (memcmp(block, &genesis, sizeof(genesis)));
	if (block->info.index != prev_block->info.index + 1)
		return (1);
	if (!block_hash(prev_block, hash_buf) ||
		memcmp(hash_buf, prev_block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (memcmp(prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH))
		return (1);
	memset(hash_buf, 0, SHA256_DIGEST_LENGTH);
	if (!block_hash(block, hash_buf) ||
		memcmp(hash_buf, block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);
	if (!hash_matches_difficulty(block->hash, block->info.difficulty))
		return (1);
	if (validate_transactions(block, all_unspent) == -1)
		return (1);
	return (0);
}
