//Angel Jonathan Puch Hernandez & Jose Luis Silva Gomez

#include <iostream>
#include <conio.h> //Se incluyo esta libreria para poder utilizar la función getch()
#include <string>
using namespace std;
//Definición del nodo de la lista 
struct Nodo{
    int dato; // INFO, variable para almacenar el valor del nodo
    Nodo* siguiente; // LIGA, apuntador al nodo siguiente de la lista
};
//Creamos una función de tipo nodo en la cual creamos un nuevo nodo de la lista y regresamos el nodo
Nodo* nuevoNodo(int numero){
    Nodo *nuevo = new Nodo;
    nuevo->dato = numero;
    nuevo->siguiente = nullptr;
    return nuevo;
}
//Función que inserta un nuevo nodo en una lista ordenada de manera ascendente.
void insertar(Nodo* &inicio, Nodo* nuevo){
    Nodo* n = nuevo;
    Nodo* aux1 = inicio;
    Nodo* aux2;
    //Recorrer la lista mientras 'aux1' no sea nulo y el valor del nodo actual sea menor que el valor del nuevo nodo
    while(aux1 != nullptr && aux1->dato < n->dato){
        aux2 = aux1;
        aux1 = aux1->siguiente;
    }
     // Verificar si el nuevo nodo debe ser insertado al principio de la lista
    if(inicio == aux1){
        inicio = n;
    }else{// Si no es el caso, el nuevo nodo debe ser insertado entre 'aux2' y 'aux1
        aux2->siguiente = n;
    }
    // Establecer el puntero siguiente del nuevo nodo para que apunte a 'aux1'
    n->siguiente = aux1;
}
//Función que imprime los elementos de la lista
void imprimirLista(Nodo* inicio){
    Nodo* aux = inicio;
    do{
        if(aux->siguiente!=nullptr){
            cout<<aux->dato<<", ";
        }else{
            cout<<aux->dato;
        }
        aux = aux->siguiente;
    }while (aux != nullptr);
}
//Función para saber si ya existe un mismo dato en la lista
bool buscarDato(Nodo* inicio, int valor){
    Nodo* aux = inicio;
    bool band = false; //Se declara una bandera para saber si encontramos el número a buscar
    while(aux != nullptr && !band){
        if(aux->dato == valor){
            band = true; //Si se encuentra el número entonces la bandera se vuelve verdadera
            break;
        }else{
            aux = aux->siguiente; 
        }
    }
    return band; //Regresamos el valor de la bandera
}
//Función que convierte una cadena de dígitos en un número
int cadAEntero(string numero){
	int i=0, entero=0, signo = 1;
    if(numero[0] == '-'){
        signo = -1;
        i = 1;
    }
	while(numero[i]!='\0'){
        //A la variable entero se le asigna el digito que tiene la cadena en esa posición
		entero=10*entero + (numero[i]-'0');
		i++;
	}
	return entero * signo;
}
//Función que verificas si los caracteres contenidos en una cadena son números
bool verificarNumero(string numeros){
	int band=false; //Se inicializa una bandera en falso
	int i=0;
    if(numeros[0] == '-'){
        i=1;
    }
	do{
		if(numeros[i]<'0' || numeros[i]>'9'){
			return band=true; //Si encuentra un caracter que no sea un digito la bandera se vuelve verdadera
		}else{
            band=false;
        }
		i++;
	}while(numeros[i]!='\0');
	return band;
}
//Función para hacer la union de listas
Nodo* unionListas(Nodo* inicio1, Nodo* inicio2){
    Nodo* listaU = nullptr;
    Nodo* aux1 = inicio1;
    Nodo* aux2 = inicio2;
    while (aux1 != nullptr){
        //Primero se insertan todos los elementos de la primer lista a una tercera lista la cual contendra la unión
        insertar(listaU, nuevoNodo(aux1->dato));
        aux1 = aux1->siguiente;
    }
    while (aux2 != nullptr){
        //Prguntamos si los datos que estan en la tercer lista es igual a algun dato de la segunda lista
        if(!buscarDato(listaU, aux2->dato)){
            //si el dato de la segunda lista no es igual al de la tercer lista entonces se inserta el elemento de la segunda lista en la tercer lista
            insertar(listaU, nuevoNodo(aux2->dato));
        }
        aux2 = aux2->siguiente;
    }
    return listaU;
}
//Función para hacer la intersección de listas
Nodo* interseccionListas(Nodo* inicio1, Nodo* inicio2){
    Nodo* listaI = nullptr;
    Nodo* aux1 = inicio1;
    Nodo* aux2 = inicio2;
    while(aux2 != nullptr){
        //Se busca si un elemento de la lista dos se encuentra en la lista 1
        if(buscarDato(aux1, aux2->dato)){
            //Si lo encuentra entonces ese elemento lo inserta en una tercer lista
            insertar(listaI, nuevoNodo(aux2->dato));
        }
        aux2 = aux2->siguiente;
    }
    return listaI;
}
//Función para encontrar la diferencia de la lista
Nodo* diferenciaListas(Nodo* inicio1, Nodo* inicio2){
    Nodo* listaD = nullptr;
    Nodo* aux1 = inicio1;
    Nodo* aux2 = inicio2;
    while(aux1 != nullptr){
        //Se buscan los elementos que pertenezcan a la lista 1 pero no a la 2
        if(!buscarDato(aux2, aux1->dato)){
            //Si encuentra elementos entonces los inserta en una tercer lista
            insertar(listaD, nuevoNodo(aux1->dato));
        }
        aux1 = aux1->siguiente;
    }
    return listaD;
}
//Función que elimina todos los elementos de una lista
void vaciarLista ( Nodo* inicio){
	Nodo* aux=inicio;
	while(aux!=nullptr){
        Nodo* aux2=aux->siguiente;
        delete aux;
        aux=aux2;
    }
}
//Función que imprime las opciones del menú
void opcionesMenu(){
    cout<<"\tIngresa la opcion que deseas realizar. \n\n";
    cout<<"1. Insertar lista 1. \n";
    cout<<"2. Insertar lista 2. \n";
    cout<<"3. UNION. \n";
    cout<<"4. INTERSECCION. \n";
    cout<<"5. DIFERENCIA. \n";
    cout<<"6. Salir. \n";
}
//Función que pausa el programa hasta que se presione una tecla
void volverMenu(){
    cout<<"\nPresione enter para volver al menu...";
    _getch(); //Esta función espera a que se presione una tecla para continuar con la ejecución del programa
   system("cls");  //Esta función limpia la pantalla de la consola
}
//Función en la que se hacen todas tareas del menu
void menu(int opcionMenu, Nodo* &inicio1, Nodo* &inicio2, Nodo* &listasUnidas, Nodo* &listasInter, Nodo* &listasDifer){
    int numero, numDatos;
    int i;
    int band=0;
    string vNum;
    switch (opcionMenu){
    case 1:
        {
        system("cls");
        cout<<"\t1. Insertar lista 1. \n\n";
        cout<<"Cuantos datos deseas ingresar: ";
        getline(cin, vNum);
        numDatos = cadAEntero(vNum);
        while (verificarNumero(vNum) || numDatos<1){
            if(verificarNumero(vNum)){
                cout<<"Solo ingrese numeros enteros (y sin espacios): ";
                getline(cin, vNum);
                numDatos = cadAEntero(vNum);
            }else if(numDatos<1){
                cout<<"Debe ingresar al menos 1 numero: ";
                getline(cin, vNum);
                numDatos = cadAEntero(vNum);
            }
        }
        i=0;
        do{
            cout<<"Ingrese el numero a la lista: ";
            getline(cin, vNum);
            numero = cadAEntero(vNum);
            while (verificarNumero(vNum) || buscarDato(inicio1, numero)){
                if(verificarNumero(vNum)){
                    cout<<"Solo ingrese numeros enteros (y sin espacios): ";
                    getline(cin, vNum);
                    numero = cadAEntero(vNum);
                }else if(buscarDato(inicio1, numero)){
                    cout<<"Ese dato ya esta registrado, por favor agrega otro: ";
                    getline(cin, vNum);
                    numero = cadAEntero(vNum);
                }
            }
            insertar(inicio1, nuevoNodo(numero));
            i++;
        }while(i<numDatos);
        cout<<"\nLa lista es: {";
        imprimirLista(inicio1);
        cout<<"}\n";
        volverMenu();
        }
        break;

    case 2:
        {
        system("cls");
        cout<<"\t2. Insertar lista 2. \n\n";
        cout<<"Cuantos datos deseas ingresar: ";
        getline(cin, vNum);
        numDatos = cadAEntero(vNum);
        while (verificarNumero(vNum) || numDatos<1){
            if(verificarNumero(vNum)){
                cout<<"Solo ingrese numeros enteros (y sin espacios): ";
                getline(cin, vNum);
                numDatos = cadAEntero(vNum);
            }else if(numDatos<1){
                cout<<"Debe ingresar al menos 1 numero: ";
                getline(cin, vNum);
                numDatos = cadAEntero(vNum);
            }
        }
        i=0;
        do{
            cout<<"Ingrese el numero que deseas ingresar a la lista: ";
            getline(cin, vNum);
            numero = cadAEntero(vNum);
            while (verificarNumero(vNum) || buscarDato(inicio2, numero)){
                if(verificarNumero(vNum)){
                    cout<<"Solo ingrese numeros enteros (y sin espacios): ";
                    getline(cin, vNum);
                    numero = cadAEntero(vNum);
                }else if(buscarDato(inicio2, numero)){
                    cout<<"Ese dato ya esta registrado, por favor agrega otro: ";
                    getline(cin, vNum);
                    numero = cadAEntero(vNum);
                }
            }
            insertar(inicio2, nuevoNodo(numero));
            i++;
        }while(i<numDatos);
        cout<<"\nLa lista es: {";
        imprimirLista(inicio2);
        cout<<"}\n";
        volverMenu();
        }
        break;

    case 3:
        {
        system("cls");
        cout<<"\t3. UNION de listas. \n";
        if(inicio1 == nullptr && inicio2 == nullptr){
            cout<<"\nPrimero llene correctamente las listas.\n";
        }else if(inicio1 == nullptr){
            cout<<"\nLa lista 1 esta vacia\n";
            cout<<"\nLa lista 2 es: {";
            imprimirLista(inicio2);
            cout<<"}\n";
            cout<<"\nLa union es: {";
            imprimirLista(inicio2);
            cout<<"}\n";
        }else if(inicio2 == nullptr){
            cout<<"\nLa lista 1 es: {";
            imprimirLista(inicio1);
            cout<<"}\n";
            cout<<"\nLa lista 2 esta vacia\n";
            cout<<"\nLa union es: {";
            imprimirLista(inicio1);
            cout<<"}\n";
        }else{
            listasUnidas = unionListas(inicio1, inicio2);
            cout<<"\nLa lista 1 es: {";
            imprimirLista(inicio1);
            cout<<"}\n";
            cout<<"\nLa lista 2 es: {";
            imprimirLista(inicio2);
            cout<<"}\n";
            cout<<"\nLa union es: {";
            imprimirLista(listasUnidas);
            cout<<"}\n";
        }
        volverMenu();
        }
        break;

    case 4:
        {
        system("cls");
        cout<<"\t4. INTERSECCION de listas. \n";
        if(inicio1 == nullptr || inicio2 == nullptr){
            cout<<"\nPrimero llene correctamente las listas.\n";
        }else{
            listasInter = interseccionListas(inicio1, inicio2);
            cout<<"\nLa lista 1 es: {";
            imprimirLista(inicio1);
            cout<<"}\n";
            cout<<"\nLa lista 2 es: {";
            imprimirLista(inicio2);
            cout<<"}\n";
            if(listasInter==nullptr){
                cout<<"\nNo existe una interseccion entre listas\n";
            }else{
                cout<<"\nLa interseccion es: {";
                imprimirLista(listasInter);
                cout<<"}\n";
            }
        }
        volverMenu();
        }
        break;
        
    case 5:
        {
        system("cls");
        cout<<"\t5. DIFERENCIA de listas. \n";
        if(inicio1 == nullptr){
            cout<<"\nPrimero llene correctamente las listas.\n";
        }else if(inicio2 == nullptr){
            cout<<"\nLa lista 1 es: {";
            imprimirLista(inicio1);
            cout<<"}\n";
            cout<<"\nLa lista 2 esta vacia\n";
            cout<<"\nLa diferencia es: {";
            imprimirLista(inicio1);
            cout<<"}\n";
        }else{
            listasDifer = diferenciaListas(inicio1, inicio2);
            cout<<"\nLa lista 1 es: {";
            imprimirLista(inicio1);
            cout<<"}\n";
            cout<<"\nLa lista 2 es: {";
            imprimirLista(inicio2);
            cout<<"}\n";
            if(listasDifer==nullptr){
                cout<<"\nNo existe una diferencia entre listas\n";
            }else{
                cout<<"\nLa diferencia es: {";
                imprimirLista(listasDifer);
                cout<<"}\n";
            }
        }
        volverMenu();
        }
        break;

    case 6:
        {
        cout<<"Saliendo del programa...\n";
        vaciarLista(inicio1);
        vaciarLista(inicio2);
        vaciarLista(listasUnidas);
        vaciarLista(listasInter);
        vaciarLista(listasDifer);
        }
        break;

    default:
        system("cls");
        cout<<"INGRESA UNA OPCION CORRECTA.\n\n";
        break;
    } 
}

int main(){
    //Los inicios de todas las listas que vamos a ocupar se declara con el valor NULL
    Nodo* inicio1 = nullptr;
    Nodo* inicio2= nullptr;
    Nodo* listasUnidas = nullptr;
    Nodo* listasInter = nullptr;
    Nodo* listasDifer = nullptr;
    int opcionMenu;
    string opcion;
    do{
        opcionesMenu();
        cout<<"Opcion: ";
        getline(cin, opcion);
        while (verificarNumero(opcion)){
            cout<<"Solo ingrese numeros enteros del 1 al 6 (y sin espacios): ";
            getline(cin, opcion);
        }
        opcionMenu = cadAEntero(opcion);
        menu(opcionMenu, inicio1, inicio2, listasUnidas, listasInter, listasDifer);

    }while( opcionMenu!= 6);
    
    return 0;
}