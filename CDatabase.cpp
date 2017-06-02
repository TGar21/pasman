// Created by Friedrich Tadeáš on 05/04/2017.
//
#include "CDatabase.h"
#include "CLogin.h"
#include <cmath>
#include "cstdlib"
using namespace std;

template <typename T>
int errorHandler(T err_desc,const int & err_number){
    cout<<"error: "<<err_desc<<endl;
    return (err_number);
}
const CDomain & CDatabase::SearchDom(const string & sDom)const{
    for(auto item : m_DomainData){
        if(sDom==item->getMainText())
            return *item;
    }
    //throw invalid_argument ("This domain does not exists.\n");
    throw "This domain does not exists.\n";
}
const CPassword & CDatabase::SearchPas(const string & sPas)const{
    for(auto item : m_PasswordData){
        if(sPas==item->getMainText())
            return *item;
    }
    //throw invalid_argument ("This password does not exists.\n");
    throw "This password does not exists.\n";
}

void CDatabase::Connection(const string & maintext, const string & sDomain, const string & sPassword){
    SCouple * connected=new SCouple;
    for(auto item : m_LoginData) {
        if(item->getMainText()==maintext){
            connected->CDom = SearchDom(sDomain);
            connected->CPas = SearchPas(sPassword);
            connected->CDom.used.push_back(item->getMainText());
            connected->CPas.used.push_back(item->getMainText());
            item->m_connections.push_back(connected);
        }
    }
}


bool CDatabase::Connect (const string & maintext){
    string sDomain,sPassword;
    SCouple connected;
    for(auto item : m_LoginData) {
        if(item->getMainText()==maintext){
            cout<<"Record " + item->getMainText() + " exists, which domain you want to add?\n";
            cin>>sDomain;
            cout<<"Which password?\n";
            cin>>sPassword;
            try {
                this->Connection(maintext,sDomain,sPassword);
            //}catch (const std::invalid_argument& e){
            }catch (const char* e){
                cout<<"This Record does not exists.\n";
                return false;
            }
            return true;
        }
    }
    return false;
}

CDatabase::CDatabase() {
    inicFile.SetFilename("PMinic.txt");
    backupFile.SetFilename("PMbackup.txt");
}

string CDatabase::XCryptString(string key,string xcrypted)const{
    return xcrypted;
    string result; size_t i; size_t minlen=min(key.length(),xcrypted.length());
    for(i = 0; i < minlen; i++)
        result.push_back(key[i]^xcrypted[i]);
    for(i = minlen; i<xcrypted.length();i++) {
            result.push_back(xcrypted[i]);
    }
    cout<<result<<endl;
/*    string key2=key;
    if(key!=key2)
        cout<<key;
    unsigned char pass_char [xcrypted.length()+2];
    unsigned char key_char [key.length()+2];
    copy( password.begin(), password.end(), pass_char );
    pass_char[password.length()] = '\0';
    copy( key.begin(), key.end(), key_char );
    key_char[key.length()] = '\0';
    unsigned char enc_out [256];
    AES_KEY enc_key;
    AES_set_encrypt_key(key_char, , &enc_key);
    AES_encrypt(pass_char, enc_out, &enc_key);
    cout<<enc_out;*/
    return result;
}

void inic (CRecord * newrec,string maintext,string note){
    newrec->setMainText(maintext);
    newrec->setNote(note);
    newrec->setType();
}
void inic (CLogin * newrec,string maintext,string note){
    newrec->setMainText(maintext);
    newrec->setNote(note);
}

void CDatabase::NewRec(string maintext, string note, char type) {
    if(type=='l'){
        CLogin * newrec=new CLogin;
        CLogin * newrec2=new CLogin;
        inic(newrec,maintext,note);
        inic(newrec2,maintext,note);
        m_LoginData.insert(newrec);
        m_AllOfThem.insert(newrec2);
    }else if(type=='p') {
        CPassword * newrec=new CPassword;
        CPassword * newrec2=new CPassword;
        inic(newrec, maintext, note);
        inic(newrec2,maintext,note);
        m_PasswordData.insert(newrec);
        m_AllOfThem.insert(newrec2);
    }
    else{
        CDomain * newrec=new CDomain;
        CDomain * newrec2=new CDomain;
        inic(newrec,maintext,note);
        inic(newrec2,maintext,note);
        m_DomainData.insert(newrec);
        m_AllOfThem.insert(newrec2);
    }
}
void CDatabase::PrintAll(const set<CRecord*> & m_RecordData)const{
   string checkPassword;
   string checkHash;
   cout<<"Please enter your main password\n";
   cin>>checkPassword;
   if(!GetMainPassword().HashString(checkPassword,checkHash))
       errorHandler("Problem with hashing\n",2);
   if(checkHash == GetMainPassword().ReturnHash()) {
       cout<<"All records in database:\n";
       for (auto item : m_RecordData) {
           item->PrintRec();
           cout << "\n";
       }
       cout << "\n";
   }else{
       cout<<"You entered wrong password.\n";
   }
}

