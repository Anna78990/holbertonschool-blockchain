#include "hblk_crypto.h"

uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	const EC_GROUP *group;
	const EC_POINT *point;
	BIGNUM *x, *y;
	uint8_t *buf;
	size_t len;

	if (!key || !pub)
		return (NULL);

	group = EC_KEY_get0_group(key);
	point = EC_KEY_get0_public_key(key);

	x = BN_new();
	y = BN_new();
	if (!group || !point || !x || !y)
	{
		BN_free(x);
		BN_free(y);
		return (NULL);
	}

	if (!EC_POINT_get_affine_coordinates_GFp(group, point, x, y, NULL))
	{
		BN_free(x);
		BN_free(y);
		return (NULL);
	}

	len = EC_POINT_point2oct(group, point, POINT_CONVERSION_UNCOMPRESSED, NULL, 0, NULL);
	if (len != EC_PUB_LEN)
	{
		BN_free(x);
		BN_free(y);
		return (NULL);
	}

	buf = pub;
	memset(buf, 0, EC_PUB_LEN);
	BN_bn2bin(x, buf + 1);
	BN_bn2bin(y, buf + EC_PUB_LEN / 2 + 1);

	BN_free(x);
	BN_free(y);

	return (pub);
}
