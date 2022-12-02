#ifndef BANK_H
#define BANK_H
#include "iostream"
using namespace std;
class Bank
{
    public:

        string name[100];
        string password[100];
        string amount[100];
        string tName[100];
        string rName[100];
        string tAmount[100];
        string tTime[100];
        int index = 0;
        int currentIndex = 0;
        int tIndex = 0;

        int userRegister();
        int userLogin();
        void menu();
        int dataLoading();
        int nameCheck(string cname);
        void dashboard();
        void dataSaving();
        void transfer();
        void withdraw();
        void recharge();
        void transferList();
        void transferListSaving();
        void transferListLoading();
};

#endif // BANK_H
