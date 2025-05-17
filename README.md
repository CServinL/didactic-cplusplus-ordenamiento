# didactic-cplusplus-ordenamiento
Fundamentos - Algoritmos - C++ - Algoritmos de Ordenamiento

Implementaciones en C++ de los algoritmos tradicionales para listas de enteros (`uniform_int_distribution<> distribucion(0, 100000);`) y realiza una comparativa del rendimiento de cada uno de ellos.

Cabe mencionar que este es el caso ideal para el Cuentas (Counting Sort).

Cuando algun algoritmo tarda mas de 5 segundos en regresar, ya no se intentan hacer pruebas con mas data, y solo se reporta como >5s. Ya que el tiempo es muy grande, pero si se quiere se puede quitar esa restriccion y dejar que corra el tiempo que sea.

`std::chrono::high_resolution_clock` no garantiza precisión de microsegundos en todos los sistemas. Por este motivo las pruebas mas cortas son tan cortas que no son medibles en algunos sistemas. Se reportan como `0 µs`.

En mis pruebas:

| Algoritmo                                      | i10   | i100  | i1k     | i10k    | i100k   | i1m      |
|-----------------------------------------------|-------|-------|---------|---------|---------|----------|
| Árbol Binario (Binary Tree Sort)              | 3 µs  | 9 µs  | 124 µs  | 1.77 ms | 24.10 ms| 674.38 ms|
| Burbuja (Bubble Sort)                         | 0 µs  | 39 µs | 3.24 ms | 367.05 ms| 35.90 s | >5s      |
| Burbuja Bidireccional (Cocktail Sort)         | 0 µs  | 32 µs | 2.73 ms | 285.64 ms| 25.47 s | >5s      |
| Casilleros (Bucket Sort)                      | 5 µs  | 26 µs | 236 µs  | 2.43 ms | 26.68 ms| 206.00 ms|
| Concha (Shell Sort)                           | 0 µs  | 6 µs  | 97 µs   | 1.53 ms | 22.91 ms| 319.42 ms|
| Cuentas (Counting Sort)                       |170 µs |161 µs | 186 µs  | 386 µs  | 1.77 ms | 10.80 ms |
| Inserción (Insertion Sort)                    | 0 µs  | 8 µs  | 665 µs  | 66.60 ms| 6.39 s  | >5s      |
| Mezcla (Merge Sort)                           | 6 µs  | 29 µs | 309 µs  | 3.65 ms | 40.86 ms| 422.34 ms|
| Montículos (Heap Sort)                        | 2 µs  | 17 µs | 209 µs  | 2.65 ms | 31.96 ms| 379.46 ms|
| Radix (Radix Sort)                            | 4 µs  | 8 µs  | 52 µs   | 530 µs  | 5.83 ms | 61.36 ms |
| Rápido (Quick Sort)                           | 2 µs  | 9 µs  | 115 µs  | 1.41 ms | 16.78 ms| 196.39 ms|
| Selección (Selection Sort)                    | 0 µs  | 16 µs | 1.22 ms |116.30 ms| 8.86 s  | >5s      |
| std::sort (usually Introsort)                 | 1 µs  | 8 µs  | 111 µs  | 1.33 ms | 15.73 ms| 179.36 ms|

Al final comparamos con el sort que la mayoria de los desarrolladores va a utilizar en la practia el std::sort.

GeeksforGeeks. (2024, marzo 11). IntroSort or Introspective sort. https://www.geeksforgeeks.org/introsort-or-introspective-sort/

Ligas a la Wikipedia sobre cada algoritmo

- [Árbol Binario (Binary Tree Sort)](https://en.wikipedia.org/wiki/Tree_sort)
- [Burbuja (Bubble Sort)](https://es.wikipedia.org/wiki/Ordenamiento_de_burbuja)
- [Burbuja Bidireccional (Cocktail Sort)](https://en.wikipedia.org/wiki/Cocktail_shaker_sort)
- [Casilleros (Bucket Sort)](https://en.wikipedia.org/wiki/Bucket_sort)
- [Concha (Shell Sort)](https://es.wikipedia.org/wiki/Ordenamiento_Shell)
- [Cuentas (Counting Sort)](https://en.wikipedia.org/wiki/Counting_sort)
- [Inserción (Insertion Sort)](https://es.wikipedia.org/wiki/Ordenamiento_por_inserción)
- [Mezcla (Merge Sort)](https://es.wikipedia.org/wiki/Ordenamiento_por_mezcla)
- [Montículos (Heap Sort)](https://es.wikipedia.org/wiki/Ordenamiento_por_montículo)
- [Radix (Radix Sort)](https://en.wikipedia.org/wiki/Radix_sort)
- [Rápido (Quick Sort)](https://es.wikipedia.org/wiki/Ordenamiento_rápido)
- [Selección (Selection Sort)](https://es.wikipedia.org/wiki/Ordenamiento_por_selección)
- [std::sort (usually Introsort)](https://en.wikipedia.org/wiki/Introsort)

Graficas comparativas en carpeta graphs
