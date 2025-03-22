#include <iostream>
#include <string>
using namespace std;

struct Producto {
    int codigo;
    string nombre;
    int cantidad;
    int precioUnidad;
    Producto* siguiente;
};

class Inventario {
private:
    Producto* frente;
    Producto* final;
    int tamaño;

public:
    Inventario() {
        frente = nullptr;
        final = nullptr;
        tamaño = 0;
    }
   
    ~Inventario() {
        while (frente != nullptr) {
            Producto* temp = frente;
            frente = frente->siguiente;
            free(temp);
        }
        
    }

    void registrarProducto(int codigo, string nombre, int cantidad, int precio) {
        Producto* nuevo = (Producto*)malloc(sizeof(Producto));
        if (nuevo == nullptr) {
            cout << "Error: No hay memoria disponible\n";
        }

        nuevo->codigo = codigo;
        nuevo->nombre = nombre;
        nuevo->cantidad = cantidad;
        nuevo->precioUnidad = precio;
        nuevo->siguiente = nullptr;

        if (frente == nullptr) {
            frente = nuevo;
            final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
        tamaño++;    
    }

    void mostrarInventario() {
        if (frente == nullptr) {
            cout << "Inventario vacio\n";
            return;
        }

        Producto* actual = frente;
        cout << "\n=== Inventario Actual ===\n";
        while (actual != nullptr) {
            int costoTotal = actual->cantidad * actual->precioUnidad;
            cout << "Codigo: " << actual->codigo <<"\n";
            cout << "Nombre: " << actual->nombre <<"\n";
            cout << "Cantidad: " << actual->cantidad <<"\n";
            cout << "Precio unidad: $" << actual->precioUnidad <<"\n";
            cout << "Costo total: $" << costoTotal <<"\n\n";
            actual = actual->siguiente;
        }  
    }

    void registrarVenta(int codigo, int cantidadVendida) {
        Producto* actual = frente;
        while (actual != nullptr) {
            if (actual->codigo == codigo) {
                if (cantidadVendida > actual->cantidad) {
                    cout << "Error: Cantidad insuficiente en inventario\n";
                    return;
                }
                actual->cantidad -= cantidadVendida;
                cout << "Venta registrada exitosamente\n";
                return;  
            }
            actual = actual->siguiente; 
        }
        cout << "Producto no encontrado\n"; 
    }
    
    int calcostoCostoTotal(int codigp) {
        int total = 0;
        Producto* actual = frente;
        while (actual != nullptr) {
            total += actual->cantidad * actual->precioUnidad;
            actual = actual->siguiente;
        }
        return total;
    }

    void eliminarProducto(int codigo) {
        if (frente = nullptr) {
            cout << "Inventario vacio\n";
            return;
        }
        
        if (frente->codigo == codigo) {
            if (frente->cantidad == 0) {
                Producto* temp = frente;
                frente = frente->siguiente;
                free(temp);
                tamaño--;
                if (frente == nullptr) final = nullptr;
                cout << "Producto eliminado exitosamente\n";
            } else {
                cout << "Error: La cantidad debe ser 0 para eliminar\n";
            }
            return; 
        }

        Producto* actual = frente;
        while (actual->siguiente != nullptr) {
            if (actual->siguiente->codigo == codigo) {
                if (actual->siguiente->codigo == 0) {
                    Producto* temp = actual->siguiente;
                    actual->siguiente = temp->siguiente;
                    if (temp == final) final = actual;
                    free(temp);
                    tamaño--;
                    cout << "Producto eliminado exitosamente\n";    
                } else {
                    cout << "Error: La cantidad debe ser 0 para eliminar\n";
                }
                return;   
            }
            actual = actual->siguiente; 
        }
        cout << "Producto no encontrado\n"; 
    }
};

int main() {
    Inventario inv;
    int opcion;

    do {
        cout << "\n=== Sistema de inventario ===\n";
        cout << "1. Registrar producto\n";
        cout << "2. Mostrar inventario\n";
        cout << "3. Registrar venta\n";
        cout << "4. Calcular costo total\n";
        cout << "5. Eliminar producto\n";
        cout << "6. Salir\n";
        cout << "Selecionar una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1: {
            int codigo, cantidad, precio;
            string nombre;
            cout <<"Codigo: "; cin >> codigo;
            cout <<"Nombre: "; cin >> nombre;
            cout <<"Cantidad: "; cin >> cantidad;
            cout <<"Precio unidad: "; cin >> precio;
            inv.registrarProducto(codigo, nombre, cantidad, precio);
            break;
        }
        case 2:
            inv.mostrarInventario();
            break;
        case 3: {
            int codigo, cantidad;
            cout << "Codigo del producto: "; cin >> codigo;
            cout << "Cantidad vendida: "; cin >> cantidad;
            inv.registrarVenta(codigo, cantidad);
            break;
        }
        case 4:
            cout << "Costo total del inventario: $" << inv.calcostoCostoTotal() << "\n";
            break;
        case 5: {
            int codigo;
            cout << "Codigo del producto a eliminar: "; cin >> codigo;
            inv.eliminarProducto(codigo);
            break;
        }
        case 6:
            cout << "Saliendo...\n";
            break;   
        default:
            cout << "Opcion invalida\n";
        }
    } while (opcion != 6);
   
    return 0;
}
