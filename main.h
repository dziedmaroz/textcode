#ifndef MAIN_H
#define MAIN_H

bool readConfig (char*, Config&);
bool readText (Config&, char**);
bool checkConfig (Config&);
char** readtext (char* filename, int& nLines);
void writeText (char* filename,char** text, int nLines);
#endif // MAIN_H
