#include "FileUtilsTester.h"


Tests::ITest * testIns = new FileSystemUtils::Tests::File;

int main(int argc, char const *argv[])
{
    int res = testIns->RunTests() == true;
    delete testIns;
    return res;
}
