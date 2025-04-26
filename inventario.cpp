#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <stdio.h>

using namespace std;

struct Producto {
    int codigo;
    char nombre[50];
    int cantidad;
    int precio;
    Producto* siguiente;
};

class Inventario {
private:
    Producto* cabeza;
    Producto* cola;

public:
    Inventario() {
        cabeza = NULL;
        cola = NULL;
    }

    ~Inventario() {
        while (cabeza != NULL)
        {
            Producto* temp = cabeza;
            cabeza = cabeza->siguiente;
            free(temp);
        } 
    }

    void registrarProducto(int codigo, const char* nombre, int cantidad, int precio) {
        if (buscarProducto(codigo) != NULL) {
            cout << "Error: Ya existe un producto con el codigo " << codigo << endl;
            return;
        }

        Producto* nuevoProducto = (Producto*)malloc(sizeof(Producto));
        if (nuevoProducto == NULL) {
            cout << "Error: No se pudo asignar memoria para el nuevo producto." << endl;
            return;
        }

        nuevoProducto->codigo = codigo;
        strncpy(nuevoProducto->nombre, nombre, 49);    
        nuevoProducto->nombre[49] = '\0';
        nuevoProducto->cantidad = cantidad;
        nuevoProducto->precio = precio;
        nuevoProducto->siguiente = NULL;

        if (cabeza == NULL) {
            cabeza = nuevoProducto;
            cola = nuevoProducto;
        } else {
            cola->siguiente = nuevoProducto;
            cola = nuevoProducto;
        }

        cout << "Producto regisreado con exito." << endl;  
    }

    Producto* buscarProducto(int codigo) {
        Producto* actual = cabeza;
        while (actual != NULL) {
            if (actual->codigo == codigo) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return NULL; 
    }

    void mostrarProducros() {
        if (cabeza == NULL) {
            cout << "El inventario esta vacio." << endl;
            return;
        }

        cout << "\n=== LISTADO DE PRODUCTOS ===" << endl;
        cout << "Codigo\tNombre\t\tCantidad\tPrecio\tCosto Total" << endl;
        cout << "------------------------------------------------------" << endl;

        Producto* actual = cabeza;
        int costoTotal = 0;

        while (actual != NULL)
        {
            int costoProducto = actual->cantidad * actual->precio;
            costoTotal += costoProducto;

            cout << actual->codigo << "\t"
                 << actual->nombre << "\t"
                 << actual->cantidad << "\t\t"
                 << actual->precio << "\t"
                 << costoProducto << endl;
            
            actual = actual->siguiente;     
        }

        cout << "------------------------------------------------------" << endl;
        cout << "Costo total del inventario: " << costoTotal << endl;
    }

    void registrarVenta(int codigo, int cantidadVendida) {
        Producto* Producto = buscarProducto(codigo);

        if (Producto == NULL) {
            cout << "Error: No existe un producto con el codigo " << endl;
            return;
        }

        if (Producto->cantidad < cantidadVendida) {
            cout << "Error: No hay suficiente stock. Stock actual: " << Producto->cantidad << endl;  
            return;
        }

        Producto->cantidad -= cantidadVendida;
        cout << "Venta registrada. Nueva cantidad de " << Producto->nombre <<": " << Producto->cantidad << endl;  
    }

    int calcularCostoTotal() {
        int costoTotal = 0;
        Producto* actual = cabeza;

        while (actual != NULL) {
            costoTotal += actual->cantidad * actual->precio;
            actual = actual->siguiente;
        }
        
        return costoTotal;
    }

    void eliminarProducto(int codigo) {
        if (cabeza == NULL) {
            cout << " El inventario esta vacio." << endl;
            return;
        }

        Producto* actual = cabeza;
        Producto* anterior = NULL;

        while (actual != NULL && actual->codigo != codigo) {
            anterior = actual;
            actual = actual->siguiente;
        }
        
        if (actual == NULL) {
            cout << " Error: No existe un producto con el codigo " << codigo << endl;
            return;
        }
        if (actual->cantidad > 0) {   
            cout << "Error: No se puede eliminar un producto con stock. Cantidad actual: " << actual->cantidad << endl;
            return;
        }    
        if (anterior == NULL) {
            cabeza = actual->siguiente;
            if (cabeza == NULL) {
                cola = NULL;
            }
            
        } else {
            anterior->siguiente = actual->siguiente;
            if (actual == cola) {
                cola = anterior;
            } 
        }

        free(actual);
        cout << "Producto eliminado con exito." << endl;   
    }
};

int main() {
    Inventario inventario;
    int opcion;
    int codigo, cantidad, precio;
    char nombre[50];

    do
    {
        cout << "\n=== SISTEMA DE GESTION DE INVENTARIO ===" << endl;
        cout << "1. Registrar producto" << endl;
        cout << "2. Mostrar producto" << endl;
        cout << "3. Registrar venta" << endl;
        cout << "4. Calcular costo total" << endl;
        cout << "5. Eliminar producto" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcio: ";
        cin >> opcion;

        switch (opcion)
        {
         case 1:
            cout << "Ingrese codigo del producto: ";
            cin >> codigo;
            cout << "Ingrese nombre del producto: ";
            cin.ignore();
            cin.getline(nombre, 50);
            cout << "Ingrese cantidad: ";
            cin >> cantidad;
            cout << "Ingrese precio por unidad: ";
            cin >> precio;
            inventario.registrarProducto(codigo, nombre, cantidad, precio);
            break;
        
         case 2:
            inventario.mostrarProducros();
            break;

         case 3:
            cout << "Ingrese codigo del producto: ";
            cin >> codigo;
            cout << "Ingrese cantidad vendida: ";
            cin >> cantidad;
            inventario.registrarVenta(codigo, cantidad);
            break;

         case 4:
            cout << "Costo total del inventario: " << inventario.calcularCostoTotal() << endl;
            break;

         case 5:
            cout << " Ingrese codigo del producto a eliminar: ";
            cin >> codigo;
            inventario.eliminarProducto(codigo);
            break;

         case 0:
            cout << " Saliendo del programa..." << endl;
            break;
        
         default:
            cout << "Opcuin invalida. Intente de nuevo." << endl; 
        }
    } while (opcion != 0);
    return 0;
}






