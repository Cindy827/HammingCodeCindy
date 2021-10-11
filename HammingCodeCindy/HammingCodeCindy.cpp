// HammingCode2020.cpp 
/* Este algoritmo es usado para la correccion de bits regido por un aformula
    2^p >= p+1+1 donde i=bits de inofrmacion y p=cantidad de bits de paridad */
#include <iostream>
#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>   
#include <math.h>     
#include <malloc.h>
#include <cstring>
#include <Windows.h>
using namespace std;

//FUNCION GENERAL
void ingresoCodigo();                                                                         //Ingreso y creacion de codigo hamming para comparar 
void imprimeHamming(int longTotalMsg, int arrBparInfo[]);                                     //Imprime los bits de paridad e informacion jutnos en orden correspondiente
void crearError(int longTotalMsg, int arrBparInfo[], int p, int arrBparInfoInvertido[]);      //Ingresa el error en el arreglo de bits

//FUNCION METODO PAR
void solParidad(int p, int longTotalMsg, int arrBparInfo[], int arrBparinfoInvert[]);         //Solucionador por paridad
void buscaErrorPar(int p, int longTotalMsg, int arrBparInfo[], int arrBparInfoInvertido[]);   //Busqueda del error par

//FUNCION METODO IMPAR
void solImparidad(int p, int longTotalMsg, int arrBparInfo[], int arrBparInfoInvertido[]);    //Solucionador por imparidad
void buscaErrorImpar(int p, int longTotalMsg, int arrBparInfo[], int arrBparInfoInvertido[]); //Busqueda del error impar

int main()
{
    printf("                                             .:Examen codigo Haming:.\n\n");

    ingresoCodigo();
}

void ingresoCodigo() {
    int  opcion = 0, longitud = 0, suma = 0, condicion1 = 0, contador = 0;
    int  bitsInfo = 0;                //catidad de bits de informacion
    int  longTotalMsg = 0;            //longitud total del mensaje (bits de paridad y bits de informacion)
    int  p = 0, k = 0, j = 0;         //
    int  arrBparInfo[1000];           //arreglo para los bits de paridad e informacion juntos  
    int  arrBparInfoInvertido[1000];  //
    int  arrBit[1000];                //arreglo del codigo binario que introdujo el usuario antes arrBinario

    printf("Ingresa la longitud de su arreglo\n"); //primero ingresar numero binario
    scanf_s("%i", &longitud);
    //---------------SE LLENA EL ARREGLO CON PUROS CEROS------------------------------------------------------------------------------------
    for (int i = 0; i < longitud; i++) {
        arrBparInfo[i] = 0;
    }
    //---------------OBTENCION DE BITS EN ARREGLO-------------------------------------------------------------------------------------------
    printf("\nIngrese cada bit\n");
    for (int i = 0; i < longitud; i++) {//quitar el -1 a longitud MODIFICAR
        scanf_s("%i", &arrBit[i]);
        //printf("\nposicion %i bit %i\n", i, bit);
    }
    printf("\n\nEste es el areglo de bits que ingreso: ");
    for (int x = 0; x < longitud; x++) {
        cout << arrBit[x];
    }
    //---------------CALCULAMOS VALOR DE BITS DE PARIDAD "P"--------------------------------------------------------------------------------
    bitsInfo = longitud;

    while (condicion1 <= suma) {
        //printf("\n\nSi entra al ciclo while %i",p);

        condicion1 = pow(2, p);      //2^p
        suma = ((p + bitsInfo) + 1); //p + i + 1

        p++; //printf("\n\nEntrada de ciclo while, valor de p: %i", p); //printf("\n%i < %i", condicion1, suma);

        if (condicion1 > suma) {
            p--;
        }
    }
    longTotalMsg = p + bitsInfo;

    printf("\n\nLa funcion 2^p >= p + i + 1 se cumple con exito: %i >= %i", condicion1, suma);
    printf("\n\nLa cantidad de bits de paridad es: %i    La cantidad de bits de informacion es: %i    La longitud total del arreglo es:%i\n", p, bitsInfo, (p + bitsInfo));
    printf("\n-----------------------------------------------------------------------------------------------------------------------\n\n");//division en pantalla

    //---------------LONGITUD TOTAL DEL MENSAJE---------------------------------------------------------------------------------------------
    longTotalMsg = p + bitsInfo;
    int LM = longTotalMsg;
    //printf("\nFun ingreso codigo\nvalor de p: %i, long Total msg: %i\n", p, longTotalMsg);
    //---------------INVERTIMOS EL ARREGLO DE BITS OBTENIDO---------------------------------------------------------------------------------
    for (int i = 0; i <= longTotalMsg - 1; i++) {
        arrBparInfoInvertido[i] = LM - 1;
        LM = LM - 1;
        //cout << "\n\n\nWACHAAAAAAAA " << arrBparInfoInvertido[i];
    }

    int sigBI = bitsInfo;
    for (int i = longTotalMsg; i >= 0; i--) {
        if (pow(2, k) == j) {
            //arrBparInfo[i] = 2;
            //arrBparInfo[k] = j - 1;
            k++;
        }
        else {
            arrBparInfo[i] = arrBit[sigBI];
            sigBI--;
        }
        j++;
    }
    imprimeHamming(longTotalMsg, arrBparInfo);
    //--------------------------------------------------------------------------------------------------------------------------------------
    printf("Seleccione la opcion que desea ejecutar:\n\n1.-Solucion par\n2.-Solucion impar\n");
    scanf_s("%i", &opcion);

    switch (opcion) {

    case 1://SOLUCION PAR
        solParidad(p, longTotalMsg, arrBparInfo, arrBparInfoInvertido);
        break;

    case 2://SULUCION IMPAR
        solImparidad(p, longTotalMsg, arrBparInfo, arrBparInfoInvertido);
        break;

    default:
        printf("El programador puede comenzar a llorar");
        break;
    }
}

