#include "CRefLogin.h"
using namespace std;

string CRefLogin::getNote() const {
    return refToLogin.getNote();
}
string CRefLogin::getMainText() const {
    return refToLogin.getMainText();
}
bool CRefLogin::PrintRec() const {return false;}

CRefLogin::CRefLogin(CLoginLogin & x) : refToLogin(x) { }

void CRefLogin::setMainText(string maintext){
    refToLogin.setMainText(maintext);
}
void CRefLogin::setNote(string note){
    refToLogin.setNote(note);
}
/*void CRefLogin::setType(char type){
    refToLogin.setType(type);
}*/
CRefLogin::~CRefLogin(){

}
