#include "blockchain.h"


/**
 * block_hash - computes the hash of a Block
 * @block: pointer to the Block to be hashed
 * @hash_buf: The resulting hash must be stored
 * Return: pointer to hash_buf on success, otherwise NULL
 */
uint8_t *block_hash(block_t const *block,
		uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t length = (sizeof(block->info) + block->data.len);
	uint8_t *temp_buf = NULL;

	if (!block || !hash_buf)
		return (NULL);
	if (length > SHA256_DIGEST_LENGTH)
	{
		temp_buf = (uint8_t *)malloc(length);
		if (temp_buf == NULL)
			return (NULL);
		memcpy(temp_buf, (uint8_t *)&block->info, sizeof(block->info));
		memcpy(temp_buf + sizeof(block->info), block->data.buffer, block->data.len);
		SHA256(temp_buf, length, hash_buf);
		free(temp_buf);
	}
	else
	{
		length = SHA256_DIGEST_LENGTH;
		temp_buf = (uint8_t *)alloca(length);
		if (temp_buf == NULL)
			return (NULL);
		memcpy(hash_buf, (uint8_t *)&block->info, sizeof(block->info));
		memcpy(hash_buf + sizeof(block->info), block->data.buffer, block->data.len);
		SHA256(temp_buf, length, hash_buf);
		free(temp_buf);
	}
	return (hash_buf);
}
