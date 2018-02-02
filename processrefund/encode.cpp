#include "encode.h"


int encode(BYTE *in, BYTE *out, int length)
{
	BYTE last;
	int i;
	for (i = 0; i < length; i++)
	{
		if (i == 0)
		{
			last = in[i];
		}
		else
		{
			last = last ^ in[i];
		}
		out[i] = last;
	}
	return i+1;
}