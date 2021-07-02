#include "../headers/functions.h"
#include <NTL/ZZ.h>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

using namespace NTL;

//euclides extendido
std::vector<ZZ> extMcdZZ(ZZ a, ZZ b)
{
    std::vector<ZZ> temp;
    ZZ q = a / b;
    ZZ res = a - (q * b);

    ZZ s1;
    s1 = 1;
    ZZ s2;
    s2 = 0;
    ZZ s = s1 - (q * s2);

    ZZ t1;
    t1 = 0;
    ZZ t2;
    t2 = 1;
    ZZ t = t1 - (q * t2);

    while (res > 0)
    {
        a = b;
        b = res;
        q = a / b;
        res = a - (q * b);

        s1 = s2;
        s2 = s;
        s = s1 - (q * s2);

        t1 = t2;
        t2 = t;
        t = t1 - (q * t2);

    }

    temp.push_back(b);
    temp.push_back(s2);
    temp.push_back(t2);

    return temp;
}

//sacamos inversa con euclides extendido
ZZ inversa(ZZ a, ZZ b)
{
    return extMcdZZ(a, b).at(1);
}

//usamos euclides clasico
ZZ mcdZZ(ZZ x, ZZ y)
{
    ZZ q, r;
    q = x / y;
    r = moduloZZ(x, y);

    while (r != 0)
    {
        x = y;
        y = r;
        q = x / y;
        r = moduloZZ(x, y);
        x = q * y + r;
    }
    return y;
}

//modulo version enteros
int modulo(int a, int b)
{
    int r = a - b * (a / b);
    r = r + (r < 0) * b;
    return r;
}

//modulo version ZZ
ZZ moduloZZ(ZZ a, ZZ b)
{
    ZZ q = a / b;
    ZZ res = a - (q * b);
    if (res < 0)
    {
        q--;
        res = a - (q * b);
    }
    return res;
}

//version optimizada del modulo
ZZ moduloZZ2(ZZ a)
{
    ZZ r = a - ((a >> 1) << 1);
    r = r + ((r < 0) << 1);
    return r;
}

//usamos rtl sin modulo para hacer una rapida potenciacion
ZZ rtl(ZZ b, ZZ e)
{
    ZZ A = conv<ZZ>("1");
    ZZ S = b;

    while (e != 0)
    {
        if (moduloZZ(e, ZZ(2)) == 1)
        {
            A = A * S;
        }
        e = e >> 1;
        if (e != 0) S = S * S;
    }
    return A;
}

//usamos RTL para hacer exponenciacion modular
ZZ powerZZ(ZZ b, ZZ e, ZZ m)
{
    ZZ A = conv<ZZ>("1");
    ZZ S = b;

    while (e != 0)
    {
        if (moduloZZ2(e) == 1)
        {
            A = moduloZZ(A * S, m);
        }
        e = e >> 1;
        if (e != 0) S = moduloZZ((S * S), m);
    }
    return A;
}

//get_coordinate es parte de la semilla que usa las coordenadas del mouse
ZZ get_coordinate()
{
    POINT P;
    GetCursorPos(&P);

    ZZ seed = conv<ZZ>(P.x * P.y);
    return seed;
}

//getPrime obtiene el aleatorio de p y q si es primo
void getPrime(coordinateRNG& number, ZZ& param)
{
    //int cont = 1;
    ZZ temp;
    do
    {
        temp = number.next();
        while (moduloZZ(moduloZZ(temp, ZZ(10)), ZZ(2)) == 0)
        {
            temp = number.next();
        }
    } while (!isPrime(temp));
    param = temp;
}

//CoordinateRNG es la congruencia linear que usamos para crear aleatorios de p y q
coordinateRNG::coordinateRNG(ZZ bits) :
    seed(time(NULL)), nBits(bits)
{
    c = ZZ(1);
    seed *= get_coordinate();
    a = rtl(ZZ(3), nBits / 2);
    m = rtl(ZZ(2), nBits - 1);
}

