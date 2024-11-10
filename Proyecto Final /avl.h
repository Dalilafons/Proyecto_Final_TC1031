/*
 * avl.h
 *
 *  Created on: 19/10/2024
 *      Author: Dalila Fonseca Maya A01711722
 */

#ifndef AVL_H_
#define AVL_H_

#include <string>
#include <sstream>
#include <iostream>
#include <exception>
#include "pelicula.h"

// Excepción OutOfMemory
class OutOfMemory : public std::exception 
{
public:
    const char* what() const noexcept override 
    {
        return "No se pudo asignar memoria.";
    }
};

// Excepción NoSuchElement
class NoSuchElement : public std::exception 
{
public:
    const char* what() const noexcept override 
    {
        return "No se encontró el elemento en el árbol.";
    }
};

template <class T>
class Node 
{
    private:
        T value;
        Node* left;
        Node* right;
        int level, balance;

        // Método privado para encontrar el predecesor.
        Node<T>* predecesor();  

        template <class U>
        friend class AVL;

    public:
        Node(T val);
        void add(T val);
        T* findByTitle(const std::string& title);
        void remove(T val);
        void removeChilds();
        void inorder(std::stringstream& aux) const;
};

/*
 * Node<T>::Node(T val) - Constructor de nodo
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Inicializa un nodo con el valor `val`, sin hijos y con balance y nivel en 0. La complejidad es constante porque solo inicializa variables.
 */
template <class T>
Node<T>::Node(T val) : value(val), left(nullptr), right(nullptr), level(0), balance(0) {}

/*
 * Node<T>::predecesor() - Encuentra el predecesor de un nodo
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el predecesor es el hijo izquierdo)
 * - Caso promedio: O(log n)
 * - Peor caso: O(log n) (si necesita moverse hacia la izquierda y luego hacia la derecha en un árbol balanceado)
 * Descripción: Encuentra el predecesor en el subárbol izquierdo del nodo actual. La complejidad es O(log n) en promedio,
 * ya que puede descender a lo largo de la altura del árbol para encontrar el predecesor.
 */
template <class T>
Node<T>* Node<T>::predecesor() 
{
    Node<T>* le = left;
    Node<T>* ri = right;

    if (left == NULL) 
    {
        right = NULL;
        return ri;
    }

    if (left->right == NULL) 
    {
        left = left->left;
        le->left = NULL;
        return le;
    }

    Node<T>* parent = left;
    Node<T>* child = left->right;

    while (child->right != NULL) 
    {
        parent = child;
        child = child->right;
    }

    parent->right = child->left;
    child->left = NULL;
    return child;
}

/*
 * Node<T>::add(T val) - Agrega un valor al árbol AVL
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el árbol tiene un solo nodo)
 * - Caso promedio: O(log n)
 * - Peor caso: O(log n) (en un árbol balanceado)
 * Descripción: Inserta un nuevo nodo en el árbol AVL. La inserción en un árbol balanceado tiene una complejidad O(log n)
 * en promedio y en el peor caso, ya que solo recorre la altura del árbol.
 */
template <class T>
void Node<T>::add(T val) 
{
    if (val.getTitulo() < value.getTitulo()) 
    {
        if (left != NULL) 
        {
            left->add(val);
        } 
        else 
        {
            left = new Node<T>(val);
        }
    } 
    else 
    {
        if (right != NULL) 
        {
            right->add(val);
        } 
        else 
        {
            right = new Node<T>(val);
        }
    }
}

/*
 * Node<T>::findByTitle(const std::string& title) - Busca un valor por título
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el valor está en el nodo raíz)
 * - Caso promedio: O(log n)
 * - Peor caso: O(log n) (en un árbol balanceado)
 * Descripción: Busca un valor en el árbol basado en el título. La complejidad es O(log n) debido a la estructura de árbol balanceado,
 * lo que permite reducir el número de nodos revisados.
 */
