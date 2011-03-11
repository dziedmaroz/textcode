#include "decode.h"
#include "cstring"
Decode::Decode()
{
    this->cdBase_=0;
    this->chLen_=0;
    this->srcLen_=0;
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
    validate ();
    this->sMaxLen_=conf.sLen;

    this->destLen_=srcLen_/chLen_+1;
    destText_= new char [destLen_];
    upcase();
    for (int i=0;i<destLen_;i++)    destText_ [i]= '0';
    destText_[destLen_]='\0';
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
    for (int i=0;i<srcLen_;i++)
    {
        if (srcText_[i]>='a' && srcText_[i]<='z')
                srcText_[i]='A'+(srcText_[i]-'a');
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


   for (int i=0;i<this->destLen_;i++)
   {
       if (convertCh (srcText_,i*chLen_)==2)
       {
           destText_[i]='\0';
           break;
       }
       destText_[i]=convertCh (srcText_,i*chLen_);
   }
}

bool Decode::emptyBlock(char *line, int pos)
{
    int i=0;
    while (line[pos+i++]=='0' && i<chLen_);
    if (i!=chLen_) return false;
    return true;

}


void Decode::validate ()
{
    int cnt =0;
    for (int i=0;i<strlen(srcText_);i++)
    {
        if (srcText_[i]=='\n')
        {
            for (int j=i;j<strlen (srcText_)-1;j++)
                srcText_[j]=srcText_[j+1];
            cnt++;
        }
    }
    srcLen_-=cnt;
}
