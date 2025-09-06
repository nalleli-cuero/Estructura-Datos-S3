#include <iostream>
using namespace std;

const int N = 10;

// 1. Pedir los números (llenarArray)
void llenarArray(int a[]) {
    cout << "Ingresa 10 números enteros positivos:\n";
    for (int i = 0; i < N; i++) {
        do {
            cout << "Número " << i + 1 << ": ";
            cin >> a[i];
            if (a[i] <= 0) {
                cout << "Debe ser positivo. Intenta de nuevo.\n";
            }
        } while (a[i] <= 0);
    }
}

// 2. Mostrar el arreglo
void mostrarArreglo(int a[]) {
    cout << "El arreglo es: ";
    for (int i = 0; i < N; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

// 3. Ordenar con Selection Sort (ascendente)
void ordenarSelectionAscendente(int a[]) {
    cout << "\nOrdenando con Selection Sort (ascendente):\n";
    for (int i = 0; i < N - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < N; j++) {
            if (a[j] < a[menor]) {
                menor = j;
            }
        }
        // Intercambiar
        int temp = a[i];
        a[i] = a[menor];
        a[menor] = temp;

        // Imprimir el arreglo después de cada intercambio
        cout << "Paso " << i + 1 << ": ";
        mostrarArreglo(a);
    }
    cout << "Arreglo ordenado (ascendente): ";
    mostrarArreglo(a);
}

// 4. Ordenar con Insertion Sort (descendente)
void ordenarInsertionDescendente(int a[]) {
    cout << "\nOrdenando con Insertion Sort (descendente):\n";
    for (int i = 1; i < N; i++) {
        int clave = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] < clave) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = clave;

        // Imprimir el arreglo después de cada inserción
        cout << "Paso " << i << ": ";
        mostrarArreglo(a);
    }
    cout << "Arreglo ordenado (descendente): ";
    mostrarArreglo(a);
}

int main() {
    int numeros[N];
    int opcion;

    // 1. Llenar el arreglo
    llenarArray(numeros);

    do {
        // 2. Mostrar el menú
        cout << "\nOpciones:\n";
        cout << "1. Ver arreglo original\n";
        cout << "2. Ordenar con Selection Sort (ascendente)\n";
        cout << "3. Ordenar con Insertion Sort (descendente)\n";
        cout << "4. Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        // 3. Hacer algo según la opción
        if (opcion == 1) {
            mostrarArreglo(numeros);
        } else if (opcion == 2) {
            int copia[N];
            for (int i = 0; i < N; i++) {
                copia[i] = numeros[i];
            }
            ordenarSelectionAscendente(copia);
        } else if (opcion == 3) {
            int copia[N];
            for (int i = 0; i < N; i++) {
                copia[i] = numeros[i];
            }
            ordenarInsertionDescendente(copia);
        } else if (opcion == 4) {
            cout << "¡Adiós!\n";
        } else {
            cout << "Opcion no valida. Intenta de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}