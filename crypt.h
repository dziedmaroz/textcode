#ifndef CRYPT_H
#define CRYPT_H

class Crypt
{
protected:
    char* srcText_;
    char* destText_;
    int srcLen_;
    char* pathIn_;
    char* pathOut_;
    int chLen_;
    int cdBase_;
    int destLen_;
    int sMaxLen_;
    void readText ();
    int getChLen ();
public:
    Crypt ();
    void writeText ();
    virtual ~Crypt();
};

#endif // CRYPT_H
