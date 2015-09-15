#include "cuaternion.h"
#include <stdio.h>

int main(void) {
	cuaternion x = {0.3, 43.5, -2.21, -0.04};
	cuaternion y = {1.8, -11.90, 3.231, 4.56};

	printf("Los cuaterniones "); imprime(x); printf(" y "); imprime(y);
	if (compara(x, y) == 0) printf(" no"); printf(" son iguales\n");
	printf("La suma de x e y es "); imprime(suma(x, y)); printf("\n");
	printf("La resta de x e y es"); imprime(resta(x, y)); printf("\n");
	printf("El producto de x e y es"); imprime(producto(x, y));
	printf("\n");
	printf("La division x/y es"); imprime(division(x, y)); printf("\n");
	printf("La division y/x es"); imprime(division(y, x)); printf("\n");
	
	return 0;
}
