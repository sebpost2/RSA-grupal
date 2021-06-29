#include <math.h>
#include <string>
#include <NTL/ZZ.h>
#include <ctime>
#include "../headers/functions.h"
#include "../headers/RSA.h"
#include <windows.h>
#include <cstring>
#include <iostream>

using std::string;
using namespace NTL;

RSA::RSA(ZZ up, ZZ uq, ZZ ue, string uAlphabet) :
    alphabet(uAlphabet), p(up), q(uq), e(ue)
{
    N = p * q;
    ZZ fiN = (p - 1) * (q - 1);
    while (mcdZZ(e, fiN) != 1)
    {
        e = RandomBnd(fiN - 1) + 1;
    }
    d = moduloZZ(inversa(e, fiN), fiN);

    std::cout << "p: " << p << std::endl;
    std::cout << "q: " << q << std::endl;
    std::cout << "N: " << N << std::endl;
    std::cout << "fiN: " << fiN << std::endl;
    std::cout << "e: " << e << std::endl;
    std::cout << "d: " << d << std::endl;
}

RSA::RSA(int nBits, string uAlphabet) :
    alphabet(uAlphabet)
{
    p = RandomPrime_ZZ(nBits);
    q = RandomPrime_ZZ(nBits);
    N = p * q;
    ZZ fiN = (p - 1) * (q - 1);
    //e = RandomBnd(fiN - 1) + 1;

    while (mcdZZ(e, fiN) != 1)
    {
        e = RandomBnd(fiN - 1) + 1;
    }

    d = moduloZZ(inversa(e, fiN), fiN);

    std::cout << "p: " << p << std::endl;
    std::cout << "q: " << q << std::endl;
    std::cout << "N: " << N << std::endl;
    std::cout << "fiN: " << fiN << std::endl;
    std::cout << "e: " << e << std::endl;
    std::cout << "d: " << d << std::endl;
}

//Cifrado del RSA
string RSA::cypher(string message, ZZ publicKey, ZZ Nb)
{
    //std::cout << "Clave publica:\t " << publicKey << std::endl;
    //std::cout << "Esto es N:\t " << N << std::endl;
    int availableDigits = std::to_string((int)alphabet.length()).length();
    int nDigits = (int)zToString(Nb).length();
    vector<string> temp = stringToVector(vectorToString(stringToVectorIndex(message, availableDigits, alphabet)), nDigits - 1);
    vector<string> tempCypher;
    for (vector<string>::iterator i = temp.begin(); i != temp.end(); i++)
    {
        string temp1 = *i;
        std::cout << "temp1:\t" << temp1 << std::endl;
        std::cout << "temp1.c_str():\t" << temp1.c_str() << std::endl;
        ZZ zTemp(INIT_VAL, temp1.c_str());
        std::cout << "temp antes:" << '\t' << zTemp << std::endl;
        ZZ m; m=powerZZ(zTemp, publicKey, Nb);
        ZZ r; r=powerZZ(m, this->d, this->N);
        ZZ s; s=powerZZ(r, publicKey, Nb);
        //temp1 = zToString(powerZZ(zTemp, publicKey, Nb));
        temp1=zToString(s);
        std::cout << string(nDigits - (int)temp1.length(), '0') + temp1 << std::endl;
        tempCypher.push_back(string(nDigits - (int)temp1.length(), '0') + temp1);
    }

    return vectorToString(tempCypher);
}

//descifrado del RSA
string RSA::decypher(string message, ZZ publickey, ZZ Na)
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
        ZZ m; m=powerZZ(zTemp, this->d, this->N);
        ZZ r; r=powerZZ(m, publickey, Na);
        ZZ s; s=powerZZ(r, this->d, this->N);
        temp1 = zToString(s);
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

