#include <cstring>
#include "CCode.h"
#include <cstdlib>
CCode::CCode ()
{
	cdBase_=0;
	maxLen_=0;
	chLen_=0;
	cLines_=0;
        opentext_=NULL;
        cryptedtext_=NULL;
}

CCode::CCode (char** source, int base, int linescount)
{
        copyText (opentext_,source,linescount);
	cdBase_=base;
	cLines_=linescount;
	maxLen_=0;
	for (int i=0;i<cLines_;i++)
		if (maxLen_<strlen (opentext_[i])) maxLen_=strlen(opentext_[i]);
        chLen_=getChLen(cdBase_);          //get max char len
        cryptedtext_=new char* [cLines_];
	for (int i=0;i<cLines_;i++)
	{
                cryptedtext_[i]=new char [maxLen_*chLen_];
		for (int j=0;j<maxLen_;j++) cryptedtext_[i][j]='0'; // fillin' strings with '0'
		cryptedtext_[i][maxLen_]='\0'; 
	}
}

CCode::~CCode ()
{
	 if (opentext_!=0) freeMyText(opentext_);
	 if (cryptedtext_!=0) freeMyText (cryptedtext_);
}

int CCode::getChLen (int base)
{
	int res=0;
	int mx=255;
	while (mx!=0)
	{
		mx/=base;
		res++;
	}
	return res;
}

void CCode::freeMyText (char** text)
{
	for (int i=0;i<cLines_;i++)
                delete (text[i]);
        delete (text);
}

char* CCode::convertCh (char ch)
{
        char* res = new char [chLen_];
	for (int i=0;i<chLen_;i++)
		res[i]='0';
    int i=0;
	int mod=0;
	while  (ch!=0)
	{
		mod=ch%cdBase_;
		if (mod<10) res[i]='0'+mod;
		else res[i]='A'+(mod-10);
	}
	res=revCodedCh(res);
    return res;
}

char* CCode::revCodedCh (char* ch)
{
	for (int i=0;i<chLen_/2;i++)
	{
		char tmp=ch[i];
		ch[i]=ch[chLen_-i];
		ch[chLen_-i]=tmp;
	}
	return ch;
}

void CCode::codeText() 
{
	for (int i=0; i<cLines_; i++ )
	{
		for (int j=0; j<strlen(opentext_[i]);j++)
			writeCh (opentext_[i][j],cryptedtext_[i],j*chLen_);		
	}
}

void CCode::writeCh (char source, char* dest, int pos)
{
    char* srcCh = convertCh(source);
	for (int i=0; i<chLen_;i++) dest[pos+i]=srcCh[i];
        delete (srcCh);
}


void CCode::setOpenText (char** text, int base,int nLines)
{
	freeMyText (cryptedtext_);
	*this = CCode (text,base, nLines);
}

void CCode::getCryptedText(char ** text, int & nLines)
{
	copyText(cryptedtext_,text,cLines_);
	nLines=cLines_;
}

void CCode::copyText (char** source, char** dest, int nLines)
{
    dest = new char* [nLines];
    for (int i=0;i<nLines;i++)
	{
                dest[i]= new char [strlen(source[i])];
		for (int j=0; j<strlen(source[i]);j++)
                        source[i][j]=dest[i][j];
                dest[strlen(source[i])]='\0';
	}
}
