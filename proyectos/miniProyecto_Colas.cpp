//Angel Jonathan Puch Hernandez & Jose Luis Silva Gomez
#include<iostream> 
#include<conio.h> // Librería para funciones de consola
#include <iomanip> // Librería para manipulación de la salida
using namespace std;

// Función para volver al menú principal
void volverMenu(){
    cout<<"Presione para continuar..."; 
    getch(); // Espera a que el usuario presione una tecla
    system("cls"); // Limpia la pantalla de la consola
}

// Función para verificar si una cadena contiene solo números
bool verificarNumero(string numeros){
    int band=false; // Bandera para indicar si hay caracteres no numéricos
    int i=0; // Índice para recorrer la cadena
    do{
        if(numeros[i]<'0' || numeros[i]>'9'){ // Si el carácter no es un número
            return band=true; // Se marca la bandera y se sale de la función
        }else{
            band=false; // Si es un número, se reinicia la bandera
        }
        i++; // Se incrementa el índice para pasar al siguiente carácter
    }while(numeros[i]!='\0'); // Se repite hasta el final de la cadena
    return band; // Se devuelve el valor de la bandera
}

// Función para convertir una cadena a un número entero
int cadAEntero(string numero){
    int i = 0, entero = 0; // Índice y variable para almacenar el número
    while(numero[i]!='\0'){ // Mientras no se llegue al final de la cadena
        entero=10*entero + (numero[i]-'0'); // Se convierte el carácter a número y se agrega al entero
        i++; // Se pasa al siguiente carácter
    }
    return entero; // Se devuelve el número entero
}

// Función para pedir al usuario que ingrese solo números válidos
void pedirNumeros(string &opcionTemporal){
    while (verificarNumero(opcionTemporal)){ // Mientras la cadena contenga caracteres no numéricos
        cout<<"Solo Ingrese numeros validos: "; // Se solicita al usuario que ingrese números válidos
        getline(cin, opcionTemporal); // Se obtiene la entrada del usuario
    }
}

// Función para verificar si la opción ingresada por el usuario es válida
void verificarOpcion(string &opcionTemporal){
    bool band = false; // Bandera para indicar si la opción es válida
    while(!band){
        if(opcionTemporal.size() > 1){ // Si la cadena tiene más de un carácter
            cout<<"Ingresa una opcion valida: "; // Se solicita al usuario que ingrese una opción válida
            getline(cin, opcionTemporal); // Se obtiene la entrada del usuario
        }else if(opcionTemporal[0] != '0' && opcionTemporal[0] != '1'){ // Si la opción no es '0' ni '1'
            cout<<"Ingresa una opcion valida: "; // Se solicita al usuario que ingrese una opción válida
            getline(cin, opcionTemporal); // Se obtiene la entrada del usuario
        }else{
            band =true; // Si la opción es válida, se marca la bandera y se sale de la función
        }
    }
}

// Función para verificar si una cadena contiene al menos un carácter distinto de espacio
bool verificarCadena(string  & opcionTemporal){
    if(opcionTemporal.empty()) return false; // Si la cadena está vacía, se devuelve falso
    for(int i=0; i<opcionTemporal.size(); i++){ // Se recorre la cadena
        if(!isspace(opcionTemporal[i])) return true; // Si se encuentra un carácter distinto de espacio, se devuelve verdadero
    }
    return false; // Si la cadena solo contiene espacios, se devuelve falso
}

// Función para pedir al usuario que ingrese un nombre válido
void pedirNombre(string &opcionTemporal){
    while(!verificarCadena(opcionTemporal)){ // Mientras la cadena esté vacía o solo contenga espacios
        cout<<"Ingresa un nombre valido: "; // Se solicita al usuario que ingrese un nombre válido
        getline(cin, opcionTemporal); // Se obtiene la entrada del usuario
    }
}

// Estructura para representar la información de un cliente
struct cliente{
    string nombre;
    int edad;
    bool esMujer;
    bool discapacidad;
    bool embarazada;
};

// Estructura de un nodo para una lista enlazada
struct nodo{
    cliente informacion;
    nodo *siguiente;
};

