#ifndef PRODUCTS_H
#define PRODUCTS_H


// Constants

#define NAMESIZE 50
#define PRODUCTSFILE "products.txt"
#define MAXPRODUCTS 50

// Structures

typedef struct  {
	int id;
	char name[NAMESIZE];
	int price;
} Product;


// Methods

int loadProducts(Product ** products);
int saveProduct(Product * product);
#endif