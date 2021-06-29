#include <NTL/ZZ.h>
#include <string>
#include <vector>

using namespace NTL;
using std::string;

class RSA
{
    private:
        ZZ p, q, fiN, d;
        string alphabet;
    public:
        ZZ e, N;
        RSA(ZZ up, ZZ uq, ZZ ue, string uAlphabet);
        RSA(int, string);
        string cypher(string,ZZ,ZZ);
        string decypher (string,ZZ,ZZ);
};
