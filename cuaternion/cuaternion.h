#ifndef _CUATERNION_H_
#define _CUATERNION_H_

/* Definir estructura del cuaternion */
typedef struct {
	double alfa;
	double beta;
	double gamma;
	double delta;
} cuaternion;

int compara(cuaternion a, cuaternion b);
cuaternion suma(cuaternion a, cuaternion b);
cuaternion resta(cuaternion a, cuaternion b);
cuaternion producto(cuaternion a, cuaternion b);
cuaternion conjugado(cuaternion q);
double norma(cuaternion q);
cuaternion inversa(cuaternion q);
cuaternion division(cuaternion a, cuaternion b);
void imprime(cuaternion q);

#endif
