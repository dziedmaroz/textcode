#include <cstring>
#include "CCode.h"
#include <cstdlib>
CCode::CCode ()
{
	cdBase=0;
	maxLen=0;
	chLen=0;
	cLines=0;
	opentext=0;
	cryptedtext=0;
}

CCode::CCode (char** source, int base, int linescount)
{
	opentext=source;
	cdBase=base;
	cLines=linescount;
	maxLen=0;
	for (int i=0;i<cLines;i++)
		if (maxLen<strlen (opentext[i])) maxLen=strlen(opentext[i]);
    chLen=getChLen(cdBase);          //get max char len
	cryptedtext=(char**) malloc (sizeof(char*)*cLines);
	for (int i=0;i<cLines;i++)
	{
		cryptedtext[i]=(char*) malloc (sizeof(char)*(maxLen*chLen+1));
		for (int j=0;j<maxLen;j++) cryptedtext[i][j]='0'; // fillin' strings with '0'
		cryptedtext[i][maxLen]='\0'; 
	}
}

CCode::~CCode ()
{
	 if (opentext!=0) freeMyText(opentext);
	 if (cryptedtext!=0) freeMyText (cryptedtext);
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
	for (int i=0;i<cLines;i++)
		free (text[i]);
	free (text);
}

char* CCode::convertCh (char ch)
{
	char* res = (char*) malloc (sizeof(char)*chLen);
	for (int i=0;i<chLen;i++)
		res[i]='0';
    int i=0;
	int mod=0;
	while  (ch!=0)
	{
		mod=ch%cdBase;
		if (mod<10) res[i]='0'+mod;
		else res[i]='A'+(mod-10);
	}
	res=revCodedCh(res);
    return res;
}

char* CCode::revCodedCh (char* ch)
{
	for (int i=0;i<chLen/2;i++)
	{
		char tmp=ch[i];
		ch[i]=ch[chLen-i];
		ch[chLen-i]=tmp;
	}
	return ch;
}
