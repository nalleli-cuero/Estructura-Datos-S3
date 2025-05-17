#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

struct Pelicula
{
    char nombre[100];
    int anio;
    char genero[50];
    float recaudacion;
    struct Pelicula *izq;
    struct Pelicula *der;
};

struct Pelicula *raiz = NULL, *aux = NULL;

// Insertar pelicula
void posicionar(struct Pelicula *nuevaRaiz) {
    if (aux->anio < nuevaRaiz->anio) 
    {
        if (nuevaRaiz->izq == NULL)
        {
            nuevaRaiz->izq = aux;
        } else {
            posicionar(nuevaRaiz->izq);
        }
    } else {
        if (nuevaRaiz->der == NULL) {
            nuevaRaiz->der = aux;
        } else {
            posicionar(nuevaRaiz->der);
        }
    }   
}

void registrar() {
    aux = (struct Pelicula *)malloc(sizeof(struct Pelicula));
    aux->izq = aux->der = NULL;

    cin.ignore();
    cout << "Nombre de la pelicula: ";
    fgets(aux->nombre, 100, stdin);
    aux->nombre[strcspn(aux->nombre, "\n")] = 0;

    cout << "Año de realizacion: ";
    cin >> aux->anio;

    cin.ignore();
    cout << "Genero: ";
    fgets(aux->genero, 50, stdin);
    aux->genero[strcspn(aux->genero, "\n")] = 0;

    cout << "Recaudacion (Millones): ";
    cin >> aux->recaudacion;

    if (raiz == NULL)
    {
        raiz = aux;
    } else {
        posicionar(raiz);
    }
    aux = NULL;
}

//Recorrido del Arbol
void inOrden(struct Pelicula *nuevaRaiz) {
    if (nuevaRaiz != NULL)
    {
        inOrden(nuevaRaiz->izq);
        cout << "Nombre: " << nuevaRaiz->nombre << ", Año: " << nuevaRaiz->anio << ", Genero: " << nuevaRaiz->genero << ", Recaudacion: $" << nuevaRaiz->recaudacion << "M"<< endl;
        inOrden(nuevaRaiz->der);
    }
}

void preOrden(struct Pelicula *nuevaRaiz) {
    if (nuevaRaiz != NULL)
    {
        cout << "Nombre: " << nuevaRaiz->nombre << ", Año: " << nuevaRaiz->anio << ", Genero: " << nuevaRaiz->genero << ", Recaudacion: $" << nuevaRaiz->recaudacion << "M"<< endl;
        preOrden(nuevaRaiz->izq);
        preOrden(nuevaRaiz->der);
    }
}

void posOrden(struct Pelicula *nuevaRaiz) {
    if (nuevaRaiz != NULL)
    {
        posOrden(nuevaRaiz->izq);
        posOrden(nuevaRaiz->der);
        cout << "Nombre: " << nuevaRaiz->nombre << ", Año: " << nuevaRaiz->anio << ", Genero: " << nuevaRaiz->genero << ", Recaudacion: $" << nuevaRaiz->recaudacion << "M"<< endl;
    }
}

//Buscar pelicula por nombre
struct Pelicula* buscarPelicula(struct Pelicula *nuevaRaiz, char nombre[])
{
    if (nuevaRaiz == NULL || strcmp(nuevaRaiz->nombre, nombre) == 0)
    {
        return nuevaRaiz;
    }
    struct Pelicula *izq = buscarPelicula(nuevaRaiz->izq, nombre);
    if (izq != NULL) return izq;
    return buscarPelicula(nuevaRaiz->der, nombre);
}

//Mostrar peliculas por genero
void mostrarPorGenero(struct Pelicula *nuevaRaiz, char genero[]) {
    if (nuevaRaiz != NULL)
    {
        mostrarPorGenero(nuevaRaiz->izq, genero);
        if (strcmp(nuevaRaiz->genero, genero) == 0)
        {
            cout << "Nombre: " << nuevaRaiz->nombre << ", Año: " << nuevaRaiz->anio << ", Genero: " << nuevaRaiz->genero << ", Recaudacion: $" << nuevaRaiz->recaudacion << "M"<< endl;
        }
        mostrarPorGenero(nuevaRaiz->der, genero);
    }
}

// Mostrar 3 fracasos taquilleros
void obtenerFracasos(struct Pelicula *nuevaRaiz, Pelicula* fraccasos[], int &cont) {
    if (nuevaRaiz != NULL && cont < 3)
    {
        obtenerFracasos(nuevaRaiz->izq, fraccasos, cont);
        if (cont < 3)
        {
            fraccasos[cont] = nuevaRaiz;
            cont++;
        }
        obtenerFracasos(nuevaRaiz->der, fraccasos, cont);
    }   
}

