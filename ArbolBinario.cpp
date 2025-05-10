#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_GENRE 50

// Estructura para un nodo del árbol
typedef struct Node {
    char nombre[MAX_NAME];
    int año;
    char genero[MAX_GENRE];
    float revenue;
    struct Node *left;
    struct Node *right;
} Node;

// Prototipos de funciones
Node* crearNode(char *nombre, int año, char *genre, float revenue);
Node* insertNode(Node *root, char *nombre, int año, char *genero, float revenue);
void inOrder(Node *root);
void preOrder(Node *root);
void postOrder(Node *root);
Node* buscarPelicula(Node *root, char *nombre);
void MostrarPorGenero(Node *root, char *genero);
void findFlops(Node *root, Node **flops, int *count);

// Función para crear un nuevo nodo

Node* crearNode(char *nombre, int año, char *genero, float revenue) {
    Node nuevoNode = (Node)malloc(sizeof(Node));
    if (nuevoNode == NULL) {
        printf("Error de memoria\n");
        exit(1);
    }
    strncpy(nuevoNode->nombre, nombre, MAX_NAME-1);
    nuevoNode->nombre[MAX_NAME-1] = '\0';
    nuevoNode->año = año;
    strncpy(nuevoNode->genero, genero, MAX_GENRE-1);
    nuevoNode->genero [MAX_GENRE-1] = '\0';
    nuevoNode->revenue = revenue;
    nuevoNode->left = nuevoNode->right = NULL;
    return nuevoNode;
}
// Función para insertar un nodo
Node* insertNode(Node *root, char *name, int year, char *genre, float revenue) {
    if (root == NULL) {
        return createNode(name, year, genre, revenue);
    }
    
    if (year < root->year || (year == root->year)) {
        root->left = insertNode(root->left, name, year, genre, revenue);
    } else {
        root->right = insertNode(root->right, name, year, genre, revenue);
    }
    return root;
}

// Recorridos del árbol
void inOrder(Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("Película: %s, Año: %d, Género: %s, Recaudación: %.2fM\n", 
               root->name, root->year, root->genre, root->revenue);
        inOrder(root->right);
    }
}

void preOrder(Node *root) {
    if (root != NULL) {
        printf("Película: %s, Año: %d, Género: %s, Recaudación: %.2fM\n", 
               root->name, root->year, root->genre, root->revenue);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(Node *root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("Película: %s, Año: %d, Género: %s, Recaudación: %.2fM\n", 
               root->name, root->year, root->genre, root->revenue);
    }
}

// Buscar película por nombre
Node* searchMovie(Node *root, char *name) {
    if (root == NULL || strcmp(root->name, name) == 0) {
        return root;
    }
    
    Node *left = searchMovie(root->left, name);
    if (left != NULL) return left;
    
    return searchMovie(root->right, name);
}

// Mostrar películas por género
void showByGenre(Node *root, char *genre) {
    if (root != NULL) {
        showByGenre(root->left, genre);
        if (strcmp(root->genre, genre) == 0) {
            printf("Película: %s, Año: %d, Recaudación: %.2fM\n", 
                   root->name, root->year, root->revenue);
        }
        showByGenre(root->right, genre);
    }
}

// Función auxiliar para encontrar los 3 fracasos taquilleros
void findFlops(Node *root, Node **flops, int *count) {
    if (root == NULL) return;
    
    findFlops(root->left, flops, count);
    
    // Insertar en el arreglo ordenado por recaudación
    if (*count < 3) {
        flops[*count] = root;
        (*count)++;
        // Ordenar
        for (int i = *count - 1; i > 0 && flops[i]->revenue < flops[i-1]->revenue; i--) {
            Node *temp = flops[i];
            flops[i] = flops[i-1];
            flops[i-1] = temp;
        }
    } else if (root->revenue < flops[2]->revenue) {
        flops[2] = root;
        // Ordenar últimos dos elementos
        if (flops[2]->revenue < flops[1]->revenue) {
            Node *temp = flops[2];
            flops[2] = flops[1];
            flops[1] = temp;
            if (flops[1]->revenue < flops[0]->revenue) {
                temp = flops[1];
                flops[1] = flops[0];
                flops[0] = temp;
            }
        }
    }
    
    findFlops(root->right, flops, count);
}

int main() {
    Node *root = NULL;
    char name[MAX_NAME], genre[MAX_GENRE];
    int year, option;
    float revenue;
    
    do {
        printf("\n1. Insertar película\n");
        printf("2. Recorrido Inorden\n");
        printf("3. Recorrido Preorden\n");
        printf("4. Recorrido Posorden\n");
        printf("5. Buscar película\n");
        printf("6. Mostrar por género\n");
        printf("7. Mostrar 3 fracasos taquilleros\n");
        printf("8. Salir\n");
        printf("Opción: ");
        scanf("%d", &option);
        getchar(); // Limpiar buffer
        
        switch(option) {
            case 1:
                printf("Nombre de la película: ");
                fgets(name, MAX_NAME, stdin);
                name[strcspn(name, "\n")] = 0;
                
                printf("Año: ");
                scanf("%d", &year);
                getchar();
                
                printf("Género: ");
                fgets(genre, MAX_GENRE, stdin);
                genre[strcspn(genre, "\n")] = 0;
                
                printf("Recaudación (millones): ");
                scanf("%f", &revenue);
                getchar();
                
                root = insertNode(root, name, year, genre, revenue);
                break;
                
            case 2:
                printf("\nRecorrido Inorden:\n");
                inOrder(root);
                break;
                
            case 3:
                printf("\nRecorrido Preorden:\n");
                preOrder(root);
                break;
                
            case 4:
                printf("\nRecorrido Posorden:\n");
                postOrder(root);
                break;
                
            case 5:
                printf("Nombre de la película a buscar: ");
                fgets(name, MAX_NAME, stdin);
                name[strcspn(name, "\n")] = 0;
                
                Node *found = searchMovie(root, name);
                if (found) {
                    printf("Película encontrada:\n");
                    printf("Nombre: %s\nAño: %d\nGénero: %s\nRecaudación: %.2fM\n",
                           found->name, found->year, found->genre, found->revenue);
                } else {
                    printf("Película no encontrada\n");
                }
                break;
                
            case 6:
                printf("Género a buscar: ");
                fgets(genre, MAX_GENRE, stdin);
                genre[strcspn(genre, "\n")] = 0;
                
                printf("\nPelículas del género %s:\n", genre);
                showByGenre(root, genre);
                break;
                
            case 7:
                {
                    Node *flops[3] = {NULL, NULL, NULL};
                    int count = 0;
                    findFlops(root, flops, &count);
                    
                    printf("\n3 mayores fracasos taquilleros:\n");
                    for (int i = 0; i < count; i++) {
                        printf("%d. %s - %.2fM (Año: %d)\n", 
                               i+1, flops[i]->name, flops[i]->revenue, flops[i]->year);
                    }
                }
                break;
                
            case 8:
                printf("Saliendo...\n");
                break;
                
            default:
                printf("Opción inválida\n");
        }
    } while (option != 8);
    
    
    return 0;
}