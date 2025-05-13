#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>

#define INDENT_SIZE 4
#define F77_LINE_SIZE 72
#if !defined(TRUE)
	#define TRUE (1 == 1)
	#define FALSE (1 == 0)
#endif

using namespace std;

char f77LineBuffer[F77_LINE_SIZE+sizeof('\n')+sizeof('\0')];
char *f77LineBufferPtr;

ofstream OutputFile("dnssumry.f77");

extern "C" int DontStartNewLine = FALSE;

static int Indent;
extern "C" void f77NewLine(int indent) {
	if(DontStartNewLine) return;
	Indent = indent;
	memset(f77LineBuffer, ' ', F77_LINE_SIZE);
	if(Indent) {
		f77LineBufferPtr = &f77LineBuffer[6+(Indent-1)*INDENT_SIZE];
		}
	else {/*Indent of 0 used for non standard statements and comments.*/
		f77LineBufferPtr = &f77LineBuffer[0];
		}
	}

extern "C" void f77PrintLine(void) {
	f77LineBuffer[strlen(f77LineBuffer)] = ' ';
	f77LineBuffer[F77_LINE_SIZE] = '\n';
	f77LineBuffer[F77_LINE_SIZE+sizeof('\n')] = '\0';
	//OutputFile.write(f77LineBuffer, strlen(f77LineBuffer));
	cout << f77LineBuffer;
	}

extern "C" void f77PutText(const char *text) {
	int length = strlen(text);
	if(&f77LineBuffer[F77_LINE_SIZE] - f77LineBufferPtr < length) {
		/*Cannot fit I have to print this line and ....*/
		f77PrintLine();
		/*...start continuation line.*/
		f77NewLine(Indent);
		f77LineBuffer[5] = '-';	/*This is a continuation line*/
		}
	if(length > F77_LINE_SIZE) {
		strncpy(f77LineBufferPtr, text, F77_LINE_SIZE - 6);
		f77LineBufferPtr = &f77LineBuffer[F77_LINE_SIZE];
		f77PutText(text+F77_LINE_SIZE - 6);
		}
	else {
		sprintf(f77LineBufferPtr, "%s", text);
		f77LineBufferPtr += length;
		}
	}

extern "C" void f77PutLabel(const char *text) {
	sprintf(f77LineBuffer, "%5s", text);
	/*Restore the space destroyed by the sprintf's '\0\ terminator.*/
	f77LineBuffer[strlen(f77LineBuffer)] = ' ';
	}
