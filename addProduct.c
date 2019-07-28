#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "product.h"
#include "headers.h"
#include <ctype.h>


int isNumber (char * str) {
	int len = strlen(str);
	int i;
	for (i=0;i<len; i++) {
	    if (!isdigit(str[i]))
	    {
	        return 0;
	    }
	}
	return 1;
}

void loadParams(char * params, int size) {
	for (int i = 0; i < size; ++i) {
		params[i] = getchar();
	}
	params[size] = '\0';
}

int createProduct(Product * p, char * params) {
	char *saveptr;
	char * t1 = strtok_r(params,"&",&saveptr);
	int errors = 0;
	while(t1 != NULL) {
		char* saveptr2;
		char* t2 = strtok_r(t1,"=", &saveptr2);
		if (t2 != NULL) {
			if (strcmp("id", t2) == 0) {
				t2 = strtok_r(NULL, "=", &saveptr2);
				if(t2 != NULL) {
					if (isNumber(t2) != 0) {
						p->id = atoi(t2);
					} else {
						printf("<div>Invalid ID: %s</div>\n", t2);
						errors++;
					}
				}
			}
			if (strcmp("price", t2) == 0) {
				t2 = strtok_r(NULL, "=", &saveptr2);
				if(t2 != NULL) {
					if (isNumber(t2)) {
						p->price = atoi(t2);
					} else {
						printf("<div>Invalid Price</div>\n");
						errors++;
					}
				}
			}
			if (strcmp("name", t2) == 0) {
				t2 = strtok_r(NULL, "=", &saveptr2);
				if(t2 != NULL) {
					strcpy(p->name,t2);
				}
			}
		}
		t1 = strtok_r(NULL,"&",&saveptr);
	}
	return errors;
}

int main()
{
	int n;
	if (getenv("CONTENT_LENGTH") != NULL) {
		sscanf(getenv("CONTENT_LENGTH"), "%d", &n);
		char params[n+1];
		loadParams(params, n);
		Product * p = malloc(sizeof(Product));
		int errors = createProduct(p, params);
		if (!errors) {
			saveProduct(p);
			redirectHeader("/cgi-bin/listProducts");
		} else {
			basicHeader();
		}
	} else {
		printf("ERROR. Post is null\n");
	}
	return 0;
}