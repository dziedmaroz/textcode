#include "crypt.h"
#include "structdef.h"
#include <stdio.h>
#include <cstring>

Crypt::Crypt()
{
 this->destText_=NULL;
 this->srcText_=NULL;
 this->chLen_=0;
 this->cdBase_=0;
 this->pathIn_="";
 this->pathIn_="";
 this->sMaxLen_=0;
}

void Crypt::readText ()
{
 FILE* f_in = fopen (this->pathIn_,"r");
 cLines_=0;
 while (!feof(f_in))
 {
    char* tmpS = new char[500];
    fgets(tmpS,500,f_in);
    this->cLines_++;
    delete tmpS;
 }

 srcText_ = new char* [cLines_];
 rewind(f_in);
 int i=0;
 sMaxLen_=0;
 while (!feof(f_in))
 {
     srcText_[i]=new char[500];
     fgets(srcText_[i],500,f_in);
     srcText_[i][strlen(srcText_[i])-1]='\0';
     int j=0;
     for (int j=0;j<500;j++) if (srcText_[i][j]=='\n') srcText_[i][j]='\0';
     if (sMaxLen_<strlen(srcText_[i])) sMaxLen_=strlen(srcText_[i]);
     i++;
 }
 fclose(f_in);
 this->destText_=new char* [this->cLines_];
}

void Crypt::writeText()
{
    FILE* f_out=fopen(this->pathOut_,"w");
    for (int i=0;i<this->cLines_;i++)
        fprintf (f_out,"%s\n",destText_[i]);
    fclose(f_out);
}

int Crypt::getChLen()
{
    int res=0;
    int mx=255;
    while (mx!=0)
    {
            mx/=this->cdBase_;
            res++;
    }
    return res;
}

Crypt::~Crypt()
{
    for (int i=0;i<cLines_;i++)
    {
        delete srcText_[i];
        delete destText_[i];
    }
    delete srcText_;
    delete destText_;
}
