#include "CLogilogin.h"
using namespace std;

string CLoginLogin::getMainText() const {
    return this->m_maintext;
}
string CLoginLogin::getNote() const {
    return this->m_note;
}

bool CLoginLogin::PrintRec() const {
    cout<<"Login: "<<this->m_maintext;
    if(m_note!="")
        cout<<", "<<this->m_note;
    cout<<"\n";
    /*
    for(size_t i=0;i<m_connections.size();i++) {
        cout << " -> ";
        m_connections[i].CDom.PrintRec();
        cout << " : ";
        m_connections[i].CPas.PrintRec();
        cout << "\n";
    }*/
    cout<<"\n";
    return false;
}
void CLoginLogin::setMainText(string maintext){
    this->m_maintext=maintext;
}
void CLoginLogin::setNote(string note){
    this->m_note=note;
}
/*void CLoginLogin::setType(char type){
    this->type=type;
}*/
CLoginLogin::~CLoginLogin() {}