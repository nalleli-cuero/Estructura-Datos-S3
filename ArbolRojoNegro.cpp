#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

//Enumeracion de color Arbol Rojo-Negro
enum Color { RED, BLACK };

//Estructura de pelicula
struct Pelicula
{
    char nombre[100];
    int anio;
    char genero[50];
    float recaudacion;
    struct Pelicula *izq, *der, *padre;
    Color color;
};

struct Pelicula *raiz = NULL, *aux = NULL;

//Funcion para consegir padre
struct Pelicula* getPadre(struct Pelicula *nodo) {
    return nodo ? nodo->padre : NULL;
}

//Funcion para consegir abuelo
struct Pelicula* getAbuelo(struct Pelicula *nodo) {
    struct Pelicula *p = getPadre(nodo);
    return p ? p->padre : NULL;
}

//Funcion para consegir Hermano
struct Pelicula* getHermano(struct Pelicula *nodo) {
    struct Pelicula *p = getPadre(nodo);
    if (!p) return NULL;
    return (nodo == p->izq) ? p->der : p->izq;
}

//Funcion para consegir tio
struct Pelicula* getTio(struct Pelicula *nodo) {
    struct Pelicula *p = getPadre(nodo);
    struct Pelicula *a = getAbuelo(nodo);
    if (!a) return NULL;
    return (p == a->izq) ? a->der : a->izq;
}

//Rotacion hacia la izquierda
void rotacionIzquierda(struct Pelicula *nodo) {
    struct Pelicula *der = nodo->der;
    nodo->der = der->izq;
    if (der->izq) der->izq->padre = nodo;
    der->padre = nodo->padre;
    if (!nodo->padre) raiz = der;
    else if (nodo == nodo->padre->izq) nodo->padre->izq = der;
    else nodo->padre->der = der;
    der->izq = nodo;
    nodo->padre = der;
}

//Rotacion hacia la derecha
void rotacionDerecha(struct Pelicula *nodo) {
    struct Pelicula *izq = nodo->izq;
    nodo->izq = izq->der;
    if (izq->der) izq->der->padre = nodo;
    izq->padre = nodo->padre;
    if (!nodo->padre) raiz = izq;
    else if (nodo == nodo->padre->der) nodo->padre->der = izq;
    else nodo->padre->izq = izq;
    izq->der = nodo;
    nodo->padre = izq;
}

//Corregir inserciones
void arreglarInsercion(struct Pelicula *nodo) {
    struct Pelicula *p, *t, *a;
    while ((p = getPadre(nodo)) && p->color == RED)
    {
        a = getAbuelo(nodo);
        if (p == a->izq)
        {
            t = getTio(nodo);
            if (t && t->color == RED)
            {
                p->color = BLACK;
                t->color = BLACK;
                a->color = RED;
                nodo = a;
            } else {
                if (nodo == p->der)
                {
                    rotacionIzquierda(p);
                    nodo = p;
                    p = getPadre(nodo);
                }
                p->color = BLACK;
                a->color = RED;
                rotacionDerecha(a);
            }
        } else {
            t = getTio(nodo);
            if (t && t->color == RED)
            {
                p->color = BLACK;
                t->color = BLACK;
                a->color = RED;
                nodo = a;
            } else {
                if (nodo == p->izq)
                {
                    rotacionDerecha(p);
                    nodo = p;
                    p = getPadre(nodo);
                }
                p->color = BLACK;
                a->color = RED;
                rotacionIzquierda(a);
            } 
        }
    }
    raiz->color = BLACK;
}

//Comprobar si año existe
bool anioExiste(struct Pelicula *nodo, int anio) {
    if (nodo == NULL) return false;
    if ( nodo->anio == anio) return true;
    if (anio < nodo->anio) return anioExiste(nodo->izq, anio);
    return anioExiste(nodo->der, anio);
}

// Insetar nueva Pelicula
void posicionar(struct Pelicula *nuevaRaiz) {
    if (aux->anio <= nuevaRaiz->anio)
    {
        if (nuevaRaiz->izq == NULL)
        {
            nuevaRaiz->izq = aux;
            aux->padre = nuevaRaiz;
        } else {
            posicionar(nuevaRaiz->izq);
        }
    } else {
        if (nuevaRaiz->der == NULL)
        {
            nuevaRaiz->der = aux;
            aux->padre = nuevaRaiz;
        } else {
            posicionar(nuevaRaiz->der);
        }
    } 
}

