#include<iostream>
#include<conio.h>
using namespace std;

void opcionesMenu(){
    cout << "\nMENU DE OPCIONES\n" 
    << "1.- Insertar elemento en la cola\n"
    << "2.- Sacar elemento de la cola\n"
    << "3.- Mostrar primer elemento de la cola\n"
    << "4.- Mostrar mostrar ultimo elemento de la cola\n"
    << "5.- Cola vacia?\n"
    << "6.- Imprimir Cola\n"
    << "7.- Contar elementos de la cola\n"
    << "8.- Eliminar cola\n"
    << "9.- Salir\n"
    << "Ingresa la opcion deseada: ";
}

void volverMenu(){
    cout<<"\n\nPresione enter para volver al menu...";
    getch();
   system("cls");
}

//Se define la estructura de la cola
struct nodo{
    int dato;
    nodo *siguiente;
};
//Función que crea un nuevo nodo
nodo* crearNodo( int dato ){
    nodo* nuevo = new nodo;
    nuevo->dato = dato;
    nuevo->siguiente = nullptr;
    return nuevo;
}
//Función 1: Inserta un elemento al final de la cola
void insertarCola(nodo *&primero, nodo *&ultimo, nodo*nuevo){
    if(primero == nullptr){
        primero = nuevo;
    }else{
        ultimo->siguiente = nuevo;
    }
    ultimo = nuevo;
}
//Función 2: Eliminar elemento de la cola
int eliminarElemento(nodo *&primero, nodo *&ultimo){
    int datoSacado = primero->dato;
    nodo *temp = primero;
    primero = primero->siguiente;
    delete temp;
    if(primero == nullptr){
        ultimo = nullptr;
    }
    return datoSacado;
}
//Funcion 3: Muestra el primero elemnto de la cola sin eliminarlo
int mostrarPrimero(nodo *primero){
    return primero->dato;
}
//Función 4: Muestra el ultimo elemento de la cola
int mostrarUltimo(nodo *ultimo){
    return ultimo->dato;
}  
//Función 5: Muestra si la cola esta vacia
void vacio(nodo *primero){
    if(primero == nullptr){
        cout<<"La cola esta vacia. \n";
    }else{
        cout<<"La cola ya contiene elementos. \n";
    }
}
//Funcion 6: Imprime todos los elementos de la cola
void imprimirCola(nodo *primero){
    nodo *aux = primero;
    while(aux != nullptr){
        cout<< aux->dato<<", ";
        aux = aux->siguiente;
    }
}
//Función 7. Cuenta el numero de elemtos que tiene la cola
int numNodos(nodo *primero){
    int contador= 1;
    nodo *aux = primero->siguiente;
    while(aux != nullptr){
        contador ++;
        aux = aux->siguiente;
    }
    return contador;
}
//Función 8: Elimina todos los elementos de la cola
void eliminarElementos(nodo *&primero) {
    nodo* aux = primero;
    while (aux != nullptr) { 
        nodo* auxSiguiente = aux->siguiente; // Guardar el siguiente nodo
        delete aux; // Eliminar el nodo actual
        aux = auxSiguiente; // Avanzar al siguiente nodo
    }
    primero = nullptr; // Establecer primero en nullptr después de eliminar todos los nodos
}
//Función que ejecuta todas las intrucciones del menu
void menu(nodo* &primero, nodo* &ultimo, int opcion){
    switch (opcion){
    case 1:{
        system("cls");
        cout<<"\t 1.- Insertar elemento en la cola\n\n";
        int dato;
        cout<<"Ingresa el dato que deseas almacenar: ";
        cin>>dato;
        insertarCola(primero, ultimo, crearNodo(dato));
        cout<<"El elemento se ha almacenado con exito. \n";
        volverMenu();
        }break;
    case 2:
        system("cls");
        cout<<"\t 2.- Sacar elemento de la cola\n";
        if(primero == nullptr){
            cout<<"La cola aun no tiene elementos para eliminar. \n";
        }else{
            cout<<"El dato eliminado es: "<<eliminarElemento(primero, ultimo)<<endl;
        }
        volverMenu();
        break;
    case 3:
        system("cls");
        cout<<"\t 3.- Mostrar primer elemento de la cola\n";
        if(primero == nullptr){
            cout<<"La cola aun no tiene elementos para mostrar. \n";
        }else{
            cout<<"El primer elemento de la cola es: "<<mostrarPrimero(primero)<<endl;
        }
        volverMenu();
        break;
    case 4:
        system("cls");
        cout<<"\t 4.- Mostrar mostrar ultimo elemento de la cola\n";
        if(primero == nullptr){
            cout<<"La cola aun no tiene elementos para mostrar. \n";
        }else{
            cout<<"El ultimo elemento de la cola es: "<<mostrarUltimo(ultimo)<<endl;
        }
        volverMenu();
        break;
    case 5:
        system("cls");
        cout<<"\t 5.- Cola vacia?\n";
        vacio(primero);
        volverMenu();
        break;
    case 6:
        system("cls");
        cout<<"\t6.- Imprimir Cola\n\n";
        imprimirCola(primero);
        volverMenu();
        break;
    case 7:
        system("cls");
        cout<<"\t 7.- Contar elementos de la cola\n";
        if(primero == nullptr){
            cout<<"La cola aun no tiene elementos. \n";
        }else{
            cout<<"La cola contiene: "<<numNodos(primero)<<" elementos. \n";
        }
        volverMenu();
        break;
    case 8: 
        system("cls");
        cout<<"\t 8.- Eliminar cola\n";
        if(primero == nullptr){
            cout<<"Aun no hay elementos en la cola. \n";
        }else{
            eliminarElementos(primero);
            cout<<"Se han eliminado todos los elementos correctamente. \n";
        }
        volverMenu();
        break;
    case 9:
        cout<<"Saliendo...\n";
        if(primero == nullptr) eliminarElementos(primero);
        break;
    default:
        cout<<"Opcion no valida. \n";
        break;
    }
}

int main(){
    nodo *primero = nullptr;
    nodo *ultimo = nullptr;
    int opcion;
    do{
        opcionesMenu();
        cin>>opcion;
        menu(primero, ultimo, opcion);
    }while(opcion != 9);

    return 0;
}