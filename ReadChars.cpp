#include <iostream>

using namespace std;

#include <memory.h>

#include "ReadChars.h"

char * ReadChars ()
  {
  const  long  StartNumChars  (50);
  char  c;
  long  CurrNumChars  (0);
  long  CurrArraySize;
  char *  pLine;
  char *  pTempLine;

  CurrArraySize = StartNumChars;
  pLine = new char [CurrArraySize + 1];  // first guess at the size of the array
  while (isspace (c = cin.get ()));
  cin.putback (c);
  while (!isspace (c = cin.get ()))
    {
    pLine [CurrNumChars++] = c;  // put character read into array and bump up the number of chars I've read so far
    if (CurrNumChars >= CurrArraySize)  // is the array full
        {
        CurrArraySize += StartNumChars;
        pTempLine = new char [CurrArraySize + 1];
        memcpy (pTempLine, pLine, CurrNumChars);
        delete [] pLine;
        pLine = pTempLine;
        }
    }
  pLine [CurrNumChars] = '\0';
  return pLine;
  }
