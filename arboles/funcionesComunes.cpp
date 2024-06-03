#include <iostream>
#include<queue>
using namespace std;
void volverMenu(){
    cout<<"\n";
    system("pause");
    system("cls");
}
void menu(){
    cout<<"1.- Es vacio? \n"; //Hecho
    cout<<"2.- Insertar elemento \n"; //Hecho
    cout<<"3.- Buscar un dato en el arbol \n"; //Hecho
    cout<<"4.- Recorrido InOrden \n"; //Hecho
    cout<<"5.- Recorrido PreOrden \n"; //Hecho
    cout<<"6.- Recorrido PostOrden \n"; //Hecho
    cout<<"7.- Mostrar acostado \n"; //Hecho
    cout<<"8.- Podar arbol \n"; //Hecho
    cout<<"9.- Elemento menor \n";//Hecho
    cout<<"10.- Elemento mayor \n"; //Hecho
    cout<<"11.- Eliminar un elemento \n"; //Hecho
    cout<<"12.- Contar hojas \n"; //Hecho
    cout<<"13.- Contar nodos \n"; //Hecho
    cout<<"14.- Mostrar elementos por niveles \n"; //Hecho
    cout<<"15.- Es Lleno? \n"; //Hecho
    cout<<"16.- Salir \n";
}
//Se define la estructura del árbol
struct nodo{
    int dato;
    nodo *izquierdo;
    nodo *derecho;
};
//Se define la raiz del árbol
struct arbol{
    nodo *raiz;
};
//Función que crea un nuevo nodo
nodo *nuevoNodo(int dato){
    nodo *nuevo = new nodo;
    nuevo->dato = dato;
    nuevo->derecho = nullptr;
    nuevo->izquierdo = nullptr;
    return nuevo;
}
//Función 1: Verifica si el árbol esta vacío
bool esVacio(nodo *arbolRaiz){
    if(!arbolRaiz) return true;
    return false;
}
//Función 2: Inserta un elemento al árbol
void insertarElemento(nodo *&arbolRaiz, nodo *nuevo){
    if(!arbolRaiz){
        arbolRaiz = nuevo;
    }else if(nuevo->dato < arbolRaiz->dato){
        insertarElemento(arbolRaiz->izquierdo, nuevo);
    }else if(nuevo->dato > arbolRaiz->dato){
        insertarElemento(arbolRaiz->derecho, nuevo);
    }
}
//Función 3: Busca un dato en el árbol, si lo encuentre regresa verdadero
bool buscarDato(nodo *arbolRaiz, int dato){
    if(!arbolRaiz){
        return false;
    }
    if(dato == arbolRaiz->dato){
        return true;
    }else{
        if(dato < arbolRaiz->dato){
            return buscarDato(arbolRaiz->izquierdo, dato);
        }else{
            return buscarDato(arbolRaiz->derecho, dato);
        }
    }
}
//Función 4: Recorre el arbol en InOrden
void recorrerInOrden(nodo *arbolRaiz){
    if(!arbolRaiz){
        return;
    }else{
        recorrerInOrden(arbolRaiz->izquierdo);
        cout<<arbolRaiz->dato<<" ";
        recorrerInOrden(arbolRaiz->derecho);
    }
}
//Función 5: Recorre el arbol en PreOrden
void recorrerPreOrden(nodo *arbolRaiz){
    if(!arbolRaiz){
        return;
    }else{
        cout<<arbolRaiz->dato<<" ";
        recorrerPreOrden(arbolRaiz->izquierdo);
        recorrerPreOrden(arbolRaiz->derecho);
    }
}
//Función 6: Recorre el arbol en PostOrden
void recorrerPostOrden(nodo *arbolRaiz){
    if(!arbolRaiz){
        return;
    }else{
        recorrerPostOrden(arbolRaiz->izquierdo);
        recorrerPostOrden(arbolRaiz->derecho);
        cout<<arbolRaiz->dato<<" ";
    }
}
//Función 7: Imrpimer el árbol de manera grafica acostado
void imprimirGrafico(nodo *arbolRaiz, int contador){
    if(!arbolRaiz){
        return ;
    }else{
        imprimirGrafico(arbolRaiz->derecho, contador+1);
        for(int i=0; i<contador; i++) 
            cout<<"  ";
        cout<<arbolRaiz->dato<<endl;
        imprimirGrafico(arbolRaiz->izquierdo, contador+1);
    }
}
//Función 8: Poda elimina todos los elementos del arbol
void podarArbol(nodo *&arbolRaiz){
    if(!arbolRaiz){
        return;
    }else{
        podarArbol(arbolRaiz->izquierdo);
        podarArbol(arbolRaiz->derecho);
        delete arbolRaiz;
        arbolRaiz=nullptr;
    }
}
//Función 9: Encuentra el nodo con el dato mas menor y lo devuelve
nodo *elementoMenor(nodo *arbolRaiz){
    if(!arbolRaiz){
        return nullptr;
    }else if(!arbolRaiz->izquierdo){
        return arbolRaiz;
    }else{
        return elementoMenor(arbolRaiz->izquierdo);
    }
}
//Función 10: Encuentra el nodo con el dato mas mayor y lo devuelve
nodo *elementoMayor(nodo *arbolRaiz){
    if(!arbolRaiz){
        return nullptr;
    }else if(!arbolRaiz->derecho){
        return arbolRaiz;
    }else{
        return elementoMayor(arbolRaiz->derecho);
    }
}
//Función 11: Función que eliminar un nodo
void eliminarElemento(nodo *&arbolRaiz, int dato){
    if(!arbolRaiz){
        return;
    }else if(dato < arbolRaiz->dato){
        eliminarElemento(arbolRaiz->izquierdo, dato);
    }else if(dato > arbolRaiz->dato){
        eliminarElemento(arbolRaiz->derecho, dato);
    }else if(arbolRaiz->izquierdo && arbolRaiz->derecho){
        nodo *mayor = elementoMayor(arbolRaiz->izquierdo);
        arbolRaiz->dato = mayor->dato;
        eliminarElemento(arbolRaiz->izquierdo, mayor->dato);
    }else{
        nodo *temporal = arbolRaiz;
        if(!arbolRaiz->izquierdo){
            arbolRaiz = arbolRaiz->derecho;
        }else if(!arbolRaiz->derecho){
            arbolRaiz = arbolRaiz->izquierdo;
        }
        delete temporal;
    }
}
//Función 12: Cuenta el numero de hojas que tiene el arbol
int numeroHojas(nodo *arbolRaiz){
    if(!arbolRaiz){
        return 0;
    }else if(!arbolRaiz->derecho && !arbolRaiz->izquierdo){
        return 1;
    }else{
        return numeroHojas(arbolRaiz->izquierdo) + numeroHojas(arbolRaiz->izquierdo);
    }
    
}
//Función 13: Cuenta el número de nodos que tiene el arbol
int numeroNodos(nodo *arbolRaiz){
    if(!arbolRaiz){
        return 0;
    }else{
        return 1 + numeroNodos(arbolRaiz->izquierdo) + numeroNodos(arbolRaiz->derecho);
    }
}
//Función 14: Imprime el arbol por niveles
void recorrerNiveles(nodo *arbolRaiz){
    nodo *auxiliar = arbolRaiz;
    queue<nodo*> cola;
    cola.push(arbolRaiz);
    while(!cola.empty()){
        auxiliar = cola.front();
        cout<<auxiliar->dato<<" - ";
        cola.pop();
        if(auxiliar->izquierdo)
            cola.push(auxiliar->izquierdo);
        if(auxiliar->derecho)
            cola.push(auxiliar->derecho);
    }

}
//Función 15: Verifica si es un árbol binario lleno
bool esLleno(nodo *arbolRaiz){
    if (!arbolRaiz) {
        return false;
    }
    if (!arbolRaiz->izquierdo && !arbolRaiz->derecho){
        return true;
    }
    if (arbolRaiz->izquierdo && arbolRaiz->derecho) {
        return esLleno(arbolRaiz->derecho) && esLleno(arbolRaiz->izquierdo);
    }
    return false;
}
void funcionesMenu(nodo *&arbolRaiz, int opcion){
    int dato, numInsert, contador=0;
    nodo *menor;
    nodo *mayor;
    system("cls");
    switch (opcion){
    case 1:
        cout<<"\t 1.-Es vacio? \n";
        if(esVacio(arbolRaiz)){
            cout<<"El arbol SI esta vacio. \n";
        }else{
            cout<<"El arbol NO esta vacio. \n";
        }
        volverMenu();
        break;
    case 2:
        cout<<"\t 2.- Insertar elemento \n";
        cout<<"Cuantos datos desea ingresar? ";
        cin>>numInsert;
        do{
            cout<<"Ingresa el dato a insetar: ";
            cin>>dato;
            insertarElemento(arbolRaiz, nuevoNodo(dato));
            numInsert--;
        }while(numInsert > 0);
        cout<<"Se han insertado los datos correctamente. \n";
        volverMenu();
        break;
    case 3: 
        cout<<"\t 3.- Buscar un dato en el arbol \n";
        if(esVacio(arbolRaiz)){
            cout<<"El arbol aun no tiene elementos. \n";
        }else{
            cout<<"Ingresa el dato que quieres buscar: ";
            cin>>dato;
            if(buscarDato(arbolRaiz, dato)){
                cout<<"El dato SI se encuentra en el arbol. \n";
            }else{
                cout<<"El dato NO se encuentra en el arbol. \n";
            }
        }
        volverMenu();
        break;
    case 4:
        cout<<"\t 4.- Recorrido InOrden \n";
        if(esVacio(arbolRaiz)){
            cout<<"El arbol aun no tiene elementos. \n";
        }else{
            recorrerInOrden(arbolRaiz);
            cout<<endl;
        }
        volverMenu();
        break;
    case 5:
        cout<<"\t 5.- Recorrido PreOrden \n";
        if(esVacio(arbolRaiz)){
            cout<<"El arbol aun no tiene elementos. \n";
        }else{
            recorrerPreOrden(arbolRaiz);
            cout<<endl;
        }
        volverMenu();
        break;
    case 6:
        cout<<"\t 6.- Recorrido PostOrden \n";
        if(esVacio(arbolRaiz)){
            cout<<"El arbol aun no tiene elementos. \n";
        }else{
            recorrerPostOrden(arbolRaiz);
            cout<<endl;
        }
        volverMenu();
        break;
    case 7: 
        cout<<"\t 7.- Mostrar grafico acostado \n";
        if(esVacio(arbolRaiz)){
            cout<<"El arbol aun no tiene elementos. \n";
        }else{
            imprimirGrafico(arbolRaiz, contador);
            cout<<endl;
        }
        volverMenu();
        break;
    case 8:
        cout<<"\t 8.- Podar arbol \n";
        if(esVacio(arbolRaiz)){
            cout<<"El arbol aun no tiene elementos. \n";
        }else{
            podarArbol(arbolRaiz);
            cout<<"Se han eliminado todos los elementos del arbol. \n";
        }
        volverMenu();
        break;
    case 9:
        cout<<"\t 9.- Elemento menor \n";
        if(esVacio(arbolRaiz)){
            cout<<"El arbol aun no tiene elementos. \n";
        }else{
            menor = elementoMenor(arbolRaiz);
            cout<<"El dato menor del arbol es el: "<<menor->dato<<endl;
        }
        volverMenu();
        break;
    case 10:
         cout<<"\t 10.- Elemento mayor \n";
         if(esVacio(arbolRaiz)){
            cout<<"El arbol aun no tiene elementos. \n";
         }else{
            mayor = elementoMayor(arbolRaiz);
            cout<<"El dato mayor del arbol es el: "<<mayor->dato<<endl;
         } 
        volverMenu();
        break;
    case 11:
        cout<<"\t 11.- Eliminar un elemento \n";
        if(esVacio(arbolRaiz)){
            cout<<"El arbol aun no tiene elementos. \n";
        }else{
            cout<<"Ingresa el dato que desea eliminar: ";
            cin>>dato;
            eliminarElemento(arbolRaiz, dato);
            cout<<"Se ha eliminado el elemento "<<dato<<" correctamente \n";
        }
        volverMenu();
        break;
    case 12:
        cout<<"\t 12.- Contar hojas \n";
        if(esVacio(arbolRaiz)){
            cout<<"El arbol aun no tiene elementos. \n";
        }else{
            cout<<"El arbol tiene "<<numeroHojas(arbolRaiz)<<" hojas. \n";
        }
        volverMenu();
        break;
    case 13:
        cout<<"\t 13.- Contar nodos \n";
        if(esVacio(arbolRaiz)){
            cout<<"El arbol aun no tiene elementos. \n";
        }else{
            cout<<"El arbol tiene "<<numeroNodos(arbolRaiz)<<" nodos. \n";
        }
        volverMenu();
        break;
    case 14:
        cout<<"\t 14.- Mostrar elementos por niveles \n";
        if(esVacio(arbolRaiz)){
            cout<<"El arbol aun no tiene elementos. \n";
        }else{
            recorrerNiveles(arbolRaiz);
        }
        volverMenu();
        break;
    case 15:
        cout<<"\t 15.- Es Lleno? \n";
        if(esVacio(arbolRaiz)){
            cout<<"El arbol aun no tiene elementos. \n";
        }else{
            if (esLleno(arbolRaiz)) {
                cout << "El arbol es binario lleno \n";
            } else {
                cout << "El arbol no es binario lleno \n";
            }
        }
        volverMenu();
        break;
    case 16:
        podarArbol(arbolRaiz);
        cout<<"Saliendo...";
        break;
    default:
        cout<<"Ingresa una opcion valida. \n";
        volverMenu();
        break;
    }
}
int main() {
    arbol *nuevoArbol = new arbol;
    nuevoArbol->raiz = nullptr;
    int opcion;
    do{
        menu();
        cin>>opcion;
        funcionesMenu(nuevoArbol->raiz, opcion);
    }while(opcion != 16);

    return 0;
}