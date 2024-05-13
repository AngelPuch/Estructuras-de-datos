#include<iostream>
#include<conio.h>
using namespace std;
void menu(){
    cout<<"1.- Agregar elemento a la pila. \n";
    cout<<"2.- Eliminar elemento de la pila \n";
    cout<<"3.- Visualizar el ultimo elemento de la pila. \n";
    cout<<"4.- Tamano de la pila. \n";
    cout<<"5.- Saber si esta vacia. \n";
    cout<<"6.- Imprimir elementos de la pila. \n";
    cout<<"7.- Eliminar elementos de la pila. \n";    
    cout<<"8.- Salir. \n";
    cout<<"Escoga una opcion: ";
}
struct nodo{
    int dato;
    nodo *siguiente;
};

nodo *nuevoNodo(int elemento){
    nodo *nuevo = new nodo;
    nuevo->dato = elemento;
    nuevo->siguiente = nullptr;
    return nuevo;
}
//Función 1. Agregar elemento a la pila
void agregarElemento(nodo *&tope, nodo* nuevo){
    if(tope == nullptr){
        tope = nuevo;
    }else{
        nuevo->siguiente = tope;
        tope = nuevo;
    }

}
//Función 2. Eliminar último dato de la pila
int eliminarElemento(nodo *&tope){
    if(tope == nullptr){
        return -1;
    }else{
        nodo *aux = tope;
        int elemento = tope->dato;
        tope = tope->siguiente;
        delete aux;
        return elemento;
    }
}
//Funcion 3. Visualizar el ultimo elemento de la pila sin eliminarlo
int visualizarElemento(nodo *tope){
    if(tope == nullptr){
        return -1;
    }else{
        return tope->dato;
    }
}
//Funcion 4. Tamano de la pila
int tamanoPila(nodo *&tope){
    nodo *topeAux = nullptr;
    nodo *aux = tope;
    int contador=0;
    if(tope == nullptr){
        return -1;
    }else{
        while(aux != nullptr){
            tope = tope->siguiente;
            contador++;
            agregarElemento(topeAux, nuevoNodo(aux->dato));
            delete aux;
            aux = tope;
        }
        aux = topeAux;
        while(aux != nullptr){
            topeAux = topeAux->siguiente;
            agregarElemento(tope, nuevoNodo(aux->dato));
            delete aux;
            aux = topeAux;
        }
    }
    return contador;
}
//Función 5: Saber si la pila esta vacia
bool vacio(nodo *tope){
    return tope == nullptr ?true :false;
}
//Funcion 6: Imprimir Pila
void imprimirPila(nodo *&tope){
    nodo *topeAux = nullptr;
    nodo *aux = tope;
    if(tope == nullptr){
        cout<<"Aun no hay elementos para mostrar. \n";
    }else{
        while(aux != nullptr){
            tope = tope->siguiente;
            cout<<aux->dato<<"\n";
            agregarElemento(topeAux, nuevoNodo(aux->dato));
            delete aux;
            aux = tope;
        }
        aux = topeAux;
        while(aux != nullptr){
            topeAux = topeAux->siguiente;
            agregarElemento(tope, nuevoNodo(aux->dato));
            delete aux;
            aux = topeAux;
        }
    }
}
//Funcion 7: Eliminar elementos de la pila
void eliminarElementos(nodo *&tope) {
    nodo* aux = tope;
    while (aux != nullptr) { 
        nodo* auxSiguiente = aux->siguiente; // Guardar el siguiente nodo
        delete aux; // Eliminar el nodo actual
        aux = auxSiguiente; // Avanzar al siguiente nodo
    }
    tope = nullptr; // Establecer primero en nullptr después de eliminar todos los nodos
}
void opcionMenu(nodo *&tope ,int opcion){
    int elemento;
    switch (opcion){
        case 1:
            system("cls");
            cout<<"\t 1.- Agregar elemento a la pila. \n";
            cout<<"Ingresa el dato que quieres agregar: ";
            cin>>elemento;
            agregarElemento(tope, nuevoNodo(elemento));
            cout<<"Se ha agregado el elemento exitosamente. \n";
            break;
        case 2:
            system("cls");
            cout<<"\t 2.- Eliminar elemento de la pila \n";
            elemento = eliminarElemento(tope);
            if(elemento == -1){
                cout<<"Aun no hay elementos para eliminar. \n";
            }else{
                cout<<"El elemento elimnado es: "<<elemento<<"\n";
            }
            break;
        case 3:
            system("cls");
            cout<<"\t 3.- Visualizar el ultimo elemento de la pila. \n";
            elemento = visualizarElemento(tope);
            if(elemento == -1){
                cout<<"Aun no hay elementos en la pila. \n";
            }else{
                cout<<"El ultimo elemento de la lista es: "<<elemento<<"\n";
            }
            break;
        case 4:
            system("cls");
            cout<<"\t 4.- Tamano de la pila. \n";
            elemento = tamanoPila(tope);
            if(elemento == -1){
                cout<<"Aun no hay elementos en la pila. \n";
            }else{
                cout<<"La pila contiene "<<elemento<<" elementos. \n";
            }
            break;
        case 5:
            system("cls");
            cout<<"\t 5.- Saber si esta vacia. \n";
            if(vacio(tope)){
                cout<<"La pila esta vacia. \n";
            }else{
                cout<<"La pila contiene elementos. \n";
            }
            break;
        case 6:
            system("cls");
            cout<<"\t 6.- Imprimir elementos de la pila. \n";
            imprimirPila(tope);
            break;
        case 7:
            system("cls");
            cout<<"\t 8.- Eliminar elementos de la pila\n";
            if(tope == nullptr){
                cout<<"Aun no hay elementos en la pila. \n";
            }else{
                eliminarElementos(tope);
                cout<<"Se han eliminado todos los elementos correctamente. \n";
            }
            break;
        case 8:
            cout<<"Saliendo... \n";
            if(tope != nullptr) eliminarElementos(tope);
            break;
        default:
            cout<<"Opcion invalida.\n";
            break;
        }
}
int main(){
    nodo *tope = nullptr;
    int opcion;
    do{
        menu();
        cin>>opcion;
        opcionMenu(tope, opcion);
        cout<<"Presiona para continuar...";
        getch();
        system("cls");
    }while(opcion != 8);

}