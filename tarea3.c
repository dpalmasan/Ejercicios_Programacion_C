#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/*
 * This struct represents a point in a 3D space.
*/
typedef struct {
	double x;
	double y;
	double z;
} coord3D;

/*
 * Node is used for implementing a queue using linked lists.
*/
typedef struct Node {
	int ID;
	double mass;
	coord3D pos;
	coord3D vel;
	struct Node* next;
} Node;

/*
 * Struct for representing a queue.
*/
typedef struct {
	int size;		// Size of the queue
	int lastID;		// ID of the last element inserted.
	Node* first;	// beginning of queue
	Node* last;		// end of queue
} LinkedQueue;

// Initializes the queue
void Init(LinkedQueue* queue) {
	queue->size = 0;
	queue->lastID = 1;
	queue->first = NULL;
	queue->last = NULL;
}

// Is the queue empty?
bool isEmpty(LinkedQueue *queue) { return queue->first == NULL; }

// The size of the queue (element's quantity)
int size(LinkedQueue *queue) { return queue->size; }

// Adds a new element to the queue, in this case, the DB.
bool enqueue(LinkedQueue *queue, double mass, coord3D pos, coord3D vel) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) return false;

	node->ID = queue->lastID++;
	node->mass = mass;
	node->pos = pos;
	node->vel = vel;
	node->next = NULL;

	if(isEmpty(queue)) {
		queue->first = node;
		queue->last = node;
	} else {
		queue->last->next = node;
		queue->last = node;
	}
	queue->size++;
	return true;
}

// Prints the entire DB.
void printQueue(LinkedQueue queue) {
	if (isEmpty(&queue)) return;

	Node *aux = queue.first;

	printf(" ID   m   posicion          velocidad\n");
	printf("------------------------------------------------\n");
	while(aux != NULL) {
		printf("%4d %4.2f (%4.2f, %4.2f, %4.2f) (%4.2f, %4.2f, %4.2f)\n", aux->ID,
			aux->mass, aux->pos.x, aux->pos.y, aux->pos.z, aux->vel.x, aux->vel.y, aux->vel.z);
		aux = aux->next;
	}
}

// Frees memory from DB.
void freeQueue(LinkedQueue *queue) {
	Node* aux = queue->first;
	while (aux != NULL) {
		Node* tmp = aux;
		aux = aux->next;
		free(tmp);
	}
	Init(queue);
}

// Moves an object to the first position in the queue, by ID
void moveObject(LinkedQueue* queue, int ID) {
    if (isEmpty(queue)) return;

	// Checks whether we are trying to move the first element.
	if (queue->first->ID == ID) return;

	Node* aux = queue->first;

	while(aux->next) {
		if (aux->next->ID == ID) {
			Node* tmp = aux->next;
			aux->next = aux->next->next;
			tmp->next = queue->first;
			queue->first = tmp;
			break;
		}
		aux = aux->next;
	}
}

// Deletes an object from the queue, by ID. Returns true if successful, false otherwise.
bool deleteObject(LinkedQueue* queue, int ID) {
    if (isEmpty(queue)) return false;
	Node* aux = queue->first;
	if (queue->first->ID == ID) {
		queue->first = aux->next;
		free(aux);
		queue->size--;
		return true;
	}

	while(aux->next) {
		if (aux->next->ID == ID) {
			Node* tmp = aux->next;
			aux->next = aux->next->next;
			free(tmp);
			queue->size--;
			return true;
		}
		aux = aux->next;
	}
	return false;
}

int main(void) {
	// Variables that will be used.
	int i;
	double mass;
	LinkedQueue q;
	coord3D pos;
	coord3D vel;

	// Seed for RNG.
	srand((unsigned)time(NULL));

	// Initialize DB.
	Init(&q);

	printf("==============================================\n");
	printf("\tPrograma de testeo Base de Datos\n");
	printf("==============================================\n\n");

	printf("Cantidad de datos en la BD %d, comportamiento de deleteObject:\n", size(&q));
	    if (!deleteObject(&q, 0)) {
            printf("Fallo la funcion borrar!\n\n");
    }

	for (i = 0; i < 10; i++) {
		pos.x = ((double)rand()/(double)RAND_MAX);
		pos.y = ((double)rand()/(double)RAND_MAX);
		pos.z = ((double)rand()/(double)RAND_MAX);
		vel.x = ((double)rand()/(double)RAND_MAX);
		vel.y = ((double)rand()/(double)RAND_MAX);
		vel.z = ((double)rand()/(double)RAND_MAX);
		mass = ((double)rand()/(double)RAND_MAX);

		// Did enqueue succeed?
		if(!enqueue(&q, mass, pos, vel)) {
			printf("No hay memoria disponible... Liberando memoria y terminar.\n");
			freeQueue(&q);
			return -1;
		}
	}
	printf("La base de datos tiene %d objetos\n", size(&q));
	printQueue(q);
	printf("\nTesteando la funcion moveObject, moviendo el objeto de ID = 9\n\n");
	moveObject(&q, 9);
	printQueue(q);
	printf("\nTesteando la funcion deleteObject, borrando el objeto de ID = 6\n\n");
	deleteObject(&q, 6);
	printQueue(q);
	printf("La base de datos ahora tiene %d objetos\n", size(&q));
	enqueue(&q, 1, pos, vel);
	printQueue(q);

	// Freeing allocated memory.
	freeQueue(&q);
	return 0;
}
