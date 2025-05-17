#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <map>
#include <functional>
#include <queue>
#include <cmath>
#include <iomanip>

using namespace std;
using namespace chrono;

string formato_tiempo(int microsegundos) {
    if (microsegundos < 1000)
        return to_string(microsegundos) + " µs";
    else if (microsegundos < 1'000'000)
        return to_string(microsegundos / 1000.0).substr(0, to_string(microsegundos / 1000.0).find(".") + 3) + " ms";
    else
        return to_string(microsegundos / 1'000'000.0).substr(0, to_string(microsegundos / 1'000'000.0).find(".") + 3) + " s";
}

void generar_datos(vector<int>& datos, int cantidad) {
    random_device semilla;
    mt19937 generador(semilla());
    uniform_int_distribution<> distribucion(0, 100000);
    datos.resize(cantidad);
    for (int& valor : datos)
        valor = distribucion(generador);
}


template <typename Funcion>
int medir_tiempo(Funcion algoritmo, vector<int> datos_originales, const string& nombre_algoritmo) {
    if (is_sorted(datos_originales.begin(), datos_originales.end())) {
        cerr << "[ERROR] La lista ya está ordenada antes de ejecutar '" << nombre_algoritmo << "'.";
    }

    auto inicio = high_resolution_clock::now();
    algoritmo(datos_originales);
    auto fin = high_resolution_clock::now();

    if (!is_sorted(datos_originales.begin(), datos_originales.end())) {
        cerr << "\n[ERROR] El algoritmo '" << nombre_algoritmo << "' no ordenó correctamente.\n";
    }

    auto duracion = duration_cast<microseconds>(fin - inicio).count();
    return duracion;
}

void ordenar_std(vector<int>& datos) {
    sort(datos.begin(), datos.end());
}

// Funciones de ordenamiento

void seleccion(vector<int>& datos) {
    for (size_t i = 0; i < datos.size() - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < datos.size(); ++j)
            if (datos[j] < datos[min_idx])
                min_idx = j;
        swap(datos[i], datos[min_idx]);
    }
}

void shell(vector<int>& datos) {
    size_t n = datos.size();
    for (size_t intervalo = n / 2; intervalo > 0; intervalo /= 2) {
        for (size_t i = intervalo; i < n; ++i) {
            int temp = datos[i];
            size_t j;
            for (j = i; j >= intervalo && datos[j - intervalo] > temp; j -= intervalo)
                datos[j] = datos[j - intervalo];
            datos[j] = temp;
        }
    }
}

void monticulos(vector<int>& datos) {
    make_heap(datos.begin(), datos.end());
    sort_heap(datos.begin(), datos.end());
}

void rapido(vector<int>& datos) {
    function<void(int, int)> quicksort = [&](int bajo, int alto) {
        if (bajo < alto) {
            int pivote = datos[alto];
            int i = bajo - 1;
            for (int j = bajo; j < alto; ++j) {
                if (datos[j] < pivote) {
                    ++i;
                    swap(datos[i], datos[j]);
                }
            }
            swap(datos[i + 1], datos[alto]);
            int pi = i + 1;
            quicksort(bajo, pi - 1);
            quicksort(pi + 1, alto);
        }
    };
    quicksort(0, datos.size() - 1);
}

void burbuja(vector<int>& datos) {
    for (size_t i = 0; i < datos.size(); ++i)
        for (size_t j = 0; j < datos.size() - i - 1; ++j)
            if (datos[j] > datos[j + 1])
                swap(datos[j], datos[j + 1]);
}

void burbuja_bidireccional(vector<int>& datos) {
    size_t inicio = 0, fin = datos.size() - 1;
    bool intercambio;
    do {
        intercambio = false;
        for (size_t i = inicio; i < fin; ++i)
            if (datos[i] > datos[i + 1]) {
                swap(datos[i], datos[i + 1]);
                intercambio = true;
            }
        if (!intercambio) break;
        intercambio = false;
        --fin;
        for (size_t i = fin; i > inicio; --i)
            if (datos[i] < datos[i - 1]) {
                swap(datos[i], datos[i - 1]);
                intercambio = true;
            }
        ++inicio;
    } while (intercambio);
}

