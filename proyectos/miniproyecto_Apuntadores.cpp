#include<iostream>
#include<cstring> //añadimos esta biblioteca para usar la funcion srtcasecmp
using namespace std;

//Función que verifica si la frase está vacía
int frase_Vacia(char *frase){
    if(*frase == '\0'){
        return 0; //Si la frase está vacía devuelve 0
    }
    for (int i=0; i<strlen(frase); i++){    
        if(!isspace( *(frase+i) ) ){
         return 1; //Si la frase no está vacía devuelve 1
        }
    }
    return 0;
}

//Función para contar las palabras de la frase
int contar_palabras(char *frase, int tamano){
    int contador=0;
    for(int i=0; i<tamano; i++){
        //Si encuentra una letra el indice se incrementa hasta que se termine la palabra 
        if(*(frase+i)!=' '){
            do{
                i++;
            }while(*(frase+i)!=' ' && *(frase+i) != '\0');
            contador+=1; //Incrementamos el contador cada que se encuentra una nueva palabra
        }
    }
    return contador; //Devuelve el número de palabras en la frase
}

//Función para reemplazar espacios con caracteres nulos en la frase
void espacios_Nulos(char *frase, int tamano_frase){
    for(int i=0; i<tamano_frase; i++){
        if(*(frase+i)==' '){
            *(frase+i)='\0'; //Reemplazamos los espacios por el carácter nulo para dividir la frase por palabras
        }   
    }

 }

//Función para almacenar cada palabra de la frase en un array de punteros
void almacenar_Palabra(char *array_Ptr[], char *frase, int tamano_Frase){
    int contador=0;
    for(int i=0; i<tamano_Frase; i++){
        if (*(frase+i)!='\0'){
            array_Ptr[contador] = &frase[i]; // Guardamos la dirección del siguiente carácter después de encontrar un carácter nulo
            contador++;
            do{
                i++;
            }while(*(frase+i)!='\0');
        }     
    }
}

//Algoritmo Quick Sort utilizado para ordenar el array alfabéticamente
void quick_Sort(char *array_Ptr[], int inicio, int final) {
    if (inicio < final) {
        char *pivote = array_Ptr[final]; //Elegimos el último elemento como pivote
        int i = inicio - 1; 

        for (int j = inicio; j <= final - 1; j++) {
            //Utilizamos la función strcasecmp para comparar las dos palabras sin distinguir entre mayúsculas y minúsculas
            if ( strcasecmp(array_Ptr[j], pivote) < 0 ) {
                i++; 
                swap(array_Ptr[i], array_Ptr[j]); //Con la función swap intercambiamos los elementos del array
            }
        }
        swap(array_Ptr[i+1], array_Ptr[final]);
        int indice_pivote = i + 1; 
        //Llamadas recursivas para ordenar los subarreglos del array
        quick_Sort(array_Ptr, inicio, indice_pivote - 1);
        quick_Sort(array_Ptr, indice_pivote + 1, final);
    }
} 

//Función para imprimir el array
void imprimir_Array(char *array_Ptr[], int tamano_Array){
    for(int i=0; i<tamano_Array; i++){
        cout<<array_Ptr[i]<<endl; //Se imprime cada elemento de array en forma de lista
    }
}

int main(){
    char frase[150];
    //Se solicita al usuario que ingrese una frase hasta que no esté vacía
    do{
        cout<<"Ingresa una frase: ";
        cin.getline(frase, 150);
    }while( frase_Vacia(frase) == 0 );

    int tamano_Frase=strlen(frase);
    int numero_Palabras=contar_palabras(frase, tamano_Frase);
    char *array_Ptr[numero_Palabras];
    
    //Se llama la función para reemplazar espacios con caracteres nulos y despues almacenar las palabras en el array
    espacios_Nulos(frase, tamano_Frase);
    almacenar_Palabra(array_Ptr, frase, tamano_Frase);
    //Se llama la función para ordenar el array de punteros alfabéticamente
    quick_Sort(array_Ptr, 0, numero_Palabras-1);
    //Imprimir el array ordenado
    cout<<"\nEl array ordenado es el siguiente: \n";
    imprimir_Array(array_Ptr, numero_Palabras);
    return 0;
}