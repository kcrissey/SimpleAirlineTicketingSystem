#include <iostream>
using namespace std;

#include <string.h>

#include "Party.h"
#include "Plane.h"
#include "ReadChars.h"
#include "ReadInteger.h"

enum Commands {ALFA, BRAVO, LOUNGE, ARRIVE, FLY, SHUTDOWN, INVALID, LIST, HELP};
char * CmdNames [] = {"ALFA <size>", "BRAVO <size>", "LOUNGE <size>", "ARRIVE <airplane> <party> <size>", "FLY <airplane>", "SHUTDOWN", "LIST - list guests", "HELP - prints this list"};
char * PlaneNames [] = {"Alfa", "Bravo"};
const int NumCommands (8);

void Fly (Planes ChosenPlane);
Commands  GetCommand ();
Planes    GetPlane ();
Planes    FlyPlane;
Plane     PlaneAlfa;
Plane     PlaneBravo;
Plane     PlaneLounge;

int main ()
  {

  long   Number;
  bool   AlfaInitialized  (false);
  bool   BravoInitialized (false);
  bool   LoungeInitialized (false);
  bool   Shutdown (false);
  Party  TempParty;
      
  cout << endl << "Welcome to Tree Top Airways Ticketing System" << endl << endl;
    
  do {
      
  cout << "Enter Command (ie. HELP): ";
  switch (GetCommand ())
    {
    case ALFA:
          if (AlfaInitialized) {
            cout << "Alfa already initialized." << endl;
            break;
          }
          Number = ReadInteger ();
          cout << "Initializing Alfa with a size of " << Number << endl;
          PlaneAlfa.MaxNumSeats        = Number;
          PlaneAlfa.NumSeatsAvailable  = Number;
          PlaneAlfa.Who                = new Party [Number];
          PlaneAlfa.HowManyParties     = 0;
          AlfaInitialized              = true;
          break;
    case BRAVO:
          if (BravoInitialized) {
            cout << "Bravo already initialized." << endl;
            break;
          }
          Number = ReadInteger ();
          cout << "Initializing Bravo with a size of " << Number << endl;
          PlaneBravo.MaxNumSeats        = Number;
          PlaneBravo.NumSeatsAvailable  = Number;
          PlaneBravo.Who                = new Party [Number];
          PlaneBravo.HowManyParties     = 0;
          BravoInitialized              = true;
          break;
    case LOUNGE:
          if (LoungeInitialized) {
            cout << "Lounge already initialized." << endl;
            break;
          }
          Number = ReadInteger ();
          cout << "Initializing Lounge with a size of " << Number << endl;
          PlaneLounge.MaxNumSeats        = Number;
          PlaneLounge.NumSeatsAvailable  = Number;
          PlaneLounge.Who                = new Party [Number];
          PlaneLounge.HowManyParties     = 0;
          LoungeInitialized              = true;
          break;
    case ARRIVE:
          switch (GetPlane ()) {
            case Alfa:
              if (AlfaInitialized) {
                TempParty.WhichPlane   = Alfa;
                TempParty.pName        = ReadChars ();
                do {
                  TempParty.HowMany    = ReadInteger ();
                  if (TempParty.HowMany == 0)
                    cout << endl << "Party cannot be zero. Re-enter number in party: ";
                  } while (TempParty.HowMany < 1);
                //see if party fits on the plane
                if (TempParty.HowMany <= PlaneAlfa.NumSeatsAvailable) {
                  PlaneAlfa.Who [PlaneAlfa.HowManyParties++] = TempParty;
                  PlaneAlfa.NumSeatsAvailable -= TempParty.HowMany;
                  cout << "Party " << TempParty.pName << " (" << TempParty.HowMany 
                       << ") boarded Alfa." << endl;
                  } else {
                  // if not, check if they fit on an empty plane
                  if (TempParty.HowMany <= PlaneAlfa.MaxNumSeats) {
                    if (TempParty.HowMany <= PlaneLounge.NumSeatsAvailable) {
                      PlaneLounge.Who [PlaneLounge.HowManyParties++] = TempParty;
                      PlaneLounge.NumSeatsAvailable -= TempParty.HowMany;
                      cout << "Party " << TempParty.pName << " (" << TempParty.HowMany << 
                              ") moved to the Lounge until capacity becomes available." << endl;
                      } else {
                      cout << "We are so sorry, but the " << TempParty.pName << 
                              " party does not fit in the Lounge and will have to leave." << endl;
                      }
                } else {
                  cout << "We apologize, but the " << TempParty.pName
                       << " party does not fit in our Alfa plane." << endl 
                       << "Good day to you." << endl;
                  }
              }

              if (PlaneAlfa.NumSeatsAvailable == 0) {
                do {
                  cout << "Plane Alfa departing with parties:" << endl;
                  for (int i = 0; i < PlaneAlfa.HowManyParties; i++) {
                    cout << PlaneAlfa.Who[i].pName << " (" << PlaneAlfa.Who[i].HowMany 
                         << ")" << endl;
                    }
                  PlaneAlfa.NumSeatsAvailable = PlaneAlfa.MaxNumSeats;
                  PlaneAlfa.HowManyParties = 0;
                  Fly (Alfa);
                  } while (PlaneAlfa.NumSeatsAvailable == 0);
                }
              } else {
                  cout << "Alfa not yet initialized." << endl;
                }
              break;
      
            case Bravo:
              if (BravoInitialized) {
                TempParty.WhichPlane   = Bravo;
                TempParty.pName        = ReadChars ();
                do {
                  TempParty.HowMany    = ReadInteger ();
                  if (TempParty.HowMany == 0)
                    cout << endl << "Party cannot be zero. Re-enter number in party: ";
                  } while (TempParty.HowMany < 1);
                //see if party fits on the plane
                if (TempParty.HowMany <= PlaneBravo.NumSeatsAvailable) {
                  PlaneBravo.Who [PlaneBravo.HowManyParties++] = TempParty;
                  PlaneBravo.NumSeatsAvailable -= TempParty.HowMany;
                  cout << "Party " << TempParty.pName << " (" << TempParty.HowMany 
                       << ") boarded Bravo." << endl;
                } else {
                  // if not, check if they fit on an empty plane
                  if (TempParty.HowMany <= PlaneBravo.MaxNumSeats) {
                    if (TempParty.HowMany <= PlaneLounge.NumSeatsAvailable) {
                      PlaneLounge.Who [PlaneLounge.HowManyParties++] = TempParty;
                      PlaneLounge.NumSeatsAvailable -= TempParty.HowMany;
                      cout << "Party " << TempParty.pName << " (" << TempParty.HowMany << 
                              ") moved to the Lounge until capacity becomes available." << endl;
                      } else {
                      cout << "We are so sorry, but the " << TempParty.pName << 
                              " party does not fit in the Lounge and will have to leave." << endl;
                      }
                    } else {
                      cout << "We apologize, but the " << TempParty.pName
                           << " party does not fit in our Bravo plane." << endl 
                           << "Good day to you." << endl;
                  }
                }

                if (PlaneBravo.NumSeatsAvailable == 0) {
                  do {
                    cout << "Plane Bravo departing with parties:" << endl;
                      for (int i = 0; i < PlaneBravo.HowManyParties; i++) {
                        cout << PlaneBravo.Who[i].pName << " (" << PlaneBravo.Who[i].HowMany 
                             << ")" << endl;
                    }
                  PlaneBravo.NumSeatsAvailable = PlaneBravo.MaxNumSeats;
                  PlaneBravo.HowManyParties = 0;
                  Fly (Bravo);
                  } while (PlaneBravo.NumSeatsAvailable == 0);
                  }
                } else
                  cout << "Bravo not yet initialized." << endl;
              break;

            case Invalid:
              cout << "Invalid plane designation" << endl;
              break;
            }
          break;
    case FLY:
          FlyPlane = GetPlane();
          if (FlyPlane == Alfa) {
            if (PlaneAlfa.HowManyParties > 0) {
              do {
                cout << "Plane Alfa departing with parties:" << endl;
                for (int i = 0; i < PlaneAlfa.HowManyParties; i++) {
                   cout << PlaneAlfa.Who[i].pName << " (" << PlaneAlfa.Who[i].HowMany 
                        << ")" << endl;
                }
                PlaneAlfa.NumSeatsAvailable = PlaneAlfa.MaxNumSeats;
                PlaneAlfa.HowManyParties = 0;
                Fly (Alfa);
              } while (PlaneAlfa.NumSeatsAvailable == 0);
            }
          } else {
            if (FlyPlane == Bravo) {
              if (PlaneBravo.HowManyParties > 0) {
                do {
                  cout << "Plane Bravo departing with parties:" << endl;
                  for (int i = 0; i < PlaneBravo.HowManyParties; i++) {
                     cout << PlaneBravo.Who[i].pName << " (" << PlaneBravo.Who[i].HowMany 
                          << ")" << endl;
                  }
                  PlaneBravo.NumSeatsAvailable = PlaneBravo.MaxNumSeats;
                  PlaneBravo.HowManyParties = 0;
                  Fly (Bravo);
                } while (PlaneBravo.NumSeatsAvailable == 0);
              }
            }
          }
          break;
    case SHUTDOWN:
          Shutdown = true;
          if (PlaneAlfa.HowManyParties > 0) {
            do {
              cout << "Plane Alfa departing with parties:" << endl;
              for (int i = 0; i < PlaneAlfa.HowManyParties; i++) {
                 cout << PlaneAlfa.Who[i].pName << " (" << PlaneAlfa.Who[i].HowMany << ")" << endl;
              }
              PlaneAlfa.NumSeatsAvailable = PlaneAlfa.MaxNumSeats;
              PlaneAlfa.HowManyParties = 0;
              Fly (Alfa);
            } while (PlaneAlfa.HowManyParties > 0);
          }
          if (PlaneBravo.HowManyParties > 0) {
            do {
              cout << "Plane Bravo departing with parties:" << endl;
              for (int i = 0; i < PlaneBravo.HowManyParties; i++) {
                 cout << PlaneBravo.Who[i].pName << " (" << PlaneBravo.Who[i].HowMany << ")" << endl;
              }
              PlaneBravo.NumSeatsAvailable = PlaneBravo.MaxNumSeats;
              PlaneBravo.HowManyParties = 0;
              Fly (Bravo);
            } while (PlaneBravo.HowManyParties > 0);
          }
          delete [] PlaneAlfa.Who;
          delete [] PlaneBravo.Who;
          delete [] PlaneLounge.Who;
          break;
    case INVALID:
          cout << "Bad Command" << endl;
          break;
    case LIST:
          cout << endl << "Listing waiting guests" << endl;
          cout << "Plane Alfa (" << PlaneAlfa.NumSeatsAvailable 
               << "/" << PlaneAlfa.MaxNumSeats << "):" << endl;
          if (PlaneAlfa.HowManyParties > 0) {
            for (int i = 0; i < PlaneAlfa.HowManyParties; i++)
            cout << PlaneAlfa.Who[i].pName << " (" << PlaneAlfa.Who[i].HowMany << ")" << endl;
          } else {
            cout << "Nobody currently waiting on plane Alfa." << endl;
          }
          cout << endl << "Plane Bravo (" << PlaneBravo.NumSeatsAvailable 
               << "/" << PlaneBravo.MaxNumSeats << "):" << endl;
          if (PlaneBravo.HowManyParties > 0) {
            for (int i = 0; i < PlaneBravo.HowManyParties; i++)
            cout << PlaneBravo.Who[i].pName << " (" << PlaneBravo.Who[i].HowMany << ")" << endl;
          } else {
            cout << "Nobody currently waiting on plane Bravo." << endl;
          }
          cout << endl << "Lounge (" << PlaneLounge.NumSeatsAvailable << "/" 
               << PlaneLounge.MaxNumSeats << "):" << endl;
          if (PlaneLounge.HowManyParties > 0) {
            for (int i = 0; i < PlaneLounge.HowManyParties; i++)
            cout << PlaneLounge.Who[i].pName << " (" << PlaneLounge.Who[i].HowMany << ")-"
                 << PlaneNames[PlaneLounge.Who[i].WhichPlane] << endl;
          } else {
            cout << "Nobody currently waiting in the Lounge." << endl;
          }
          break;
    case HELP:
          for (int i = 0; i < NumCommands; i++)
            cout << CmdNames [i] << endl;
          break;
    default:
          cout << "Internal Error, Contact Customer Support" << endl;
    }
  } while (!Shutdown);

  cout << endl << "Thank you for flying with Tree Top Airways!" << endl << endl;
}


