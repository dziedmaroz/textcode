#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include "structdef.h"
#include "code.h"

#include "main.h"

int main ()
{
  Config conf;
  if (!readConfig("codethis.conf",conf))
  {	
	  printf ("Closing application...\n");
          delete (conf.sInFilename);
          delete (conf.sOutFilename);
	  return 100;
  }
  printf ("\n\n");
//  if (!checkConfig(conf))
//  {
//	  printf ("Closing application...\n");
//	  delete (conf.sInFilename);
//	  delete (conf.sOutFilename);
//	  return 200;
//  }

  Code tocode (conf);
  tocode.code();
  tocode.writeText();
  delete (conf.sInFilename);
  delete (conf.sOutFilename);

  system ("PAUSE");
  return 0;
}

bool readConfig (char* confFileName, Config& conf)
{
    FILE* fConf = fopen (confFileName, "r");
    conf.sInFilename   = new char [200];
    conf.sOutFilename  = new char [200];
    if (!fConf)
    {
        printf ("Error:Can't find configuration file ('%s').\n",confFileName);
        return false;
    }
    fscanf(fConf,"%d\n",&conf.base);
    fscanf(fConf,"%d\n",&conf.sLen);
    fscanf(fConf,"%c\n",&conf.mode);
    fgets (conf.sInFilename,200,fConf);
    fgets (conf.sOutFilename,200,fConf);
    conf.sInFilename[strlen(conf.sInFilename)-1]='\0';
    conf.sOutFilename[strlen(conf.sOutFilename)-1]='\0';

    printf ("Base             : %d\n", conf.base);
    printf ("Line max length  : %d\n",conf.sLen);
    if (conf.mode=='c')
      printf ("Mode             : code\n");
    else
        printf ("Mode             : decode\n");
    printf ("Source file      :'%s'\n",conf.sInFilename);
    printf ("Destination file :'%s'\n",conf.sOutFilename);
    fclose (fConf);
    return true;
}

bool checkConfig (Config& conf)
{
    bool isOk=true;
    if (conf.base>36)
    {
        printf ("Error:Too big base (%d). Max base is 36.\n",conf.base);
        isOk=false;
    }
    FILE* test = fopen(conf.sInFilename,"r");
    if (!test)
    {
        printf ("Error: File with open text ('%s') does not exist.\n",conf.sInFilename);
        isOk=false;
    }
    fclose (test);
    test  = fopen(conf.sOutFilename,"r");
    if (test)
    {
        printf ("Warring: File for output (%s) already exists. It will be overwritten.  Do you whant to continue? [Y/N]\n>",conf.sOutFilename);
		char choise;
        scanf("%c",&choise);
        if (choise!='Y'|| choise !='y') return false;
    }
    fclose (test);
    if (!strcmp(conf.sInFilename,conf.sOutFilename))
    {
        printf ("Warring: Source('%s')  and destination('%s') are matching. All data in source file will be lost. Do you whant to continue? [Y/N]\n>",conf.sInFilename,conf.sOutFilename);
        char choise;
        scanf("%c",&choise);
        if (choise!='Y'|| choise !='y') return false;
    }
    return isOk;
}

char** readtext (char* filename, int& nLines)
{
	char** text = new char* ;
	FILE* fin = fopen (filename,"r");
	nLines=0;
	while (!feof(fin))
	{
		text[nLines]= new char [500];
		fgets(text[nLines],500,fin);
		if (strlen(text[nLines])!=0) 
		{
			text[nLines][strlen(text[nLines])]='\0';
			nLines++;
		}
	}
	fclose(fin);
	return text;
}
void writeText (char* filename,char** text, int nLines)
{
	FILE* fout = fopen (filename,"w");
	for (int i=0;i<nLines;i++)
		fprintf (fout,"%s\n", text[i]);
	fclose(fout);
}
