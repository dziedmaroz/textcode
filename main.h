#ifndef MAIN_H
#define MAIN_H
struct Config
{
    int base;
    int sLen;
    char mode;
    char* sOutFilename;
    char* sInFilename;
};

bool readConfig (char*, Config&);
bool readText (Config&, char**);
bool checkConfig (Config&);
#endif // MAIN_H
