#include "code.h"
#include <cstring>
#include <stdio.h>
Code::Code(Config &conf)
{
    this->cdBase_ = conf.base;
    this->chLen_ = getChLen();
    this->pathIn_=conf.sInFilename;
    this->pathOut_=conf.sOutFilename;
    this->readText();
    this->sMaxLen_=conf.sLen;
    this->destLen_ = srcLen_*chLen_+sMaxLen_-(srcLen_*chLen_)%sMaxLen_+1;

    destText_ = new char [destLen_];
    for (int i=0;i<destLen_;i++)  destText_[i]='0';
    destText_[destLen_]='\0';

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
     for (int i=0;i<srcLen_;i++)
           writeCh (srcText_[i],destText_,i*chLen_);
     writeCh ((char)2,destText_,srcLen_*chLen_);
}

void Code::writeText ()
{
    FILE* fout = fopen(this->pathOut_,"w");
    for (int i=0;i<destLen_;i++)
    {
        if (i%sMaxLen_==0 && i!=0) fprintf(fout,"\n");
        fprintf (fout,"%c",destText_[i]);
    }
    fclose(fout);
}
