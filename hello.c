#include <stdio.h>

int main()
{
	printf("Content-type: text/html\n\n");
	printf(
		"\
		<html>\
			<head>\
				<title>\
					Titulo!!\
				</title>\
				<h4>Cabeza</h4>\
			</head>\
			<body>\
				<h1>\
					Cuerpo\
				</h1>\
			</body>\
		</html>");
	return 0;
}