set <CRecord *> CDatabase::GetAllOfThem() {
    return m_AllOfThem;
}

void CDatabase::PrintAllLogins()const {
    cout<<"List of all logins in database:\n";
    for(auto item : m_LoginData) {
        item->PrintRec();
        cout<<"\n";
    }
    cout<<"\n";
}

void CDatabase::PrintAllDomains() const{
    cout<<"List of all domains in database:\n";
    for(auto item : m_DomainData) {
        item->PrintRec();
        cout<<"\n";
    }
    cout<<"\n";
}

void CDatabase::PrintAllPasswords() const{
    string checkPassword;
    string checkHash;
    cout<<"To see passwords you need to enter your main password\n";
    cin>>checkPassword;
    if(!GetMainPassword().HashString(checkPassword,checkHash))
        errorHandler("Problem with hashing\n",2);
    if(checkHash == GetMainPassword().ReturnHash()){
        for(auto item : m_PasswordData) {
            item->PrintRec();
            cout<<"\n";
        }
    } else {
        cout<<"You entered wrong password.\n";
    }
    cout<<"\n";
}

CDatabase::~CDatabase() {
    for(auto item : m_LoginData) {
        delete item;
    }
    for(auto item2 : m_DomainData) {
        delete item2;
    }
    for(auto item3 : m_PasswordData) {
        delete item3;
    }
    for(auto item4 : m_AllOfThem) {
        delete item4;
    }
}

template <typename S>
bool erase(string maintext, S & Data){
    for (auto item : Data) {
        cout<<item->getMainText()<<endl;
        if (item->getMainText() == maintext) {
            delete item;
            Data.erase(item);
            return true;
        }
    }
    errorHandler("Record " + maintext + " not found", 9);
    return false;
}

bool CDatabase::RemoveRec(const string & maintext, const char &type) {
    erase(maintext,m_AllOfThem);
    if(type=='l')
        return erase(maintext,m_LoginData);
    else if(type == 'p') {
        for (auto item:m_LoginData) {
            int i=0;
            for (auto item2:item->m_connections) {
                i++;
                if (item2->CPas.getMainText() == maintext) {
                    item->m_connections.erase(item->m_connections.begin()+i-1);
                    delete item2;
                }
            }
        }
        return erase(maintext, m_PasswordData);
    }
    else {
        for (auto item:m_LoginData) {
            int i=0;
            for (auto item2:item->m_connections) {
                i++;
                if (item2->CDom.getMainText() == maintext) {
                    cout<<i;
                    item->m_connections.erase(item->m_connections.begin()+i-1);
                    delete item2;
                }
            }
        }
        return erase(maintext, m_DomainData);
        cout<<"aa";
    }
}

bool CDatabase::UpdateRec(string old_maintext, string new_maintext, string note, char type) {
    if(!RemoveRec(old_maintext,type))
        return false;
    NewRec(new_maintext,note,type);
    return true;
}

CMainPassword CDatabase::GetMainPassword()const{
    return mainPassword;
}

void CDatabase::PrintWhole()const {
    cout<<"List of all logins in database:\n";

    for(auto item : m_LoginData) {



        auto lower1 = lower_bound(m_LoginData.begin(), m_LoginData.end(),item,
                                  [ ](const CLogin & lhs, const CLogin & rhs){
                                      if (lhs.getMainText()==rhs.getMainText())
                                          return lhs.getNote() < rhs.getNote();
                                      else
                                          return lhs.getMainText() < rhs.getMainText();
                                  });



        cout<<"\n========\n";
        item->PrintRec();
        cout<<"\n";
        for(int i=0;i<item->m_connections.size();i++) {
            cout << item->m_connections[i]->CDom.m_MainText<<" -> ";//GetMainText();
            cout << item->m_connections[i]->CPas.m_MainText<<"\n";
        }
    }
    cout<<"\n";

}

void CDatabase::FindRec(const string &searched) const {
    for(auto item : m_AllOfThem){
        if(item->getMainText()==searched || item->getNote()==searched){
            item->PrintRec();
            cout<<"\n";
        }
    }
    cout<<"\n";
}

