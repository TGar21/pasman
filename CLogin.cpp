//
// Created by Friedrich Tadeáš on 24.05.17.
//
#include "CLogin.h"

bool SCouple::operator<(SCouple com) {
    return (this->CDom.getMainText() > com.CDom.getMainText());
}
CLogin::CLogin(){}
CLogin::~CLogin() {}

bool CLogin::PrintRec() const {
    cout<<"Login: "<<this->m_MainText;
    if(m_Note!="")
        cout<<", "<<this->m_Note;
    return false;
}
void CLogin::setType() {
    m_Type='d';
}
