#ifndef PARTY_H
#define PARTY_H

enum Planes {Alfa, Bravo, Invalid};

struct Party
  {
  char *  pName;
  long  HowMany;
  Planes  WhichPlane;
  };

#endif
