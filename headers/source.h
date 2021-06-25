#include <NTL/ZZ.h>
#include <string>
#include <vector>

using namespace NTL;
using std::string;
using std::vector;

class source
{
    private:
        string alphabet;
    public:
        ZZ publicKey;
        ZZ N;
        source (ZZ, ZZ, string);
        //vector <string> stringToVector(string, int);
        //vector <string> stringToVectorIndex(string, int);
        //string vectorToString(vector <string>);
        string cypher(string);
};
