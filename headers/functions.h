#include <NTL/ZZ.h>
#include <string>
#include <vector>
#include <windows.h>

using namespace NTL;
using std::vector;
using std::string;

vector<ZZ> extMcdZZ(ZZ, ZZ);
ZZ inversa(ZZ, ZZ);
ZZ mcdZZ(ZZ, ZZ);
int modulo(int ,int );
ZZ moduloZZ(ZZ, ZZ);
ZZ moduloZZ2(ZZ);
ZZ powerZZ(ZZ, ZZ, ZZ);
ZZ rtl(ZZ,ZZ);
ZZ get_coordinate();
ZZ CL(ZZ,ZZ,ZZ,ZZ);
ZZ Getrand(ZZ);
bool isPrime(ZZ);
class blumblumshubRNG{
public:
    ZZ seed;
    ZZ m;
    blumblumshubRNG(time_t , ZZ );
    ZZ next();
};
class coordinateRNG{
public:
    ZZ seed, nBits, a, c,m;
    coordinateRNG(ZZ);
    ZZ next();
private:
    ZZ get_coordinate();
};
ZZ getPrime(coordinateRNG &);
string zToString(ZZ);
vector <string> stringToVector(string, int);
vector <string> stringToVectorIndex(string, int, string);
string vectorToString(vector <string>);

