#include<iostream>
#include<conio.h>
using namespace std;
//Funcion que imprime las funciones que puede realizar el programa
void opcionesMenu(){
    cout<<"\tIngresa la opcion que deseas realizar. \n\n";
    cout<<"1. Insertar un numero al final de la lista. \n";
    cout<<"2. Insertar un numero al inicio de la lista. \n";
    cout<<"3. Insertar un numero y que se ordene automaticamente. \n";
    cout<<"4. Imprimir lista. \n";
    cout<<"5. Buscar un nodo. \n";
    cout<<"6. Saber si esta vacia. \n";
    cout<<"7. Eliminar primera ocurrencia. \n";
    cout<<"8. Eliminar todas las ocurrencias. \n";
    cout<<"9. Contar el numero de nodos. \n";
    cout<<"10. Recuperar el nodo de la posicion N. \n";
    cout<<"11. Vaciar lista. \n";
    cout<<"12. Convertir array en lista ordenada. \n";
    cout<<"13. Imprimir lista usando recursividad. \n";
    cout<<"14. Salir. \n\n";
    
}
//Función para leer los datos de un array
void leerArray(int array[], int tamano){
    for(int i=0; i<tamano; i++){
        cout<<"Ingrese el dato "<<i+1<<" del array: ";
        cin>>array[i];
    }
}
//Funcion que espera una tecla para borrar pantalla y regresar al menu
void volverMenu(){
    cout<<"\nPresione enter para volver al menu...";
    _getch();
   system("cls");
}
//Creacion de la estructura con los elemnentos que contendra el nodo
struct nodo{
    int dato;
    nodo *siguiente;
};
//Funcion 1: Crea un nuevo nodo con sus elementos
nodo *nuevoNodo(int numero){
    nodo *nuevo = new nodo;
    nuevo->dato = numero;
    nuevo->siguiente = nullptr;
    return nuevo;
}
//Funcion 2: Inserta un nuevo nodo al final de la lista
void insertarFinal(nodo *&inicio, nodo *nuevo){
    if(inicio == nullptr){
        inicio = nuevo;
    }else{
        nodo *aux = inicio;
        while(aux->siguiente != nullptr)
            aux = aux->siguiente;
        aux->siguiente=nuevo;
    }
}
//Funcion 3: Inserta un nuevo nodo al inicio de la lista 
void insertarInicio(nodo *&inicio, nodo *nuevo){
    if(inicio == nullptr){
        inicio = nuevo;
    }else{
        nuevo->siguiente = inicio;
        inicio = nuevo;
    }
}
//Funcion 4: Inserta un nuevo nodo ordenado en la lista
void insertarOrdenado(nodo *&inicio, nodo *nuevo) {
    if (inicio == nullptr || nuevo->dato < inicio->dato) {
        nuevo->siguiente = inicio;
        inicio = nuevo;
    } else {
        nodo *actual = inicio;
        while (actual->siguiente != nullptr && actual->siguiente->dato < nuevo->dato) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
}
//Funcion 5: Imprime la lista
void imprimirLista(nodo *inicio){
    nodo *aux = inicio;
    while (aux != nullptr){
        cout<<aux->dato<<", ";
        aux = aux->siguiente;
    }
    
}
//Funcion 6: Saber si existe un dato en la lista
bool buscarNodo(nodo *inicio, int valor){
    nodo *aux = inicio;
    bool band = false;
    while(aux != nullptr && !band){
        if(aux->dato == valor){
            band = true;
            break;
        }else{
            aux = aux->siguiente;
        }
    }
    return band;
}
//Funcion 7: Saber si la lista se encuentra vacia
bool listaVacia(nodo *inicio){
    if(inicio == nullptr){
        return true;
        //cout<<"La lista esta vacia.";
    }else{
        return false;
        //cout<<"La lista contiene elementos.";
    }
}
//Funcion 8: Elimina el primer dato encontrado que sea igual al dato dado
nodo *eliminarPrimeraOcurrencia(nodo *&inicio, int dato){
    nodo *aux = inicio;
    nodo *anterior;
    bool band = true;
    if(inicio->dato == dato){
        aux = inicio->siguiente;
        delete inicio;
        inicio=aux;
    }else{
        while(aux != nullptr && band){
            if(aux->dato == dato){
                anterior->siguiente = aux->siguiente;
                delete aux;
                band = false;
            }{
                anterior = aux;
                aux = aux->siguiente;
            }
        }
    }
    return inicio;
}
//Fucion 9: Elimina todos los datos encontrados que sean igual al dato dado
nodo *eliminarTodaOcurrencia(nodo *&inicio, int dato){
    nodo *aux = inicio;
    nodo *anterior;
    do{
        if(inicio->dato == dato){
            aux = inicio->siguiente;
            delete inicio;
            inicio=aux;
        }else if(aux->dato == dato){
            anterior->siguiente = aux->siguiente;
            delete aux;
            aux = anterior->siguiente;
        }else{
            anterior = aux;
            aux = aux->siguiente;
        }        
    }while(aux != nullptr);
    return inicio;
}
//Funcion 10: Cuenta cuantos elementos hay en la lista
int numNodos(nodo *inicio){
    int contador= 1;
    nodo *aux = inicio->siguiente;
    while(aux != nullptr){
        contador ++;
        aux = aux->siguiente;
    }
    return contador;
}
//Funcion 11: Mostrar el elemento de la posicion n
void recuperarNodo(nodo *inicio, int posicion){
    int contador = 1;
    nodo *aux= inicio;
    bool band = true;
    while(aux != nullptr && band){
        if(contador == posicion){
            cout<<"El elemento en la posicion "<<posicion<<" es: "<<aux->dato;
            band = false;
        }else{
            contador++;
            aux = aux->siguiente;
        }
    }
}
//Funcion 12: Elimina todos los elementos de la lista
void vaciarLista(nodo *&inicio){
    nodo *aux = inicio;
    nodo *siguiente;
    while(aux != nullptr){
        siguiente = aux->siguiente;
        delete aux;
        aux = siguiente;
    }
    inicio = nullptr;
}
//Función 13: Convierte un array en una lista ordenada
void array_A_Lista(nodo *&inicioArray, int array[], int tamano){
    for(int i=0; i<tamano; i++){
        insertarOrdenado(inicioArray, nuevoNodo(array[i]));
    }
}
//Función 14:Imprime la lista utilizando recursividad
void imprimirRecursividad(nodo *inicio){
    if(inicio == nullptr) return;
    cout<<inicio->dato<<", ";
    imprimirRecursividad (inicio->siguiente);
}
void menu(int opcionMenu, nodo *&inicio, nodo*&inicioArray){
    int numero, numDatos;
    int array[50];
    int i;
    switch (opcionMenu){
    case 1:
        system("cls");
        cout<<"\t1. Insertar un numero al final de la lista. \n\n";
        cout<<"Cuantos datos deseas ingresar: ";
        cin>>numDatos;
        i=0;
        do{
            cout<<"Ingrese el numero que deseas ingresar a la lista: ";
            cin>>numero;
            insertarFinal(inicio, nuevoNodo(numero));
            i++;
        }while(i<numDatos);
        cout<<"\nEl numero se almaceno con exito.";
        volverMenu();
        break;

    case 2:
        system("cls");
        cout<<"\t2. Insertar un numero al inicio de la lista. \n";
        cout<<"Cuantos datos deseas ingresar: ";
        cin>>numDatos;
        i=0;
        do{
            cout<<"Ingrese el numero que deseas ingresar a la lista: ";
            cin>>numero;
            insertarInicio(inicio, nuevoNodo(numero));
            i++;
        }while(i<numDatos);
        cout<<"\nEl numero se almaceno con exito.";
        volverMenu();
        break;

    case 3:
        system("cls");
        cout<<"\t3. Insertar un numero y que se ordene automaticamente. \n";
        cout<<"Cuantos datos deseas ingresar: ";
        cin>>numDatos;
        i=0;
        do{
            cout<<"Ingrese el numero que deseas ingresar a la lista: ";
            cin>>numero;
            insertarOrdenado(inicio, nuevoNodo(numero));
            i++;
        }while(i<numDatos);
        cout<<"\nEl numero se almaceno con exito.";
        volverMenu();
        break;

    case 4:
        system("cls");
        cout<<"\t4. Imprimir lista. \n";
        if(!listaVacia(inicio)){
            imprimirLista(inicio);
        }else{
            cout<<"Aun no hay ningun dato en la lista.";
        }
        volverMenu();
        break;

    case 5:
        system("cls");
        cout<<"\t5. Buscar un nodo. \n";
        if(!listaVacia(inicio)){
            cout<<"Ingres el numero el cual deseas saber si esta en la lista: ";
            cin>>numero;
            if(buscarNodo(inicio, numero)){
                cout<<"El elemento si se encuentra en la lista.";
            }else{
                cout<<"El dato no se encontro en la lista.";
            }
        }else{
            cout<<"Aun no hay ningun dato en la lista.";
        }
        volverMenu();
        break;

    case 6:
        system("cls");
        cout<<"\t6. Saber si esta vacia. \n";
        if(listaVacia(inicio)){
            cout<<"La lista esta vacia.";
        }else{
            cout<<"La lista contiene elementos.";
        }
        volverMenu();
        break;

    case 7:
        system("cls");
        cout<<"\t7. Eliminar primera ocurrencia. \n";
        if(!listaVacia(inicio)){
            cout<<"Ingresa el elemento que deseas eliminar: ";
            cin>>numero;
            if(buscarNodo(inicio, numero)){
                inicio = eliminarPrimeraOcurrencia(inicio, numero);
                cout<<"El elemento se ha borrado correctamente.";
            }else{
                cout<<"El elemento que deseas eliminar no se encuentra en la lista.";
            }
        }else{
            cout<<"Aun no hay ningun dato en la lista.";
        }
        volverMenu();
        break;

    case 8:
        system("cls");
        cout<<"\t8. Eliminar todas las ocurrencias. \n";
        if(!listaVacia(inicio)){
            cout<<"Ingres el elemento que deseas eliminar: ";
            cin>>numero;
            if(buscarNodo(inicio, numero)){
                inicio=eliminarTodaOcurrencia(inicio, numero);
                cout<<"Se han borrado todos los datos iguales correctamente.";
            }else{
                cout<<"El elemento que deseas eliminar no se encuentra en la lista.";
            }
        }else{
            cout<<"Aun no hay ningun dato en la lista.";
        }
        volverMenu();
        break;

    case 9:
        system("cls");
        cout<<"\t9. Contar el numero de nodos. \n";
        if(!listaVacia(inicio)){
            cout<<"El numero de datos que tiene la lista son: "<<numNodos(inicio);
        }else{
            cout<<"Aun no hay ningun dato en la lista.";
        }
        volverMenu();
        break;

    case 10:
        system("cls");
        cout<<"\t10. Recuperar el nodo de la posicion N. \n";
        if(!listaVacia(inicio)){
            cout<<"Ingresa la posicion del nodo que quieres visualizar: ";
            cin>>numero;
            if(numNodos(inicio) < numero){
                cout<<"La posicion ingresada no existe.";
            }else{
                recuperarNodo(inicio, numero);
            }
        }else{
            cout<<"Aun no hay ningun dato en la lista.";
        }
        volverMenu();
        break;

    case 11:
        system("cls");
        cout<<"\t11. Vaciar lista. \n";
        if(!listaVacia(inicio)){
            vaciarLista(inicio);
            cout<<"Se eliminaros todos los datos correctamente.";
        }else{
            cout<<"Aun no hay ningun dato en la lista.";
        }
        volverMenu();
        break;

    case 12:
        system("cls");
        cout<<"\t12. Convertir array en lista ordenada. \n";
        cout<<"Ingresa cuantos datos va a tener el array: ";
        cin>>numero;
        leerArray(array, numero);
        array_A_Lista(inicioArray, array, numero);
        cout<<"La lista creada es: \n";
        imprimirLista(inicioArray);
        volverMenu();
        break;

    case 13:
        system("cls");
        cout<<"\t13. Imprimir lista usando recursividad. \n";
        if(!listaVacia(inicio)){
            imprimirRecursividad(inicio);
        }else{
            cout<<"Aun no hay ningun dato en la lista.";
        }
        volverMenu();
        break;

    case 14:
        vaciarLista(inicio);
        vaciarLista(inicioArray);
        cout<<"Saliendo del programa...";
        break;

    default:
        break;
    }
}
int main(){
    nodo *inicio = nullptr;
    nodo *inicioArray = nullptr;
    int opcionMenu;
    do{
        opcionesMenu();
        cout<<"Opcion: "; cin>>opcionMenu;
        menu(opcionMenu, inicio, inicioArray);

    }while( opcionMenu!= 14);
    
    return 0;
}