template <class T>
T* Node<T>::findByTitle(const std::string& title) 
{
    if (title == value.getTitulo()) 
    {
        return &value;
    } 
    else if (title < value.getTitulo()) 
    {
        return (left != NULL) ? left->findByTitle(title) : NULL;
    } 
    else 
    {
        return (right != NULL) ? right->findByTitle(title) : NULL;
    }
}

/*
 * Node<T>::remove(T val) - Elimina un nodo del árbol AVL
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el nodo a eliminar es una hoja)
 * - Caso promedio: O(log n)
 * - Peor caso: O(log n)
 * Descripción: Elimina un nodo con valor `val` del árbol. La eliminación en un árbol balanceado es O(log n) ya que necesita buscar el nodo
 * y realizar rotaciones si es necesario para mantener el equilibrio.
 */
template <class T>
void Node<T>::remove(T val) 
{
    if (val.getTitulo() < value.getTitulo()) 
    {
        if (left != NULL) 
        {
            if (left->value.getTitulo() == val.getTitulo()) 
            {
                Node<T>* old = left;
                Node<T>* succ = left->predecesor();

                if (succ != NULL) 
                {
                    succ->left = old->left;
                    succ->right = old->right;
                }
                left = succ;
                delete old;
            } 
            else 
            {
                left->remove(val);
            }
        }
    } 
    else if (val.getTitulo() > value.getTitulo()) 
    {
        if (right != NULL) 
        {
            if (right->value.getTitulo() == val.getTitulo()) 
            {
                Node<T>* old = right;
                Node<T>* succ = right->predecesor();

                if (succ != NULL) 
                {
                    succ->left = old->left;
                    succ->right = old->right;
                }
                right = succ;
                delete old;
            } 
            else 
            {
                right->remove(val);
            }
        }
    }
}

/*
 * Node<T>::removeChilds() - Elimina todos los hijos de un nodo
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el nodo no tiene hijos)
 * - Caso promedio: O(n)
 * - Peor caso: O(n) (si el nodo tiene muchos descendientes)
 * Descripción: Elimina recursivamente todos los hijos del nodo. En el peor caso, tiene que recorrer todos los nodos en el subárbol,
 * resultando en una complejidad de O(n).
 */
template <class T>
void Node<T>::removeChilds() 
{
    if (left != NULL) 
    {
        left->removeChilds();
        delete left;
        left = NULL;
    }
    if (right != NULL) 
    {
        right->removeChilds();
        delete right;
        right = NULL;
    }
}

/*
 * Node<T>::inorder(std::stringstream& aux) - Realiza un recorrido inorden del árbol
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Realiza un recorrido inorden del árbol y almacena la información en `aux`. Dado que visita todos los nodos una vez, su complejidad es O(n).
 */
template <class T>
void Node<T>::inorder(std::stringstream& aux) const 
{
    if (left != NULL) 
    {
        left->inorder(aux);
    }

    aux << "Titulo: " << value.getTitulo() << "\n"
        << "Director: " << value.getDirector() << "\n"
        << "Genero: " << value.getGenero() << "\n"
        << "Año de lanzamiento: " << value.getLanzamiento() << "\n"
        << "Duración: " << value.getDuracion() << " minutos\n\n";

    if (right != NULL) 
    {
        right->inorder(aux);
    }
}

template <class T>
class AVL 
{
    private:
        Node<T>* root;

    public:
        AVL();
        ~AVL();
        bool empty() const;
        void add(T val);
        T* findByTitle(const std::string& title) const;
        void remove(T val);
        void removeAll();
        std::string inorder() const;
};

/*
 * AVL<T>::AVL() - Constructor del árbol AVL
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Inicializa un árbol AVL vacío. La operación es constante ya que solo establece el puntero `root` en NULL.
 */
template <class T>
AVL<T>::AVL() : root(NULL) {}

