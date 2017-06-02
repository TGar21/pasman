//
// Created by Friedrich Tadeáš on 24.05.17.
//

#ifndef SEMESTRALKA_CLOGIN_H
#define SEMESTRALKA_CLOGIN_H

#include "CRecord.h"

using namespace std;
/**
 * structure for the connections that will be used for login
 */
struct SCouple{
public:
    bool                    operator <(SCouple com);
    CDomain                 CDom;
    CPassword               CPas;
};
/**
 * child class of records for login, it has overriden construction, destruction, adding and prinitng
 */
class CLogin:public CRecord{
public:
    CLogin();
    CLogin(string maintext);
    /**
     * here is stored the domains and passwords connected with this exact login
     */
    vector<SCouple*>        m_connections;
    virtual void            setType() override;
    virtual                 ~CLogin();
    virtual bool            PrintRec () const override;
    CLogin & AddRec(string text, string note)override  {
        string x=text;x=note;
        return *this;
    }
};

#endif //SEMESTRALKA_CLOGIN_H
