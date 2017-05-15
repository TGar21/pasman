// Created by Friedrich Tadeáš on 05/04/2017.
//
#include "CRecord.h"
using namespace std;

template <typename T>
int errorHandlerD(T err_desc,int err_number){
    cout<<"error: "<<err_desc<<endl;
    return err_number;
}

CRecord::CRecord(){
    m_UsageCount=0;
}

CRecord::CRecord(string maintext) {
    m_MainText=maintext;
    m_UsageCount=0;
}

CRecord::CRecord(string maintext, string note) {
    m_MainText=maintext;
    m_Note=note;
    m_UsageCount=0;
}

string CRecord::getMainText() const {
    return m_MainText;
}

bool CRecord::operator<(const CRecord &com) const {
  //  if(this->m_MainText==com.m_MainText)
    //    return this->m_Note < com.m_Note;
    return this->m_MainText < com.m_MainText;
}

char CRecord::getType() const {
    return m_Type;
}

void CRecord::setNote(string note) {
    m_Note=note;
}

void CRecord::setMainText(string maintext) {
    m_MainText=maintext;
}

string CRecord::getNote() const {
    return m_Note;
}

void CRecord::setType(char type) {
    m_Type=type;
}

bool CRecord::PrintRec() const {
    return false;
}

CRecord::~CRecord() { }

CPassword::CPassword(){
    m_Type='p';
    //hesovani
}

bool CPassword::PrintRec() const {
    cout<<"Neni mozne vypisovat heslo"<<endl;
    return false;
}

CPassword &CPassword::AddRec(string text, string note)  {
    cout<<text<<note;
    return *this;
}

CPassword::~CPassword() { }

bool SCouple::operator<(SCouple com) {
    return (this->CDom.getMainText() > com.CDom.getMainText());
}

CLogin::CLogin(){
    this->m_Type='l';
}

CLogin::CLogin(string maintext) : CRecord(maintext){
    this->m_MainText=maintext;
    this->m_Type='l';
}

bool CLogin::PrintRec() const {
    cout<<"Login: "<<this->m_MainText;
    if(m_Note!="")
        cout<<", "<<this->m_Note<<"\n";
    else
        cout<<"\n";
    for(size_t i=0;i<m_connections.size();i++) {
        m_connections[i].CDom.PrintRec();
        cout << " : ";
        m_connections[i].CPas.PrintRec();
        cout << "\n";
    }
    return false;
}

CLogin &CLogin::AddRec(string text, string note) {
    CLogin * y=new CLogin;
    y->m_MainText=text;
    y->m_Note=note;
    return *y;
}

CLogin::~CLogin() { }

CDomain::CDomain(){
    m_Type='d';
}

bool CDomain::PrintRec() const {
    cout<<"Domena: "<<this->m_MainText;
    if(m_Note!="")
        cout<<", "<<this->m_Note<<"\n";
    else
        cout<<"\n";
    return false;
}

CDomain &CDomain::AddRec(string text, string note) {
    cout<<text<<note;
    /*CDomain & x;
    x.m_Type='d';
    x.m_MainText=text;
    x.m_Note=note;*/
    return *this;
}

CDomain::~CDomain() { }

CDomain::CDomain(string maintext) : CRecord(maintext) { }
