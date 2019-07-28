all: hello listProducts addProduct

hello: hello.c
	gcc -o hello hello.c -I.

listProducts: listProducts.c
	gcc -o listProducts product.c headers.c listProducts.c -I.

addProduct: addProduct.c
	gcc -o addProduct product.c headers.c addProduct.c -I.