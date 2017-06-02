#include "CLogin.h"
#include "CLogilogin.h"
using namespace std;
/**
 * subclass for references to CLogilogin
 */
class CRefLogin:public CLogin{
private:
        CLoginLogin & refToLogin;
public:

        CRefLogin(CLoginLogin&);
        virtual ~CRefLogin() override;
        virtual string          getMainText() const override;
        virtual string          getNote() const override;
        virtual bool            PrintRec () const override;
        virtual void            setMainText(string maintext) override;
        virtual void            setNote(string note) override;
   //     virtual void            setType(char type) override;
};