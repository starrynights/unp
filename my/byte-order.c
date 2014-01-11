#include <stdio.h>

int main(int argc, char **argv)
{
	union 
	{
		short n;
		char c[sizeof(short)];
	} un;

	un.n = 0x0102;

	if (sizeof(short) == 2)
	{
		if (un.c[0] == 1 && un.c[1] == 2)
		{
			printf("big ending\n");
		}
		else if (un.c[0] == 2 && un.c[1] == 1)
		{
			printf("little ending\n");
		}
		else
		{
			printf("other\n");
		}
	}
	return 0;
}
