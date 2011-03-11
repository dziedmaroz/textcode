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
 srcLen_=0;
 while (!feof(f_in))
 {
   char ch = fgetc(f_in);
   srcLen_++;
 }

 srcText_ = new char [srcLen_];
 rewind(f_in);
 int i=0;
 sMaxLen_=0;
 while (!feof(f_in))
 {
      srcText_[i++]=fgetc(f_in);
 }
 fclose(f_in); 
}

void Crypt::writeText()
{
    FILE* f_out=fopen(this->pathOut_,"w");    
    int i=0;
    while(destText_[i++]!='\0')
        fprintf(f_out,"%c",destText_[i]);
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
    delete[] srcText_;
    delete[] destText_;
}
