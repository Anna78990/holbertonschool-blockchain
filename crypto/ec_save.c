#include "hblk_crypto.h"

/**
 * ec_save - Save an EC key pair on the disk
 * @key: Pointer to the EC key pair to be saved
 * @folder: Path to the folder in which to save the keys
 *
 * Return: 1 on success, 0 on failure
 */
int ec_save(EC_KEY *key, char const *folder)
{
{
	FILE *fp;
	char path[256];
	EVP_PKEY *pkey = EVP_PKEY_new();

	if (mkdir(folder, 0700) != 0 && errno != EEXIST)
		return (0);

	if (!EVP_PKEY_set1_EC_KEY(pkey, key))
		return (0);

	snprintf(path, sizeof(path), "%s/key.pem", folder);
	fp = fopen(path, "w");
	if (!fp)
		return (0);
	if (!PEM_write_PrivateKey(fp, pkey, NULL, NULL, 0, NULL, NULL))
	{
		fclose(fp);
		return (0);
	}
	fclose(fp);

	snprintf(path, sizeof(path), "%s/key_pub.pem", folder);
	fp = fopen(path, "w");
	if (!fp)
		return (0);
	if (!PEM_write_EC_PUBKEY(fp, key))
	{
		fclose(fp);
		return (0);
	}
	fclose(fp);

	EVP_PKEY_free(pkey);

	return (1);

}
