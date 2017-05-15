// Created by Friedrich Tadeáš on 05/04/2017.
//
#include "CDatabase.h"
#include <cmath>
using namespace std;

template <typename T>
int errorHandler(T err_desc,int err_number){
    cout<<"error: "<<err_desc<<endl;
    return err_number;
}

bool   CMainPassword::HashString(string input, string & output) const{
    //method for hashing strings, sha256 is chosen cipher
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    if(!SHA256_Init(&sha256))
        return false;
    if(!SHA256_Update(&sha256, input.c_str(), input.size()))
        return false;
    if(!SHA256_Final(hash, &sha256))
        return false;
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    output=ss.str();
    return true;
}
bool   CMainPassword::ChangeMainPassword(){
    string   currPassword;
    string   currHash;
    string   newPassword;
    string   newHash1;
    string   newHash2;
    char     ans_again='y';

    cout<<"Please write your current password (max 30 chars) \n";
    cin>>currPassword;
    if(!HashString(currPassword,currHash)){
        errorHandler("Problem with hashing 1.\n",2);
        return false;
    }
    if(currHash!=m_mainPasswordHash) {
        cout<<"Wrong password\n";
        return false;
    }
    while(ans_again=='y'){
        cout<<"Please write your new password\n";
        cin>>newPassword;
        if(!HashString(newPassword,newHash1)){
            errorHandler("Problem with hashing 2.\n",2);
            return false;
        }
        cout<<"Please write it again.\n";
        cin>>newPassword;
        if(!HashString(newPassword,newHash2)){
            errorHandler("Problem with hashing 3.\n",2);
            return false;
        }
        if(newHash1==newHash2) {
            if(newHash1==currHash)
                errorHandler("Warning: New and current password are the same.\n",0);
            m_mainPasswordHash = newHash1;
            cout<<"Password changed.\n";
            return true;
        } else {
            cout<<"Passwords differ. Try again? (y/n)\n";
            cin>>ans_again;
            if(ans_again!='y')
                cout<<"Ok, password wasn't changed";
        }
    }
    return false;
}
bool   CMainPassword::PasswordCorrect(string input) const{
    string hash;
    if(!HashString(input,hash)){
        errorHandler("Problem with hashing 4.",2);
        return false;
    }
    if(hash==m_mainPasswordHash){
        return true;
    } else
        //cout<<"\n"<<input<<", "<< hash<<", heslo: "<<m_mainPasswordHash<<"\n";
        return false;
}
bool   CMainPassword::MakeMainPassword(){
    string cPassword;
    cout<<"Please type a new password\n";
    cin>>cPassword;
    if(!HashString(cPassword,m_mainPasswordHash)){
        errorHandler("Problem with hashing 5.\n",2);
        return false;
    }
    return true;
}
string  CMainPassword::ReturnHash() const{
    return m_mainPasswordHash;
}

void CMainPassword::setMainPassword(string set_hash){
    m_mainPasswordHash=set_hash;
}

CDomain CDatabase::SearchDom(string sRecord, set<CDomain *> setOfRecords){
    for(auto item : setOfRecords){
        if(sRecord==item->getMainText())
            return *item;
    }
    throw "This domain does not exists.\n";
}
CPassword CDatabase::SearchPas(string sRecord, set<CPassword *> setOfRecords){
    for(auto item : setOfRecords){
        if(sRecord==item->getMainText())
            return *item;
    }
    throw invalid_argument ("This password does not exists.\n");
}

bool CDatabase::Connect (string maintext){
    string sDomain,sPassword;
    SCouple connected;
    for(auto item : m_LoginData) {
        if(item->getMainText()==maintext){
            cout<<"Record " + item->m_MainText + " exists, which domain you want to add?\n";
            cin>>sDomain;
            cout<<"Which password?\n";
            cin>>sPassword;

            try {
                connected.CDom = SearchDom(sDomain, this->m_DomainData);
                connected.CPas = SearchPas(sPassword, this->m_PasswordData);
            }catch (const std::invalid_argument& e){
                cout<<"This Record does not exists.\n";
                return false;
            }
            item->m_connections.push_back(connected);
            cout<<"Succesfully connected";
            return true;
        }
    }
    return false;
}

CDatabase::CDatabase() {
   // minimalne se tu musi nacist main password
    //cout<<y<<"\n";
    inicFile.SetFilename("PMinic.txt");
    backupFile.SetFilename("PMbackup.txt");
}

string CDatabase::XCryptString(string key,string xcrypted){
    string result;
    int i;
    size_t minlen=min(key.length(),xcrypted.length());
    for(i = 0; i < minlen; i++)
        result.push_back(key[i]^xcrypted[i]);
    for(i = minlen; i<xcrypted.length();i++) {
            result.push_back(xcrypted[i]);
    }
    cout<<result<<endl;
/*    string key2=key;
    if(key!=key2)
        cout<<key;
  */  /*cout<<"t";
    unsigned char pass_char [xcrypted.length()+2];
    unsigned char key_char [key.length()+2];
    copy( password.begin(), password.end(), pass_char );
    pass_char[password.length()] = '\0';
    cout<<"t";
    copy( key.begin(), key.end(), key_char );
    key_char[key.length()] = '\0';
    cout<<"t";



    unsigned char enc_out [256];

    AES_KEY enc_key;

    AES_set_encrypt_key(key_char, , &enc_key);
    AES_encrypt(pass_char, enc_out, &enc_key);


    cout<<enc_out;*/
    return result;
}

