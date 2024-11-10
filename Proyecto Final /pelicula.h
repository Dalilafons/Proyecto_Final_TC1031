/*
 * pelicula.h
 *
 *  Created on: 19/10/2024
 *      Author: Dalila Fonseca Maya A01711722
 */

#ifndef PELICULA_H
#define PELICULA_H

#include <iostream>
#include <string>
#include <algorithm> 

class Pelicula
{
    // Variables de instancia (atributos de la película).
    protected:
        std::string titulo;
        std::string director;
        std::string genero;
        int lanzamiento;
        int duracion;

    // Métodos de Pelicula (funciones).
    public:
        Pelicula();
        Pelicula(std::string titulo_1, std::string director_1, std::string genero_1, int lanzamiento_1, int duracion_1);
        std::string getGenero() const;
        std::string getTitulo() const;
        std::string getDirector() const;
        int getLanzamiento() const;
        int getDuracion() const;
        void mostrarInformacion() const;
};  

/*
 * Pelicula() - Constructor por defecto.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Este constructor inicializa los atributos de la película a valores predeterminados sin realizar operaciones adicionales. 
 * La complejidad es O(1) ya que la asignación de valores a cada atributo es una operación de tiempo constante.
 */
Pelicula::Pelicula() 
    : titulo(""), director(""), genero(""), lanzamiento(0), duracion(0) {}

/*
 * Pelicula(string, string, string, int, int) - Constructor parametrizado.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Este constructor asigna valores iniciales a los atributos utilizando los parámetros proporcionados. 
 * La complejidad es O(1) porque solo asigna valores de los parámetros a los atributos de la clase, lo cual es una operación constante.
 */
Pelicula::Pelicula(std::string titulo_1, std::string director_1, 
                   std::string genero_1, int lanzamiento_1, int duracion_1)
    : titulo(titulo_1), director(director_1), genero(genero_1), 
      lanzamiento(lanzamiento_1), duracion(duracion_1) {}

/*
 * getGenero() const - Getter para el género.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: La función retorna directamente el valor del atributo 'genero'. 
 * Dado que solo accede a una variable miembro y no realiza cálculos adicionales, la complejidad es O(1).
 */
std::string Pelicula::getGenero() const 
    {
        return genero;
    }

/*
 * getTitulo() const - Getter para el título.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Esta función retorna el valor del atributo 'titulo'. 
 * La operación es directa y constante, ya que solo implica el acceso a un dato interno sin operaciones complejas.
 */
std::string Pelicula::getTitulo() const
    {
        return titulo;
    }

/*
 * getDirector() const - Getter para el director.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: La función devuelve directamente el valor del atributo 'director', por lo que su complejidad es constante.
 */
std::string Pelicula::getDirector() const 
{
    return director;
}

/*
 * getLanzamiento() const - Getter para el año de lanzamiento.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Retorna el valor del atributo 'lanzamiento'. No requiere cálculos ni accesos complejos, lo que la hace de tiempo constante.
 */        
int Pelicula::getLanzamiento() const
    {
        return lanzamiento;
    }

/*
 * getDuracion() const - Getter para la duración.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Esta función devuelve el valor de 'duracion', por lo que solo accede a un valor almacenado sin realizar otras operaciones.
 */
int Pelicula::getDuracion() const
    {
        return duracion;
    }

/*
 * mostrarInformacion() const - Muestra la información de la película.
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Imprime cada atributo de la película en la consola. Cada operación de impresión es de tiempo constante, 
 * por lo que esta función también tiene complejidad O(1) en cualquier caso.
 */
void Pelicula::mostrarInformacion() const
    {
        std::cout << "Titulo: " << titulo << std::endl;
        std::cout << "Director: " << director << std::endl;
        std::cout << "Genero: " << genero << std::endl;
        std::cout << "Anio de lanzamiento: " << lanzamiento << std::endl;
        std::cout << "Duracion: " << duracion << std::endl;
    }

#endif // PELICULA_H