void regitrar() {
    aux = ( struct Pelicula *) malloc(sizeof(struct Pelicula));
    if (aux == NULL)
    {
        cout << "Error: No se pudo asignar memoria." << endl;
        return;
    }
    aux->izq = aux->der = aux->padre = NULL;
    aux->color = RED;

    cin.ignore();
    cout << "Nombre de la pelicula: ";
    fgets(aux->nombre, 100, stdin);
    aux->nombre[strcspn(aux->nombre, "\n")] = 0;

    cout << "Año de realizacion: ";
    cin >> aux->anio;

    if (raiz != NULL && anioExiste(raiz, aux->anio))
    {
        cout << "Error: El año " << aux->anio << " ya existe." << endl;
        free(aux);
        aux = NULL;
        return;
    }
    
    cin.ignore();
    cout << "Genero: ";
    fgets(aux->genero, 50, stdin);
    aux->genero[strcspn(aux->genero, "\n")] = 0;

    cout << "Recaudacion (millones): ";
    cin >> aux->recaudacion;

    if (raiz == NULL)
    {
        raiz = aux;
        raiz->color = BLACK;
    } else {
        posicionar(raiz);
        arreglarInsercion(aux);
    }
    aux = NULL;
}

//Buscar pelicula por nombre
struct Pelicula* buscarPelicula(struct Pelicula *nodo, char nombre[]) {
    if (nodo == NULL || strcmp(nodo->nombre, nombre) == 0)
    {
        return nodo;
    }
    struct Pelicula *izq = buscarPelicula(nodo->izq, nombre);
    if (izq != NULL) return izq;
    return buscarPelicula(nodo->der, nombre);  
}

// Mostrar peliculas por genero
void moatrarPorGenero(struct Pelicula *nodo, char genero[]) {
    if (nodo != NULL)
    {
        moatrarPorGenero(nodo->izq, genero);
        if (strcmp(nodo->genero, genero) == 0)
        {
            cout << "Nombre: " << nodo->nombre << "Año: " << nodo->anio
                 << ", Recaudacion: $" << nodo->recaudacion << "M" << endl;
        }
       moatrarPorGenero(nodo->der, genero);
    }
}

//Mostrar los 3 fracasos taquilleros
void obtenerFracasos(struct Pelicula *nodo, Pelicula* fracasos[], int &cont) {
    if (nodo != NULL)
    {
        obtenerFracasos(nodo->izq, fracasos, cont);
        if (cont < 3)
        {
            fracasos[cont] = nodo;
            cont++;
        } else {
            int maxIdx = 0;
            for (int i = 1; i < 3; i++)
            {
                if (fracasos[i] && fracasos[i]->recaudacion > fracasos[maxIdx]->recaudacion);
                {
                    maxIdx = i;
                } 
            }
            if (nodo->recaudacion < fracasos[maxIdx]->recaudacion)
            {
                fracasos[maxIdx] = nodo;
            }
        }
        obtenerFracasos(nodo->der, fracasos, cont);
    } 
}

void mostrarFracasos() {
    Pelicula *fracasos[3] = {NULL, NULL, NULL};
    int cont = 0;
    obtenerFracasos(raiz, fracasos, cont);

    for (int i = 0; i < cont - 1; i++)
    {
        for (int j = 0; j < cont - i - 1; j++)
        {
            if (fracasos[j] && fracasos[j + i] && fracasos[j]->recaudacion > fracasos[j + 1]->recaudacion)
            {
                Pelicula *temp = fracasos[j];
                fracasos[j] = fracasos[j + 1];
                fracasos[j + 1] = temp;
            }
        } 
    }
    
    cout << "Los 3 mayores fracasos taquilleros:" << endl;
    for (int i = 0; i < cont && fracasos[i] != NULL; i++)
    {
        cout << i + 1 << ". " << fracasos[i]->nombre << " ($"
             << fracasos[i]->recaudacion << "M)" << endl;
    }
    if (cont == 0) cout << "No hay peliculas regisreadas." << endl;
}

//Arreglo por eliminacion
void arreglerEliminacion(struct Pelicula *nodo, struct Pelicula *padre) {
    struct Pelicula *hermano;
    while (nodo != raiz && (!nodo || nodo->color == BLACK))
    {
        if (nodo == padre->izq)
        {
            hermano = padre->der;
            if (hermano->color == RED)
            {
                hermano->color == BLACK;
                padre->color = RED;
                rotacionIzquierda(padre);
                hermano = padre->der;
            }
            if ((!hermano->izq || hermano->izq->color == BLACK) && 
                (!hermano->der || hermano->der->color == BLACK))
            {
                hermano->color = RED;
                nodo = padre;
                padre = getPadre(nodo);
            } else {
                if (!hermano->der || hermano->der->color == BLACK)
                {
                    if (hermano->izq) hermano->der->color = BLACK;
                    hermano->color = RED;
                    rotacionDerecha(hermano);
                    hermano = padre->der;
                }
                hermano->color = padre->color;
                padre->color = BLACK;
                if (hermano->der) hermano->der->color = BLACK;
                rotacionIzquierda(padre);
                nodo = raiz;
            }
        } else {
            hermano = padre->izq;
            if (hermano->color == RED)
            {
                hermano->color = BLACK;
                padre->color = RED;
                rotacionDerecha(padre);
                hermano = padre->izq;
            }
            if ((!hermano->izq || hermano->izq->color == BLACK) && 
                (!hermano->der || hermano->der->color == BLACK))
            {
                hermano->color = RED;
                nodo = padre;
                padre = getPadre(nodo); 
            } else {
                if (!hermano->izq || hermano->izq->color == BLACK)
                {
                    if (hermano->der) hermano->izq->color = BLACK;
                    hermano->color = RED;
                    rotacionIzquierda(hermano);
                    hermano = padre->izq; 
                }
                hermano->color = padre->color;
                padre->color = BLACK;
                if (hermano->izq) hermano->izq->color = BLACK;
                rotacionDerecha(padre);
                nodo = raiz;
            }
        }
    }
    if (nodo) nodo->color = BLACK;
}

