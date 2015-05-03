#include <iostream>
using namespace std;
#include <ctype.h>

#include "ReadInteger.h"

int ReadInteger ()
  {
  char c;
  bool Digits (false);
  int  Num    (0);
  int  Sign   (0);

  while (!isspace (c = cin.get ()))
    {
    switch (c)
      {
      case '+':
      case '-':
        if ((Sign == 0) && !Digits)
            if (c == '+')
                Sign = 1;
              else  // c == '-'
                Sign = -1;
          else;
        break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        Digits = true;
        Num = (Num * 10) + (c - '0');
        break;
      default:
        c = '\a';
      }
    }
  if (Sign < 0)
      Num = -Num;
    else;
  return Num;
  }
