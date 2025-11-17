// en este archivo se implementa un suffix array sin usar estructuras de la stl
// solo se utilizan arreglos y funciones auxiliares propias
// esta implementación sirve como ejemplo práctico de la definición formal
// presentada en el informe: un arreglo que contiene una permutación de las
// posiciones de inicio de todos los sufijos de un texto, ordenados
// lexicográficamente (manber y myers, 1993; gusfield, 1997)

#include <iostream>
using namespace std;

// estructura que representa un sufijo mediante un puntero al texto original y su posición de inicio
// esto corresponde a la definición de sufijo si = sisi+1...sn del informe
// donde cada sufijo se identifica por su posición inicial en el texto
struct sufijo {
    const char* texto;   // puntero al inicio del texto completo
    int posicion;        // posición donde comienza este sufijo en el texto
};

// función auxiliar para obtener la longitud de una cadena terminada en '\0'
int longitud_cadena(const char* cadena) {
    int n = 0;
    while (cadena[n] != '\0') {
        n++;
    }
    return n;
}

// comparación lexicográfica entre dos sufijos
// retorna un valor negativo si a < b, cero si son iguales, positivo si a > b
// esta comparación implementa el orden lexicográfico descrito en el informe
// (crochemore, hancart y lecroq, 2007), que se usa para ordenar los sufijos
int comparar_sufijos(const sufijo& a, const sufijo& b) {
    const char* s1 = a.texto + a.posicion;
    const char* s2 = b.texto + b.posicion;

    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] < s2[i]) return -1;
        if (s1[i] > s2[i]) return 1;
        i++;
    }

    // si uno termina antes que el otro, el más corto es menor
    if (s1[i] == '\0' && s2[i] == '\0') return 0;
    if (s1[i] == '\0') return -1;
    return 1;
}

// función para intercambiar dos sufijos en un arreglo
void intercambiar_sufijos(sufijo& a, sufijo& b) {
    sufijo temp = a;
    a = b;
    b = temp;
}

// partición para quicksort sobre el arreglo de sufijos
int particion(sufijo* arr, int inicio, int fin) {
    sufijo pivote = arr[fin];
    int i = inicio - 1;

    for (int j = inicio; j <= fin - 1; j++) {
        if (comparar_sufijos(arr[j], pivote) <= 0) {
            i++;
            intercambiar_sufijos(arr[i], arr[j]);
        }
    }

    intercambiar_sufijos(arr[i + 1], arr[fin]);
    return i + 1;
}

// quicksort para ordenar los sufijos de manera lexicográfica
void quicksort_sufijos(sufijo* arr, int inicio, int fin) {
    if (inicio < fin) {
        int p = particion(arr, inicio, fin);
        quicksort_sufijos(arr, inicio, p - 1);
        quicksort_sufijos(arr, p + 1, fin);
    }
}

// función para construir el suffix array a partir de un texto dado como arreglo de chars
// el resultado se guarda en el arreglo "suffix_array" de tamaño n
// esta función construye exactamente la estructura definida en el informe:
// un arreglo sa[0..n-1] que contiene una permutación de {0..n-1}, tal que
// los sufijos t[sa[i]..n-1] están ordenados lexicográficamente
// aquí se usa un ordenamiento tipo quicksort, no un algoritmo específico
// como manber y myers o sa-is; por lo tanto la complejidad de construcción
// es más alta que o(n log n), pero la idea conceptual del suffix array es la misma
void construir_suffix_array(const char* texto, int* suffix_array) {
    int n = longitud_cadena(texto);

    // crear un arreglo de estructuras sufijo
    sufijo* lista_sufijos = new sufijo[n];

    // generar todos los sufijos del texto
    // cada sufijo se representa por su posición inicial en el texto
    for (int i = 0; i < n; i++) {
        lista_sufijos[i].texto = texto;
        lista_sufijos[i].posicion = i;
    }

    // ordenar los sufijos lexicográficamente usando quicksort propio
    quicksort_sufijos(lista_sufijos, 0, n - 1);

    // extraer las posiciones ya ordenadas y guardarlas en suffix_array
    for (int i = 0; i < n; i++) {
        suffix_array[i] = lista_sufijos[i].posicion;
    }

    // liberar la memoria del arreglo de sufijos
    delete[] lista_sufijos;
}