Commands GetCommand ()
  {
  char *    Command;
  Commands  Cmd;

  Command = ReadChars ();
  if (strcasecmp (Command, "ALFA") == 0)
      Cmd = ALFA;
    else
      if (strcasecmp (Command, "BRAVO") == 0)
          Cmd = BRAVO;
        else
          if (strcasecmp (Command, "LOUNGE") == 0)
              Cmd = LOUNGE;
            else
              if (strcasecmp (Command, "ARRIVE") == 0)
                  Cmd = ARRIVE;
                else
                  if (strcasecmp (Command, "FLY") == 0)
                      Cmd = FLY;
                    else
                      if (strcasecmp (Command, "SHUTDOWN") == 0)
                          Cmd = SHUTDOWN;
                        else
                          if (strcasecmp (Command, "HELP") == 0)
                              Cmd = HELP;
                              else
                                if (strcasecmp (Command, "LIST") == 0)
                                  Cmd = LIST;
                              else
                                Cmd = INVALID;
  delete [] Command;
  return Cmd;
  }

Planes GetPlane () {

  char *  WhichPlane;
  Planes  MyPlane;

  WhichPlane = ReadChars ();
  if (strcasecmp (WhichPlane, "Alfa") == 0)
      MyPlane = Alfa;
    else
      if (strcasecmp (WhichPlane, "Bravo") == 0)
          MyPlane = Bravo;
        else
          MyPlane = Invalid;
  delete [] WhichPlane;
  return MyPlane;
 }


