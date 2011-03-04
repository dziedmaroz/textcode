#ifndef DECODE_H
#define DECODE_H
#include "crypt.h"
#include "structdef.h"
class Decode : public Crypt
{
    int intpow (int x, int y);
    char convertCh (char*,int pos);
  //  void writeCh (char ch, char* destLine, int pos);
    void upcase ();
    bool emptyBlock (char* line, int pos);
public:
    Decode();
    Decode (Config& conf);
    void decode ();
};

#endif // DECODE_H
