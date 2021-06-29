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
    //nuestro abecedario
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-( )abcdefghijklmnopqrstuvwxyz<>*1234567890";
    string firma="Sebas Sebas2 Fabian Hoaquin Frank Sebas Sebas2 Fabian Hoaquin Frank Sebas Sebas2 Fabian Hoaquin Frank";
    cout<<"\nEmisor\n";RSA Emisor(1024, alpha,firma);
    cout<<"\nReceptor\n";RSA Receptor(1024, alpha,firma);

    string mensaje;
    cout << "\nIngrese el mensaje a ser cifrado: ";
    getline(cin, mensaje);
    //claves publicas
    ZZ ea=Emisor.e;
    ZZ Na=Emisor.N;
    ZZ eb=Receptor.e;
    ZZ Nb=Receptor.N;
    bool WithSig=true;
    //Emisor cifra
    //string mensajeCifrado = Emisor.cypher(mensaje,eb,Nb,WithSig);
    vector<string>messagecif=Emisor.cypherwithsignature(mensaje,eb,Nb);
    //cout << "El mensajeCifrado es: " << mensajeCifrado << endl;
    cout << "El mensajeCifrado es: " << messagecif.at(0)<<"\nfirma:\n"<<messagecif.at(1) << endl;
    //Receptor decifra
    //string mensajeDecifrado = Receptor.decypher(mensajeCifrado,ea,Na,WithSig);
    vector<string>messagedec=Receptor.decypherwithsignature(messagecif,ea,Na);
    //cout << "El mensajeDecifrado es: " << mensajeDecifrado << endl;
    cout<<"\nMensaje:\n"<<messagedec.at(0)<<"\nfirma\n"<<messagedec.at(1)<<endl;
}
