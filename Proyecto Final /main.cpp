/*
 * main.cpp
 *
 *  Created on: 09/11/2024
 *      Author: Dalila Fonseca Maya A01711722
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>

#include "pelicula.h"
#include "avl.h"
#include "inventario.h"

/*
 * guardarEnArchivo(const Inventario& inventario, const std::string& nombreArchivo) - Guarda el inventario en un archivo de texto.
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Esta función recorre el inventario y escribe cada película en el archivo. La complejidad es O(n) en todos los casos,
 * donde `n` es el número de películas en el inventario, ya que cada película se escribe secuencialmente.
 */
void guardarEnArchivo(const Inventario& inventario, const std::string& nombreArchivo) 
{
    std::ofstream archivo_salida(nombreArchivo);
    if (!archivo_salida.is_open()) 
    {
        std::cerr << "No se pudo abrir el archivo para escribir el inventario." << std::endl;
        return;
    }

    for (const auto& pelicula : inventario.getPeliculas()) 
    { 
        archivo_salida << pelicula.getTitulo() << ","
                       << pelicula.getDirector() << ","
                       << pelicula.getGenero() << ","
                       << pelicula.getLanzamiento() << ","
                       << pelicula.getDuracion() << "\n";
    }

    archivo_salida.close();
    std::cout << "Inventario guardado en el archivo con exito." << std::endl;
}

