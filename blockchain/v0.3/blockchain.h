#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "../../crypto/hblk_crypto.h"
#include "provided/endianness.h"
#include "transaction/transaction.h"
#include <llist.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#define CHECK_ENDIAN(x) (endian ? SWAPENDIAN(x) : (void)0)


#define BLOCKCHAIN_DATA_MAX 1024


/**
 * enum _LLIST - All the different functions errors
 *
 * @LLIST_SUCCESS:           Success
 * @LLIST_NODE_NOT_FOUND:     No matching node found
 * @LLIST_NULL_ARGUMENT:      NULL argument
 * @LLIST_OUT_OF_RANGE:       Index out of range
 * @LLIST_MALLOC_ERROR:       Memory allocation error
 * @LLIST_MULTITHREAD_ISSUE:  Multithreading error
 */

/**
 * typedef enum _LLIST
 * {
 *	LLIST_SUCCESS = 0,
 *	LLIST_NODE_NOT_FOUND,
 *	LLIST_NULL_ARGUMENT,
 *	LLIST_OUT_OF_RANGE,
 *	LLIST_MALLOC_ERROR,
 *	LLIST_MULTITHREAD_ISSUE
 *} E_LLIST;
 */

/* Opaque linked list structure */
/* typedef struct __list llist_t; */

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
 * struct block_info_s - Block info structure
 *
 * @index:      Index of the Block in the Blockchain
 * @difficulty: Difficulty of proof of work (hash leading zero bits)
 * @timestamp:  Time the Block was created at (UNIX timestamp)
 * @nonce:      Salt value used to alter the Block hash
 * @prev_hash:  Hash of the previous Block in the Blockchain
 */
typedef struct block_info_s
{
    /*
     * The order of the elements in this structure should remain the same.
     * It was designed so every element of this structure is aligned and
     * doesn't require padding from the compiler.
     * Therefore, it is possible to use the structure as an array of char,
     * on any architecture.
     */
    uint32_t    index;
    uint32_t    difficulty;
    uint64_t    timestamp;
    uint64_t    nonce;
    uint8_t     prev_hash[SHA256_DIGEST_LENGTH];
} block_info_t;

/**
 * struct block_s - Block structure
 *
 * @info:         Block info
 * @data:         Block data
 * @transactions: List of transactions
 * @hash:         256-bit digest of the Block, to ensure authenticity
 */
typedef struct block_s
{
    block_info_t    info; /* This must stay first */
    block_data_t    data; /* This must stay second */
    llist_t     *transactions;
    uint8_t     hash[SHA256_DIGEST_LENGTH];
} block_t;

/**
 * struct blockchain_s - Blockchain structure
 *
 * @chain:   Linked list of Blocks
 * @unspent: Linked list of unspent transaction outputs
 */
typedef struct blockchain_s
{
    llist_t     *chain;
    llist_t     *unspent;
} blockchain_t;

# define BLOCK_GENERATION_INTERVAL 1
# define DIFFICULTY_ADJUSTMENT_INTERVAL 5

blockchain_t *blockchain_create(void);
block_t *block_create(block_t const *prev, int8_t const *data,
		uint32_t data_len);
void block_destroy(block_t *block);
void blockchain_destroy(blockchain_t *blockchain);
uint8_t *block_hash(block_t const *block, uint8_t hash_buf[SHA256_DIGEST_LENGTH]);
int blockchain_serialize(blockchain_t const *blockchain, char const *path);
blockchain_t *blockchain_deserialize(char const *path);
int block_is_valid(block_t const *block, block_t const *prev_block, llist_t *all_unspent);
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH], uint32_t difficulty);
void block_mine(block_t *block);
uint32_t blockchain_difficulty(blockchain_t const *blockchain);
llist_t *update_unspent(llist_t *transactions, uint8_t block_hash[SHA256_DIGEST_LENGTH],
		llist_t *all_unspent);

#endif
