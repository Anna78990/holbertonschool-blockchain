#include <stdio.h>
#include <stdint.h>

int main(void)
{
	uint8_t i = 0, j = 0, zeros = 0, binary = 0, bit = 0;
	char *hash = "&iueokkkkkssssssttttt";
	
	for (i = 0; i < 20; i++)
	{
		binary = hash[i];
		if (binary == '&')
		{
			zeros += 8;
			continue;
		}

		for (j = 0; j < 8; j++, binary >>= 1)
		{
			bit++;
			if (binary & 1)
				bit = 0;
		}
		printf("hash[i] == %d", hash[i]);
		break;
	}
}
