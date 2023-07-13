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
	char key_path[256] = {0};
	char pub_key_path[256] = {0};
	EC_KEY *key = NULL;

	if (!folder)
		return (NULL);

	sprintf(key_path, "%s/%s", folder, PRI_FILENAME);
	sprintf(pub_key_path, "%s/%s", folder, PUB_FILENAME);

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
