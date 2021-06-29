#include <NTL/ZZ.h>
#include <iostream>
#include "./headers/RSA.h"
#include "headers/functions.h"

#include <vector>
// g++ -g -O2 -std=c++11 -pthread -march=native "$string/$file" -o "$string/$output" -lntl -lgmp -lm

using std::cin;
using std::cout;
using std::endl;

int main()
{
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-( )abcdefghijklmnopqrstuvwxyz<>*1234567890";
    cout<<"\nEmisor\n";RSA Emisor(128, alpha);
    cout<<"\nReceptor\n";RSA Receptor(128, alpha);

    string mensaje;
    cout << "\nIngrese el mensaje a ser cifrado: ";
    getline(cin, mensaje);
    ZZ ea=Emisor.e;
    ZZ Na=Emisor.N;
    ZZ eb=Receptor.e;
    ZZ Nb=Receptor.N;
    //Emisor cifra
    string mensajeCifrado = Emisor.cypher(mensaje,eb,Nb);
    cout << "El mensajeCifrado es: " << mensajeCifrado << endl;
    //Receptor decifra
    string mensajeDecifrado = Receptor.decypher(mensajeCifrado,ea,Na);
    cout << "El mensajeDecifrado es: " << mensajeDecifrado << endl;
}
