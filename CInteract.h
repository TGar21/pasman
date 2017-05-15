#include "CDatabase.h"

class  CInteract{
public:
    char GetType(string text);
    char GetAction();
    void CoverAll();
    void Entry();
    bool Authenticate();
    void Connect();
    void Add();
    void Delete();
    void Update();
    void Print();


private:
    CDatabase database;
    string mainpassword;
    char action;
    char type;
    string text;
    string note;
    string login;
    string domain;
    string password;

};

