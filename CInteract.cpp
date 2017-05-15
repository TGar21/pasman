#include "CInteract.h"
#include "CDatabase.h"
#include <cstdlib>
#ifdef OS_WINDOWS
#define clearscreen system("cls");
#else
#define clearscreen system("clear");
#endif

using namespace std;

char CInteract::GetType(string text){
    cout << text;
    cout << "Login l, Password p, Domain d\n";
    cin >> type;
    return type;
}

void CInteract::Entry() {
    clearscreen;
    cout<<"======WELCOME IN PASSWORD MANAGER======\n";
}
bool CInteract::Authenticate(){

    short attempts=0;
    database.FirstSetup(database.GetInicFile());
    cout<<"Please add your password for entry:\n";
    cin>>mainpassword;
    if(!database.GetMainPassword().PasswordCorrect(mainpassword)) {
        do {
            if (attempts > 1) {
                cout << "Wrong again! Too many attempts. Sorry.\n";
                exit(1);
            }
            cout << "Wrong password!\n";
            attempts++;
            cout << "Please try again:\n";
            cin >> mainpassword;
        } while (!database.GetMainPassword().PasswordCorrect(mainpassword));
        return true;
    }
    return true;
}
char CInteract::GetAction(){
    char action;
    cout << "\nNew record n, Delete record d, Update record u, Print p, Connect c, Exit x\n";
    cin >> action;
    return action;
}
void CInteract::Add() {
    type = GetType("What to add?\n");
    cout << "enter text\n";
    cin >> text;
    cout << "enter note\n";
    cin >> note;
    this->database.NewRec(text, note, type);
}
void CInteract::Connect() {
    cout << "Which login you want to connect?\n";
    cin >> login;
    this->database.Connect(login);
}
void CInteract::Delete() {
    type = GetType("What record do you want to delete?\n");
    cin >> text;
    this->database.RemoveRec(text, type);
}
void CInteract::Update() {
    type = GetType("What record do you want to change?\n");
    cin >> text;
}
void CInteract::Print() {
    char yesno;
    type = GetType("What do you want to print?\n");
    switch (type) {
        case 'l':
            cout<<"With connected records? (y/n)\n";
            cin>>yesno;
            if(yesno=='y'){
                this->database.PrintWhole();
            }
            else if(yesno=='n')
                this->database.PrintAllLogins();
            else {
                cout << "Wrong option, printing without connections.\n";
                this->database.PrintAllLogins();
            }
            break;
        case 'p':
            this->database.PrintAllPasswords();
            break;
        case 'd':
            this->database.PrintAllDomains();
            break;
        default:
            break;
    }
}
void CInteract::CoverAll() {
    Entry();
    Authenticate();
    while (true) {
        switch (GetAction()) {
            case 'c':
                Connect();
                break;
            case 'n':
                Add();
                break;
            case 'd':
                Delete();
                break;
            case 'u':
                Update();
                break;
            case 'p':
                Print();
                break;
            case 'x':
                cout << "See ya.\n";
                database.WriteTo(database.GetBackupFile());
                return;
            default:
                cout << "You entered a wrong option, please try again\n";
                break;
        }
    }
}
