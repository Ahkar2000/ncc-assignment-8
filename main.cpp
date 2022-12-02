#include <iostream>
#include "Bank.h"
using namespace std;

int main()
{
    Bank myObj;
    myObj.dataLoading();
    myObj.transferListLoading();
    myObj.menu();
    return 0;
}
