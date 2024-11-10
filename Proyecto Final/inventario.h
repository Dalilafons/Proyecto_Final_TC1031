/*
 * inventario.h
 *
 *  Created on: 19/10/2024
 *      Author: Dalila Fonseca Maya A01711722
 */

#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <iostream>
#include <vector>

#include "pelicula.h"

/*
 * limpiarEspacios() - Función auxiliar para eliminar espacios.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: La función elimina espacios en blanco del inicio y final de una cadena. Recorre la cadena una vez
 * para encontrar la primera y la última posición de un carácter no-espacio, por lo que la complejidad es lineal respecto al tamaño de la cadena.
 */
std::string limpiarEspacios(const std::string& str) 
{
    std::string resultado = str;

    // Eliminar espacios al inicio y al final de la cadena.
    resultado.erase(0, resultado.find_first_not_of(" \t\n\r\f\v"));
    resultado.erase(resultado.find_last_not_of(" \t\n\r\f\v") + 1);

    return resultado;
}

class Inventario
{
    private:
        // Vector que contiene las películas.
        std::vector<Pelicula> peliculas;

        // Métodos privados para ordenar.
        void copyArray(std::vector<Pelicula> &A, 
                       std::vector<Pelicula> &B, int low, int high);
        void mergeSplitLanzamiento(std::vector<Pelicula>& A, 
                                   std::vector<Pelicula>& B, int low, int high);
        void mergeSplitDuracion(std::vector<Pelicula>& A, 
                                   std::vector<Pelicula>& B, int low, int high); 
        void mergeSplitTitulo(std::vector<Pelicula>& A, 
                                   std::vector<Pelicula>& B, int low, int high);                       
        void mergeArrayLanzamiento(std::vector<Pelicula>& A, 
                          std::vector<Pelicula>& B, int low, int mid, int high);
        void mergeArrayDuracion(std::vector<Pelicula>& A, 
                          std::vector<Pelicula>& B, int low, int mid, int high);
        void mergeArrayTitulo(std::vector<Pelicula>& A, 
                          std::vector<Pelicula>& B, int low, int mid, int high);

    public:
        void agregarPelicula(const Pelicula& pelicula);
        void mostrarPeliculas() const;
        void ordenarPorLanzamiento();
        void ordenarPorDuracion();
        void ordenarPorTitulo();
        void eliminarPelicula(const std::string& titulo );
        const std::vector<Pelicula>& getPeliculas() const;
};

/*
 * copyArray() - Copia elementos de un vector a otro en un rango específico.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Copia los elementos desde el índice `low` hasta `high` de un vector a otro.
 * La complejidad es O(n) porque en el peor de los casos recorre `n` elementos dentro del rango especificado.
 */
void Inventario::copyArray(std::vector<Pelicula> &A, 
                           std::vector<Pelicula> &B, int low, int high)
    {
        for (int i = low; i <= high; i++) 
        {
            A[i] = B[i];
        }
    }

/*
 * mergeSplitLanzamiento() - Divide el vector para ordenar por lanzamiento usando Merge Sort.
 * Complejidad temporal:
 * - Mejor caso: O(n log n)
 * - Caso promedio: O(n log n)
 * - Peor caso: O(n log n)
 * Descripción: Esta función implementa la parte de división de Merge Sort. Cada llamada recursiva divide el vector en dos mitades,
 * realizando `log n` divisiones y fusionando en O(n) para lograr una complejidad total de O(n log n).
 */
void Inventario::mergeSplitLanzamiento(std::vector<Pelicula>& A, 
                            std::vector<Pelicula>& B, int low, int high)
    {
        if(low < high)
        {
            int mid = (high + low) / 2;
		    //mergeSplit de la primera mitad.
	        mergeSplitLanzamiento(A,B,low,mid);

	        //mergeSplit de la segunda mitad.
	        mergeSplitLanzamiento(A,B,mid + 1, high);

	        //mergeArray de ambas mitades.
	        mergeArrayLanzamiento(A,B,low, mid,high);
        }
    }

