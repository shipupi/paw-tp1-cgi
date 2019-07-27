#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define PRODUCTSFILE "products.txt"
#define NAMESIZE 50
#define MAXPRODUCTS 50

typedef struct  {
	int id;
	char name[NAMESIZE];
	int price;
} Product;

void headers() {
	printf("Content-type: text/html\n\n");
}

void upperBody() {
	printf("\
		<html>\
			<head>\
				<title>\
					Titulo!!\
				</title>\
				<h4>Cabeza</h4>\
			</head>\
			<body>"
	);
}
void lowerBody() {
	printf("\
			</body>\
		</html>"
	);
}

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
	return i;
}


void listProducts() {
	Product *products[MAXPRODUCTS];
	int size = loadProducts(products);
	printf("<ul>");
	for (int i = 0; i < size; ++i)
	{
		printf("<li>%d - %s - %d</li>", products[i]->id, products[i]->name, products[i]->price);
	}
	printf("</ul>");
}

void html() {
	upperBody();

	listProducts();

	lowerBody();
}

int main()
{
	headers();
	html();

	return 0;
}