void insercion(vector<int>& datos) {
    for (size_t i = 1; i < datos.size(); ++i) {
        int clave = datos[i];
        int j = i - 1;
        while (j >= 0 && datos[j] > clave) {
            datos[j + 1] = datos[j];
            j--;
        }
        datos[j + 1] = clave;
    }
}

void mezcla(vector<int>& datos) {
    if (datos.size() <= 1) return;
    auto fusionar = [](vector<int>& a, vector<int>& izq, vector<int>& der) {
        a.clear();
        size_t i = 0, j = 0;
        while (i < izq.size() && j < der.size())
            a.push_back(izq[i] < der[j] ? izq[i++] : der[j++]);
        while (i < izq.size()) a.push_back(izq[i++]);
        while (j < der.size()) a.push_back(der[j++]);
    };
    function<void(vector<int>&)> ordenar_mezcla = [&](vector<int>& a) {
        if (a.size() <= 1) return;
        size_t mitad = a.size() / 2;
        vector<int> izq(a.begin(), a.begin() + mitad);
        vector<int> der(a.begin() + mitad, a.end());
        ordenar_mezcla(izq);
        ordenar_mezcla(der);
        fusionar(a, izq, der);
    };
    ordenar_mezcla(datos);
}

void cuentas(vector<int>& datos) {
    if (datos.empty()) return;
    int maximo = *max_element(datos.begin(), datos.end());
    vector<int> conteo(maximo + 1, 0);
    for (int valor : datos) conteo[valor]++;
    size_t idx = 0;
    for (int i = 0; i <= maximo; ++i)
        while (conteo[i]-- > 0)
            datos[idx++] = i;
}

void casilleros(vector<int>& datos) {
    if (datos.empty()) return;
    int maximo = *max_element(datos.begin(), datos.end());
    int n = datos.size();
    vector<vector<int>> cubetas(n);
    for (int valor : datos) {
        int indice = (1.0 * valor / (maximo + 1)) * n;
        cubetas[indice].push_back(valor);
    }
    datos.clear();
    for (auto& cubeta : cubetas) {
        sort(cubeta.begin(), cubeta.end());
        datos.insert(datos.end(), cubeta.begin(), cubeta.end());
    }
}

struct Nodo {
    int valor;
    Nodo* izq;
    Nodo* der;
    Nodo(int v) : valor(v), izq(nullptr), der(nullptr) {}
};

void insertar(Nodo*& raiz, int valor) {
    if (!raiz) raiz = new Nodo(valor);
    else if (valor < raiz->valor) insertar(raiz->izq, valor);
    else insertar(raiz->der, valor);
}

void recorrido_inorden(Nodo* raiz, vector<int>& datos) {
    if (!raiz) return;
    recorrido_inorden(raiz->izq, datos);
    datos.push_back(raiz->valor);
    recorrido_inorden(raiz->der, datos);
}

void arbol_binario(vector<int>& datos) {
    Nodo* raiz = nullptr;
    for (int valor : datos) insertar(raiz, valor);
    vector<int> resultado;
    recorrido_inorden(raiz, resultado);
    datos = resultado;
}

void radix(vector<int>& datos) {
    if (datos.empty()) return;
    int maximo = *max_element(datos.begin(), datos.end());
    for (int exp = 1; maximo / exp > 0; exp *= 10) {
        vector<int> salida(datos.size());
        vector<int> conteo(10, 0);
        for (int valor : datos) conteo[(valor / exp) % 10]++;
        for (int i = 1; i < 10; ++i) conteo[i] += conteo[i - 1];
        for (int i = datos.size() - 1; i >= 0; --i) {
            int digito = (datos[i] / exp) % 10;
            salida[--conteo[digito]] = datos[i];
        }
        datos = salida;
    }
}