/*
 * mergeSplitDuracion() - Divide el vector para ordenar por duración usando Merge Sort.
 * Complejidad temporal:
 * - Mejor caso: O(n log n)
 * - Caso promedio: O(n log n)
 * - Peor caso: O(n log n)
 * Descripción: Similar a `mergeSplitLanzamiento`, esta función divide el vector por duración y alcanza complejidad O(n log n) por las divisiones y fusiones.
 */
void Inventario::mergeSplitDuracion(std::vector<Pelicula>& A, 
                            std::vector<Pelicula>& B, int low, int high)
    {
        if(low < high)
        {
            int mid = (high + low) / 2;
		    //mergeSplit de la primera mitad.
	        mergeSplitDuracion(A,B,low,mid);

	        //mergeSplit de la segunda mitad.
	        mergeSplitDuracion(A,B,mid + 1, high);

	        //mergeArray de ambas mitades.
	        mergeArrayDuracion(A,B,low, mid,high);
        }
    }

/*
 * mergeSplitTitulo() - Divide el vector para ordenar por título usando Merge Sort.
 * Complejidad temporal:
 * - Mejor caso: O(n log n)
 * - Caso promedio: O(n log n)
 * - Peor caso: O(n log n)
 * Descripción: Realiza divisiones para ordenar por título en tiempo O(n log n), dividiendo en `log n` niveles y fusionando en cada nivel en O(n).
 */
void Inventario::mergeSplitTitulo(std::vector<Pelicula>& A, 
                            std::vector<Pelicula>& B, int low, int high)
    {
        if(low < high)
        {
            int mid = (high + low) / 2;
		    //mergeSplit de la primera mitad.
	        mergeSplitTitulo(A,B,low,mid);

	        //mergeSplit de la segunda mitad.
	        mergeSplitTitulo(A,B,mid + 1, high);

	        //mergeArray de ambas mitades.
	        mergeArrayTitulo(A,B,low, mid,high);
        }
    }

/*
 * mergeArrayLanzamiento() - Fusiona dos mitades ordenadas por año de lanzamiento.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Fusiona dos mitades ordenadas de `A` en `B`. La complejidad es O(n) porque recorre todos los elementos en el rango de fusión una sola vez.
 */
void Inventario::mergeArrayLanzamiento(std::vector<Pelicula>& A, 
                    std::vector<Pelicula>& B, int low, int mid, int high)
    {
        int i = low;
        int j = mid + 1;
	    int k = low;
	        
        while (i <= mid && j <= high) 
        {
            if (A[i].getLanzamiento() <= A[j].getLanzamiento()) 
            {
                B[k] = A[i];
                i++;
            } 

            else 
            {
                B[k] = A[j];
                j++;
            }

            k++;
        }

        // Copiar los elementos restantes de la primera mitad.
        while (i <= mid) 
        {
            B[k] = A[i];
            i++;
            k++;
        } 
            
        // Copiar los elementos restantes de la segunda mitad.
        while (j <= high) 
        {
            B[k] = A[j];
            j++;
            k++;
        }

        // Copiar la fusión de nuevo al array original.
        copyArray(A, B, low, high);
    }

/*
 * mergeArrayDuracion() - Fusiona dos mitades ordenadas por duración.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Fusiona dos mitades ordenadas de `A` en `B` por duración. La complejidad es O(n), ya que el algoritmo recorre cada elemento una sola vez.
 */
void Inventario::mergeArrayDuracion(std::vector<Pelicula>& A, 
                    std::vector<Pelicula>& B, int low, int mid, int high)
    {
        int i = low;
        int j = mid + 1;
	    int k = low;
	        
        while (i <= mid && j <= high) 
        {
            if (A[i].getDuracion() <= A[j].getDuracion()) 
            {
                B[k] = A[i];
                i++;
            } 

            else 
            {
                B[k] = A[j];
                j++;
            }

            k++;
        }

        // Copiar los elementos restantes de la primera mitad.
        while (i <= mid) 
        {
            B[k] = A[i];
            i++;
            k++;
        } 
            
        // Copiar los elementos restantes de la segunda mitad.
        while (j <= high) 
        {
            B[k] = A[j];
            j++;
            k++;
        }

        // Copiar la fusión de nuevo al array original.
        copyArray(A, B, low, high);
    }

