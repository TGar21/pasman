#include "CDatabase.h"

/**
 * class for main user interaction, it has the menu and connects it with the functions
 */
class  CInteract{
public:
    /**
     * The user interface menu, all other things are called from here
     */
    void CoverAll();
    /**
     * mathod usefull in many other methods, it is asking user for the type
     * @param text to print as a question
     * @return type of the record
     */
    char Type(const string & text);
    /**
     * method prints all record in add-order, usefull especially when user wants to connect something
     */
    void PrintAllRec();
    /**
     * similar as Type, but for action
     * @return action, user wanted to do
     */
    char GetAction() const;
    /**
     * Here starts the user activity in the app, prints the Welcome string and calls the setup from file
     */
    void Entry();
    /**
     * this methods deals with the authentication of the user by the main password
     * @return false when he provides wrong answer and app is closed
     */
    bool Authenticate() ;
    /**
     * called when user wants to connect login, domain and password
     */
    void Connect();
    /**
     * When new record should be added to the database
     */
    void Add();
    /**
     * Deleting of the records in the database
     */
    void Delete();
    /**
     * Changing of the logins, or unconnected domains or passwords
     */
    void Update();
    /**
     * Printing any of the records, possibility to print logins with or withou connections
     */
    void Print(const char & type)const;
    /**
     * Method to find some record in the database
     */
    void Find()const;
    /**
     * Close the app and say good bye to user
     */
    void  Exit() const;
    /**
     * UI for user backup database and also calls methods to actually backups it
     * @return false if the works with the files fails
     */
    bool Backup() const;
    /**
     * Getting the database from backup, provides a dialogue if user really wants to delte current database
     * @return false if the works with the files fails
     */
    bool Restore();
    /**
     * Changing the main password of the database
     */
    void ChangePass();

private:
    CDatabase database;
    string mainpassword;
    char type;
    string text;
    string note;
    string login;
    string domain;
    string password;

};

