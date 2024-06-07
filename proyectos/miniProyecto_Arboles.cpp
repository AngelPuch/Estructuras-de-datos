#include <iostream>
#include <iomanip>
#include<windows.h>
using namespace std;
//Función que verifica que una cadena contenga solo números
bool verificarNumero(string numeros){
    int band=false;
    int i=0;
    do{
        if(numeros[i]<'0' || numeros[i]>'9'){
            return band=true; //Si encuentra otro caracter distinto de un numero regresa verdadero
        }else{
            band=false;
        }
        i++;
    }while(numeros[i]!='\0');
    return band;
}
//Función que convierte un string a un tipo de dato entero
int cadAEntero(string numero){
    int i = 0, entero = 0;
    while(numero[i]!='\0'){
        entero=10*entero + (numero[i]-'0');
        i++;
    }
    return entero; 
}
//Función que solicita un número valido al usuario
void pedirNumeros(string &opcionTemporal){
    while (verificarNumero(opcionTemporal)){ 
        cout<<"Ingresa una numero valido: ";
        getline(cin, opcionTemporal);
    }
}
//Función que verifica si una cadena no está vacía y tambien que no contenga solo espacios
bool verificarCadena(string  & opcionTemporal){
    if(opcionTemporal.empty()) return false; //Si esta vacia regresa falso
    for(int i=0; i<opcionTemporal.size(); i++){
        if(!isspace(opcionTemporal[i])) return true; //Si encuentra un caracter diferente de espacio regrsa verdadero
    }
    return false; //En case de que toda la cadena sea espacio regresa falso
}
//Función que solicita una cadena no vacia al usuario
void pedirCadena(string &opcionTemporal){
    while(!verificarCadena(opcionTemporal)){
        cout<<"Llena este campo: ";
        getline(cin, opcionTemporal);
    }
}
//Función que pausa y limpia la consola
void volverMenu(){
    cout<<"\n";
    system("pause");
    system("cls");
}
void menu(){
    cout<<"\t --Menu-- \n";
    cout<<"1.- Agregar cliente.\n";
    cout<<"2.- Mostrar arbol. \n";
    cout<<"3.- Mostrar clientes. \n";
    cout<<"4.- Eliminar cliente. \n";
    cout<<"5.-Salir.\n";
    cout<<"> ";
}
struct cliente{
    int id;
    string nombre;
    string email;
};
struct nodo{
    cliente informacion;
    int altura;
    nodo *izquierdo;
    nodo *derecho;
};
struct arbol{
    nodo *raiz;
};
nodo *crearNodo(cliente nuevoCliente){
    nodo *nuevo = new nodo;
    nuevo->informacion = nuevoCliente;
    nuevo->altura = 1;
    nuevo->izquierdo = nullptr;
    nuevo->derecho = nullptr;
    return nuevo;
}
int altura(nodo *arbolRaiz) {
    if (!arbolRaiz) return 0; // Si el nodo es nulo, la altura es 0
    else return arbolRaiz->altura; // De lo contrario, retorna la altura almacenada en el nodo
}
//Función que calcula la altura de un árbol
void actualizarAltura(nodo *&arbolRaiz){
    arbolRaiz->altura = 1 + max(altura(arbolRaiz->izquierdo), altura(arbolRaiz->derecho));
}
//Función que obtiene el balance del árbol
int obtenerBalance(nodo *arbolRaiz){
    if(!arbolRaiz) return 0;
    return altura(arbolRaiz->izquierdo) - altura(arbolRaiz->derecho);
}
//Función que hace una rotación simple a la derecha
void rotarDerecha(nodo *&arbolRaiz){
    nodo *auxIzquierdo = arbolRaiz->izquierdo; //Almacena el subarbol izquierdo
    nodo *auxDerecho = auxIzquierdo->derecho; //Almacena el subarbol derecho del subarbol izquierdo
    auxIzquierdo->derecho = arbolRaiz; //Coloca el nodo raiz actual como el hijo derecho del subarbol izquierdo
    arbolRaiz->izquierdo = auxDerecho; //Asiga el subarbol derecho del izquierdo como hijo izquierdo del nodo raiz actual
    actualizarAltura(arbolRaiz); //Actualiza la altura del nodo raíz
    actualizarAltura(auxIzquierdo); //Actualiza la altura del subárbol izquierdo
    arbolRaiz = auxIzquierdo; //Asigna el nuevo nodo raíz después de la rotación
}
//Función que hace una rotación simple a la izquierda
void rotarIzquierda(nodo *&arbolRaiz){
    nodo *auxDerecho = arbolRaiz->derecho; //Almacena el subárbol derecho
    nodo *auxIzquierdo = auxDerecho->izquierdo; //Almacena el subárbol izquierdo del subarbol derecho
    auxDerecho->izquierdo = arbolRaiz; //Coloca el nodo raíz actual como el hijo izquierdo del subarbol derecho
    arbolRaiz->derecho = auxIzquierdo; //Asigna el subárbol izquierdo del derecho como el hijo derecho del nodo raíz actual
    actualizarAltura(arbolRaiz);//Actualiza la altura del nodo raíz
    actualizarAltura(auxDerecho);//Actualiza la altura del del subárbol derecho
    arbolRaiz = auxDerecho; //Asigna el nuevo nodo raíz despues de la rotación
}
//Función que hace una rotación doble Izquierda - Derecha   
void rotarIzquierdaDerecha(nodo *&arbolRaiz){
    rotarIzquierda(arbolRaiz->izquierdo);//Primero realiza una rotación simple a la izquierda en el subárbol izquierdo
    rotarDerecha(arbolRaiz);// Luego realiza una rotación simple a la derecha en la raíz actual
}
//Función que hace una rotación doble Derecha - Izquierda
void rotarDerechaIzquierda(nodo *&arbolRaiz){
    rotarDerecha(arbolRaiz->derecho);//Primero realiza una rotación simple a la derecha en el subárbol derecho
    rotarIzquierda(arbolRaiz);//Luego realiza una rotación simple a la izquierda en la raíz actual
}
//Función que balancea el árbol revisando que tipo de rotación se tiene que hacer
void balancear(nodo *&arbolRaiz){
    int equilbrio = obtenerBalance(arbolRaiz); //Calcula el balance del nodo raíz
    if(equilbrio > 1 && obtenerBalance(arbolRaiz->izquierdo) >= 0){ //Si el arbol esta desbalanceado hacia la izquierda y su subárbol izquierdo esta balanceado o inclinado hacia la izquierda
        rotarDerecha(arbolRaiz);
    }else if(equilbrio < -1 && obtenerBalance(arbolRaiz->derecho) <= 0){ //Si el arbol esta desbalanceado hacia la derecha y su subárbol derecho está balanceado o inclinado hacia la derecha 
        rotarIzquierda(arbolRaiz);
    }else if(equilbrio > 1 && obtenerBalance(arbolRaiz->izquierdo) < 0){//Si el árbol esta desbalanceado hacia la izquierda y su subárbol izquierdo esta inclinado hacia la derecha
        rotarIzquierdaDerecha(arbolRaiz);
    }else if(equilbrio < -1 && obtenerBalance(arbolRaiz->derecho) > 0){//Si el árbol esta desbalanceado hacia la derecha y su subárbol derecho esta inclinado hacia la izquierda
        rotarDerechaIzquierda(arbolRaiz);
    }
}
//Función que añade un nuevo cliente al árbol
void insertarCliente(nodo *&arbolRaiz, nodo *nuevo){
    if(!arbolRaiz){
        arbolRaiz = nuevo;
    }else if(nuevo->informacion.id < arbolRaiz->informacion.id){ //Si el id es menor lo añade a la izquierda
        insertarCliente(arbolRaiz->izquierdo, nuevo);
    }else if(nuevo->informacion.id > arbolRaiz->informacion.id){ //Si el id es mayor lo añade a la derecha
        insertarCliente(arbolRaiz->derecho, nuevo);
    }
    actualizarAltura(arbolRaiz); //Actualiza la altura del nodo raíz
    balancear(arbolRaiz);//Llama a la función para balancear el árbol
}
//Función que pide al usuario su información
void pedirInformacion(cliente &nuevoCliente, int id){
    string datoTemporal;
    nuevoCliente.id = id;
    cout<<"Ingrese el nombre del usuario: ";
    getline(cin, datoTemporal);
    pedirCadena(datoTemporal);
    nuevoCliente.nombre = datoTemporal;
    
    cout<<"Ingresa el email del usuario: ";
    getline(cin, datoTemporal);
    pedirCadena(datoTemporal);
    nuevoCliente.email = datoTemporal;
}
//Función que imprime de manera gráfica el árbol con el ID
void imprimirGrafico(nodo *arbolRaiz, int contador){
    if(!arbolRaiz){
        return ;
    }else{
        imprimirGrafico(arbolRaiz->derecho, contador+1);
        for(int i=0; i<contador; i++) 
            cout<<"  ";
        cout<<arbolRaiz->informacion.id<<endl;
        imprimirGrafico(arbolRaiz->izquierdo, contador+1);
    }
}
//Función que imprime la información de todos los usuarios
void mostrarInformacion(nodo *arbolRaiz){
    if(!arbolRaiz){
        return;
    }else{
        mostrarInformacion(arbolRaiz->izquierdo);
        cout<<"┌-----------------------------------┐\n";
        cout<<"|\t Cliente "<<arbolRaiz->informacion.id<<setw(21)<<"| \n";
        cout<<"|-----------------------------------|\n";
        cout<<"| ID:"<<setw(31)<<arbolRaiz->informacion.id<<"| \n";
        cout<<"| Nombre:"<<setw(27)<<arbolRaiz->informacion.nombre<<"| \n";
        cout<<"| Email:"<<setw(28)<<arbolRaiz->informacion.email<<"| \n";
        cout<<"└-----------------------------------┘\n";
        mostrarInformacion(arbolRaiz->derecho);
    }
}
//Función que retorna el elemento mayor del árbol
nodo *elementoMayor(nodo *arbolRaiz){
    if(!arbolRaiz){
        return nullptr;
    }else if(!arbolRaiz->derecho){
        return arbolRaiz;
    }else{
        return elementoMayor(arbolRaiz->derecho);
    }
}
//Función que elimina un cliente por su ID
void eliminarElemento(nodo *&arbolRaiz, int id, bool &encontrado){
    if(!arbolRaiz){ //Si es nulo no se hace nada
        return;
    }else if(id < arbolRaiz->informacion.id){//Si el id a eliminar es menor que el actual busca en la izquierda
        eliminarElemento(arbolRaiz->izquierdo, id, encontrado);
    }else if(id > arbolRaiz->informacion.id){//Si el id a eliminar es mayor que el actual busca en la derecha
        eliminarElemento(arbolRaiz->derecho, id, encontrado);
    }else{//Si el nodo se encontro se hace lo siguiente
        encontrado = true; //Marca que el nodo es encontrado
        if(arbolRaiz->izquierdo && arbolRaiz->derecho){ //Caso en el que el nodo tiene dos hijos
            nodo *mayor = elementoMayor(arbolRaiz->izquierdo); //Encuentra el elemento mayor del subárbol izquierdo
            arbolRaiz->informacion.id = mayor->informacion.id;//Actualiza la información del nodo actual con la del predecesor
            eliminarElemento(arbolRaiz->izquierdo, mayor->informacion.id, encontrado); //Elimina el predecesor del subárbol izquierdo
        }else{ //Caso en el que el nodo tiene un solo hijo o ninguno
            nodo *temporal = arbolRaiz; //Guarda el nodo actual
            if(!arbolRaiz->izquierdo){//Si no tiene un hijo izquierdo, reemplaza el nodo actual por el derecho
                arbolRaiz = arbolRaiz->derecho;
            }else if(!arbolRaiz->derecho){//Si no tiene el hijo derecho, reemplaza el nodo actual por el izquierdo
                arbolRaiz = arbolRaiz->izquierdo;
            }
            delete temporal; //Elimina el nodo
        }
    }
    if(arbolRaiz){
        actualizarAltura(arbolRaiz);//Actualiza la altura del nodo actual 
        balancear(arbolRaiz);//Llama a la función para balancear el árbol
    }
}
//Eliina todos los nodos del árbol
void eliminarArbol(nodo *&arbolRaiz){
    if(!arbolRaiz){
        return;
    }else{
        eliminarArbol(arbolRaiz->izquierdo);
        eliminarArbol(arbolRaiz->derecho);
        delete arbolRaiz;
        arbolRaiz=nullptr;
    }
}
//Gestiona todas las opciones del menú
void opcionesMenu(nodo *&arbolRaiz, cliente &nuevoCliente, int opcion, int &id){
    int contador = 0, idBorrar;
    bool encontrado = false;
    string idBorrarTemp;
    system("cls");
    switch (opcion)
    {
    case 1:
        cout<<"\t 1.- Agregar cliente.\n";
        pedirInformacion(nuevoCliente, ++id);
        insertarCliente(arbolRaiz, crearNodo(nuevoCliente));
        cout<<"Se ha registrado correctamente el usuario. \n";
        volverMenu();
        break;
    case 2:
        cout<<"\t 2.- Mostrar arbol. \n";
        if(!arbolRaiz){
            cout<<"Aun no hay clientes registrados. \n";
        }else{
            imprimirGrafico(arbolRaiz, contador);
            cout<<endl;
        }
        volverMenu();
        break;
    case 3:
        cout<<"\t 3.- Mostrar clientes. \n";
        if(!arbolRaiz){
            cout<<"Aun no hay clientes registrados. \n";
        }else{
            mostrarInformacion(arbolRaiz);    
        }
        volverMenu();
        break;
        case 4:
            cout<<"\t 4.- Eliminar cliente. \n";
            if(!arbolRaiz){
                cout<<"Aun no hay clientes registrados. \n";
            }else{
                cout<<"Ingresa el id del cliente que deseas eliminar: ";
                getline(cin, idBorrarTemp);
                pedirNumeros(idBorrarTemp);
                idBorrar = cadAEntero(idBorrarTemp);
                eliminarElemento(arbolRaiz, idBorrar, encontrado);
                if(encontrado) cout<<"Se ha eliminado correctamente el usuario con ese ID. \n";
                else cout<<"No se ha encontrado ningun usuario con ese ID. \n";
            }
            volverMenu();
            break;
    case 5:
        eliminarArbol(arbolRaiz);
        cout<<"Saliendo... \n";
        break;
    
    default:
        cout<<"Opcion no valida. \n";
        volverMenu();
        break;
    }
}
int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    arbol *nuevoArbol = new arbol;
    nuevoArbol->raiz = nullptr;
    cliente nuevoCliente;
    string opcionTemporal;
    int opcion;
    int id = 0;
    do{
        menu();
        getline(cin, opcionTemporal);
        pedirNumeros(opcionTemporal);
        opcion = cadAEntero(opcionTemporal);
        opcionesMenu(nuevoArbol->raiz, nuevoCliente, opcion, id);
    }while(opcion != 5);
    return 0;
}