
template <class T>
Conjunto<T>::Conjunto() : _raiz(NULL) {}

template <class T>
Conjunto<T>::~Conjunto() { 
    destruir(_raiz);
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    bool res = false;
    if(_raiz == NULL){
        return false;
    } else {
        Nodo* ite = _raiz;
        while(true){
            if(ite->valor == clave){
                return true;
            } else {
                if(clave < ite->valor){
                    if(ite->izq == NULL){
                        return false;
                    } else {
                        ite = ite->izq;
                    }
                } else {
                    if(ite->der == NULL){
                        return false;
                    } else {
                        ite = ite->der;
                    }
                }
            }
        }
    }
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if(!pertenece(clave)) {
        if(_raiz == NULL){
            _raiz = new Nodo(clave, NULL, NULL, NULL);
        } else {
            bool insertado = false;
            Nodo* ite = _raiz;
            Nodo *nuevo = NULL;
            while (!insertado) {
                if(clave < ite->valor){
                    if(ite->izq == NULL){
                        nuevo = new Nodo(clave, NULL, NULL, ite);
                        ite->izq = nuevo;
                        insertado = true;
                    } else {
                        ite = ite->izq;
                    }
                } else {
                    if(ite->der == NULL){
                        nuevo = new Nodo(clave, NULL, NULL, ite);
                        ite->der = nuevo;
                        insertado = true;
                    } else {
                        ite = ite->der;
                    }
                }
            }
        }
    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    if (pertenece(clave)) {
        Nodo *ite = _raiz;
        Nodo *nodoClave = NULL;
        bool encontrado = false;
        while (!encontrado) {                                   // busco el nodo
            if (ite->valor == clave) {
                nodoClave = ite;
                encontrado = true;
            } else {
                if (ite->valor < clave) {
                    ite = ite->der;
                } else {
                    ite = ite->izq;
                }
            }
        }
        Nodo *temp;
        if (nodoClave->izq == NULL and nodoClave->der == NULL) {  // si es hoja
            if(nodoClave == _raiz){
                _raiz = NULL;
            } else {
                Nodo *padre = nodoClave->_padre;
                if(nodoClave->valor < padre->valor){
                    padre->izq = NULL;
                } else {
                    padre->der = NULL;
                }
            }
            delete nodoClave;
        } else if (nodoClave->izq != NULL and nodoClave->der == NULL) {                                                //si tiene un hijo izquierdo
            temp = nodoClave->izq;
            nodoClave->valor = nodoClave->izq->valor;
            nodoClave->der = nodoClave->izq->der;
            nodoClave->izq = nodoClave->izq->izq;
            if(nodoClave->izq != NULL){
                nodoClave->izq->_padre = nodoClave;
            }
            if(nodoClave->der != NULL){
                nodoClave->der->_padre = nodoClave;
            }
            delete temp;
        } else if (nodoClave->izq == NULL and nodoClave->der != NULL) {
            temp = nodoClave->der;
            nodoClave->valor = nodoClave->der->valor;
            nodoClave->izq = nodoClave->der->izq;
            nodoClave->der = nodoClave->der->der;
            if(nodoClave->izq != NULL){
                nodoClave->izq->_padre = nodoClave;
            }
            if(nodoClave->der != NULL){
                nodoClave->der->_padre = nodoClave;
            }
            delete temp;
        } else {
            Nodo *nodoSiguiente = obtenerMinimoSubDerecho(nodoClave->der);
            nodoClave->valor = nodoSiguiente->valor;
            if(nodoClave->der == nodoSiguiente){
                nodoClave->der = nodoSiguiente->der;
                if(nodoSiguiente->der != NULL){
                    nodoSiguiente->der->_padre = nodoClave;
                }
            } else if(nodoSiguiente->der == NULL){
                nodoSiguiente->_padre->izq = NULL;
            } else {
                nodoSiguiente->_padre->izq = nodoSiguiente->der;
                nodoSiguiente->der->_padre = nodoSiguiente->_padre;
            }
            delete nodoSiguiente;
        }
    }
}


template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    bool encontrado = false;
    Nodo *ite = _raiz;
    while (!encontrado) {
        if (ite->valor == clave) {
            encontrado = true;
        } else {
            if (ite->valor < clave) {
                ite = ite->der;
            } else {
                ite = ite->izq;
            }
        }
    }
    if (ite->der != NULL) {             //tiene subarbol derecho
        ite = ite->der;
        while(true){
            if(ite->izq == NULL){
                return ite->valor;
            } else {
                ite = ite->izq;
            }
        }
    }
    Nodo *padre = ite->_padre;
    Nodo *actual = ite;
    if (ite->valor < padre->valor) {  //es hijo izquierdo
        return padre->valor;
    }
    if (ite->valor > ite->_padre->valor) {        //es hijo derecho
        while((padre != NULL) and (actual == padre->der)) {
            actual = padre;
            padre = actual->_padre;
        }
        return padre->valor;
    }
}

template <class T>
const T& Conjunto<T>::minimo() const {
        Nodo *ite = _raiz;
        while(ite != NULL){
            if(ite->izq == NULL){
                return ite->valor;
            } else {
                ite = ite->izq;
            }
        }
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* ite = _raiz;
    while(ite != NULL){
        if(ite->der == NULL){
            return ite->valor;
        } else {
            ite = ite->der;
        }
    }
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    if(_raiz == NULL){
        return 0;
    } else {
        return 1 + cardinalRecursivo(_raiz->izq) + cardinalRecursivo(_raiz->der);
    }
}

template <class T>
unsigned int Conjunto<T>::cardinalRecursivo(Nodo* n) const {
    if(n == NULL){
        return 0;
    } else {
        return 1 + cardinalRecursivo(n->izq) + cardinalRecursivo(n->der);
    }
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

template<class T>
typename Conjunto<T>::Nodo *Conjunto<T>::obtenerMinimoSubDerecho(Conjunto::Nodo *der) {
    Nodo *res = der;
    while(res->izq != NULL){
        res = res->izq;
    }
    return res;
}

template<class T>
void Conjunto<T>::destruir(Conjunto::Nodo *n) {
    if(n != NULL){
        destruir(n->izq);
        destruir(n->der);
        delete n;
    }
}






