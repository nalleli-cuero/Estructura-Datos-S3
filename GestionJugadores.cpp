#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para un jugador
typedef struct Jugador {
    int id;
    char nombre[30];
    int edad;
    char genero;
    char deporte[50];
} Jugador;

// Nodo para la cola y pila
typedef struct Nodo {
    Jugador jugador;
    struct Nodo* siguiente;
} Nodo;

// Estructura para la cola
typedef struct Cola {
    Nodo* frente;
    Nodo* final;
    int contador;
} Cola;

// Estructura para la pila
typedef struct Pila {
    Nodo* tope;
    int contador;
} Pila;

// Funciones para la cola
void inicializarCola(Cola* cola) {
    cola->frente = NULL;
    cola->final = NULL;
    cola->contador = 0;
}

int contarGenero(Cola* cola, char genero) {
    Nodo* actual = cola->frente;
    int contador = 0;
    while (actual != NULL) {
        if (actual->jugador.genero == genero) {
            contador++;
        }
        actual = actual->siguiente;
    }
    return contador;
}

int validarIngreso(Cola* cola, Jugador jugador) {
    // Validar edad
    if (jugador.edad < 15) {
        printf("Error: El jugador debe tener al menos 15 años.\n");
        return 0;
    }
    
    // Validar balance de género
    int hombres = contarGenero(cola, 'M');
    int mujeres = contarGenero(cola, 'F');
    
    if (jugador.genero == 'M' && hombres - mujeres >= 4) {
        printf("Error: Demasiados hombres en la cola. Espere a que se equilibre.\n");
        return 0;
    }
    if (jugador.genero == 'F' && mujeres - hombres >= 4) {
        printf("Error: Demasiadas mujeres en la cola. Espere a que se equilibre.\n");
        return 0;
    }
    
    return 1;
}

void encolar(Cola* cola, Jugador jugador) {
    if (!validarIngreso(cola, jugador)) {
        return;
    }
    
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->jugador = jugador;
    nuevo->siguiente = NULL;
    
    if (cola->final == NULL) {
        cola->frente = nuevo;
        cola->final = nuevo;
    } else {
        cola->final->siguiente = nuevo;
        cola->final = nuevo;
    }
    cola->contador++;
    printf("Jugador agregado a la cola.\n");
}

Jugador desencolar(Cola* cola) {
    if (cola->frente == NULL) {
        Jugador vacio = {0, "", 0, ' ', ""};
        return vacio;
    }
    
    Nodo* temp = cola->frente;
    Jugador jugador = temp->jugador;
    cola->frente = cola->frente->siguiente;
    
    if (cola->frente == NULL) {
        cola->final = NULL;
    }
    
    free(temp);
    cola->contador--;
    return jugador;
}

void mostrarCola(Cola* cola) {
    if (cola->frente == NULL) {
        printf("La cola está vacía.\n");
        return;
    }
    
    Nodo* actual = cola->frente;
    printf("\nJugadores en espera:\n");
    while (actual != NULL) {
        printf("ID: %d, Nombre: %s, Edad: %d, Género: %c, Deporte: %s\n",
               actual->jugador.id, actual->jugador.nombre, actual->jugador.edad,
               actual->jugador.genero, actual->jugador.deporte);
        actual = actual->siguiente;
    }
}

// Funciones para la pila
void inicializarPila(Pila* pila) {
    pila->tope = NULL;
    pila->contador = 0;
}

void apilar(Pila* pila, Jugador jugador) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->jugador = jugador;
    nuevo->siguiente = pila->tope;
    pila->tope = nuevo;
    pila->contador++;
}

Jugador desapilar(Pila* pila) {
    if (pila->tope == NULL) {
        Jugador vacio = {0, "", 0, ' ', ""};
        return vacio;
    }
    
    Nodo* temp = pila->tope;
    Jugador jugador = temp->jugador;
    pila->tope = pila->tope->siguiente;
    free(temp);
    pila->contador--;
    return jugador;
}

void mostrarPila(Pila* pila) {
    if (pila->tope == NULL) {
        printf("El historial está vacío.\n");
        return;
    }
    
    Nodo* actual = pila->tope;
    printf("\nHistorial de participación:\n");
    while (actual != NULL) {
        printf("ID: %d, Nombre: %s, Edad: %d, Género: %c, Deporte: %s\n",
               actual->jugador.id, actual->jugador.nombre, actual->jugador.edad,
               actual->jugador.genero, actual->jugador.deporte);
        actual = actual->siguiente;
    }
}

// Función principal
int main() {
    Cola cola;
    Pila pila;
    inicializarCola(&cola);
    inicializarPila(&pila);
    int opcion, id = 1;
    
    do {
        printf("\n=== Menú de Gestión de Torneo ===\n");
        printf("1. Agregar jugador a la cola\n");
        printf("2. Mostrar jugadores en espera\n");
        printf("3. Contar jugadores en espera\n");
        printf("4. Permitir participación del siguiente jugador\n");
        printf("5. Mostrar historial de participación\n");
        printf("6. Deshacer última participación\n");
        printf("7. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1: {
                Jugador nuevo;
                nuevo.id = id++;
                printf("Nombre: ");
                scanf(" %[^\n]", nuevo.nombre);
                printf("Edad: ");
                scanf("%d", &nuevo.edad);
                printf("Género (M/F): ");
                scanf(" %c", &nuevo.genero);
                printf("Deporte: ");
                scanf(" %[^\n]", nuevo.deporte);
                encolar(&cola, nuevo);
                break;
            }
            case 2:
                mostrarCola(&cola);
                break;
            case 3:
                printf("Jugadores en espera: %d\n", cola.contador);
                break;
            case 4: {
                Jugador participante = desencolar(&cola);
                if (participante.id != 0) {
                    printf("Participante: %s\n", participante.nombre);
                    apilar(&pila, participante);
                } else {
                    printf("No hay jugadores en la cola.\n");
                }
                break;
            }
            case 5:
                mostrarPila(&pila);
                break;
            case 6: {
                Jugador ultimo = desapilar(&pila);
                if (ultimo.id != 0) {
                    printf("Se deshizo la participación de: %s\n", ultimo.nombre);
                    encolar(&cola, ultimo);
                } else {
                    printf("No hay participaciones para deshacer.\n");
                }
                break;
            }
            case 7:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while (opcion != 7);
    
    // Liberar memoria
    while (cola.frente != NULL) {
        desencolar(&cola);
    }
    while (pila.tope != NULL) {
        desapilar(&pila);
    }
    
    return 0;
}