// Función para solicitar al usuario la información de un nuevo cliente
void pedirInformacion(cliente &nuevoCliente){
    string datoTemporal; // Variable temporal para almacenar datos
    cout<<"Ingrese el nombre: "; // Se solicita al usuario que ingrese el nombre del cliente
    getline(cin, datoTemporal); // Se obtiene la entrada del usuario
    pedirNombre(datoTemporal); // Se verifica que el nombre sea válido
    nuevoCliente.nombre = datoTemporal; // Se asigna el nombre al nuevo cliente

    cout<<"Ingrese la edad: "; // Se solicita al usuario que ingrese la edad del cliente
    getline(cin, datoTemporal); // Se obtiene la entrada del usuario
    pedirNumeros(datoTemporal); // Se verifica que la edad sea un número válido
    nuevoCliente.edad = cadAEntero(datoTemporal); // Se convierte la edad a entero y se asigna al nuevo cliente

    cout<<"Ingrese el sexo. \n 0.-Hombre. \n 1.-Mujer. \n >"; // Se solicita al usuario que ingrese el sexo del cliente
    getline(cin, datoTemporal); // Se obtiene la entrada del usuario
    verificarOpcion(datoTemporal); // Se verifica que la opción sea válida
    nuevoCliente.esMujer = cadAEntero(datoTemporal); // Se asigna el sexo al nuevo cliente

    cout<<"Tiene algun tipo de discapacidad? \n 0.-No \n 1.-Si \n >"; // Se solicita al usuario que ingrese si tiene discapacidad
    getline(cin, datoTemporal); // Se obtiene la entrada del usuario
    verificarOpcion(datoTemporal); // Se verifica que la opción sea válida
    nuevoCliente.discapacidad = cadAEntero(datoTemporal); // Se asigna la discapacidad al nuevo cliente

    if(nuevoCliente.esMujer == 1){ // Si el cliente es mujer
        cout<<"Esta embarazada? \n 0.-No \n 1.-Si \n >"; // Se solicita al usuario que ingrese si está embarazada
        getline(cin, datoTemporal); // Se obtiene la entrada del usuario
        verificarOpcion(datoTemporal); // Se verifica que la opción sea válida
        nuevoCliente.embarazada = cadAEntero(datoTemporal); // Se asigna el estado de embarazo al nuevo cliente
    }else{
        nuevoCliente.embarazada = 0; // Si el cliente no es mujer, se asigna 0 al estado de embarazo
    }
}

// Función para crear un nuevo nodo de la lista enlazada con un cliente dado
nodo *nuevoNodo(cliente nuevoCliente){
    nodo *nuevo = new nodo; // Se crea un nuevo nodo
    nuevo ->informacion = nuevoCliente; // Se asigna la información del cliente al nodo
    nuevo->siguiente = nullptr; // El siguiente nodo apunta a nulo
    return nuevo; // Se devuelve el nuevo nodo creado
}

// Función para agregar un nuevo cliente al final de la lista enlazada
void agregarCliente(nodo *&inicio, nodo*&fin, nodo *nuevo){
    if(inicio == nullptr){ // Si la lista está vacía
        inicio = nuevo; // El inicio y fin de la lista apuntan al nuevo nodo
        fin = nuevo;
    }else{ // Si la lista no está vacía
        fin->siguiente = nuevo; // El siguiente del último nodo apunta al nuevo nodo
        fin = nuevo; // El nuevo nodo se convierte en el último nodo
    }
}

// Función para agregar un nuevo cliente con discapacidad al principio de la lista enlazada
void agregarDiscapacidad(nodo *&inicio, nodo*&fin, nodo *nuevo){
    if(inicio == nullptr){ // Si la lista está vacía
        inicio = nuevo; // El inicio y fin de la lista apuntan al nuevo nodo
        fin = nuevo;
    }else if(inicio->informacion.discapacidad != 1){ // Si el primer cliente no tiene discapacidad
        nuevo->siguiente = inicio; // El siguiente del nuevo nodo apunta al primer nodo
        inicio = nuevo; // El nuevo nodo se convierte en el primer nodo
        if ( !inicio->siguiente ) fin = inicio; // Actualiza el puntero fin si el nuevo nodo es el único en la lista
    }else{ // Si el primer cliente tiene discapacidad
        nodo *aux = inicio; // Se crea un nodo auxiliar para recorrer la lista
        nodo *aux2; // Nodo auxiliar para almacenar el nodo anterior al que se va a insertar
        while(aux != nullptr){ // Se recorre la lista
            if(aux->informacion.discapacidad == 1){ // Si el cliente tiene discapacidad
                aux2 = aux; // Se almacena el nodo anterior
                aux = aux->siguiente; // Se pasa al siguiente nodo
            }else{ // Si se encuentra un cliente sin discapacidad
                break; // Se sale del bucle
            }
        }
        aux2->siguiente = nuevo; // El siguiente del nodo anterior al nuevo nodo apunta al nuevo nodo
        nuevo->siguiente = aux; // El siguiente del nuevo nodo apunta al nodo siguiente del nodo anterior
        if ( !aux ) fin = nuevo; // Si aux llegó al final de la lista, actualiza fin a nuevo
    }
}