void inic (CRecord * newrec,string maintext,string note,char type){
    newrec->setMainText(maintext);
    newrec->setNote(note);
    newrec->setType(type);
}

void CDatabase::NewRec(string maintext, string note, char type) {
    //Osetrovat plnost databaze
    if(type=='l'){
        CLogin * newrec=new CLogin;
        inic(newrec,maintext,note,type);
        m_LoginData.insert(newrec);
    }else if(type=='p') {
        CPassword * newrec=new CPassword;
        inic(newrec, maintext, note, type);
        m_PasswordData.insert(newrec);
    }
    else{
        CDomain * newrec=new CDomain;
        inic(newrec,maintext,note,type);
        m_DomainData.insert(newrec);
    }
}

void CDatabase::PrintAllLogins() {
    cout<<"List of all logins in database:\n";
    for(auto item : m_LoginData) {
        item->PrintRec();
    }
    cout<<"\n";
}

void CDatabase::PrintAllPasswords() {
    string checkPassword;
    string checkHash;
    cout<<"To see passwords you need to enter your main password\n";
    cin>>checkPassword;
    if(!GetMainPassword().HashString(checkPassword,checkHash))
        errorHandler("Problem with hashing\n",2);
    if(checkHash == GetMainPassword().ReturnHash()){
        for(auto item : m_PasswordData) {
            item->PrintRec();
        }
    } else {
        cout<<"You entered wrong password.\n";
    }
    cout<<"\n";
}

void CDatabase::PrintAllDomains() {
    cout<<"List of all domains in database:\n";
    for(auto item : m_DomainData) {
        item->PrintRec();
    }
    cout<<"\n";
}

CDatabase::~CDatabase() {
    for(auto item : m_LoginData) {
        delete item;
    }
}

template <typename S>
bool erase(string maintext, S & Data){
    for (auto item : Data) {
        if (item->getMainText() == maintext) {
            delete item;
            Data.erase(item);
            return true;
        }
    }
    errorHandler("Record " + maintext + " not found", 9);
    return false;
}

bool CDatabase::RemoveRec(string maintext, char type) {
    if(type=='l')
        return erase(maintext,m_LoginData);
    else if(type == 'p')
        return erase(maintext,m_PasswordData);
    else
        return erase(maintext,m_DomainData);
}

bool CDatabase::UpdateRec(string old_maintext, string new_maintext, string note, char type) {
        if(!RemoveRec(old_maintext,type))
            return false;
        NewRec(new_maintext,note,type);
        return true;
}
CMainPassword CDatabase::GetMainPassword(){
    return mainPassword;
}


void CDatabase::AddDomain() {
    string login;
    cout<<"What Login?\n";
    cin>>login;
}

void CDatabase::PrintWhole() {
    cout<<"List of all logins in database:\n";
    for(auto item : m_LoginData) {
        item->PrintRec();
        /*for(int i=0;i<item->m_connections.size();i++) {
            cout << item->m_connections[i].CDom.m_MainText;//GetMainText();
            cout<<"PRINTWHOLE";
            cout << item->m_connections[i].CPas.m_MainText;
        }*/
    }
    cout<<"\n";

}

bool CDatabase::SetupFrom(CFile cFile) {
    ifstream inic(cFile.GetFilename());
    string setup;
    if(!inic && inic.good()) {
        errorHandler("Problem with opening a file.", 100);
        return false;
    }else{
        string passwordHash;
        getline(inic, passwordHash);
        mainPassword.setMainPassword(passwordHash);
        getline(inic,setup);
        for(int i=0;i<setup.length();i++){

        }

        //TADY SE BUDE MUSET NEJAK NACIST VSECHNO Z TOHO SPUBORU POCINAJE TIM CISLEM
        inic.close();
        return true;
    }
}


bool CDatabase::FirstSetup(CFile cInicFile) {
    ifstream inic(cInicFile.GetFilename());
    if(!inic.is_open()){
        cout<<"Welcome. First things first, you need to setup your main password:\n";
        mainPassword.MakeMainPassword();
        cout<<"Please remember this password, you will need it (right now for example).\n";
        WriteTo(inicFile);
    }else{
        SetupFrom(cInicFile);
    }
    if(!inic && inic.good()) {
        errorHandler("Problem with opening a file.", 100);
        return false;
    }
    return true;
}

bool CDatabase::WriteTo(CFile cFile) {
    //cout<<cFile.GetFilename();
    ofstream inic;
    inic.open(cFile.GetFilename());
    inic << mainPassword.ReturnHash() <<"\n";
    for(auto item : m_LoginData) {
        inic<<item->m_connections.size()<<":";
        for(size_t i=0;i<item->m_connections.size();i++)
            inic<<item->getMainText()
                <<":"
                <<item->getNote()
                <<":"
                <<item->m_connections[i].CDom.getMainText()
                <<":"
                <<item->m_connections[i].CDom.getNote()
                <<":"
                <<XCryptString(mainPassword.ReturnHash(),item->m_connections[i].CPas.getMainText());
    }
    inic.close();
    return false;
}

CDatabase::CFile CDatabase::GetInicFile() {
    return inicFile;
}

CDatabase::CFile CDatabase::GetBackupFile() {
    return backupFile;
}

void CDatabase::CFile::SetFilename(string set_filename) {
    filename = set_filename;
}

string CDatabase::CFile::GetFilename() const {
    return filename;
}
