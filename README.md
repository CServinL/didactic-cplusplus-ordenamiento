# didactic-cplusplus-ordenamiento
Fundamentos - Algoritmos - C++ - Algoritmos de Ordenamiento

Implementaciones en C++ de los algoritmos tradicionales para listas de enteros (`uniform_int_distribution<> distribucion(0, 100000);`) y realiza una comparativa del rendimiento de cada uno de ellos.

Cabe mencionar que este es el caso ideal para el Cuentas (Counting Sort).

En mis pruebas:

| Algoritmo                                 | i10 | i100 | i1k  | i10k  | i100k    |
|-------------------------------------------|-----|------|------|-------|----------|
| Burbuja (Bubble Sort)                     | 1   | 58   | 3978 | 361833 | 34353344 |
| Burbuja Bidireccional (Cocktail Sort)     | 0   | 24   | 2506 | 257523 | 23422899 |
| Casilleros (Bucket Sort)                  | 7   | 24   | 225  | 2282   | 23048    |
| Cuentas (Counting Sort)                   | 165 | 158  | 209  | 393    | 1702     |
| Inserción (Insertion Sort)                | 0   | 7    | 685  | 67995  | 6605644  |
| Mezcla (Merge Sort)                       | 7   | 28   | 323  | 3692   | 41798    |
| Radix (Radix Sort)                        | 4   | 6    | 50   | 559    | 5095     |
| Árbol Binario (Binary Tree Sort)          | 3   | 8    | 102  | 1484   | 23892    |
| std::sort (usually Introsort)             | 1   | 9    | 102  | 1355   | 16024    |

Al final comparamos con el sort que la mayoria de los desarrolladores va a utilizar en la practia el std::sort.

GeeksforGeeks. (2024, marzo 11). IntroSort or Introspective sort. https://www.geeksforgeeks.org/introsort-or-introspective-sort/

Ligas a la Wikipedia sobre cada algoritmo

* Burbuja (Bubble Sort): https://en.wikipedia.org/wiki/Bubble_sort
* Burbuja Bidireccional (Cocktail Shaker Sort): https://en.wikipedia.org/wiki/Cocktail_shaker_sort
* Casilleros (Bucket Sort): https://en.wikipedia.org/wiki/Bucket_sort
* Cuentas (Counting Sort): https://en.wikipedia.org/wiki/Counting_sort
* Inserción (Insertion Sort): https://en.wikipedia.org/wiki/Insertion_sort
* Mezcla (Merge Sort): https://en.wikipedia.org/wiki/Merge_sort
* Radix (Radix Sort): https://en.wikipedia.org/wiki/Radix_sort
* Árbol Binario (Binary Tree Sort): https://en.wikipedia.org/wiki/Tree_sort
* std::sort (Introsort): https://en.wikipedia.org/wiki/Introsort