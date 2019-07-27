all: hello listProducts

hello: hello.c
	gcc -o hello hello.c -I.

listProducts: listProducts.c
	gcc -o listProducts listProducts.c -I.