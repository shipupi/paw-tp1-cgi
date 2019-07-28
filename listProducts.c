#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "product.h"
#include "headers.h"


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

	if (from != -1) {
		printf("<div>From: %d</div>", from);
	}
	if (to != -1) {
		printf("<div>To: %d</div>", to);
	}

	printf("<table>");
	printf("<thead>");
	printf("<tr><td>ID</td><td>Name</td><td>Price</td></tr>");
	printf("</thead>");
	printf("<tbody>");
	for (int i = 0; i < size; ++i)
	{
		if (((from == -1) || (products[i]->price > from)) && ((to == -1) || (products[i]->price < to))) {
			printf("<tr><td>%d</td><td>%s</td><td>%d</td></tr>", products[i]->id, products[i]->name, products[i]->price);
		}
	}
	printf("</tbody>");
	printf("</table>");
	printf("<div>");
	printf("<a href=\"/\"><button type=\"button\">HOME</button></a>");
	printf("<a href=\"/addProduct.html\"><button type=\"button\">ADD</button></a>");
	printf("</div>");

	

}

void html() {
	upperBody();

	listProducts();

	lowerBody();
}

int main()
{
	basicHeader();
	html();

	return 0;
}