// Función para agregar un nuevo cliente mayor de 65 años o sin discapacidad al principio de la lista enlazada
void agregarMayores(nodo *&inicio, nodo*&fin, nodo *nuevo){
    if(inicio == nullptr){ // Si la lista está vacía
        inicio = nuevo; // El inicio y fin de la lista apuntan al nuevo nodo
        fin = nuevo;
    }else if(inicio->informacion.discapacidad != 1 && inicio->informacion.edad < 65){ // Si el primer cliente no tiene discapacidad y es menor de 65 años
        nuevo->siguiente = inicio; // El siguiente del nuevo nodo apunta al primer nodo
        inicio = nuevo; // El nuevo nodo se convierte en el primer nodo
        if ( !inicio->siguiente ) fin = inicio; // Actualiza el puntero fin si el nuevo nodo es el único en la lista
    }else{ // Si el primer cliente tiene discapacidad o es mayor de 65 años
        nodo *aux = inicio; // Se crea un nodo auxiliar para recorrer la lista
        nodo *aux2; // Nodo auxiliar para almacenar el nodo anterior al que se va a insertar
        while(aux != nullptr){ // Se recorre la lista
            if(aux->informacion.discapacidad == 1 || aux->informacion.edad >= 65){ // Si el cliente tiene discapacidad o es mayor de 65 años
                aux2 = aux; // Se almacena el nodo anterior
                aux = aux->siguiente; // Se pasa al siguiente nodo
            }else{ // Si se encuentra un cliente sin discapacidad y menor de 65 años
                break; // Se sale del bucle
            }
        }
        aux2->siguiente = nuevo; // El siguiente del nodo anterior al nuevo nodo apunta al nuevo nodo
        nuevo->siguiente = aux; // El siguiente del nuevo nodo apunta al nodo siguiente del nodo anterior
        if ( !aux ) fin = nuevo; // Si aux llegó al final de la lista, actualiza fin a nuevo
    }
}

// Función para agregar un nuevo cliente embarazada al principio de la lista enlazada
void agregarEmbarazadas(nodo *&inicio, nodo*&fin, nodo *nuevo){
    if(inicio == nullptr){ // Si la lista está vacía
        inicio = nuevo; // El inicio y fin de la lista apuntan al nuevo nodo
        fin = nuevo;
    }else if(inicio->informacion.discapacidad != 1 && inicio->informacion.edad < 65 && inicio->informacion.embarazada !=1){ // Si el primer cliente no tiene discapacidad, es menor de 65 años y no está embarazada
        nuevo->siguiente = inicio; // El siguiente del nuevo nodo apunta al primer nodo
        inicio = nuevo; // El nuevo nodo se convierte en el primer nodo
        if ( !inicio->siguiente ) fin = inicio;// Actualiza el puntero fin si el nuevo nodo es el único en la lista
    }else{ // Si el primer cliente tiene discapacidad, es mayor de 65 años o está embarazada
        nodo *aux = inicio; // Se crea un nodo auxiliar para recorrer la lista
        nodo *aux2; // Nodo auxiliar para almacenar el nodo anterior al que se va a insertar
        while(aux != nullptr){ // Se recorre la lista
            if(aux->informacion.discapacidad == 1 || aux->informacion.edad >= 65 || aux->informacion.embarazada == 1){ // Si el cliente tiene discapacidad, es mayor de 65 años o está embarazada
                aux2 = aux; // Se almacena el nodo anterior
                aux = aux->siguiente; // Se pasa al siguiente nodo
            }else{ // Si se encuentra un cliente sin discapacidad, menor de 65 años y no embarazada
                break; // Se sale del bucle
            }
        }
        aux2->siguiente = nuevo; // El siguiente del nodo anterior al nuevo nodo apunta al nuevo nodo
        nuevo->siguiente = aux; // El siguiente del nuevo nodo apunta al nodo siguiente del nodo anterior
        if ( !aux ) fin = nuevo; // Si aux llegó al final de la lista, actualiza fin a nuevo
    }
}

// Función para registrar un nuevo cliente en la lista enlazada
void registrarCliente(nodo *&inicio, nodo *&fin, cliente &nuevoCliente){
    pedirInformacion(nuevoCliente); // Se solicita al usuario la información del nuevo cliente
    if(nuevoCliente.discapacidad == 1){ // Si el cliente tiene discapacidad
        agregarDiscapacidad(inicio, fin, nuevoNodo(nuevoCliente)); // Se agrega al principio de la lista de discapacitados
    }else if(nuevoCliente.edad >= 65){ // Si el cliente es mayor o igual de 65 años
        agregarMayores(inicio, fin, nuevoNodo(nuevoCliente)); // Se agrega al principio de la lista de mayores de 65 años
    }else if(nuevoCliente.embarazada == 1){ // Si el cliente está embarazada
        agregarEmbarazadas(inicio, fin, nuevoNodo(nuevoCliente)); // Se agrega al principio de la lista de embarazadas
    }else{ // Si el cliente no cumple ninguna condición especial
         agregarCliente(inicio ,fin, nuevoNodo(nuevoCliente)); // Se agrega al final de la lista de clientes
    }
}

