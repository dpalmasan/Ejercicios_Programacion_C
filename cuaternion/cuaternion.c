#include "cuaternion.h"
#include <stdio.h>
#include <math.h>

/*
 * Imprime un cuaternion.
*/
void imprime(cuaternion q) {
	printf("(%.5f, %.5f, %.5f, %.5f)", q.alfa, q.beta, q.gamma, q.delta);
}

/*
 * Compara dos cuaterniones. Retorna 1 si los cuaterniones son iguales
 * y 0 en caso contrario.
*/
int compara(cuaternion a, cuaternion b) {
	if (a.alfa == b.alfa && a.beta == b.beta && a.gamma == b.gamma &&
		a.delta == b.delta)
		return 1;
	return 0;
}

/*
 * Retorna el cuaternion resultante entre la suma de dos cuaterniones
*/
cuaternion suma(cuaternion a, cuaternion b) {
	cuaternion c;

	c.alfa = a.alfa + b.alfa;
	c.beta = a.beta + b.beta;
	c.gamma = a.gamma + b.gamma;
	c.delta = a.delta + b.delta;

	return c;
}

/*
 * Retorna el cuaternion resultante entre la resta de dos cuaterniones
*/
cuaternion resta(cuaternion a, cuaternion b) {
	cuaternion c;

	c.alfa = a.alfa - b.alfa;
	c.beta = a.beta - b.beta;
	c.gamma = a.gamma - b.gamma;
	c.delta = a.delta - b.delta;

	return c;
}

/*
 * Retorna el cuaternion resultante entre el producto de dos cuaterniones
*/
cuaternion producto(cuaternion a, cuaternion b) {
	cuaternion c;

	c.alfa = a.alfa*b.alfa - a.beta*b.beta - a.gamma*b.gamma - a.delta*b.delta;
	c.beta = a.alfa*b.beta + a.beta*b.alfa + a.gamma*b.delta - a.delta*b.gamma;
	c.gamma = a.alfa*b.gamma - a.beta*b.delta + a.gamma*b.alfa + a.delta*b.beta;
	c.delta = a.alfa*b.delta + a.beta*b.gamma - a.gamma*b.beta + a.delta*b.alfa;

	return c;
}

/*
 * Retorna el conjugado del cuaternion de entrada.
*/
cuaternion conjugado(cuaternion q) {
	cuaternion q_star;
	q_star.alfa = q.alfa;
	q_star.beta = -q.beta;
	q_star.gamma = -q.gamma;
	q_star.delta = -q.delta;

	return q_star;
}

/*
 * Retorna la norma de un cuaternion.
*/
double norma(cuaternion q) {
	return sqrt(q.alfa*q.alfa + q.beta*q.beta + q.gamma*q.gamma + q.delta*q.delta);
}

/*
 * Retorna el cuaternion a la inversa.
*/
cuaternion inversa(cuaternion q) {
	double inner = q.alfa*q.alfa + q.beta*q.beta + q.gamma*q.gamma + q.delta*q.delta;
	
	cuaternion inv_q = conjugado(q);
	inv_q.alfa = inv_q.alfa/inner; inv_q.beta = inv_q.beta/inner;
	inv_q.gamma = inv_q.gamma/inner; inv_q.delta = inv_q.delta/inner;
	
	return inv_q;
}

/*
 * Retorna el cuaternion resultante entre la division de dos cuaterniones.
*/
cuaternion division(cuaternion a, cuaternion b) {
	return producto(a, inversa(b));
}

