#include "netpbm.h"

int main(void)
{
	if (netpbm_terminal() != NO_ERROR)
		exit(EXIT_FAILURE);
	return 0;
}