void mostrarFracasos() {
    Pelicula *fracasos[3] = {NULL, NULL, NULL};
    int cont = 0;
    obtenerFracasos(raiz, fracasos, cont);

    //Ordenar por recaudacion (burbuja simple)
    for (int i = 0; i < cont - 1; i++)
    {
        for (int j = 0; j < cont - i - 1; j++)
        {
            if (fracasos[j]->recaudacion > fracasos[j + 1]->recaudacion)
            {
                Pelicula *temp = fracasos[j];
                fracasos[j] = fracasos[j + 1];
                fracasos[j + 1] = temp;
            }
        }
    }

    cout << "Los 3 mayores freacasos taquilleros: " << endl;
    for (int i = 0; i < cont; i++)
    {
        cout << i + 1 << ". " << fracasos[i]->nombre << " ($" << fracasos[i]->recaudacion << "M)" << endl;
    }
}

// Eliminacion de nodos
struct Pelicula* encontrarMin(struct Pelicula *nuevaRaiz)
{
    while (nuevaRaiz->izq != NULL)
    {
        nuevaRaiz = nuevaRaiz->izq;
    }
    return nuevaRaiz;
}

struct Pelicula* eliminarNodo(struct Pelicula *nuevaRaiz, char nombre[])
{
    if (nuevaRaiz == NULL) return NULL;

    if (strcmp(nombre, nuevaRaiz->nombre) < 0)
    {
        nuevaRaiz->izq = eliminarNodo(nuevaRaiz->izq, nombre);
    } else if (strcmp(nombre, nuevaRaiz->nombre) < 0)
    {
        nuevaRaiz->der = eliminarNodo(nuevaRaiz->der, nombre);
    } else
    {
        // Caso 1: sin hijos
        if (nuevaRaiz->izq == NULL && nuevaRaiz->der == NULL)
        {
            free(nuevaRaiz);
            return NULL;
        }
        // Casa 2: un hijo
        if (nuevaRaiz->izq == NULL)
        {
            struct Pelicula *temp = nuevaRaiz->der;
            free(nuevaRaiz);
            return temp;
        }
        if (nuevaRaiz->der == NULL)
        {
            struct Pelicula *temp = nuevaRaiz->izq;
            free(nuevaRaiz);
            return temp;
        }
        // Caso 3: dos hijos
        struct Pelicula *temp = encontrarMin(nuevaRaiz->der);
        strcpy(nuevaRaiz->nombre, temp->nombre);
        nuevaRaiz->anio = temp->anio;
        strcpy(nuevaRaiz->genero, temp->genero);
        nuevaRaiz->recaudacion = temp->recaudacion;
        nuevaRaiz->der = eliminarNodo(nuevaRaiz->der, temp->nombre);
    }
    return nuevaRaiz;   
}

int main() {
    int opcion;
    char nombre[100], genero[50];

    do
    {
        cout << "\n1. Registrar pelicula" << endl;
        cout << "2. Mostrar InOrden" << endl;
        cout << "3. Mostrar PreOrden" << endl;
        cout << "4. Mostrar PosOrden" << endl;
        cout << "5. Buscar pelicula" << endl;
        cout << "6. Mostrar Por genero" << endl;
        cout << "7. Mostrar fracasos taquilleros" << endl;
        cout << "8. Eliminar pelicula" << endl;
        cout << "9. Salir" << endl;
        cout << "Opcion: " << endl;
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            registrar();
            break;
        case 2:
            cout << "Recorrido InOrden: " << endl;
            inOrden(raiz);
            break;
        case 3:
            cout << "Recorrido PreOrden: " << endl;
            preOrden(raiz);
            break;
        case 4:
            cout << "Recorrido PosOrden: " << endl;
            posOrden(raiz);
            break;
        case 5:
            cin.ignore();
            cout << "Nombre de la pelicula a buscar: " << endl;
            fgets(nombre, 100, stdin);
            nombre[strcspn(nombre, "\n")] = 0;
            struct Pelicula *encontrada = buscarPelicula(raiz, nombre);
            if (encontrada != NULL)
            {
                cout << "Pelicula encontrada:" << endl;
                cout << "Nombre:" << encontrada->nombre << ", Año: " << encontrada->anio << ", Genero: " << encontrada->genero << ", Recaudacion: $" << encontrada->recaudacion << "M" << endl;
            } else {
                cout << "Pelicula no encontrada" << endl;
            }
            break;
        case 6:
            cin.ignore();
            cout << "Genero a buscar: " << endl;
            fgets(genero, 50, stdin);
            genero[strcspn(genero, "\n")] = 0;
            cout << "Peliculas del genero " << genero << ":" << endl;
            mostrarPorGenero(raiz, genero);
            break;
        case 7:
            mostrarFracasos();
            break;
        case 8:
            cin.ignore();
            cout << "Nombre de la pelicula a eliminar: " << endl;
            fgets(nombre, 100, stdin);
            nombre[strcspn(nombre, "\n")] = 0;
            raiz = eliminarNodo(raiz, nombre);
            cout << "Pelicula eliminada" << endl;
            break;
        }
    } while (opcion != 9);

    return 0; 
}