ZZ coordinateRNG::next()
{
    seed = seed * a + c;
    if (seed > m)
    {
        seed = moduloZZ(seed, m);
    }
    while (seed < (m >> 1))
    {
        seed = (seed << 1) + 1;
    }
    return seed;
}

ZZ coordinateRNG::get_coordinate()
{
    POINT P;
    GetCursorPos(&P);

    ZZ seed = conv<ZZ>(P.x * P.y);
    return seed;
}

//Utilizando test de fermat
bool isPrime(ZZ x)
{
    /*
    ZZ k, q, a;
    k = 0;
    while (moduloZZ(x - 1, rtl(ZZ(2), ++k)) == ZZ(0));
    q = (x - 1) / rtl(ZZ(2), --k);


    a = moduloZZ(coordinateRNG(ZZ(256)).next(), x - 1) + 1;

    if (IsOne(powerZZ(a, q, x))) {
        return 1;
    }

    ZZ j;
    for (j = 0; j < k; j++) {
        ZZ t = rtl(ZZ(2), j) * q;
        if (powerZZ(a, t, x) == x - 1)
            return 1;
    }

    return 0;
    */
    ZZ res;
    ZZ y;
    ZZ gcd;
    coordinateRNG randnro(ZZ(1024));
    if (moduloZZ2(x) == 0) {
        return false;
    }
    srand(time(NULL));
    y = randnro.next();
    //y=ZZ(2);
    gcd = mcdZZ(x, y);
    while (gcd != 1) {
        y = randnro.next();
        //y=ZZ(2);
        gcd = mcdZZ(x, y);
    }
    res = powerZZ(y, (x - 1), x);
    if (res == 1) {
        return true;
    }
    else {
        return false;
    }
}

//Blumblum es nuestro generador de clave publica.
blumblumshubRNG::blumblumshubRNG(time_t initialSeed, ZZ uM, ZZ nBits) :
    m(uM), limInf(rtl(ZZ(2), nBits - 1) - 1), limSup(rtl(ZZ(2), nBits) - 1)
{
    seed = (long)initialSeed;
    seed = moduloZZ(seed, m);
    while (mcdZZ(seed, m) != 1 && seed > 1)
    {
        seed = moduloZZ(seed + seed + 1, m);
    }
}

ZZ blumblumshubRNG::next()
{
    ZZ temp = moduloZZ(seed * seed, m);
    while (temp < 1 || (temp < limInf || temp > limSup))
    {
        temp = moduloZZ(2 * temp + 1, m);
    }
    seed = temp;
    return seed;
}

//convierte ZZ a string
std::string zToString(ZZ z) {
    std::stringstream buffer;
    buffer << z;
    return buffer.str();
}

//convierte string a vector
vector<string> stringToVector(string message, int ddigits)
{
    vector<string> blocks;
    for (int i = 0; i < (int)message.length(); i += ddigits)
    {
        blocks.push_back(string(message, i, ddigits));
    }
    return blocks;
}

//esta funcion inserta un string en un vector y lo divide en bloques
vector<string> stringToVectorIndex(string message, int ddigits, string alphabet)
{
    vector<string> firstBlock;
    for (string::iterator i = message.begin(); i != message.end(); i++)
    {
        //IF NOT FOUND WILL RETURN 0
        string temp = std::to_string(alphabet.find(*i));
        //std::cout << temp.length();
        string block = string(ddigits - (int)temp.length(), '0') + temp;
        firstBlock.push_back(block);
    }
    return firstBlock;
}

//convierte vector a string
string vectorToString(vector<string> blocks)
{
    string final;
    if (!blocks.empty())
    {
        for (vector<string>::iterator i = blocks.begin(); i != blocks.end(); i++)
        {
            final.append(*i);
        }
    }
    return final;
}


