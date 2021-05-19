#include "Lista.h"

template <typename T>
Lista<T>::Lista() : _prim(NULL), _ult(NULL) {}

template <typename T>
Lista<T>::Lista(const Lista<T>& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
    }

template <typename T>
Lista<T>::~Lista() {
    if(_prim != NULL) {
        Nodo* ite = _prim;
        while (ite != NULL) {
            Nodo* siguiente = ite->_sig;
            delete ite;
            ite = siguiente;
        }
    }
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& aCopiar) {
    Nodo* ite = _prim;
    while(ite != NULL){
        Nodo* siguiente = ite->_sig;
        delete ite;
        ite = siguiente;
    }
    _prim = NULL;
    _ult = NULL;
    ite = aCopiar._prim;
    while(ite != NULL){
        agregarAtras(ite->_valor);
        ite = ite->_sig;
    }
    return *this;
}

template <typename T>
void Lista<T>::agregarAdelante(const T& elem) {
    if(_prim == NULL) {
        Nodo* nuevo = new Nodo(NULL, elem, NULL);
        _prim = nuevo;
        _ult = nuevo;
    } else {
        Nodo* nuevo = new Nodo(NULL, elem, _prim);
        _prim->_ant = nuevo;
        _prim = nuevo;
    }
}

template <typename T>
void Lista<T>::agregarAtras(const T& elem) {
    if(_prim == NULL) {
        Nodo* nuevo = new Nodo(NULL, elem, NULL);
        _prim = nuevo;
        _ult = nuevo;
    } else {
        Nodo* nuevo = new Nodo(_ult, elem, NULL);
        _ult->_sig = nuevo;
        _ult = nuevo;
    }
}

template <typename T>
void Lista<T>::eliminar(Nat i) {
    Nodo* ite = _prim;
    int contador = 0;
    while(ite != NULL){
        if(contador == i) {
            if(ite->_ant != NULL){
                ite->_ant->_sig = ite->_sig;
            } else {
                _prim = ite->_sig;
            }
            if(ite->_sig != NULL){
                ite->_sig->_ant = ite->_ant;
            } else {
                _ult = ite->_ant;
            }
            delete ite;
            ite = NULL;
        }
        if (ite != NULL) {
            Nodo* iteSig = ite->_sig;
            ite = iteSig;
        }
        contador++;
    }
}

template <typename T>
int Lista<T>::longitud() const {
    Nodo* ite = _prim;
    int contador = 0;
    while(ite != NULL){
        contador++;
        ite = ite->_sig;
    }
    return contador;
}

template <typename T>
const T& Lista<T>::iesimo(Nat i) const {
    Nodo* ite = _prim;
    int contador = 0;
    while(ite != NULL){
        if(contador == i){
            return ite->_valor;
        }
        contador++;
        ite = ite->_sig;
    }
}

template <typename T>
T& Lista<T>::iesimo(Nat i) {
    Nodo* ite = _prim;
    int contador = 0;
    while(ite != NULL){
        if(contador == i){
            return ite->_valor;
        }
        contador++;
        ite = ite->_sig;
    }
}

template <typename T>
void Lista<T>::mostrar(ostream& o) {
    // Completar
}