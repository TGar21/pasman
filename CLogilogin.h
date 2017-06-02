#include "CLogin.h"
using  namespace std;
class CLoginLogin:public CLogin{
protected:
    vector<SCouple>         m_connections;
    string m_maintext;
    string m_note;
public:
    virtual string          getMainText() const override;
    virtual string          getNote() const override;
    virtual bool            PrintRec () const override;
    virtual void            setMainText(string maintext) override;
    virtual void            setNote(string note) override;
    virtual ~CLoginLogin() override;

    //virtual void            setType(char type) override;

};
