#include "transaction.h"
#include "../provided/provided.h"


/**
 * find_unspent - finds unspent matching txo
 * @node: current node, unspent_txo_t
 * @arg: txo id
 * Return: 0 if continue else 1
 */
int find_unspent(llist_node_t node, void *arg)
{
	unspent_tx_out_t *utxo = node;

	if (!memcmp(arg, utxo->out.hash, SHA256_DIGEST_LENGTH))
		return (1);
	return (0);
}

/**
 * map_input - maps output to input transactions
 * @node: current node, txi
 * @idx: index of node
 * @_args: arguments
 * Return: 0 if continue else 1
 */
int map_input(llist_node_t node, unsigned int idx, void *_args)
{
	void **args = _args;
	tx_in_t *txi = node;

	llist_remove_node(args[0], find_unspent, txi->tx_out_hash, 1, free);
	return (0);
	(void)idx;
	(void)txi;
	(void)args;
}

/**
 * map_output - maps output to input transactions
 * @node: current node, txo
 * @idx: index of node
 * @_args: arguments
 * Return: 0 if continue else 1
 */
int map_output(llist_node_t node, unsigned int idx, void *_args)
{
	void **args = _args;
	tx_out_t *txo = node;
	unspent_tx_out_t *utxo;

	utxo = unspent_tx_out_create(args[1], args[2], txo);
	if (!utxo)
		exit(1);

	if (llist_add_node(args[0], utxo, ADD_NODE_REAR))
		exit(1);
	return (0);
	(void)idx;
}

/**
 * foreach_transaction - maps output to input transactions
 * @node: current node, tx
 * @idx: index of node
 * @__args: arguments
 * Return: 0 if continue else 1
 */
int foreach_transaction(llist_node_t node, unsigned int idx, void *__args)
{
	transaction_t *transaction = node;
	void *args[3] = {0}, **_args = __args;

	args[0] = _args[0], args[1] = _args[1], args[2] = transaction->id;
	llist_for_each(transaction->inputs, map_input, args);
	llist_for_each(transaction->outputs, map_output, args);
	return (0);
	(void)idx;
}
/**
 * update_unspent - updates list of UTXOs
 * @transactions: list of validate transactions
 * @block_hash: hash of block containing transactions
 * @all_unspent: list of all UTXOs
 * Return: new UTXO list
 */
llist_t *update_unspent(llist_t *transactions,
	uint8_t block_hash[SHA256_DIGEST_LENGTH], llist_t *all_unspent)
{
	void *args[2] = {0};

	args[0] = all_unspent, args[1] = block_hash;
	llist_for_each(transactions, foreach_transaction, args);
	(void)block_hash;
	(void)transactions;
	(void)all_unspent;
	return (all_unspent);
}
