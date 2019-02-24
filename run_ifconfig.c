#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	if (execlp("/sbin/ifconfig", "ifconfig", NULL) != 0)
		if (execlp("ipconfig", "ipconfig", NULL) != 0) {
			fprintf(stderr, "Cannot run ipconfig: %s", strerror(execlp("ipconfig", "ipconfig", NULL)));
			return 1;	
		}
	return 0;
}