void solParidad(int p, int longTotalMsg, int arrBparInfo[], int arrBparInfoInvertido[]) {//p, longTotalMsg, arrBparInfo, arrBparinfoInvert
    printf("\n-----------------------------------------------------------------------------------------------------------------------\n\n");//division en pantalla
    printf("                                        .:Ha comenzado el solucionador par:.");
    int contador = 0;//printf("\n valor de p: %i, long Total msg: %i\n", p, longTotalMsg);

    for (int x = 0; x <= p - 1; x++) {//pasando por cada uno de los bits de paridad
        contador = -2;
        //printf("\nValor de contador: %i\n", contador);

        for (int y = pow(2, x); y <= longTotalMsg; y = y + 2 * pow(2, x)) {

            for (int z = y; z <= y + pow(2, x) - 1; z++) {
                if (z <= longTotalMsg) {
                    contador = contador + arrBparInfo[arrBparInfoInvertido[z - 1]];//cambiar longTotalMsg por arrBparInfoInvert[z-1]
                }
            }
        }
        int c = pow(2, x);
        if (contador % 2 == 0) {
            arrBparInfo[arrBparInfoInvertido[c - 1]] = 0;
        }
        else {
            arrBparInfo[arrBparInfoInvertido[c - 1]] = 1;
        }
    }

    imprimeHamming(longTotalMsg, arrBparInfo);
    crearError(longTotalMsg, arrBparInfo, p, arrBparInfoInvertido);
    buscaErrorPar(p, longTotalMsg, arrBparInfo, arrBparInfoInvertido);//funcion para solucionar error
}

void solImparidad(int p, int longTotalMsg, int arrBparInfo[], int arrBparInfoInvertido[]) {//p, longTotalMsg, arrBparInfo, arrBparinfoInvert
    printf("\n-----------------------------------------------------------------------------------------------------------------------\n\n");//division en pantalla
    printf("                                        .:Ha comenzado el solucionador Impar:.");
    int contador = 0;//printf("\n valor de p: %i, long Total msg: %i\n", p, longTotalMsg);

    for (int x = 0; x <= p - 1; x++) {//pasando por cada uno de los bits de paridad
        contador = -2;//printf("\nValor de contador: %i\n", contador);
        for (int y = pow(2, x); y <= longTotalMsg; y = y + 2 * pow(2, x)) {
            for (int z = y; z <= y + pow(2, x) - 1; z++) {
                if (z <= longTotalMsg) {
                    contador = contador + arrBparInfo[arrBparInfoInvertido[z - 1]];//cambiar longTotalMsg por arrBparInfoInvert[z-1]
                }
            }
        }
        int c = pow(2, x);
        if (contador % 2 == 0) {
            arrBparInfo[arrBparInfoInvertido[c - 1]] = 1;
        }
        else {
            arrBparInfo[arrBparInfoInvertido[c - 1]] = 0;
        }
    }

    imprimeHamming(longTotalMsg, arrBparInfo);
    crearError(longTotalMsg, arrBparInfo, p, arrBparInfoInvertido);
    buscaErrorPar(p, longTotalMsg, arrBparInfo, arrBparInfoInvertido);//buscaErrorPar();//funcion para solucionar error
}

