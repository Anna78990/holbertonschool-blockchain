#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include "../../../crypto/hblk_crypto.h"
#include "../blockchain.h"
#include <llist.h>

# define COINBASE_AMOUNT 50

typedef struct tx_out_s tx_out_t;
typedef struct unspent_tx_out_s unspent_tx_out_t;
typedef struct tx_in_s tx_in_t;
typedef struct transaction_s transaction_t;

tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN]);
unspent_tx_out_t *unspent_tx_out_create(uint8_t block_hash[SHA256_DIGEST_LENGTH], uint8_t tx_id[SHA256_DIGEST_LENGTH], tx_out_t const *out);
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent);
uint8_t *transaction_hash(transaction_t const *transaction, uint8_t hash_buf[SHA256_DIGEST_LENGTH]);
sig_t *tx_in_sign(tx_in_t *in, uint8_t const tx_id[SHA256_DIGEST_LENGTH], EC_KEY const *sender, llist_t *all_unspent);
transaction_t *transaction_create(EC_KEY const *sender, EC_KEY const *receiver, uint32_t amount, llist_t *all_unspent);
int transaction_is_valid(transaction_t const *transaction, llist_t *all_unspent);
transaction_t *coinbase_create(EC_KEY const *receiver, uint32_t block_index);
int coinbase_is_valid(transaction_t const *coinbase, uint32_t block_index);
void transaction_destroy(transaction_t *transaction);

#endif