/*
 * AVL<T>::~AVL() - Destructor del árbol AVL
 * Complejidad temporal:
 * - Mejor caso: O(n) (si el árbol tiene nodos)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Llama a `removeAll()` para eliminar todos los nodos en el árbol. Dado que elimina todos los nodos, la complejidad es O(n).
 */
template <class T>
AVL<T>::~AVL() 
{
    removeAll();
}

/*
 * AVL<T>::empty() const - Verifica si el árbol está vacío
 * Complejidad temporal:
 * - Mejor caso: O(1)
 * - Caso promedio: O(1)
 * - Peor caso: O(1)
 * Descripción: Verifica si el árbol está vacío comprobando si `root` es NULL. La operación es constante en todos los casos.
 */
template <class T>
bool AVL<T>::empty() const 
{
    return root == NULL;
}

/*
 * AVL<T>::add(T val) - Agrega un valor al árbol AVL
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el árbol está vacío y el nodo se convierte en la raíz)
 * - Caso promedio: O(log n)
 * - Peor caso: O(log n) (en un árbol balanceado)
 * Descripción: Inserta un valor en el árbol AVL. La complejidad es O(log n) en promedio y en el peor caso debido al balanceo del árbol.
 */
template <class T>
void AVL<T>::add(T val) 
{
    if (root != nullptr) 
    {
        if (findByTitle(val.getTitulo()) == NULL) 
        {
            root->add(val);
        }
    } 
    else 
    {
        root = new Node<T>(val);
    }
}

/*
 * AVL<T>::findByTitle(const std::string& title) const - Busca un valor por título
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el valor está en la raíz)
 * - Caso promedio: O(log n)
 * - Peor caso: O(log n) (en un árbol balanceado)
 * Descripción: Busca un valor en el árbol por título. En un árbol balanceado, la búsqueda tiene una complejidad O(log n).
 */
template <class T>
T* AVL<T>::findByTitle(const std::string& title) const 
{
    return (root != NULL) ? root->findByTitle(title) : NULL;
}

/*
 * AVL<T>::remove(T val) - Elimina un nodo del árbol AVL
 * Complejidad temporal:
 * - Mejor caso: O(1) (si el árbol solo tiene la raíz)
 * - Caso promedio: O(log n)
 * - Peor caso: O(log n)
 * Descripción: Elimina un valor en el árbol AVL. La operación es O(log n) porque, en un árbol balanceado, necesita recorrer la altura
 * del árbol para encontrar el nodo y ajustarlo si es necesario.
 */
template <class T>
void AVL<T>::remove(T val) 
{
    if (root != NULL) 
    {
        if (val.getTitulo() == root->value.getTitulo()) 
        {
            Node<T>* succ = root->predecesor();

            if (succ != NULL) 
            {
                succ->left = root->left;
                succ->right = root->right;
            }
            delete root;
            root = succ;
        } 
        else 
        {
            root->remove(val);
        }
    }
}

/*
 * AVL<T>::removeAll() - Elimina todos los nodos del árbol AVL
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Llama a `removeChilds` en la raíz y elimina cada nodo del árbol. Recorre todos los nodos, por lo que la complejidad es O(n).
 */
template <class T>
void AVL<T>::removeAll() 
{
    if (root != NULL) 
    {
        root->removeChilds();
        delete root;
        root = NULL;
    }
}

/*
 * AVL<T>::inorder() const - Realiza un recorrido inorden y devuelve los elementos como una cadena
 * Complejidad temporal:
 * - Mejor caso: O(n)
 * - Caso promedio: O(n)
 * - Peor caso: O(n)
 * Descripción: Realiza un recorrido inorden del árbol y devuelve una cadena con la información de todos los nodos. La complejidad es O(n),
 * ya que recorre todos los nodos del árbol.
 */
template <class T>
std::string AVL<T>::inorder() const 
{
    std::stringstream aux;

    if (!empty()) 
    {
        root->inorder(aux);
    }
    return aux.str();
}

#endif // AVL_H 