void imprimeHamming(int longTotalMsg, int arrBparInfo[]) {
    printf("\n\nEl codigo con bits de informacion y bits de paridad en su orden correspondiente es:\n");
    for (int x = 0; x <= (longTotalMsg - 1); x++) {
        printf("%i", arrBparInfo[x]);
    }
    //for (int x = (longTotalMsg - 1); x >= 0; x--) {//recordar que el arreglo se usa invertido para ingresar el error
    //    printf("%i", arrBparInfo[x]);
    //}
}

void crearError(int longTotalMsg, int arrBparInfo[], int p, int arrBparInfoInvertido[]) {//
    int posError = 0;
    //printf("\nDentro de crear error\nEste es el valor de p:%i", p);
    printf("\n-----------------------------------------------------------------------------------------------------------------------\n\n");//division en pantalla
    printf("                                           .:INGRESE EL ERROR:.");
    printf("\nSeleccione una posicioin entre el 0 y el %i para generar el error\n", longTotalMsg - 1);
    scanf_s("%i", &posError);

    if (arrBparInfo[posError] == 1) {
        printf("\nSe ha remplazado la posicion %i que contenia un %i por 0 con exito", posError, arrBparInfo[posError]);
        arrBparInfo[posError] = 0;
    }
    else {
        printf("\nSe ha remplazado la posicion %i que contenia un %i por 1 con exito", posError, arrBparInfo[posError]);
        arrBparInfo[posError] = 1;
    }
    imprimeHamming(longTotalMsg, arrBparInfo);
    printf("\n\n");
}

void buscaErrorPar(int p, int longTotalMsg, int arrBparInfo[], int arrBparInfoInvertido[]) {//p longTotalMsg 
    int contador = 0;
    int codError[100];
    printf("\n-----------------------------------------------------------------------------------------------------------------------\n\n");//division en pantalla
    printf("                                              .:Busqueda Par inicializadda:.\n");
    //printf("\n valor de p: %i, long Total msg: %i\n", p, longTotalMsg);
    printf("\nEl error esta en la posicion: ");
    for (int x = 0; x <= p - 1; x++) {//pasando por cada uno de los bits de paridad
        contador = -2;//printf("\nValor de contador: %i\n", contador);
        for (int y = pow(2, x); y <= longTotalMsg; y = y + 2 * pow(2, x)) {
            for (int z = y; z <= y + pow(2, x) - 1; z++) {
                if (z <= longTotalMsg) {
                    contador = contador + arrBparInfo[arrBparInfoInvertido[z - 1]];//cambiar longTotalMsg por arrBparInfoInvert[z-1]
                }
            }
        }
        printf("%i", contador % 2);
        codError[x] = contador % 2;
    }
    printf("\n");
}

void buscaErrorImpar(int p, int longTotalMsg, int arrBparInfo[], int arrBparInfoInvertido[]) {
    int contador = 0;
    int codError[100];
    for (int x = 0; x <= p - 1; x++) {//pasando por cada uno de los bits de paridad
        contador = -2;//printf("\nValor de contador: %i\n", contador);
        for (int y = pow(2, x); y <= longTotalMsg; y = y + 2 * pow(2, x)) {
            for (int z = y; z <= y + pow(2, x) - 1; z++) {
                if (z <= longTotalMsg) {
                    contador = contador + arrBparInfo[arrBparInfoInvertido[z - 1]];//cambiar longTotalMsg por arrBparInfoInvert[z-1]
                }
            }
        }

        if (contador % 2 == 0) {
            printf("1");
            codError[x] = 1;
        }
        else {
            printf("0");
            codError[x] = 0;
        }
    }
    printf("\n");
}
