 #include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Función para verificar si una cadena es un palíndromo
bool probarPalindromo(string, size_t, size_t);

// Función de Radix Sort para ordenar palabras
void radixSort(vector<string>& palabras);
int obtenerMaximoLongitud(const vector<string>& palabras);
void contarSort(vector<string>& palabras, int exp);

int main() {
    string entrada;
    cout << "Ingrese una oración:\n";
    getline(cin, entrada);

    // Dividir la entrada en palabras
    vector<string> palabras;
    string palabra;
    for (char c : entrada) {
        if (isspace(c)) {
            if (!palabra.empty()) {
                palabras.push_back(palabra);
                palabra.clear();
            }
        } else {
            palabra += c;
        }
    }
    if (!palabra.empty()) {
        palabras.push_back(palabra);
    }

    // Ordenar las palabras usando Radix Sort
    radixSort(palabras);

    // Imprimir las palabras ordenadas
    cout << "Palabras ordenadas:\n";
    for (const string& p : palabras) {
        cout << p << " ";
    }
    cout << endl;

    // Verificar si la oración original es un palíndromo
    entrada.erase(remove(entrada.begin(), entrada.end(), ' '), entrada.end()); // Quitar espacios
    if (probarPalindromo(entrada, 0, entrada.length() - 1)) {
        cout << '"' << entrada << "\" es un palíndromo." << endl;
    } else {
        cout << '"' << entrada << "\" no es un palíndromo." << endl;
    }

    return 0;
}

// Implementación de la función para verificar si una cadena es un palíndromo
bool probarPalindromo(string palindromo, size_t izquierda, size_t derecha) {
    if (izquierda >= derecha) {
        return true;
    } else if (palindromo[izquierda] != palindromo[derecha]) {
        return false;
    }
    return probarPalindromo(palindromo, izquierda + 1, derecha - 1);
}

// Implementación de Radix Sort
void radixSort(vector<string>& palabras) {
    int maxLong = obtenerMaximoLongitud(palabras);
    for (int exp = maxLong - 1; exp >= 0; exp--) {
        contarSort(palabras, exp);
    }
}

// Obtener la longitud máxima entre las palabras
int obtenerMaximoLongitud(const vector<string>& palabras) {
    int maxLong = 0;
    for (const string& palabra : palabras) {
        if (palabra.length() > maxLong) {
            maxLong = palabra.length();
        }
    }
    return maxLong;
}

// Ordenar las palabras con base en el carácter en la posición 'exp'
void contarSort(vector<string>& palabras, int exp) {
    vector<string> output(palabras.size());
    int count[256] = {0};

    // Contar la ocurrencia de cada carácter
    for (const string& palabra : palabras) {
        char c = exp < palabra.length() ? palabra[exp] : 0;
        count[c]++;
    }

    // Transformar en posiciones acumuladas
    for (int i = 1; i < 256; i++) {
        count[i] += count[i - 1];
    }

    // Construir el arreglo de salida
    for (int i = palabras.size() - 1; i >= 0; i--) {
        char c = exp < palabras[i].length() ? palabras[i][exp] : 0;
        output[count[c] - 1] = palabras[i];
        count[c]--;
    }

    // Copiar el arreglo ordenado de regreso
    palabras = output;
}