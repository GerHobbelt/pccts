/******************************************************************************/
/*                                                                            */
/* COPYRIGHT:                                                                 */
/* ----------                                                                 */
/* Copyright (C) International Business Machines Corp., 1991,1992.            */
/*                                                                            */
/* DISCLAIMER OF WARRANTIES:                                                  */
/* -------------------------                                                  */
/* The following [enclosed] code is sample code created by IBM                */
/* Corporation.  This sample code is not part of any standard IBM product     */
/* and is provided to you solely for the purpose of assisting you in the      */
/* development of your applications.  The code is provided "AS IS",           */
/* without warranty of any kind.  IBM shall not be liable for any damages     */
/* arising out of your use of the sample code, even if they have been         */
/* advised of the possibility of such damages.                                */
/*                                                                            */
/******************************************************************************/
/*-------------------------------------------------------------*\
|  xsrtset.h  -  Class Planet for use in our Sorted Set example |
\*-------------------------------------------------------------*/

class Planet   {
 private:
   char* plname;
   float dist;
   float mass;
   float bright;

 public:
     // Let's use the compiler generated default for
     // the copy constructor

   Planet(char* aname, float adist, float amass, float abright) :
     plname(aname), dist(adist),  mass(amass), bright(abright) {}

     // For any Set we need to provide element equality.
   Boolean operator== (Planet const& aPlanet) const
      { return plname == aPlanet.plname; }

     // For a Sorted Set we need to provide element comparision.
   Boolean operator< (Planet const& aPlanet) const
      { return dist < aPlanet.dist; }

   char*   name()     { return  plname; }

   Boolean isHeavy()  { return (mass   > 1.0); }
   Boolean isBright() { return (bright < 0.0); }
};


/*-------------------------------------------------------------*\
|   Iterator                                                    |
\*-------------------------------------------------------------*/
#include <iostream.h>

class SayPlanetName : public IIterator<Planet>   {
 public:
   virtual Boolean applyTo(Planet& p)
         { cout << " " << p.name() << " "; return True;}
};

