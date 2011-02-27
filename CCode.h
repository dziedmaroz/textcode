#pragma once

class CCode
{
	char** opentext_;
	char** cryptedtext_;
	int cdBase_;
	int maxLen_;
	int chLen_;
	int cLines_;
	int getChLen (int);
	char* convertCh (char);
	void writeCh (char, char*, int);
	void freeMyText (char**);
	char* revCodedCh (char*);
	void copyText (char**, char** &, int);
public:
	CCode(void);
	CCode (char**, int, int);
	void setOpenText (char**, int, int);
	void getCryptedText (char**& ,int&);
    void codeText (void);	
	~CCode(void);
};
