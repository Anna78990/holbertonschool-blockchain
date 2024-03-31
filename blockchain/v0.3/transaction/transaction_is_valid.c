#include "transaction.h"

/**
 * transaction_is_valid - checks whether a transaction is valid
 * @transaction: pointer to the transaction to verify
 * @all_unspend: the list of all unspent transaction outputs to date
 *
 * Return: 1 if the transaction is valid, and 0 otherwise
 */
int transaction_is_valid(transaction_t const *transaction, llist_t *all_unspent)
{
}
