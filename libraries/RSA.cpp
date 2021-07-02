#include <math.h>
#include <string>
#include <NTL/ZZ.h>
#include <ctime>
#include "../headers/functions.h"
#include "../headers/RSA.h"
#include <windows.h>
#include <cstring>
#include <iostream>
#include <thread>

using std::string;
using namespace NTL;

RSA::RSA(ZZ up, ZZ uq, ZZ ue, string uAlphabet, string uSignature) :
    alphabet(uAlphabet), p(up), q(uq), e(ue), signature(uSignature)
{
    N = p * q;
    ZZ fiN = (p - 1) * (q - 1);
    d = moduloZZ(inversa(e, fiN), fiN);

    /*std::cout << "p: " << p << std::endl;
    std::cout << "q: " << q << std::endl;
    std::cout << "N: " << N << std::endl;
    std::cout << "fiN: " << fiN << std::endl;
    std::cout << "e: " << e << std::endl;
    std::cout << "d: " << d << std::endl;*/
}

RSA::RSA(ZZ nBits, string uAlphabet, string uSignature) :
    alphabet(uAlphabet), signature(uSignature)
{
    //std::cout << "Time before generating the primes\t" << time(NULL) << std::endl;
    coordinateRNG pseudorandom(nBits);
    std::thread thread1(getPrime, std::ref(pseudorandom), std::ref(p));
    std::thread thread2(getPrime, std::ref(pseudorandom), std::ref(q));
    thread1.join();
    thread2.join();
    //std::cout << "Time after generating the primes\t" << time(NULL) << std::endl;
    N = p * q;
    ZZ fiN = (p - 1) * (q - 1);
    blumblumshubRNG blumblum(time(NULL), fiN, nBits);
    e = blumblum.next();
    while (mcdZZ(e, fiN) != 1)
    {
        e = blumblum.next();
    }
    d = moduloZZ(inversa(e, fiN), fiN);

    /*std::cout << "p: " << p << std::endl;
    std::cout << "q: " << q << std::endl;
    std::cout << "N: " << N << std::endl;
    std::cout << "fiN: " << fiN << std::endl;
    std::cout << "e: " << e << std::endl;
    std::cout << "d: " << d << std::endl;*/
}

//Cifrado del RSA
string RSA::cypher(string message, ZZ publicKey, ZZ Nb, bool withSig)
{
    int availableDigits = std::to_string((int)alphabet.length()).length();
    int nDigits = (int)zToString(Nb).length();
    vector<string> temp = stringToVector(vectorToString(stringToVectorIndex(message, availableDigits, alphabet)), nDigits - 1);
    vector<string> tempCypher;
    for (vector<string>::iterator i = temp.begin(); i != temp.end(); i++)
    {
        string temp1 = *i;
        ZZ zTemp(INIT_VAL, temp1.c_str());
        ZZ m = powerZZ(zTemp, publicKey, Nb);
        if (withSig) {
            //std::cout << "\nCon firma\n";
            m = powerZZ(m, this->d, this->N);
            m = powerZZ(m, publicKey, Nb);
        }
        else {
            //std::cout << "\nSin firma\n";
        }
        temp1 = zToString(m);
        std::cout << string(nDigits - (int)temp1.length(), '0') + temp1 << std::endl;
        tempCypher.push_back(string(nDigits - (int)temp1.length(), '0') + temp1);
    }

    return vectorToString(tempCypher);
}

vector<string> RSA::cypherwithsignature(string message, ZZ publicKey, ZZ Nb) {
    vector<string>temp; temp.push_back(cypher(message, publicKey, Nb));
    temp.push_back(cypher(signature, publicKey, Nb, true));
    return temp;
}

//descifrado del RSA
string RSA::decypher(string message, ZZ publickey, ZZ Na, bool withSig)
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
        ZZ m = powerZZ(zTemp, this->d, this->N);
        if (withSig) {
            //std::cout << "\nCon firma\n";
            m = powerZZ(m, publickey, Na);
            m = powerZZ(m, this->d, this->N);
        }
        else {
            //std::cout << "\nSin firma\n";
        }
        // temp1 = zToString(powerZZ(zTemp, d, N));
        temp1 = zToString(m);
        string auxiliar = string((nDigits - 1) - (int)temp1.length(), '0') + temp1;
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

vector<string> RSA::decypherwithsignature(vector<string>message, ZZ publickey, ZZ Na) {
    vector<string>temp; temp.push_back(decypher(message.at(0), publickey, Na));
    temp.push_back(decypher(message.at(1), publickey, Na, true));
    return temp;
}

