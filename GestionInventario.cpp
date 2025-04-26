#include <iostream>
#include <string>
#include <malloc.h>
using namespace std;

struct Producto {
    int codigo;
    string nombre;
    int cantidad;
    int precio;
    Producto *siguiente;
};

struct Producto *cabeza, *auxilar, *ultimo;

void registraProducto() {
    auxilar = ((struct Producto *) malloc(sizeof(struct Producto)));
    cout << "Ingrese codigo unico: ";
    cin >> auxilar->codigo;
    cin.ignore();
    cout << "Ingrese nombre del producto: ";
    getline(cin, auxilar->nombre);
    cout << "Ingrese cantidad: ";
    cin >> auxilar->cantidad;
    cout << "Ingrese precio por unidad: ";
    cin >> auxilar->precio;
    auxilar->siguiente = NULL;

    if (cabeza == NULL) {
        cabeza = auxilar;
    } else {
        ultimo = cabeza;
        while (ultimo->siguiente != NULL) {
            ultimo = ultimo->siguiente;
        }
        ultimo->siguiente = auxilar;
        ultimo = NULL;
        free(ultimo);
    }
    auxilar = NULL;
    free(auxilar);
}

void mostrarProducto() {
    if (cabeza == NULL) {
        cout << "Inventario vacio" << endl;
        return;
    }
    int totalInventario = 0;
    for (auxilar = cabeza; auxilar != NULL; auxilar->siguiente) {
        int costoProducto = auxilar->cantidad * auxilar->precio;
        cout << "Codigo: " << auxilar->codigo << endl;
        cout << "Nombre: " << auxilar->nombre << endl;
        cout << "Cantidad: " << auxilar->cantidad << endl;
        cout << "Precio: $" << auxilar->precio << endl;
        cout << "Costo total del producto: $" << costoProducto << endl;
        cout << "----------------------------" << endl;
        totalInventario += costoProducto;
    }
    cout << "Costo total del inventario: $" << totalInventario << endl;
}
void regostrarVenta() {
    if (cabeza == NULL) {
        cout << "Inventario vacio" << endl;
        return;
    }
    int cod, cant;
    cout << "Ingrese codigo del producto: ";
    cin >> cod;
    cout << "Ingrese cantidad vendida: ";
    cin >> cant;

    for (auxilar = cabeza; auxilar != NULL; auxilar->siguiente) {
        if (auxilar->codigo == cod) {
            if (auxilar->cantidad >= cant) {
                auxilar->cantidad -= cant;
                cout << "Venta registrada exitosamente" << endl;
                return;
            } else {
                cout << "No hay suficiente cantidad en inventario" << endl;
                return;
            }
            
        }
    }
    cout << "Producto no encontrado" << endl;
}

void eliminarPruoducto() {
    if (cabeza == NULL) {
        cout << "Inventario vacio" << endl;
        return;
    }
    int cod;
    cout << "Ingrese codigo del producto a eliminar: ";
    cin >> cod;

    if (cabeza->codigo == cod && cabeza->cantidad == 0) {
        auxilar = cabeza;
        cabeza = cabeza->siguiente;
        free(auxilar);
        cout << "Producto eliminado" << endl;
        return;
    }

    struct Producto *anterior = cabeza;
    auxilar = cabeza->siguiente;
    while (auxilar != NULL) {
        if (auxilar->codigo == cod && auxilar->cantidad == 0) {
            anterior->siguiente = auxilar->siguiente;
            free(auxilar);
            cout << "Producto elimunado" << endl;
            return;
        }
        anterior = auxilar;
        auxilar = auxilar->siguiente;
    }
    cout << "Producto no encontrado o cantidad no es cero" << endl;  
}

int main(){
    int opc;
    do {
        cout << "\n=== GESTION DE INVENTARIO ==="<<endl;
        cout << "1. Regestrar Producto" << endl;
        cout << "2. Mostrar Productos" << endl;
        cout << "3. Registrar venta" << endl;
        cout << "4. Eliminar producto" << endl;
        cout << "5.Salir" << endl;
        cout << "Seleccione opcion: ";
        cin >> opc;
        switch (opc) {
            case 1: registraProducto(); break;
            case 2: mostrarProducto(); break;
            case 3: registraProducto(); break;
            case 4: eliminarPruoducto(); break;
            case 5: cout << "Saliendo..." << endl; break;
            default: cout << "Opcion invalida" << endl;
        }
    } while (opc != 5);

    while (cabeza != NULL) {
        auxilar = cabeza;
        cabeza = cabeza->siguiente;
        free(auxilar);
    }

    return 0; 
}