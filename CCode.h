#pragma once

class CCode
{
	char** opentext;
	char** cryptedtext;
	int cdBase;
	int maxLen;
	int chLen;
	int cLines;
	int getChLen (int);
	char* convertCh (char);
	void freeMyText (char**);
	char* revCodedCh (char*);
public:
	CCode(void);
	CCode (char**, int, int);

	~CCode(void);
};
