#include "decode.h"
#include "cstring"
Decode::Decode()
{
    this->cdBase_=0;
    this->chLen_=0;
    this->cLines_=0;
    this->srcText_=0;
    this->sMaxLen_=0;
    this->pathIn_=0;
    this->pathOut_=0;
    this->srcText_=0;
    this->destText_=0;
}

Decode::Decode (Config &conf)
{
    this->cdBase_=conf.base;
    this->chLen_=getChLen();
    this->pathIn_=conf.sInFilename;
    this->pathOut_=conf.sOutFilename;
    readText();
    //this->sMaxLen_=conf.sLen;
    destText_= new char* [cLines_];
    upcase();
    for (int i=0;i<cLines_;i++)
    {
        destText_ [i]= new char [sMaxLen_/chLen_+1];
        destText_ [i][sMaxLen_/chLen_]='\0';
    }
}

int Decode::intpow(int x, int y)
{
    if (y==0) return 1;
    int pwx = x;
    for (int i=1;i<y;i++)
        pwx*=x;
    return pwx;
}

void Decode::upcase()
{
    for (int i=0;i<cLines_;i++)
    {
        for (int j=0;j<strlen(srcText_[i]);j++)
            if (srcText_[i][j]>='a' && srcText_[i][j]<='z')
                srcText_[i][j]='A'+(srcText_[i][j]-'a');
    }
}

char Decode::convertCh(char * ch, int pos)
{
    char res=0;
    for (int i=0;i<chLen_;i++)
    {
        char tmp=ch[i+pos];
        if (tmp>='0' && tmp<='9') tmp-='0';
        else
            if (tmp>='A' && tmp<='Z') tmp=tmp+10-'A';
                else return 0;
        res+=tmp*intpow(cdBase_,chLen_-i-1);
    }
    return res;
}


void Decode::decode()
{

    for (int i=0;i<cLines_;i++)
    {
        if (strlen(srcText_[i])==0) destText_[i][0]=0;
        for (int j=0;j<strlen(srcText_[i]);j+=chLen_)
        {
            if (emptyBlock(srcText_[i],j))
            {
                destText_[i][j/chLen_]='\0';
                break;
            }
            else destText_[i][j/chLen_]=convertCh(srcText_[i],j);
        }
    }
}

bool Decode::emptyBlock(char *line, int pos)
{
    int i=0;
    while (line[pos+i++]=='0' && i<chLen_);
    if (i!=chLen_) return false;
    return true;

}
