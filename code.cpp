#include "code.h"
#include <cstring>

Code::Code(Config &conf)
{
    this->cdBase_ = conf.base;
    this->chLen_ = getChLen();
    this->pathIn_=conf.sInFilename;
    this->pathOut_=conf.sOutFilename;
    this->readText();
    this->sMaxLen_=conf.sLen;
    destText_ = new char* [cLines_];

    for (int i=0;i<cLines_;i++)
    {
        destText_[i]=new char [(chLen_*sMaxLen_)+1];
        for (int j=0;j<sMaxLen_*chLen_;j++)
            destText_[i][j]='0';
        destText_[i][sMaxLen_*chLen_]='\0';
    }

}

char* Code::convertCh (char ch)
{
    char* res = new char [chLen_];
    for (int i=0;i<chLen_;i++)
        res[i]='0';
    int i=0;
    int mod=0;
    while  (ch!=0)
    {
        mod=ch%cdBase_;
        ch/=cdBase_;
        if (mod<10) res[i]='0'+mod;
        else res[i]='A'+(mod-10);
        i++;
    }
    res=revCodedCh(res);
    return res;
}

char* Code::revCodedCh (char* ch)
{
        for (int i=0;i<chLen_/2;i++)
        {
                char tmp=ch[i];
                ch[i]=ch[chLen_-i-1];
                ch[chLen_-i-1]=tmp;
        }
        return ch;
}


void Code::writeCh (char  source,char* destLine,  int pos)
{
    char* srcCh = convertCh(source);
    for (int i=0; i<chLen_;i++) destLine[pos+i]=srcCh[i];
    delete (srcCh);
}

void Code::code()
{
    for (int i=0; i<cLines_; i++ )
    {
        for (int j=0; j<strlen(srcText_[i]);j++)
                writeCh (srcText_[i][j],destText_[i],j*chLen_);
    }
}