void CDatabase::addFromFile(const int & connectionNumber, const char & type, const string & recString){
    string resultText, resultNote;
    string sDomain,sPassword;
    int i=0;
    while(recString[i]!=':') {
        resultText.push_back(recString[i]);
        i++;
    }
    i++;
    while (recString[i] != ':') {
        resultNote.push_back(recString[i]);
        i++;
    }
    i++;
    this->NewRec(resultText,resultNote,type);
    for (int j=0;j<connectionNumber;j++) {
        while (recString[i] != ':') {
            //cout<<"D pushing: "<<recString[i]<<endl;
            sDomain.push_back(recString[i]);
            i++;
        }
        i++;
        while (recString[i] != ':') {
           // cout<<"P pushing: "<<recString[i]<<endl;
            sPassword.push_back(recString[i]);
            i++;
        }
        i++;
        this->Connection(resultText,sDomain,sPassword);
        sDomain="";
        sPassword="";
    }
}
void CDatabase::addFromFile(const char & type, const string & recString){
    string resultText;
    string resultNote;
    int i=0;
    while (recString[i] != ':') {
        resultText.push_back(recString[i]);
        i++;
    }
    i++;
    while (recString[i] != ':') {
        resultNote.push_back(recString[i]);
        i++;
    }
    this->NewRec(resultText,resultNote,type);
}

bool CDatabase::SetupFrom(const CFile & cFile) {
    this->m_DomainData.clear();
    this->m_PasswordData.clear();
    this->m_LoginData.clear();
    this->m_AllOfThem.clear();
    ifstream inic(cFile.GetFilename());
    if(!inic && inic.good()) {
        errorHandler("Problem with opening a file.", 100);
        return false;
    }else{
        string passwordHash;
        getline(inic, passwordHash);
        mainPassword.setMainPassword(passwordHash);
        size_t logsize,domsize,passize;
        char c;
        string one_login,one_domain,one_password;
        inic >> logsize;
        if (!inic) errorHandler("Problem with reading a file.", 101);
        inic >> c;
        if (!inic) errorHandler("Problem with reading a file.", 102);
        inic >> domsize;
        if (!inic) errorHandler("Problem with reading a file.", 103);
        inic >> c;
        if (!inic) errorHandler("Problem with reading a file.", 104);
        inic >> passize;
        if (!inic) errorHandler("Problem with reading a file.", 105);
        string str;
        getline(inic, str);
        for (size_t i = 0; i < domsize; i++) {
            getline(inic, one_domain);
            this->addFromFile('d', one_domain);
        }
        for (size_t i = 0; i < passize; i++) {
            getline(inic, one_password);
            this->addFromFile('p', one_password);
        }
        for (size_t i = 0; i < logsize; i++) {
            int connectionNumber;
            inic >> connectionNumber;
            inic >> c;
            getline(inic, one_login);
            this->addFromFile(connectionNumber, 'l', one_login);
        }
        inic.close();
        return true;
    }
}

bool CDatabase::FirstSetup(const CFile & cInicFile) {
    ifstream inic(cInicFile.GetFilename());
    if(!inic.is_open()){
        cout<<"Welcome. First things first, you need to setup your main password:\n";
        mainPassword.MakeMainPassword();
        cout<<"Please remember this password, you will need it (right now for example).\n";
        WriteTo(inicFile);
    }else{
        inic.seekg (0, inic.end);
        int length = inic.tellg();
        if (length == 0) {
            errorHandler("Inic file empty.\n", 98);
        }
        SetupFrom(cInicFile);
    }
    if(!inic && inic.good()) {
        errorHandler("Problem with opening a file.", 100);
        return false;
    }
    return true;
}

bool CDatabase::WriteTo(const CFile & cFile)const {
    //cout<<"Writing to "<<cFile.GetFilename()<<".\n";
    //cout<<cFile.GetFilename();
    ofstream inic;
    inic.open(cFile.GetFilename());
    inic << mainPassword.ReturnHash() <<"\n";
    inic << m_LoginData.size()<<":";
    inic << m_DomainData.size()<<":";
    inic << m_PasswordData.size()<<"\n";
    //cout<<m_LoginData.size()<<" size\n";
    //typename set<m_DomainData*>::iterator it;
    for(auto item2 : m_DomainData) {
        inic<<item2->getMainText()
            <<":"
            <<item2->getNote()
            <<":"
            <<"\n";
    }
    for(auto item3 : m_PasswordData) {
        inic<<XCryptString(mainPassword.ReturnHash(),item3->getMainText())
            <<":"
            <<item3->getNote()
            <<":"
            <<"\n";
    }
    for(auto item : m_LoginData) {
        inic<<item->m_connections.size()<<":"
            <<item->getMainText()
            <<":"
            <<item->getNote();
        for(size_t i=0;i<item->m_connections.size();i++){
            inic<<":"
                <<item->m_connections[i]->CDom.getMainText()
                <<":"
                <<XCryptString(mainPassword.ReturnHash(),item->m_connections[i]->CPas.getMainText());
        }
        inic<<":\n";
    }
    inic.close();
    return false;
}

CDatabase::CFile CDatabase::GetInicFile() const {
    return inicFile;
}

CDatabase::CFile CDatabase::GetBackupFile() const{
    return backupFile;
}

void CDatabase::CFile::SetFilename(const string & set_filename) {
    filename = set_filename;
}

string CDatabase::CFile::GetFilename() const {
    return filename;
}
