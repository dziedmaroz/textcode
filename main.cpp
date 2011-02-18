#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include "CCode.h"

#include "main.h"

int main ()
{
  Config conf;
  if (!readConfig("codethis.conf",conf)) return 100;
  printf ("\n\n");
  if (!checkConfig(conf)) return 200;

  free (conf.sInFilename);
  free (conf.sOutFilename);
  system ("PAUSE");
  return 0;
}

bool readConfig (char* confFileName, Config& conf)
{
    FILE* fConf = fopen (confFileName, "r");
    conf.sInFilename   = (char*) malloc (sizeof(char)*200);
    conf.sOutFilename  = (char*) malloc (sizeof(char)*200);
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
        printf ("Warring: File for output (%s) already exists. It will be overwritten.\n",conf.sOutFilename);
    }
    fclose (test);
    if (!strcmp(conf.sInFilename,conf.sOutFilename))
    {
        printf ("Warring: Source('%s')  and destination('%s') are matching. All data in source file will be lost. Do you whant to continue? [Y/N]\n>",conf.sInFilename,conf.sOutFilename);
        char choise;
        scanf("%c",&choise);
        if (choise!='Y'|| choise !='y') isOk=false;
    }
    return isOk;
}
