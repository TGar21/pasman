/**
 * Created by Friedrich Tadeáš on 05/04/2017.
 */
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
#include "CLogin.h"
#include "CMainPassword.h"
//#include <SDL2/SDL.h>

using namespace std;
/**
 * Main class of the program, it solves all the database operations
 */
class CDatabase{
private:

    /**
     * class for storing files for backup and initialization of the database.
     */
    class CFile{
    private:
        string                  filename;
    public:
        void                    SetFilename(const string & set_name);
        string                  GetFilename() const;
    };

    //one password is covering entry to all the passwords
    /**
     * There are three sets of records here, for storing all logins, domains and passwords.
     */
      set<CLogin*>            m_LoginData;
      set<CDomain*>           m_DomainData;
      set<CPassword*>         m_PasswordData;
      set<CRecord*>           m_AllOfThem;
    /**
     * Two files:
     * one of them, the inicFile is the main inic file, it is used when the app is launched and ended
     * the second one, the backupFile is for storing another backup of database, it can be filled by the user
     */
      CFile                   inicFile;
      CFile                   backupFile;
    public:
      CMainPassword           mainPassword;
    /**
     * Getter for the record set
     * @return set of all records in the database
     */
      set <CRecord *> GetAllOfThem();
    /**
     * constructor, it mainly handles the files and their names
     */
      CDatabase();
    /**
     * destructor, it deletes the database (after it is safely stored in in the file)
     */
      ~CDatabase();
    /**
     * Methods for adding new record to the database
     * @param maintext the name of the record
     * @param note the note to add
     * @param type
     */
    void                    NewRec(string maintext, string note, char type);
    /**
     * Updates some record in the database, there is currently problem with connected domains and passwords
     * @param old_maintext current text
     * @param new_maintext text we want
     * @param note new note to add
     * @param type type of the changed record
     * @return false if the original record doesn't exists
     */
      bool                    UpdateRec (string old_maintext, string new_maintext, string note, char type);
    /**
     * @return  main password for the database (getter)
     */
      CMainPassword           GetMainPassword()const;
    /**
     * Method for removing files from database
     * @param maintext name of the record, you want to remove
     * @param type type of the record, you want to remove
     * @return false if the orginial record doesn't exists
     */
      bool                    RemoveRec (const string & maintext, const char & type);
    /**
     * Method for connecting the data, it uses method Connections, this is more UI
     * @param login
     * @return false if the login doesn't exists
     */
      bool                    Connect (const string & login);
    /**
     * Changes the data, strictly data method, used even on places without user output
     * @param maintext login to connect
     * @param sDomain  domain to connect
     * @param sPassword  password to connect
     */
      void                    Connection(const string & maintext, const string & sDomain, const string & sPassword);
    /**
     * Methods for printing lot of different things
     */
      void                    PrintAll(const set<CRecord*> & m_RecordData)const;
      void                    PrintAllLogins()const;
      void                    PrintAllDomains()const;
      void                    PrintAllPasswords()const;
      void                    PrintWhole()const;
    /**
     * Currently not working. It should return En/Decrypted string
     * @param key
     * @param xcrypted
     * @return
     */
      string                  XCryptString(string key,string xcrypted)const;
    /**
     * Method is used to connect logins with domains, this is searching the domains in the database
     * @param sRecord name of the domain
     * @param setOfRecords where to search
     * @return found domain
     */
    const CDomain &               SearchDom(const string & sDom) const;
    /**
     * The same as preious method, but for Passwords, it is searching them in the database
     * @param sRecord
     * @param setOfRecords set of Passwords
     * @return found password
     */
    const CPassword &             SearchPas(const string & sPas)const;
    /**
     * Important method for getting data from files
     * @param cFile the file to gat the data from
     * @return false if opening a file was unsuccessful
     */
      bool                    SetupFrom(const CFile & cFile);
    /**
     * Searching Record
     * @param searched is string we are looking for in texts and notes
     */
      void                     FindRec(const string & searched )const;
    /**
     * Using previous method it is getting data when app is launched for the first time
     * @param cInicFile the inic file, if it is empty, it is the first launch
     * @return false if opening a file was unsuccessful
     */
      bool                    FirstSetup(const CFile & cInicFile);
    /**
     * Method writes data in the file, both backup and inic
     * @param cFile where to store the data
     * @return
     */
      bool                    WriteTo(const CFile & cFile)const;
    /**
     * Getter for Inic file
     * @return a file
     */
      CFile                   GetInicFile()const;
    /**
     * Getter for Backup File
     * @return a file
     */
      CFile                   GetBackupFile()const;
    /**
     * Method for storing the data -- domains and password from the SetupFrom method.
     * @param type is type of the record
     * @param rec name of the record
     */
      void                    addFromFile(const char & type,const string & rec);
    /**
     * overloaded function, this one is for logins
     * @param connectionNumber how many connections this login have
     * @param type
     * @param rec name of the record
     */
      void                    addFromFile(const int & connectionNumber, const char & type,const string & rec);
};




#endif //SEMESTRALKA_SEME_H
