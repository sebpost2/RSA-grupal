#include <NTL/ZZ.h>
#include <iostream>
#include "./headers/receiver.h"
#include "./headers/source.h"
#include "headers/functions.h"

#include <vector>
// g++ -g -O2 -std=c++11 -pthread -march=native "$string/$file" -o "$string/$output" -lntl -lgmp -lm

using std::cin;
using std::cout;
using std::endl;

int main()
{
    string alpha = "abcdefghijklmnopqrstuvwxyz ";
    receiver myReceiver(ZZ(64), alpha);
    source mySource(myReceiver.e, myReceiver.N, alpha);

    string mensaje;
    cout << "Ingrese el mensaje a ser cifrado: ";
    getline(cin, mensaje);
    string mensajeCifrado = mySource.cypher(mensaje);
    cout << "El mensajeCifrado es: " << mensajeCifrado << endl;
    string mensajeDecifrado = myReceiver.decypher(mensajeCifrado);
    cout << "El mensajeDecifrado es: " << mensajeDecifrado << endl;
}
