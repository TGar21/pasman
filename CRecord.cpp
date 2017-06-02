// Created by Friedrich Tadeáš on 05/04/2017.
//
#include "CRecord.h"
using namespace std;

template <typename T>
int errorHandlerD(T err_desc,const int & err_number){
    cout<<"error: "<<err_desc<<endl;
    return err_number;
}

void CRecord::setType() {}


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

CRecord::CRecord(string maintext, string note,int usage) {
    m_MainText=maintext;
    m_Note=note;
    m_UsageCount=usage;
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

bool CRecord::PrintRec() const {
    return false;
}

CRecord::~CRecord() { }

CPassword::CPassword(){
    m_Type='p';
    //hesovani
}

void CPassword::setType() {
    m_Type='p';
}

bool CPassword::PrintRec() const {
        cout<<"Password: "<<this->m_MainText<<" ";
    return false;
}

CPassword &CPassword::AddRec(string text, string note)  {
    string x=text;x=note;
    return *this;
}

CPassword::~CPassword() { }

CDomain::CDomain(){
    m_Type='d';
}

CDomain::CDomain(string maintext, string note, int usage) {
    m_MainText=maintext;
    m_Note=note;
    m_UsageCount=usage;
}

bool CDomain::PrintRec() const {
    cout<<"Domain: "<<this->m_MainText;
    if(m_Note!="")
        cout<<", "<<this->m_Note;
    cout<<" ";
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

void CDomain::setType() {
    m_Type='d';
}
