#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	char key_path[BUFSIZ], pub_key_path[BUFSIZ];
	EC_KEY *key = NULL;

	if (!folder)
		return (NULL);

	snprintf(key_path, BUFSIZ, "%s/%s", folder, "key.pem");
	snprintf(pub_key_path, BUFSIZ, "%s/%s", folder, "key_pub.pem");

	fp = fopen(key_path, "r");
	if (!fp)
		return (NULL);

	key = PEM_read_ECPrivateKey(fp, NULL, NULL, NULL);
	fclose(fp);
	if (!key)
		return (NULL);
	fp = fopen(pub_key_path, "r");
	if (!fp)
	{
		EC_KEY_free(key);
		return (NULL);
	}

	if (!PEM_read_EC_PUBKEY(fp, &key, NULL, NULL))
	{
		fclose(fp);
		EC_KEY_free(key);
		return (NULL);
	}

	fclose(fp);

	return (key);
}
