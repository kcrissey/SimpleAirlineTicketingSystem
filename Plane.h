#ifndef PLANE_H
#define PLANE_H

#include "Party.h"

struct Plane
  {
  long  MaxNumSeats;
  long  NumSeatsAvailable;
  long  HowManyParties;
  Party *  Who;
  };

#endif
