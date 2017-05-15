//
// Created by Friedrich Tadeáš on 05/04/2017.
//
#ifndef SEMESTRALKA_SEME_H
#define SEMESTRALKA_SEME_H

#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <openssl/sha.h>
#include <openssl/aes.h>
#include <sstream>
#include "CRecord.h"

//#include <SDL2/SDL.h>

using namespace std;

class CMainPassword{
private:
    string                  m_mainPasswordHash;
public:
    bool                    HashString(string input, string & output) const;
    bool                    ChangeMainPassword();
    bool                    PasswordCorrect(string input) const;
    bool                    MakeMainPassword();
    string                  ReturnHash() const;
    void                    setMainPassword(string set_hash);
    string x="abc";

};

class CDatabase{
private:

    class CFile{
    private:
        string                  filename;
    public:
        void                    SetFilename(string set_name);
        string                  GetFilename() const;
    };


    //one password is covering entry to all the passwords
      set<CLogin*>            m_LoginData;
      set<CDomain*>           m_DomainData;
      set<CPassword*>         m_PasswordData;
      CMainPassword           mainPassword;
      CFile                   inicFile;
      CFile                   backupFile;
    public:
      CDatabase();
      ~CDatabase();
      bool                    UpdateRec (string old_maintext, string new_maintext, string note, char type);
      CMainPassword           GetMainPassword();
    //methdo supports only updating main texts
      bool                    RemoveRec (string maintext, char type);
      bool                    Connect (string login);
      //Add new item in database, made from three basic records
      void                    PrintAllLogins();
      void                    PrintAllDomains();
      string                  XCryptString(string key,string xcrypted);
      void                    AddDomain();
      void                    AddPassword();
      void                    PrintAllPasswords();
      void                    PrintWhole();
      void                    NewRec(string maintext, string note, char type);
      CDomain                 SearchDom(string sRecord, set<CDomain *> setOfRecords);
      CPassword               SearchPas(string sRecord, set<CPassword *> setOfRecords);
      bool                    SetupFrom(CFile cFile);
      bool                    FirstSetup(CFile cInicFile);
      bool                    WriteTo(CFile cFile);
      CFile                   GetInicFile();
      CFile                   GetBackupFile();
   /*   template <typename T>
      bool                    setData(T cData);*/
};




#endif //SEMESTRALKA_SEME_H