void Fly (Planes ChosenPlane) {

  cout << "Plane " << PlaneNames[ChosenPlane] 
       << " seems to simply dematerialize and rematerialize."  << endl;
  cout << "Plane " << PlaneNames[ChosenPlane] << " is now ready for boarding." << endl;
  if (PlaneLounge.HowManyParties > 0) {
    for (int i = 0; i <= PlaneLounge.HowManyParties - 1; i++) {
      if (PlaneLounge.Who[i].WhichPlane == ChosenPlane) {
        switch (ChosenPlane) {

        case Alfa:
          if (PlaneLounge.Who[i].HowMany <= PlaneAlfa.NumSeatsAvailable) {
          PlaneLounge.HowManyParties--;
          PlaneLounge.NumSeatsAvailable += PlaneLounge.Who[i].HowMany;
          PlaneAlfa.NumSeatsAvailable -= PlaneLounge.Who[i].HowMany;
          PlaneAlfa.Who[PlaneAlfa.HowManyParties] = PlaneLounge.Who[i];
          PlaneAlfa.Who[PlaneAlfa.HowManyParties].pName = PlaneLounge.Who[i].pName;
          PlaneAlfa.Who[PlaneAlfa.HowManyParties].HowMany = PlaneLounge.Who[i].HowMany;
          PlaneAlfa.Who[PlaneAlfa.HowManyParties++].WhichPlane = PlaneLounge.Who[i].WhichPlane;

          cout << PlaneLounge.Who[i].pName << " (" << PlaneLounge.Who[i].HowMany 
               << ") now boards Alfa." << endl;
          for (int x = i; x <= PlaneLounge.HowManyParties - 1; x++) {
            PlaneLounge.Who[x].pName = PlaneLounge.Who[x + 1].pName;
            PlaneLounge.Who[x].HowMany = PlaneLounge.Who[x + 1].HowMany;
            PlaneLounge.Who[x].WhichPlane = PlaneLounge.Who[x + 1].WhichPlane;
            }
          i--;
          }
          break;
    
        case Bravo:
          if (PlaneLounge.Who[i].HowMany <= PlaneBravo.NumSeatsAvailable) {
          PlaneLounge.HowManyParties--;
          PlaneLounge.NumSeatsAvailable += PlaneLounge.Who[i].HowMany;
          PlaneBravo.NumSeatsAvailable -= PlaneLounge.Who[i].HowMany;
          PlaneBravo.Who[PlaneBravo.HowManyParties] = PlaneLounge.Who[i];
          PlaneBravo.Who[PlaneBravo.HowManyParties].pName = PlaneLounge.Who[i].pName;
          PlaneBravo.Who[PlaneBravo.HowManyParties].HowMany = PlaneLounge.Who[i].HowMany;
          PlaneBravo.Who[PlaneBravo.HowManyParties++].WhichPlane = PlaneLounge.Who[i].WhichPlane;

          cout << PlaneLounge.Who[i].pName << " (" << PlaneLounge.Who[i].HowMany 
               << ") now boards Bravo." << endl;
          for (int x = i; x <= PlaneLounge.HowManyParties - 1; x++) {
            PlaneLounge.Who[x].pName = PlaneLounge.Who[x + 1].pName;
            PlaneLounge.Who[x].HowMany = PlaneLounge.Who[x + 1].HowMany;
            PlaneLounge.Who[x].WhichPlane = PlaneLounge.Who[x + 1].WhichPlane;
            }
          i--;
          }
          break;

        }
      }
    }
  }
}
