#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "../../crypto/hblk_crypto.h"
#include <llist.h>

/**
 * struct blockchain_s - Blockchain structure
 *
 * @chain: Linked list of pointers to block_t
 */
typedef struct blockchain_s
{
    llist_t     *chain;
} blockchain_t;


#define BLOCKCHAIN_DATA_MAX 1024

/**
 * struct block_data_s - Block data
 *
 * @buffer: Data buffer
 * @len:    Data size (in bytes)
 */
typedef struct block_data_s
{
    /*
     * @buffer must stay first, so we can directly use the structure as
     * an array of char
     */
    int8_t      buffer[BLOCKCHAIN_DATA_MAX];
    uint32_t    len;
} block_data_t;

/**
 * struct block_s - Block structure
 *
 * @info: Block info
 * @data: Block data
 * @hash: 256-bit digest of the Block, to ensure authenticity
 */
typedef struct block_s
{
    block_info_t    info; /* This must stay first */
    block_data_t    data; /* This must stay second */
    uint8_t     hash[SHA256_DIGEST_LENGTH];
} block_t;

blockchain_t *blockchain_create(void);
block_t *block_create(block_t const *prev, int8_t const *data,
		uint32_t data_len);
 void block_destroy(block_t *block);

#endif