int main() {
    vector<int> base_10, base_100, base_1000, base_10000, base_100000, base_1000000;
    generar_datos(base_10, 10);
    generar_datos(base_100, 100);
    generar_datos(base_1000, 1000);
    generar_datos(base_10000, 10000);
    generar_datos(base_100000, 100000);
    generar_datos(base_1000000, 1000000);

    map<string, function<void(vector<int>&)>> algoritmos = {
        {"Burbuja (Bubble Sort)", burbuja},
        {"Burbuja Bidireccional (Cocktail Sort)", burbuja_bidireccional},
        {"Casilleros (Bucket Sort)", casilleros},
        {"Cuentas (Counting Sort)", cuentas},
        {"Inserción (Insertion Sort)", insercion},
        {"Mezcla (Merge Sort)", mezcla},
        {"Selección (Selection Sort)", seleccion},
        {"Montículos (Heap Sort)", monticulos},
        {"Rápido (Quick Sort)", rapido},
        {"Arbol Binario (Binary Tree Sort)", arbol_binario},
        {"Radix (Radix Sort)", radix},
        {"Concha (Shell Sort)", shell},
        {"std::sort (usually Introsort)", ordenar_std},
    };

    vector<tuple<string, string, string, string, string, string, string>> resultados; // contiene: nombre, t10, t100, t1k, t10k, t100k, t1m
    for (const auto& [nombre, algoritmo] : algoritmos) {
        cout << "Ejecutando: " << nombre << endl;

        string t10, t100, t1000, t10000, t100000, t1000000;
        bool salto = false;

        cout << "  Ejecutando algoritmo para i10" << endl;
        int t10_us = medir_tiempo(algoritmo, base_10, nombre);
        t10 = formato_tiempo(t10_us);
        if (t10_us > 5'000'000) salto = true;

        if (!salto) {
            cout << "  Ejecutando algoritmo para i100" << endl;
            int t100_us = medir_tiempo(algoritmo, base_100, nombre);
            t100 = formato_tiempo(t100_us);
            if (t100_us > 5'000'000) salto = true;
        } else t100 = ">5s";

        if (!salto) {
            cout << "  Ejecutando algoritmo para i1k" << endl;
            int t1000_us = medir_tiempo(algoritmo, base_1000, nombre);
            t1000 = formato_tiempo(t1000_us);
            if (t1000_us > 5'000'000) salto = true;
        } else t1000 = ">5s";

        if (!salto) {
            cout << "  Ejecutando algoritmo para i10k" << endl;
            int t10000_us = medir_tiempo(algoritmo, base_10000, nombre);
            t10000 = formato_tiempo(t10000_us);
            if (t10000_us > 5'000'000) salto = true;
        } else t10000 = ">5s";

        if (!salto) {
            cout << "  Ejecutando algoritmo para i100k" << endl;
            int t100000_us = medir_tiempo(algoritmo, base_100000, nombre);
            t100000 = formato_tiempo(t100000_us);
            if (t100000_us > 5'000'000) salto = true;
        } else t100000 = ">5s";

        if (!salto) {
            cout << "  Ejecutando algoritmo para i1m" << endl;
            int t1000000_us = medir_tiempo(algoritmo, base_1000000, nombre);
            t1000000 = formato_tiempo(t1000000_us);
        } else t1000000 = ">5s";

        resultados.emplace_back(nombre, t10, t100, t1000, t10000, t100000, t1000000);
    }

    cout << "\n\nRESULTADOS COMPARATIVOS (tiempos):" << endl;
    cout << left << setw(40) << "Algoritmo"
         << right << setw(15) << "i10"
         << setw(15) << "i100"
         << setw(15) << "i1k"
         << setw(15) << "i10k"
         << setw(15) << "i100k"
         << setw(15) << "i1m" << endl;
    cout << string(130, '-') << endl;

    for (const auto& [nombre, t10, t100, t1000, t10000, t100000, t1000000] : resultados) {
        cout << left << setw(40) << nombre
             << right << setw(15) << t10
             << setw(15) << t100
             << setw(15) << t1000
             << setw(15) << t10000
             << setw(15) << t100000
             << setw(15) << t1000000 << endl;
    }
        
    return 0;
}
