#include <math.h>
#include <string>
#include <NTL/ZZ.h>
#include <ctime>
#include "../headers/functions.h"
//#include "./functions.cpp"
#include "../headers/receiver.h"
#include <windows.h>

#include <iostream>

using std::string;
using namespace NTL;

receiver::receiver(ZZ nBits, string uAlphabet) :
    alphabet(uAlphabet)
{
    coordinateRNG pseudorandom(nBits);
    p = getPrime(pseudorandom);
    q = getPrime(pseudorandom);
    N = p * q;
    fiN = (p - 1) * (q - 1);
    blumblumshubRNG blumblum(time(NULL), fiN);
    e = blumblum.next();
    while (mcdZZ(e, fiN) != 1)
    {
        e = blumblum.next();
    }
    d = moduloZZ(inversa(e, fiN), fiN);

    std::cout << "p: " << p << std::endl;
    std::cout << "q: " << q << std::endl;
    std::cout << "N: " << N << std::endl;
    std::cout << "fiN: " << fiN << std::endl;
    std::cout << "e: " << e << std::endl;
    std::cout << "d: " << d << std::endl;
}

//descifrado del RSA
string receiver::decypher(string message)
{
    string toReturn;
    int availableDigits = std::to_string((int)alphabet.length()).length();
    int nDigits = (int)zToString(N).length();
    vector<string> temp = stringToVector(message, nDigits);
    vector<string> tempDecypher;
    for (vector<string>::iterator i = temp.begin(); i != temp.end(); i++)
    {
        string temp1 = *i;
        ZZ zTemp(INIT_VAL, temp1.c_str());
        temp1 = zToString(powerZZ(zTemp, d, N));
        string auxiliar =  string((nDigits - 1) - (int)temp1.length(), '0') + temp1;
        while (modulo(auxiliar.length(), availableDigits) && i == temp.end() - 1)
        {
                auxiliar.erase(0, 1);
        }
        tempDecypher.push_back(auxiliar);

    }
    temp = stringToVector(vectorToString(tempDecypher), availableDigits);
    for (vector<string>::iterator i = temp.begin(); i != temp.end(); i++)
    {
        string temp1 = *i;
        int iTemp = std::stoi(temp1);
        if (iTemp < (int)alphabet.length()) toReturn.append(alphabet, iTemp, 1);
    }
    return toReturn;
}
