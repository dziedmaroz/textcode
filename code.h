#ifndef CODE_H
#define CODE_H
#include "structdef.h"
#include "crypt.h"

class Code : public Crypt
{
    char* convertCh (char);
    void writeCh (char  ,char* , int);
    char* revCodedCh (char*);
public:
    Code(Config &conf);
    void writeText ();
    void code();

};

#endif // CODE_H
