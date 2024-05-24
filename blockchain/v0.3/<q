#include "blockchain.h"

/**
 * hash_tx_ids - hash outputs
 * @node: struct transaction_t
 * @idx: index of node
 * @arg: pointer to address to write to
 * Return: 0 if success, otherwise 1
 */
int hash_tx_ids(llist_node_t node, unsigned int idx, void *arg)
{
	memcpy(*(uint8_t **)arg, ((transaction_t *)node)->id, SHA256_DIGEST_LENGTH);
	*(uint8_t **)arg += SHA256_DIGEST_LENGTH;
	return (0);
	(void)idx;
}

/**
 * block_hash - computes the hash of a Block
 * @block: pointer to the Block to be hashed
 * @hash_buf: The resulting hash must be stored
 * Return: pointer to hash_buf on success, otherwise NULL
 */
uint8_t *block_hash(block_t const *block,
		uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t length = (sizeof(block->info) + block->data.len), _length;
	uint8_t *temp_buf = NULL, *buf;

	_length = length;
	if (llist_size(block->transactions) > 0)
		_length += llist_size(block->transactions) * SHA256_DIGEST_LENGTH;

	temp_buf = buf = calloc(1, _length);
	if (buf == NULL)
		return (NULL);
	memcpy(buf, (uint8_t *)&block->info, length);
	buf += length;
	llist_for_each(block->transactions, hash_tx_ids, &buf);
	SHA256(temp_buf, _length, hash_buf);
	free(temp_buf);
	return (hash_buf);
}
