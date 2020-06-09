/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup molchem molchem
/// @{
#ifndef MOLCHEM_CONSTANTS_H
#define MOLCHEM_CONSTANTS_H

#include <mclib/McMath.h>

// --------------------------------------------------------
//              math constants 

#define MC_E 2.7182818284590452353602874713527 // e

// --------------------------------------------------------
//              physical constants (all in SI units)

#define MC_N_A 6.02214E23               // N_A - avogardo constant - unitless
#define MC_k 1.3806505E-23              // k - boltzmann constan - joule/kelvin
#define MC_R 8.314472                   // R - Universal gas constant - joule/kelvin*mol
#define MC_epsilon_0 8.85419E-12        // epsilon_0 - dielectric permitivity of vacuum - unitless
#define MC_e   1.602177E-19             // e - electron charge - cb
#define MC_e_2 2.566971E-38             // e^2 - electron charge square - cb^2

// --------------------------------------------------------
//                  unit conversion factors

// math
#define MC_Grad2Rad (M_PI/180.)
#define MC_Rad2Grad (180./M_PI)
#define toRadians(deg) (((float)deg)*MC_Grad2Rad)

// energy stuff

#define MC_Joule2Cal 0.239 
#define MC_Cal2Joule 4.184
#define MC_EV2Joule  (MC_e) 
#define MC_Joule2EV (1. / MC_e )


// Lengths

#define MC_Angstroem2Meter   1E-10
#define MC_Meter2Angstroem   1E10

// atomic mass units (u or dalton) to kg)
#define MC_amu2kg 1.66053886E-27
#define MC_kg2amu 0.602214151E27
//

#define MC_Kilo2Standard 1000.;
#define MC_Standard2Kilo .001;

// 

#define MC_PerMolecule2PerMol (MC_N_A)
#define MC_PerMol2PerMolecule (1./MC_PerMolecule2PerMol)

// SI <--> Gauss System

#define MC_Charge_Gauss2SI  (MC_e)
#define MC_Force_Gauss2SI   2.307078E-8
#define MC_Energy_Gauss2SI   2.307078E-18 

#define MC_Charge_SI2Gauss  ( 1. / MC_Charge_Gauss2SI )
#define MC_Force_SI2Gauss   ( 1. / MC_Force_Gauss2SI )
#define MC_Energy_SI2Gauss  ( 1. / MC_Energy_Gauss2SI )

#endif

/// @}
