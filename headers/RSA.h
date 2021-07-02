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
    string signature;
    RSA(ZZ, ZZ, ZZ, string, string);
    RSA(ZZ, string, string);
    string cypher(string, ZZ, ZZ, bool = false);
    std::vector<string> cypherwithsignature(string, ZZ, ZZ);
    std::vector<string> decypherwithsignature(std::vector<string>, ZZ, ZZ);
    string decypher(string, ZZ, ZZ, bool = false);
};