// Función para imprimir la lista de clientes
void imprimirLista(nodo *inicio){
    nodo *aux = inicio; // Se crea un nodo auxiliar para recorrer la lista
    int numCliente = 0; // Variable para contar el número de cliente
    while(aux != nullptr){ // Mientras no se llegue al final de la lista
        cout<<"\t Cliente "<<++numCliente<<"\n"; // Se muestra el número de cliente
        cout << "+------------------------------------+\n"; // Se imprime una línea divisoria
        cout<<"| Nombre:"<< setw(28)<<aux->informacion.nombre<<"|\n"; // Se muestra el nombre del cliente
        cout<<"| Edad:"<< setw(30)<<aux->informacion.edad<<"|\n"; // Se muestra la edad del cliente
        if(aux->informacion.discapacidad == 1){ // Si el cliente tiene discapacidad
            cout<<"| Discapacidad:"<<setw(22)<<"Si"<<"|\n"; // Se muestra que tiene discapacidad
        }else{ // Si el cliente no tiene discapacidad
            cout<<"| Discapacidad:"<<setw(22)<<"No"<<"|\n"; // Se muestra que no tiene discapacidad
        }
        if(aux->informacion.esMujer == 1){ // Si el cliente es mujer
            if(aux->informacion.embarazada == 1){ // Si el cliente está embarazada
                cout << "| Embarazada:" << setw(24) << "Si" << "|\n"; // Se muestra que está embarazada
            }else{ // Si el cliente no está embarazada
                cout << "| Embarazada:" << setw(24) << "No" << "|\n"; // Se muestra que no está embarazada
            }
        }
        cout << "+------------------------------------+\n\n"; // Se imprime una línea divisoria
        aux = aux->siguiente; // Se pasa al siguiente nodo
    }
}

// Función para liberar la memoria de los nodos de la lista enlazada
void borrarDatos(nodo *&inicio){
    nodo* aux=inicio; // Se crea un nodo auxiliar para recorrer la lista
	while(aux!=nullptr){ // Mientras no se llegue al final de la lista
        nodo* aux2=aux->siguiente; // Se crea un nodo auxiliar para almacenar el siguiente nodo
        delete aux; // Se libera la memoria del nodo actual
        aux=aux2; // Se pasa al siguiente nodo
    }
}

// Función principal del programa
int main(){
    cliente nuevoCliente; // Variable para almacenar la información de un nuevo cliente
    nodo *inicio = nullptr; // Puntero al inicio de la lista enlazada
    nodo *fin = nullptr; // Puntero al final de la lista enlazada
    string opcionTemporal; // Variable para almacenar la opción ingresada por el usuario
    int opcion; // Variable para almacenar la opción como entero

    do{
        cout<<"1.- Registrar cliente. \n"; // Se muestra la opción para registrar un nuevo cliente
        cout<<"2.- Mostrar lista de clientes. \n"; // Se muestra la opción para mostrar la lista de clientes
        cout<<"3.- Salir. \n"; // Se muestra la opción para salir del programa
        cout<<"> Opcion: "; // Se solicita al usuario que ingrese la opción
        getline(cin, opcionTemporal); // Se obtiene la entrada del usuario
        pedirNumeros(opcionTemporal); // Se verifica que la opción sea válida
        opcion = cadAEntero(opcionTemporal); // Se convierte la opción a entero

        switch (opcion){ // Se realiza una acción dependiendo de la opción seleccionada por el usuario
        case 1: 
            system("cls"); 
            cout<<"\t -Registrar cliente. \n"; // Se muestra el título de la sección para registrar un nuevo cliente
            registrarCliente(inicio, fin, nuevoCliente); // Se registra un nuevo cliente
            cout<<"Se ha almacenado la informacion correctamente. \n"; // Se muestra un mensaje de éxito
            volverMenu(); 
            break; 
        case 2: 
            system("cls"); 
            if(inicio == nullptr){ // Si la lista está vacía
                cout<<"Aun no hay datos para mostrar. \n"; // Se muestra un mensaje indicando que no hay datos
            }else{ // Si la lista no está vacía
                imprimirLista(inicio); // Se muestra la lista de clientes
            }
            volverMenu(); 
            break; 
        case 3: 
            cout<<"Saliendo... \n"; // Se muestra un mensaje indicando que se está saliendo del programa
            borrarDatos(inicio); // Se libera la memoria de los nodos de la lista enlazada
            break; 
        default: // Si la opción ingresada no es válida
            system("cls"); 
            cout<<"Ingresa una opcion valida. \n\n"; // Se muestra un mensaje indicando que la opción ingresada no es válida
            break; 
        }
    }while(opcion != 3); // Se repite el bucle hasta que se seleccione la opción 3 (Salir)

    return 0;
}