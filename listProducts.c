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

void loadParameters(int* from, int* to) {
		char qs[200];
		char *saveptr;
		strcpy(qs,getenv("QUERY_STRING"));
		char * t1 = strtok_r(qs,"&",&saveptr);
		while(t1 != NULL) {
			char* saveptr2;
			char* t2 = strtok_r(t1,"=", &saveptr2);
			if (t2 != NULL) {
				if (strcmp("from", t2) == 0) {
					t2 = strtok_r(NULL, "=", &saveptr2);
					if(t2 != NULL) {
						*(from) = atoi(t2);
					}
				}
				if (strcmp("to", t2) == 0) {
					t2 = strtok_r(NULL, "=", &saveptr2);
					if(t2 != NULL) {
						*(to) = atoi(t2);
					}
				}
			}
			t1 = strtok_r(NULL,"&",&saveptr);
		}
}

void listProducts() {
	Product *products[MAXPRODUCTS];
	int size = loadProducts(products);
	int from = -1;
	int to = -1;
	loadParameters(&from, &to);

	printf("From: %d - To: %d\n", from,to);
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