int main() 
{
    AVL<Pelicula> arbolPeliculas;
    Inventario inventario;


    std::ifstream archivo_entrada("Lista.txt");
    if (!archivo_entrada.is_open()) 
    {
        std::cout << "No se pudo abrir el archivo de peliculas." << std::endl;
        return 1;
    }

    std::string line;
    std::getline(archivo_entrada, line); 

    /*
    * Cargar películas desde "Lista.txt" en el `main` - Lee datos de un archivo para inicializar el inventario y el árbol AVL.
    * Complejidad temporal:
    * - Mejor caso: O(n)
    * - Caso promedio: O(n)
    * - Peor caso: O(n)
    * Descripción: Lee cada línea de "Lista.txt" y carga cada película en el inventario y el árbol AVL. La complejidad es O(n),
    * donde `n` es el número de líneas en el archivo, ya que se procesa cada línea una vez.
    */
    while (getline(archivo_entrada, line)) 
    {
        std::stringstream ss(line);
        std::string titulo, director, genero, lanzamiento_str, duracion_str;
        int lanzamiento, duracion;

        getline(ss, titulo, ',');
        getline(ss, director, ',');
        getline(ss, genero, ',');
        getline(ss, lanzamiento_str, ',');
        getline(ss, duracion_str, ',');

        lanzamiento = std::stoi(lanzamiento_str);
        duracion = std::stoi(duracion_str);

        Pelicula pelicula(titulo, director, genero, lanzamiento, duracion);
        inventario.agregarPelicula(pelicula);

        if (arbolPeliculas.findByTitle(titulo) == NULL) 
        {
            arbolPeliculas.add(pelicula);
        } 
    }
    archivo_entrada.close();  

    int opcion;
    std::string volverMenuPrincipal = "si";

    while (volverMenuPrincipal == "si")
    {
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "MOVIE SELECTOR" << std::endl;
        std::cout << "Menu principal: " << std::endl;
        std::cout << "1. Mostrar inventario de peliculas." << std::endl;
        std::cout << "2. Agregar pelicula." << std::endl;
        std::cout << "3. Ordenar inventario. " << std::endl;
        std::cout << "4. Buscar pelicula. " << std::endl;
        std::cout << "5. Eliminar pelicula. " << std::endl;
        std::cout << "6. Guardar inventario en archivo. " << std::endl;
        std::cout << "7. Salir. " << std::endl;
        std::cout << "Elige una opcion...";
        std::cin >> opcion;

        if (opcion == 1)
        {
            std::cout << "INVENTARIO--------------------------" << std::endl;
            std::cout << arbolPeliculas.inorder() << std::endl;
        }

        else if (opcion == 2)
        {
            std::string titulo, director, genero;
            int lanzamiento, duracion;

            std::cout << "\nAGREGAR PELICULA--------------------";
            std::cout << "\nRecuerda! al agregar una pelicula, no se guarda en el archivo InventarioPeliculas, si deseas guardarla, despues de agregarla, selecciona la opción 6";
            std::cout << "\nAgregar una nueva pelicula al inventario:\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Introduce el titulo de la pelicula: ";
            std::getline(std::cin, titulo);  

            std::cout << "Introduce el director de la pelicula: ";
            std::getline(std::cin, director);  

            std::cout << "Introduce el genero de la pelicula: ";
            std::getline(std::cin, genero);  

            std::cout << "Introduce el anio de lanzamiento: ";
            std::cin >> lanzamiento; 
            std::cin.ignore();

            std::cout << "Introduce la duracion en minutos: ";
            std::cin >> duracion;  
            std::cin.ignore();

            Pelicula nuevaPelicula(titulo, director, genero, lanzamiento, duracion);
            inventario.agregarPelicula(nuevaPelicula);

            if (arbolPeliculas.findByTitle(titulo) == NULL) 
            {
                arbolPeliculas.add(nuevaPelicula);
            } 
        }

        else if (opcion == 3) 
        {
            std::string VolverAOrdenar = "si";
            int criterio;
            
            while (VolverAOrdenar == "si")
            {
                std::cout << "\nORDENAR PELICULA----------------------\n";
                std::cout << "Elige el criterio de ordenamiento:" << std::endl;
                std::cout << "1. Por titulo." << std::endl;
                std::cout << "2. Por duracion." << std::endl;
                std::cout << "3. Por anio de lanzamiento." << std::endl;
                std::cin >> criterio;

                if (criterio == 1)
                {
                    inventario.ordenarPorTitulo();
                    std::cout << "Peliculas ordenadas por Titulo:" << std::endl;
                    inventario.mostrarPeliculas();
                }
                else if (criterio == 2)
                {
                    inventario.ordenarPorDuracion();
                    std::cout << "Peliculas ordenadas por Duracion:" << std::endl;
                    inventario.mostrarPeliculas();
                }
                else if (criterio == 3)
                {
                    inventario.ordenarPorLanzamiento();
                    std::cout << "Peliculas ordenadas por Lanzamiento:" << std::endl;
                    inventario.mostrarPeliculas();
                }
                else
                {
                    std::cout << "Criterio invalido." << std::endl;
                }

                if (volverMenuPrincipal != "no") 
                {
                    std::cout << "Deseas volver a ordenar? (si/no):";
                    std::cin >> VolverAOrdenar;
                    std::cin.ignore();
                }   
            } 
        }

        else if (opcion == 4)
        {
            std::string buscarTitulo;

            std::cout << "\nBUSCAR PELICULA-----------------------\n";
            std::cout << "Introduce el titulo de la pelicula a buscar: ";
            std::cin.ignore();  
            std::getline(std::cin, buscarTitulo);
    
            std::cout << "\nBuscando la pelicula \"" << buscarTitulo << "\" por titulo..." << std::endl;
            
            Pelicula* peliculaEncontrada = arbolPeliculas.findByTitle(buscarTitulo);
            
            if (peliculaEncontrada != NULL) 
            {
                std::cout << "La pelicula \"" << buscarTitulo << "\" fue encontrada." << std::endl;
                peliculaEncontrada->mostrarInformacion();  
            } 
            else 
            {
                std::cout << "La pelicula \"" << buscarTitulo << "\" no se encontro." << std::endl;
            }
        }

        else if (opcion == 5)
        {
            std::string eliminarTitulo;

            std::cout << "\nELIMINAR PELICULA-----------------------\n";
            std::cout << "\nRecuerda! Si eliminas una pelicula, no se actulizará el archivo InventarioPeliculas, por lo tanto después de eliminar una pelicula, ingresa la opción 6 en el menú.";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Introduce el titulo de la pelicula a eliminar: ";
            std::getline(std::cin, eliminarTitulo);  

            if (eliminarTitulo.empty()) 
            {
                std::cout << "Error: No se ingreso ningun titulo. Intentalo nuevamente." << std::endl;
            } 
            else 
            {
                std::cout << "\nEliminando la pelicula \"" << eliminarTitulo << "\"..." << std::endl;
                Pelicula peliculaEliminar(eliminarTitulo, "", "", 0, 0);

                try 
                {
                    arbolPeliculas.remove(peliculaEliminar);
                    inventario.eliminarPelicula(eliminarTitulo);
                    std::cout << "La pelicula \"" << eliminarTitulo << "\" fue eliminada." << std::endl;
                } 
                catch (NoSuchElement& e) 
                {
                    std::cout << "No se pudo eliminar la pelicula \"" << eliminarTitulo << "\" porque no se encontro." << std::endl;
                }

            }
        }

        else if (opcion == 6)
        {
            guardarEnArchivo(inventario, "InventarioPeliculas.txt");
        }

        else if (opcion == 7)
        {
            volverMenuPrincipal = "no";
        }

        else 
        {
            std::cout << "Opcion invalida, intenta nuevamente." << std::endl;
        }

        if (volverMenuPrincipal != "no") 
        {
            std::cout << "Deseas volver al menu? (si/no):";
            std::cin >> volverMenuPrincipal;
            std::cin.ignore();
        }
    }

    std::cout << "Gracias por usar el Movie Selector." << std::endl;
    std::cout << "Vuelva pronto!" << std::endl;
    
    return 0;
}