//Reemplazar nodo
void reemplazarNodo(struct Pelicula *nodo, struct Pelicula *hijo) {
    if (!nodo->padre)
    {
        raiz = hijo;
    } else if (nodo == nodo->padre->izq)
    {
        nodo->padre->izq = hijo;
    } else {
        nodo->padre->der = hijo;
    }
    if (hijo) hijo->padre = nodo->padre;
}

// Enconter nodo minimo
struct Pelicula* encontraMin(struct Pelicula *nodo) {
    while (nodo->izq != NULL)
    {
        nodo = nodo->izq;
    }
    return nodo;
}

// Eliminar nodo
struct Pelicula* eliminarNodo(struct Pelicula *nodo, char nombre[]) {
    if (nodo == NULL) return NULL;

    int cmp = strcmp(nombre, nodo->nombre);
    if (cmp < 0)
    {
        nodo->izq = eliminarNodo(nodo->izq, nombre);
    } else if (cmp > 0)
    {
        nodo->der = eliminarNodo(nodo->der, nombre);
    } else {
        // Caso 1: sin hijos
        if (nodo->izq == NULL && nodo->der == NULL)
        {
            if (nodo->color == BLACK) arreglerEliminacion(nodo, nodo->padre);
            if (nodo == raiz) raiz = NULL;
            free(nodo);
            return NULL;
        }
        // Caso 2: con un hijo
        if (nodo->izq == NULL || nodo->der == NULL)
        {
            struct Pelicula *hijo = nodo->izq ? nodo->izq : nodo->der;
            if (nodo->color == BLACK && hijo->color == BLACK)
            {
                arreglerEliminacion(hijo, nodo->padre);
            } else if (hijo)
            {
                hijo->color =BLACK;
            }
            reemplazarNodo(nodo, hijo);
            free(nodo);
            return hijo;
        }
        // Caso 3: con dos hijos
        struct Pelicula *temp = encontraMin(nodo->der);
        strcpy(nodo->nombre, temp->nombre);
        nodo->anio = temp->anio;
        strcpy(nodo->genero, temp->genero);
        nodo->recaudacion = temp->recaudacion;
        nodo->der = eliminarNodo(nodo->der, temp->nombre);
    }
    return nodo;
}

int main() {
    int opcion;
    char nombre[100], genero[50];

    do
    {
        cout << "\n1. Registrar pelicula" << endl;
        cout << "2. Buscar pelicula" << endl;
        cout << "3. Mostrar por genero" << endl;
        cout << "4. Mostrar fracasos taquilleros" << endl;
        cout << "5. Eliminar pelicula" << endl;
        cout << "6. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            registrar();
            break;
        case 2:
            cin.ignore();
            cout << "Nombre de la pelicula a buscar: ";
            fgets(nombre, 100, stdin);
            nombre[strcspn(nombre, "\n")] = 0;
            struct Pelicula *encontrada = buscarPelicula(raiz, nombre);
            if (encontrada != NULL)
            {
                cout << "Pelicula encontrada:" << endl;
                cout << "Nombre: " << encontrada->nombre << ", Año: " << encontrada->anio
                     << ", Genero: " << encontrada->genero << ", Recaudacion: $"
                     << encontrada->recaudacion << "M" << endl;
            } else {
                cout << "Pelicula no encontrada" << endl;
            }
            break;
        case 3:
            cin.ignore();
            cout << "Genero a buscar: ";
            fgets(genero, 50, stdin);
            genero[strcspn(genero, "\n")] = 0;
            cout << "Peliculas del genero" << genero << ";" << endl;
            mostrarPorGenero(raiz, genero);
            break;
        case 4:
            mostrarFracasos();
            break;
        case 5:
            cin.ignore();
            cout << "Nombre de pelicula a eliminar: ";
            fgets(nombre, 100, stdin);
            nombre[strcpn(nombre, "\n")] = 0;
            raiz = eliminarNodo(raiz, nombre);
            cout << "Pelicula eliminada (si existia)" << endl;
            break;
        case 6;
            break;           
        default:
            cout << "Opcion invalida." << endl;
        }
    } while (opcion != 6);

    // limpiar memoria
    while (raiz != NULL)
    {
        raiz = eliminarNodo(raiz, raiz->nombre);
    }
    
    return 0;
}