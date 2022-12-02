#include "iostream"
#include "string"
#include "Bank.h"
#include "fstream"
#include "time.h"
using namespace std;

void Bank::menu(){
    string option;
    cout<<"Welcome to our bank!"<<endl;
    cout<<"Press 1 to register\nPress 2 to login\nPress 3 to exit : "<<endl;
    cin>>option;
    if(option == "1"){
        userRegister();
    }else if(option == "2"){
        userLogin();
    }else if(option == "3"){
        cout<<"Bye Bye"<<endl;
        dataSaving();
        transferListSaving();
        exit(1);
    }
    else{
        cout<<"Invalid Input!"<<endl;
        menu();
    }

}
int Bank::userRegister(){
    string cname;
    string pass;
    string cpass;
    int camount;
    cout<<"This is register."<<endl;
    cout<<"Enter your name : ";
    cin>>cname;
    int check = nameCheck(cname);
    if(check != -1){
        cout<<"Name already exists. Please enter another name."<<endl;
        userRegister();
    }else{
        while(1){
            cout<<"Enter your password : ";
            cin>>pass;
            cout<<"Confirm your password : ";
            cin>>cpass;
            if(pass == cpass){
                while(1){
                    cout<<"Minimum amount is 1000.Enter you amount : ";
                    cin>>camount;
                    if(camount < 1000){
                        cout<<"Please enter valid amount."<<endl;
                    }else{
                        name[index] = cname;
                        password[index] = pass;
                        amount[index] = to_string(camount);
                        index++;
                        cout<<"Registration success.Please login."<<endl;
                        userLogin();
                    }
                }
            }else{
                cout<<"Passwords do not match."<<endl;
            }
        }
    }
}
int Bank::userLogin(){
    string cname;
    string cpass;
    int attempt = 3;
    cout<<"This is login."<<endl;
    cout<<"Enter your name to login : ";
    cin>>cname;
    int check = nameCheck(cname);
    if(check == -1){
        cout<<"Name does not exist."<<endl;
        userLogin();
    }else{
        while(1){
            cout<<"Enter your password to login : ";
            cin>>cpass;
            if(password[check] == cpass){
                currentIndex = check;
                dashboard();
            }else{
                if(attempt == 0){
                    cout<<"Too many attempts to login.Please try again later."<<endl;
                    menu();
                }else{
                    cout<<"Incorrect password!"<<endl;
                    cout<<"You have "<<attempt<<" chances left to try."<<endl;
                    attempt--;
                }
            }
        }
    }
}
int Bank::dataLoading(){
    int count = 0;
    string data;
    string dataLine;
    string userFile = "userData.txt";
    ifstream file(userFile);
    if(!file.is_open()){
        cout<<"File cannot open!"<<endl;
        exit(1);
    }else{
        while(getline(file,dataLine)){
            dataLine = dataLine + " ";
            for(auto &ch :dataLine){
                if(ch == ' '){
                    if(count == 0){
                        name[index] = data;
                        data = "";
                        count++;
                    }else if(count == 1){
                        password[index] = data;
                        data = "";
                        count++;
                    }else if(count == 2){
                        amount[index] = data;
                        data = "";
                        index++;
                        count = 0;
                    }
                }else{
                    string st(1,ch);
                    data = data + st;
                }
            }
        }
    }
    file.close();
}
int Bank::nameCheck(string cname){
    for(int i=0; i<index; i++){
        if(name[i] == cname){
            return i;
        }
    }
    return -1;
}
void Bank::dashboard(){
    string choice;
    cout<<"Welcome to dashboard!"<<endl;
    cout<<"Name : "<<name[currentIndex]<<endl;
    cout<<"Amount : "<<amount[currentIndex]<<endl;
    while(1){
        cout<<"Press 1 to transfer\nPress 2 to withdraw\nPress 3 to recharge\nPress 4 to view transfer list\nPress 5 to back\nPress 6 to exit : ";
        cin>>choice;
        if(choice == "1"){
            transfer();
        }else if(choice == "2"){
            withdraw();
        }else if(choice == "3"){
            recharge();
        }else if(choice == "4"){
            transferList();
        }else if(choice == "5"){
            menu();
        }else if(choice == "6"){
            dataSaving();
            transferListSaving();
            exit(1);
        }else{
            cout<<"Invalid Input!"<<endl;
        }
    }
}
void Bank::dataSaving(){
    string filename ="userData.txt";
    ofstream file;
    file.open(filename);

    if(!file.is_open()){
        cout<<"Unable to record!"<<endl;
    } else{
        for(int i=0 ; i<index ; i++){
            string dataLine=name[i]+" "+password[i]+" "+amount[i]+"\n";
            file<<dataLine;
        }
    }

    file.close();
}
void Bank::transfer(){
    string receiverName;
    string myPass;
    int myAmount = stoi(amount[currentIndex]);
    int receiverAmount = 0;
    int tamount = 0;
    cout<<"This is transfer section."<<endl;
    while(1){
        cout<<"Enter name you want to transfer : ";
        cin>>receiverName;
        int check = nameCheck(receiverName);
        if(check == -1){
            cout<<"User not found."<<endl;
        }else{
            while(1){
                cout<<"Enter amount to transfer : ";
                cin>>tamount;
                if(tamount > myAmount){
                    cout<<"Not enough amount!"<<endl;
                }else{
                    while(1){
                        cout<<"Enter your password again to transfer : ";
                        cin>>myPass;
                        if(myPass != password[currentIndex]){
                            cout<<"Incorrect Password!"<<endl;
                        }else{
                            //account update
                            amount[currentIndex] = to_string(myAmount - tamount);
                            receiverAmount = stoi(amount[check]);
                            amount[check] = to_string(receiverAmount + tamount);

                            //add to transfer list
                            tName[tIndex] = name[currentIndex];
                            rName[tIndex] = name[check];
                            tAmount[tIndex] = to_string(tamount);
                            cout<<"You transfered "<<tAmount[tIndex]<<" to "<<rName[tIndex]<<endl;
                            //add time
                            time_t now = time(0);
                            string cTime = ctime(&now);
                            tTime[tIndex] = cTime;
                            tIndex++;

                            dashboard();
                        }
                    }
                }
            }

        }
    }
}
void Bank::withdraw(){
    int withdraw = 0;
    int myAmount = stoi(amount[currentIndex]);
    cout<<"This is withdraw section."<<endl;
    while(1){
        cout<<"Enter amount to withdraw : ";
        cin>>withdraw;
        if(withdraw > myAmount){
            cout<<"Not enough amount!"<<endl;
        }else{
            amount[currentIndex] = to_string(myAmount - withdraw);
            cout<<withdraw<<" is reduced from your account"<<endl;
            dashboard();
        }
    }
}
void Bank::recharge(){
    int rechargeAmount = 0;
    int myAmount = stoi(amount[currentIndex]);
    cout<<"This is recharge section."<<endl;
    while(1){
        cout<<"Enter amount to recharge : ";
        cin>>rechargeAmount;
        if(rechargeAmount < 1000){
            cout<<"Minimum recharge amount is 1000."<<endl;
        }else{
            amount[currentIndex] = to_string(myAmount + rechargeAmount);
            cout<<rechargeAmount<<" is added to your account"<<endl;
            dashboard();
        }
    }
}
void Bank::transferList(){
    for(int i=0; i<tIndex; i++){
        cout<<tName[i]<<" transfered "<<tAmount[i]<<" to "<<rName[i]<<" at "<<tTime[i]<<endl;
    }
}
void Bank::transferListSaving(){
    string fileName = "transferList.txt";
    ofstream file;
    file.open(fileName);
    if(!file.is_open()){
        cout<<"Unable to record!"<<endl;
    } else{
        for(int i=0 ; i<index ; i++){
            string dataLine=tName[i]+" "+tAmount[i]+" "+rName[i]+" "+tTime[i]+"\n";
            file<<dataLine;
        }
    }
    file.close();
}
void Bank::transferListLoading(){
    int count = 0;
    string data;
    string dataLine;
    string fileName = "transferList.txt";
    ifstream file(fileName);
    if(!file.is_open()){
        cout<<"File cannot open!"<<endl;
        exit(1);
    }else{
        while(getline(file,dataLine)){
            dataLine = dataLine + " ";
            for(auto &ch :dataLine){
                if(ch == ' '){
                    if(count == 0){
                        tName[tIndex] = data;
                        data = "";
                        count++;
                    }else if(count == 1){
                        tAmount[tIndex] = data;
                        data = "";
                        count++;
                    }else if(count == 2){
                        rName[tIndex] = data;
                        data = "";
                    }else if(count == 3){
                        tTime[tIndex] = data;
                        data = "";
                        tIndex++;
                        count = 0;
                    }
                }else{
                    string st(1,ch);
                    data = data + st;
                }
            }
        }
    }
    file.close();

}
