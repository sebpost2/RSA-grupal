//#include <NTL/ZZ.h>
#include "../headers/source.h"
#include "../headers/functions.h"
#include <cstring>
#include <iostream>

using std::string;

source::source(ZZ userPublic, ZZ uN, string uAlphabet) :
    publicKey(userPublic), N(uN), alphabet(uAlphabet)
{

}

//cifrado del RSA
string source::cypher(string message)
{
    //std::cout << "Clave publica:\t " << publicKey << std::endl;
    //std::cout << "Esto es N:\t " << N << std::endl;
    int availableDigits = std::to_string((int)alphabet.length()).length();
    int nDigits = (int)zToString(N).length();
    vector<string> temp = stringToVector(vectorToString(stringToVectorIndex(message, availableDigits, alphabet)), nDigits - 1);
    vector<string> tempCypher;
    for (vector<string>::iterator i = temp.begin(); i != temp.end(); i++)
    {
        string temp1 = *i;
        std::cout << "temp1:\t" << temp1 << std::endl;
        std::cout << "temp1.c_str():\t" << temp1.c_str() << std::endl;
        ZZ zTemp(INIT_VAL, temp1.c_str());
        std::cout << "temp antes:" << '\t' << zTemp << std::endl;
        temp1 = zToString(powerZZ(zTemp, publicKey, N));
        std::cout << string(nDigits - (int)temp1.length(), '0') + temp1 << std::endl;
        tempCypher.push_back(string(nDigits - (int)temp1.length(), '0') + temp1);
    }

    return vectorToString(tempCypher);
}
