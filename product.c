#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "product.h"


int loadProducts(Product ** products) {
	FILE *prods;
	int r;
	size_t len;
	char * productStr;
	prods = fopen(PRODUCTSFILE, "r");
	if (prods == NULL) {
		fprintf(stderr, "Unable to load products");
		return 0;
	}
	int i = 0;
	while((r = getline(&productStr,&len,prods)) != -1) {
		if(i == MAXPRODUCTS) {
			fprintf(stderr, "Max product number reached, truncating...");
			return i;
		}
		char * tok = strtok(productStr,",");
		Product *p = (Product*) malloc(sizeof(Product));
		p->id = atoi(tok);
		tok = strtok (NULL, ",");
		strcpy(p->name,tok);
		tok = strtok (NULL, ",");
		p->price = atoi(tok);
		products[i] = p;
		i++;
	}
	fclose(prods);
	return i;
}

int saveProduct(Product * product) {
	FILE *prods;
	prods = fopen(PRODUCTSFILE, "a");
	fprintf(prods, "%d,%s,%d\n", product->id, product->name, product->price);
	fclose(prods);
	return 1;
}