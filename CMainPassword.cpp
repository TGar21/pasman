// Created by Friedrich Tadeáš on 05/04/2017.
//
#include "CDatabase.h"
#include "CLogin.h"
#include <cmath>
using namespace std;

template <typename T>
int errorHandler(T err_desc,const int & err_number){
    cout<<"error: "<<err_desc<<endl;
    return err_number;
}
bool   CMainPassword::HashString(const string & input, string & output) const{
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
string   CMainPassword::ChangeMainPassword(){
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
        return "false";
    }
    if(currHash!=m_mainPasswordHash) {
        cout<<"Wrong password\n";
        return "false";
    }
    while(ans_again=='y'){
        cout<<"Please write your new password\n";
        cin>>newPassword;
        if(!HashString(newPassword,newHash1)){
            errorHandler("Problem with hashing 2.\n",2);
            return "false";
        }
        cout<<"Please write it again.\n";
        cin>>newPassword;
        if(!HashString(newPassword,newHash2)){
            errorHandler("Problem with hashing 3.\n",2);
            return "false";
        }
        if(newHash1==newHash2) {
            if(newHash1==currHash)
                errorHandler("Warning: New and current password are the same.\n",0);
            this->setMainPassword(newHash1);
            cout<<"Password changed.\n";
            return m_mainPasswordHash;
        } else {
            cout<<"Passwords differ. Try again? (y/n)\n";
            cin>>ans_again;
            if(ans_again!='y')
                cout<<"Ok, password wasn't changed";
        }
    }
    return "false";
}
bool   CMainPassword::PasswordCorrect(const string & input) const{
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

void CMainPassword::setMainPassword(const string & set_hash){
    m_mainPasswordHash=set_hash;
}