// función auxiliar para comparar un patrón con un sufijo que comienza en una posición dada
// retorna un valor negativo si el sufijo es menor que el patrón, cero si el patrón coincide
// al inicio del sufijo, positivo si el sufijo es mayor que el patrón
// esta función se usa durante la búsqueda binaria para comparar el patrón p
// con el sufijo t[sa[i]..n-1], tal como se describe en la sección de definiciones
int comparar_patron_con_sufijo(const char* texto, int posicion_sufijo, const char* patron) {
    int i = 0;
    while (texto[posicion_sufijo + i] != '\0' && patron[i] != '\0') {
        if (texto[posicion_sufijo + i] < patron[i]) return -1;
        if (texto[posicion_sufijo + i] > patron[i]) return 1;
        i++;
    }

    // si se consumió todo el patrón, hay coincidencia al inicio del sufijo
    if (patron[i] == '\0') return 0;

    // si el texto terminó antes que el patrón, el sufijo es menor
    if (texto[posicion_sufijo + i] == '\0') return -1;

    return 1;
}

// función para buscar un patrón dentro del texto usando el suffix array
// se realiza una búsqueda binaria sobre los sufijos
// esta operación implementa la búsqueda de patrones descrita en el informe:
// mediante búsqueda binaria sobre los sufijos ordenados se obtiene una
// complejidad de o(m log n), donde m es la longitud del patrón y n la
// longitud del texto (manber y myers, 1993; abouelhoda et al., 2004)
bool buscar_patron(const char* texto, int* suffix_array, int n, const char* patron) {
    int izquierda = 0;
    int derecha = n - 1;

    while (izquierda <= derecha) {
        int medio = (izquierda + derecha) / 2;
        int posicion_sufijo = suffix_array[medio];

        int comparacion = comparar_patron_con_sufijo(texto, posicion_sufijo, patron);

        if (comparacion == 0) {
            cout << "patron encontrado en la posicion: " << posicion_sufijo << "\n";
            return true;
        } else if (comparacion < 0) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }

    cout << "patron no encontrado en el texto\n";
    return false;
}

int main() {
    // texto de ejemplo terminado en '\0'
    // en el informe se usa el ejemplo t = "banana" para ilustrar la
    // definición del suffix array; aquí se utiliza el mismo texto para
    // que el resultado del programa sea consistente con esa explicación
    const char texto[] = "banana";

    // patrón de ejemplo a buscar dentro del texto
    const char patron[] = "ana";

    // obtener longitud del texto
    int n = longitud_cadena(texto);

    // arreglo para guardar el suffix array (mismas posiciones que el texto)
    // esto representa la estructura estática descrita en el informe: una vez
    // construido este arreglo no se actualiza dinámicamente; si el texto
    // cambiara, sería necesario reconstruir todo el suffix array
    int* suffix_array = new int[n];

    // construir el suffix array
    construir_suffix_array(texto, suffix_array);

    // mostrar el texto original
    cout << "texto original: " << texto << "\n\n";

    // mostrar los sufijos ordenados junto con su posicion original
    // esta salida permite verificar manualmente la definición formal del sa:
    // se debe obtener una permutación de las posiciones del texto tal que
    // los sufijos aparezcan en orden lexicográfico, como en el ejemplo de
    // "banana" del informe (con índices adaptados a base 0)
    cout << "suffix array construido:" << "\n";
    for (int i = 0; i < n; i++) {
        int pos = suffix_array[i];
        cout << i << ": " << (texto + pos) << " | posicion original = " << pos << "\n";
    }

    cout << "\n" << "buscando patron \"" << patron << "\"..." << "\n";
    buscar_patron(texto, suffix_array, n, patron);

    // liberar memoria del suffix array
    delete[] suffix_array;

    return 0;
}