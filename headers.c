
#include <stdio.h>

void redirectHeader(char * url) {
	printf("Location: %s\n\n", url);
}

void basicHeader() {
	printf("Content-type: text/html\n\n");
}