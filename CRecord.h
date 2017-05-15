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

class CRecord{
    //CRecord is a parent class for domains, usernames and passwords
    public:
      CRecord();
     // ~CRecord();
      virtual                  ~CRecord();
      virtual CRecord &       AddRec (string maintext, string note) = 0;
                              CRecord(string maintext, string note);
                              CRecord(string maintext);
      virtual bool            PrintRec() const;
      string                  getMainText() const;
      void                    setMainText(string maintext);
      string                  getNote() const;
      void                    setNote(string note);
      char                    getType() const;
      void                    setType(char type);
      bool                    operator< (const CRecord &com) const;

    void setM_MainText(const string &m_MainText);

//protected:
      string                  m_MainText;
      string                  m_Note;
      char                    m_Type;
      unsigned int            m_UsageCount;
};

struct find_by_maintext {
    find_by_maintext(const string & maintext) : maintext(maintext) {}
    bool operator()(const CRecord & cRec) {
          return cRec.getMainText() == maintext;
    }
private:
    string maintext;
};

class CDomain:public CRecord{
    public:
      //CDomain is a class for each domain
                              CDomain();
                              CDomain(string maintext);
   //   ~CDomain();
      virtual                 ~CDomain() override;
      virtual bool            PrintRec () const override;
      virtual CDomain &       AddRec (string text, string note) override;

};
class CPassword:public CRecord{
    public:
      //CPassword is a class for storing single passwords
                              CPassword();
    //  ~CPassword();
      virtual                 ~CPassword() override;
      virtual bool            PrintRec () const override;
      //Password is not writtable, so it has its own method
      virtual CPassword &     AddRec (string text, string note)  override;
    private:
      string                  m_hash;
};
struct SCouple{
    public:
      bool                    operator <(SCouple com);
      CDomain                 CDom;
      CPassword               CPas;
};
class CLogin:public CRecord{
    public:
                              CLogin();
                              CLogin(string maintext);
   //   ~CLogin();
      virtual                 ~CLogin() override;
      virtual bool            PrintRec () const override;
      //CLogin is a class for single usernames
      vector<SCouple>         m_connections;
      virtual CLogin &        AddRec (string text, string note) override;
};



#endif //SEMESTRALKA_SEME_HR
