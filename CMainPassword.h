/**
 * Created by Friedrich Tadeáš on 05/04/2017.
 */

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
//#include <SDL2/SDL.h>

using namespace std;

/**
 *Class CMain Password that represents the password for entering the program
 *
 */
class CMainPassword{
private:
    string                  m_mainPasswordHash;
public:
    /**
     * Method that hashes the string, so it is not human-readable
     * @param input the inserted string, which needs to be hashed
     * @param output already hashed string
     * @return a false when hashing fails
     */
    bool                    HashString(const string & input, string & output) const;
    /**
     * Method for handling changes of password
     * @return new, changed password
     */
    string                  ChangeMainPassword();
    /**
     * Method for deciding whether the password is current main password of the daatabase.
     * @param input is string which needs to be change for it correctness
     * @return true if the input and current password is the same, false if it's not
     */
    bool                    PasswordCorrect(const string & input) const;
    /**
     * Method creates main password, when database is started for the first time
     * @return false if hashing fails
     */
    bool                    MakeMainPassword();
    /**
     * Method for retrieving hash of the main password, mainly for checks, and usefull for developing
     * @return hash of the current database main password in the std::string
     */
    string                  ReturnHash() const;
    /**
     * Setter for main password (hash)
     * @param set_hash string -- what should be setted as main password hash
     */
    void                    setMainPassword(const string & set_hash);
};
