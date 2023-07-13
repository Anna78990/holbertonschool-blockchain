#include "hblk_crypto.h"

/**
 * ec_load - Load an EC key pair from disk
 *
 * @folder: Path to the folder from which to load the keys
 *
 * Return: Pointer to the EC key pair upon success, or NULL upon failure
 */
EC_KEY *ec_load(char const *folder)
{
	FILE *fp;
	char key_path[BUFSIZ] = {0};
	char pub_key_path[BUFSIZ] = {0};
	EC_KEY *key = NULL;

	if (!folder)
		return (NULL);

	snprintf(key_path, BUFSIZ, "%s/%s", folder, PRI_FILENAME);
	snprintf(pub_key_path, BUFSIZ, "%s/%s", folder, PUB_FILENAME);

	fp = fopen(pub_key_path, "r");
	if (!fp)
		return (NULL);

	key = PEM_read_EC_PUBKEY(fp, &key, NULL, NULL);
	if (!key)
		return (NULL);
	fclose(fp);
	fp = fopen(pub_key_path, "r");
	if (!fp)
		return (NULL);
	key = PEM_read_ECPrivateKey(fp, &key, NULL, NULL);
	if (!key)
		return (NULL);

	fclose(fp);

	return (key);
}