/*
 * mergeArrayTitulo() - Fusiona dos mitades ordenadas por título.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Fusiona dos mitades ordenadas por título de `A` en `B`. La operación tiene complejidad O(n) debido a la comparación y copia secuencial.
 */
void Inventario::mergeArrayTitulo(std::vector<Pelicula>& A, 
                    std::vector<Pelicula>& B, int low, int mid, int high)
    {
        int i = low;
        int j = mid + 1;
	    int k = low;
	        
        while (i <= mid && j <= high) 
        {
            if (A[i].getTitulo() <= A[j].getTitulo()) 
            {
                B[k] = A[i];
                i++;
            } 

            else 
            {
                B[k] = A[j];
                j++;
            }

            k++;
        }

        // Copiar los elementos restantes de la primera mitad.
        while (i <= mid) 
        {
            B[k] = A[i];
            i++;
            k++;
        } 
            
        // Copiar los elementos restantes de la segunda mitad.
        while (j <= high) 
        {
            B[k] = A[j];
            j++;
            k++;
        }

        // Copiar la fusión de nuevo al array original.
        copyArray(A, B, low, high);
    }

/*
 * agregarPelicula() - Agrega una película al vector.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(n) (si el vector necesita redimensionarse)
 * Descripción: Inserta una película al final del vector. En el caso promedio y mejor caso, es una operación de tiempo constante.
 * Sin embargo, si el vector necesita redimensionarse, puede tener una complejidad de O(n) debido a la reasignación de memoria y copia de elementos.
 */
void Inventario::agregarPelicula(const Pelicula& pelicula)
    {
        peliculas.push_back(pelicula);
    }

/*
 * mostrarPeliculas() - Muestra todas las películas en el inventario.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Recorre el vector de películas y muestra la información de cada una, lo que requiere tiempo lineal O(n) respecto al número de películas.
 */
void Inventario::mostrarPeliculas() const
    {
        for (const auto& pelicula : peliculas)
        {
            pelicula.mostrarInformacion();
            std::cout << "-------------------------" << std::endl;
        }
    }

// Ordenar por año de lanzamiento usando Merge Sort.
void Inventario::ordenarPorLanzamiento()
    {
        std::vector<Pelicula> tmp(peliculas.size());

        // Llama a mergeSplit para iniciar el proceso de ordenación.
        mergeSplitLanzamiento(peliculas, tmp, 0, peliculas.size() - 1);
    }

// Ordenar por duración usando Merge Sort.
void Inventario::ordenarPorDuracion()
    {
        std::vector<Pelicula> tmp(peliculas.size());

        // Llama a mergeSplit para iniciar el proceso de ordenación.
        mergeSplitDuracion(peliculas, tmp, 0, peliculas.size() - 1);
    }

// Ordenar por titulo usando Merge Sort.
void Inventario::ordenarPorTitulo()
    {
        std::vector<Pelicula> tmp(peliculas.size());

        // Llama a mergeSplit para iniciar el proceso de ordenación.
        mergeSplitTitulo(peliculas, tmp, 0, peliculas.size() - 1);
    }

/*
 * eliminarPelicula() - Elimina una película por título.
 * Complejidad temporal:
 * - Mejor caso: O(n) (si la primera película coincide con el título)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Usa std::remove_if para recorrer el vector y eliminar la película que coincida con el título. Esto requiere O(n) en promedio, ya que necesita evaluar cada elemento.
 */
void Inventario::eliminarPelicula(const std::string& titulo) 
{
    peliculas.erase(std::remove_if(peliculas.begin(), peliculas.end(),
                                   [&titulo](const Pelicula& p) 
                                   {
                                       return p.getTitulo() == titulo;
                                   }),
                    peliculas.end());
}

/*
 * getPeliculas() - Retorna el vector de películas.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Regresa una referencia al vector de películas sin realizar copias, por lo que tiene una complejidad de tiempo constante O(1).
 */
const std::vector<Pelicula>& Inventario::getPeliculas() const 
{
    return peliculas;
}

#endif // INVENTARIO_H