#include "CInteract.h"
#include "CDatabase.h"
#include <cstdlib>
#ifdef OS_WINDOWS
#define clearscreen system("cls");
#else
#define clearscreen system("clear");
#endif

using namespace std;

char CInteract::Type(const string & text) {
    type='n';
    cout << text;
    cout << "Login l, Password p, Domain d\n";
    cin >> type;
    if(type == 'l' || type == 'd' || type == 'p')
        return type;
    else
        while(type != 'l' && type != 'd' && type != 'p') {
            cout << "You entered wrong type, please try again:\n";
            cout << "Login l, Password p, Domain d, Exit x\n";
            cin >> type;
            if (type=='x')
                Exit();
        }
    return type;

}

void CInteract::Entry() {
    clearscreen;
    cout<<"======WELCOME IN PASSWORD MANAGER======\n";
    database.FirstSetup(database.GetInicFile());
}
bool CInteract::Authenticate(){

    short attempts=0;
    cout<<"Please add your password for entry:\n";
    cin>>mainpassword;
    if(!database.GetMainPassword().PasswordCorrect(mainpassword)) {
        do {
            if (attempts > 1) {
                cout << "Wrong again! Too many attempts. Sorry.\n";
                exit(1);
            }
            cout << "Wrong password!\n";
            //cout<<database.GetMainPassword().ReturnHash();
            //cout<<"\n"<<mainpassword;
            attempts++;
            cout << "Please try again:\n";
            cin >> mainpassword;
        } while (!database.GetMainPassword().PasswordCorrect(mainpassword));
        return true;
    }
    return true;
}
char CInteract::GetAction()const{
    char action;
    cout << " - - - - - - - - - - - - -  \n"
         << "|  New record            n |\n"
         << "|  Delete record         d |\n"
         << "|  Update record         u |\n"
         << "|  Print                 p |\n"
         << "|  Print all             a |\n"
         << "|  Find                  f |\n"
         << "|  Connect               c |\n"
         << "|  Backup                b |\n"
         << "|  Restore from backup   r |\n"
         << "|  Change main password  z |\n"
         << "|  Exit                  x |\n"
         << " - - - - - - - - - - - - -  \n";
    cin >> action;
    return action;
}
void CInteract::Add() {
    type = Type("What to add?\n");
    cout << "enter text\n";
    cin >> text;
    if(type!='p') {
        cout << "enter note\n";
        cin >> note;
        cout<<"You entered "+text+ ", "+ note+"\n";
    }else {
        cout << "You entered " + text + "\n";
        note="";
    }
    //getline(cin,note);
    this->database.NewRec(text, note, type);
}
void CInteract::Connect() {
    cout << "Which login you want to connect?\n";
    cin >> login;
    if(this->database.Connect(login)){
        cout<<"Succesfully connected.\n";
    }else{
        cout<<"Doesn't exists\n";
    }
}
void CInteract::Delete() {
    type = Type("What type of record do you want to delete?\n");
    cout<<"What record do you want to delete?\n";
    cin >> text;
    if(this->database.RemoveRec(text, type))
        cout<<text<<" removed.\n";
}
void CInteract::Update() {
    string new_text;
    string new_note;
    type = Type("What type of record do you want to change?\n");
/*    if(type!='l')
        cout<<"Please note, that currently we are supporting only unconnected domains and passwords,\n"
            <<"it is a known issue, and it will be solved in the next version of the Pasman\n";*/
    cout<<"What record do you want to change?\n";
    cin >> text;
    cout<<"To what?\n";
    cin >> new_text;
    cout<<"New note?\n";
    cin >> new_note;
    this->database.UpdateRec(text,new_text,new_note,type);
}
void CInteract::Find() const{
    string search;
    cout<<"Type record or note you want to find\n";
    cin>>search;
    if(search==""){
        cout<<"You can't search empty strings\n";
        return;
    }
    cout<<"Searching "<<search<<"\n";
    database.FindRec(search);
}
bool CInteract::Backup() const{
    cout<<"Backup created.\n";
    return database.WriteTo(database.GetBackupFile());
}
bool CInteract::Restore(){
    char ans;
    cout<<"Your database will be deleted and restored from your backup. Right? (y/n)?\n";
    cin>>ans;
    if(ans=='y') {
        cout<<"Restored\n";
        return database.SetupFrom(database.GetBackupFile());
    } else {
        cout << "Cancelling. Backup wasn't used.\n";
        return false;
    }
}
void CInteract::ChangePass(){
    string hash=database.GetMainPassword().ChangeMainPassword();
    if(hash!="false")
        database.mainPassword.setMainPassword(hash);
}
void CInteract::Print(const char & type) const{
    char yesno;
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
void CInteract::PrintAllRec(){
    database.PrintAll(database.GetAllOfThem());
}
void CInteract::Exit()const{
    cout << "See ya.\n";
    database.WriteTo(database.GetInicFile());
    exit (0);
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
            case 'b':
                Backup();
                break;
            case 'r':
                Restore();
                break;
            case 'u':
                Update();
                break;
            case 'p':
                type = Type("What do you want to print?\n");
                Print(type);
                break;
            case 'z':
                ChangePass();
                break;
            case 'f':
                Find();
                break;
            case 'x':
                Exit();
                break;
            case 'a':
                PrintAllRec();
                break;
            case 'm':
                cout<<database.GetMainPassword().ReturnHash()<<endl;
                break;
            default:
                cout << "You entered a wrong option, please try again\n";
                break;
        }
    }
}
