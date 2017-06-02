//
// Created by Friedrich Tadeáš on 05/04/2017.
//
#ifndef SEMESTRALKA_SEME_HR
#define SEMESTRALKA_SEME_HR

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


//#include <SDL2/SDL.h>

using namespace std;

/**
 * parent class for all types of records-- domains, logins, passwords
 */
class CRecord{
public:
    CRecord();
    CRecord(string maintext, string note);
    CRecord(string maintext, string note,int usage);
    CRecord(string maintext);
    virtual                 ~CRecord();
    virtual CRecord &       AddRec (string maintext, string note) {return *this;};
    /**
     * virtual function for printing
     * @return always false
     */
    virtual bool            PrintRec() const;
    /**
     * The following are getters and setters for the main text of records, its note and type
     */
    string                  getMainText() const;
    void                    setMainText(string maintext);
    string                  getNote() const;
    void                    setNote(string note);
    char                    getType() const;
    virtual void            setType();
    /**
     *  overloaded operator for the set operations
     * @param com
     * @return
     */
    bool                    operator< (const CRecord &com) const;
    string                  m_MainText;
protected:
    string                  m_Note;
    char                    m_Type;
    unsigned int            m_UsageCount;
};
/**
 * structure for the set operations
 */
struct find_by_maintext {
    find_by_maintext(const string & maintext) : maintext(maintext) {}
    bool operator()(const CRecord & cRec) {
        return cRec.getMainText() == maintext;
    }
private:
    string maintext;
};

/**
 * child class of records for domain, it has overriden construction, destruction, adding and prinitng
 */
class CDomain:public CRecord{
public:
    vector <string>         used;
    CDomain();
    CDomain(string maintext, string note,int usage);
    CDomain(string maintext);
    virtual                 ~CDomain() override;
    virtual bool            PrintRec () const override;
    virtual void            setType() override;
    virtual CDomain &       AddRec (string text, string note) override;

};

/**
 * child class of records for password, it has overriden construction, destruction, adding and printing
 */
class CPassword:public CRecord{
public:
    CPassword();
    virtual                 ~CPassword() override;
    virtual bool            PrintRec () const override;
    virtual void            setType() override;
    virtual CPassword &     AddRec (string text, string note)  override;
    vector <string>         used;
private:
    string                  m_hash;
};




#endif //SEMESTRALKA_SEME_HR
