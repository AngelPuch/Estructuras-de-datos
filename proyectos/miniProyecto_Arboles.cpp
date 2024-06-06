#include <iostream>
#include <iomanip>
#include<windows.h>
using namespace std;
bool verificarNumero(string numeros){
    int band=false;
    int i=0;
    do{
        if(numeros[i]<'0' || numeros[i]>'9'){
            return band=true;
        }else{
            band=false;
        }
        i++;
    }while(numeros[i]!='\0');
    return band;
}
int cadAEntero(string numero){
    int i = 0, entero = 0;
    while(numero[i]!='\0'){
        entero=10*entero + (numero[i]-'0');
        i++;
    }
    return entero; 
}
void pedirNumeros(string &opcionTemporal){
    while (verificarNumero(opcionTemporal)){ 
        cout<<"Ingresa una numero valido: ";
        getline(cin, opcionTemporal);
    }
}
bool verificarCadena(string  & opcionTemporal){
    if(opcionTemporal.empty()) return false; 
    for(int i=0; i<opcionTemporal.size(); i++){
        if(!isspace(opcionTemporal[i])) return true;
    }
    return false;
}
void pedirCadena(string &opcionTemporal){
    while(!verificarCadena(opcionTemporal)){
        cout<<"Llena este campo: ";
        getline(cin, opcionTemporal);
    }
}

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
int alturaArbol(nodo *arbolRaiz){
    if(!arbolRaiz){
        return 0;
    }else{
        int alturaIzquierdo = alturaArbol(arbolRaiz->izquierdo);
        int alturaDerecho = alturaArbol(arbolRaiz->derecho);
        return 1 + max(alturaIzquierdo, alturaDerecho);
    }
}
int obtenerBalance(nodo *arbolRaiz){
    if(!arbolRaiz) return 0;
    return alturaArbol(arbolRaiz->izquierdo) - alturaArbol(arbolRaiz->derecho);
}
void rotarDerecha(nodo *&arbolRaiz){
    nodo *auxIzquierdo = arbolRaiz->izquierdo;
    nodo *auxDerecho = auxIzquierdo->derecho;
    auxIzquierdo->derecho = arbolRaiz;
    arbolRaiz->izquierdo = auxDerecho;
    alturaArbol(arbolRaiz);
    alturaArbol(auxIzquierdo);
    arbolRaiz = auxIzquierdo;
}
void rotarIzquierda(nodo *&arbolRaiz){
    nodo *auxDerecho = arbolRaiz->derecho;
    nodo *auxIzquierdo = auxDerecho->izquierdo;
    auxDerecho->izquierdo = arbolRaiz;
    arbolRaiz->derecho = auxIzquierdo;
    alturaArbol(arbolRaiz);
    alturaArbol(auxDerecho);
    arbolRaiz = auxDerecho;
}
void rotarIzquierdaDerecha(nodo *&arbolRaiz){
    rotarIzquierda(arbolRaiz->izquierdo);
    rotarDerecha(arbolRaiz);
}
void rotarDerechaIzquierda(nodo *&arbolRaiz){
    rotarDerecha(arbolRaiz->derecho);
    rotarIzquierda(arbolRaiz);
}
void balancear(nodo *&arbolRaiz){
    int equilbrio = obtenerBalance(arbolRaiz);
    if(equilbrio > 1 && obtenerBalance(arbolRaiz->izquierdo) >= 0){
        rotarDerecha(arbolRaiz);
    }else if(equilbrio < -1 && obtenerBalance(arbolRaiz->derecho) <= 0){
        rotarIzquierda(arbolRaiz);
    }else if(equilbrio > 1 && obtenerBalance(arbolRaiz->izquierdo) < 0){
        rotarIzquierdaDerecha(arbolRaiz);
    }else if(equilbrio < -1 && obtenerBalance(arbolRaiz->derecho) > 0){
        rotarDerechaIzquierda(arbolRaiz);
    }
}
void insertarCliente(nodo *&arbolRaiz, nodo *nuevo){
    if(!arbolRaiz){
        arbolRaiz = nuevo;
    }else if(nuevo->informacion.id < arbolRaiz->informacion.id){
        insertarCliente(arbolRaiz->izquierdo, nuevo);
    }else if(nuevo->informacion.id > arbolRaiz->informacion.id){
        insertarCliente(arbolRaiz->derecho, nuevo);
    }
    alturaArbol(arbolRaiz);
    balancear(arbolRaiz);
}
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
nodo *elementoMayor(nodo *arbolRaiz){
    if(!arbolRaiz){
        return nullptr;
    }else if(!arbolRaiz->derecho){
        return arbolRaiz;
    }else{
        return elementoMayor(arbolRaiz->derecho);
    }
}
void eliminarElemento(nodo *&arbolRaiz, int id, bool &encontrado){
    if(!arbolRaiz){
        return ;
    }else if(id < arbolRaiz->informacion.id){
        eliminarElemento(arbolRaiz->izquierdo, id, encontrado);
    }else if(id > arbolRaiz->informacion.id){
        eliminarElemento(arbolRaiz->derecho, id, encontrado);
    }else{
        encontrado = true;
        if(arbolRaiz->izquierdo && arbolRaiz->derecho){
            nodo *mayor = elementoMayor(arbolRaiz->izquierdo);
            arbolRaiz->informacion.id = mayor->informacion.id;
            eliminarElemento(arbolRaiz->izquierdo, mayor->informacion.id, encontrado);
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
    alturaArbol(arbolRaiz);
    balancear(arbolRaiz);
}
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