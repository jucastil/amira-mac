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

/// @addtogroup hxskeleton hxskeleton
/// @{
#ifndef PREDEFINEDMASKS_H
#define PREDEFINEDMASKS_H

#include <stdlib.h>

/* This file contains pre-defined coefficients for masks of different sizes and dimensions.
   To cope with the notion of shape-based interpolation ('Shape-based Interpolation' G.T.HERMAN & al.),
   coefficients for initialization masks are given (initialization coefficients are smaller than the other ones)
*/

// coefficients for 2D 3x3 chamfer mask. 
static unsigned char ** chamfer2D3x3;
// coefficients for 2D 3x3 initialization chamfer mask, corresponding to the previous one. 
static unsigned char ** chamfer2D3x3Init;
static float epsilon2D3x3;
static float maxRelErr2D3x3;

// coefficients for 2D 5x5 chamfer mask. 
static unsigned char ** chamfer2D5x5;
// coefficients for 2D 5x5 initialization chamfer mask, corresponding to the previous one.
static unsigned char ** chamfer2D5x5Init;
static float epsilon2D5x5;
static float maxRelErr2D5x5;

// coefficients for 2D 7x7 chamfer mask. 
static unsigned char ** chamfer2D7x7;
static unsigned char ** chamfer2D7x7Init;
static float epsilon2D7x7;
static float maxRelErr2D7x7;


// coefficients for 3D 3x3x3 chamfer mask. 
static unsigned char *** chamfer3D3x3x3;
// coefficients for 3D 3x3x3 initialization chamfer mask, corresponding to the previous one.
static unsigned char *** chamfer3D3x3x3Init;
static float epsilon3D3x3x3;
static float maxRelErr3D3x3x3;

// coefficients for 3D 5x5x5 chamfer mask. 
static unsigned char *** chamfer3D5x5x5;
// coefficients for 3D 5x5x5 initialization chamfer mask, corresponding to the previous one.
static unsigned char *** chamfer3D5x5x5Init;
static float epsilon3D5x5x5;
static float maxRelErr3D5x5x5;

// coefficients for 3D 7x7x7 chamfer mask. 
static unsigned char *** chamfer3D7x7x7;
// coefficients for 3D 7x7x7 initialization chamfer mask, corresponding to the previous one.
static unsigned char *** chamfer3D7x7x7Init;
static float epsilon3D7x7x7;
static float maxRelErr3D7x7x7;

// allocation and initialization of the pre-defined masks
static void initPredefinedMasks()
{
  int i, j;

  /* chamfer2D3x3 */
  chamfer2D3x3 = (unsigned char **) malloc(2 * sizeof (unsigned char *));
  for (i = 0; i < 2; i++)
    chamfer2D3x3[i] = (unsigned char *) malloc(2 * sizeof (unsigned char));
  
  chamfer2D3x3Init = (unsigned char **) malloc(2 * sizeof (unsigned char *));
  for (i = 0; i < 2; i++)
    chamfer2D3x3Init[i] = (unsigned char *) malloc(2 * sizeof (unsigned char));

  
  /* chamfer2D5x5 */
  chamfer2D5x5 = (unsigned char **) malloc(3 * sizeof (unsigned char *));
  for (i = 0; i < 3; i++)
    chamfer2D5x5[i] = (unsigned char *) malloc(3 * sizeof (unsigned char));

  chamfer2D5x5Init = (unsigned char **) malloc(2 * sizeof (unsigned char *));
  for (i = 0; i < 2; i++)
    chamfer2D5x5Init[i] = (unsigned char *) malloc(2 * sizeof (unsigned char));


  /* chamfer2D7x7 */
  chamfer2D7x7 = (unsigned char **) malloc(4 * sizeof (unsigned char *));
  for (i = 0; i < 4; i++)
    chamfer2D7x7[i] = (unsigned char *) malloc(4 * sizeof (unsigned char));

  chamfer2D7x7Init = (unsigned char **) malloc(2 * sizeof (unsigned char *));
  for (i = 0; i < 2; i++)
    chamfer2D7x7Init[i] = (unsigned char *) malloc(2 * sizeof (unsigned char));
   

  /* chamfer3D3x3x3 */
  chamfer3D3x3x3 = (unsigned char ***) malloc(2 * sizeof (unsigned char **));
  for (i = 0; i < 2; i++)
    {
      chamfer3D3x3x3[i] = (unsigned char **) malloc(2 * sizeof(unsigned char *));
      for (j = 0; j < 2; j++)
	chamfer3D3x3x3[i][j] = (unsigned char *) malloc(2 * sizeof (unsigned char));
    }

  chamfer3D3x3x3Init = (unsigned char ***) malloc(2 * sizeof (unsigned char **));
  for (i = 0; i < 2; i++)
    {
      chamfer3D3x3x3Init[i] = (unsigned char **) malloc(2 * sizeof(unsigned char *));
      for (j = 0; j < 2; j++)
	chamfer3D3x3x3Init[i][j] = (unsigned char *) malloc(2 * sizeof (unsigned char));
    }
  

  /* chamfer3D5x5x5 */
  chamfer3D5x5x5 = (unsigned char ***) malloc(3 * sizeof (unsigned char **));
  for (i = 0; i < 3; i++)
    {
      chamfer3D5x5x5[i] = (unsigned char **) malloc (3 * sizeof (unsigned char *));
      for (j = 0; j < 3; j++)
	chamfer3D5x5x5[i][j] = (unsigned char *) malloc (3 * sizeof (unsigned char));
    }

  chamfer3D5x5x5Init = (unsigned char ***) malloc(2 * sizeof (unsigned char **));
  for (i = 0; i < 2; i++)
    {
      chamfer3D5x5x5Init[i] = (unsigned char **) malloc (2 * sizeof (unsigned char *));
      for (j = 0; j < 2; j++)
	chamfer3D5x5x5Init[i][j] = (unsigned char *) malloc (2 * sizeof (unsigned char));
    }


  /* chamfer3D7x7x7  */
  chamfer3D7x7x7 = (unsigned char ***) malloc(4 * sizeof (unsigned char **));
  for (i = 0; i < 4; i++)
    {
      chamfer3D7x7x7[i] = (unsigned char **) malloc (4 * sizeof (unsigned char *));
      for (j = 0; j < 4; j++)
	chamfer3D7x7x7[i][j] = (unsigned char *) malloc (4 * sizeof (unsigned char));
    }

  chamfer3D7x7x7Init = (unsigned char ***) malloc(2 * sizeof (unsigned char **));
  for (i = 0; i < 2; i++)
    {
      chamfer3D7x7x7Init[i] = (unsigned char **) malloc (2 * sizeof (unsigned char *));
      for (j = 0; j < 2; j++)
	chamfer3D7x7x7Init[i][j] = (unsigned char *) malloc (2 * sizeof (unsigned char));
    }




  /* Mask 2D 3x3 */  
  epsilon2D3x3 = 6.14512f;
  maxRelErr2D3x3 = 0.079446f;
  chamfer2D3x3[0][0] = 0;               // (does not exist) 
  chamfer2D3x3[1][0] = 6;               // = 3 * 2
  chamfer2D3x3[0][1] = 6;               // = 3 * 2
  chamfer2D3x3[1][1] = 8;               // = 4 * 2
  // 2D 3x3 corresponding initialization mask
  chamfer2D3x3Init[0][0] = 0;           // (does not exist)
  chamfer2D3x3Init[1][0] = 3;           // chamfer2D3x3[1][0] * 1/2
  chamfer2D3x3Init[0][1] = 3;           // chamfer2D3x3[0][1] * 1/2
  chamfer2D3x3Init[1][1] = 4;           // chamfer2D3x3[1][1] * 1/2


  /* Mask 2D 5x5 */
  epsilon2D5x5 = 60.386264f;
  maxRelErr2D5x5 = 0.039993f;
  chamfer2D5x5[0][0] = 0;               // (does not exist)
  chamfer2D5x5[1][0] = 58;              // = 29 * 2
  chamfer2D5x5[2][0] = 0;               // (does not exist)
  chamfer2D5x5[0][1] = 58;              // = 29 * 2
  chamfer2D5x5[1][1] = 82;              // = 41 * 2
  chamfer2D5x5[2][1] = 140;             // = 70 * 2
  chamfer2D5x5[0][2] = 0;               // (does not exist)
  chamfer2D5x5[1][2] = 140;             // = 70 * 2
  chamfer2D5x5[2][2] = 0;               // (does not exist)
  // 2D 5x5 corresponding initialization mask
  chamfer2D5x5Init[0][0] = 0;           // (does not exist)
  chamfer2D5x5Init[1][0] = 29;          // chamfer2D5x5[1][0] * 1/2  
  chamfer2D5x5Init[0][1] = 29;          // chamfer2D5x5[0][1] * 1/2
  chamfer2D5x5Init[1][1] = 41;          // chamfer2D5x5[1][1] * 1/2
  
  
  /* Mask 2D 7x7 */
  epsilon2D7x7 = 22.533548f;
  maxRelErr2D7x7 = 0.027431f;
  chamfer2D7x7[0][0] = 0;               // (does not exist)
  chamfer2D7x7[1][0] = 22;              // = 11 * 2
  chamfer2D7x7[2][0] = 0;               // (does not exist)
  chamfer2D7x7[3][0] = 0;               // (does not exist)
  
  chamfer2D7x7[0][1] = 22;              // = 11 * 2
  chamfer2D7x7[1][1] = 32;              // = 16 * 2
  chamfer2D7x7[2][1] = 50;              // = 25 * 2
  chamfer2D7x7[3][1] = 72;              // = 36 * 2
  
  chamfer2D7x7[0][2] = 0;               // (does not exist)
  chamfer2D7x7[1][2] = 50;              // = 25 * 2
  chamfer2D7x7[2][2] = 0;               // (does not exist)
  chamfer2D7x7[3][2] = 82;              // = 41 * 2
  
  chamfer2D7x7[0][3] = 0;               // (does not exist)
  chamfer2D7x7[1][3] = 72;              // = 36 * 2
  chamfer2D7x7[2][3] = 82;              // = 41 * 2
  chamfer2D7x7[3][3] = 0;               // (does not exist)
  
  // 2D 5x5 corresponding initialization mask
  chamfer2D7x7Init[0][0] = 0;
  chamfer2D7x7Init[1][0] = 11;
  chamfer2D7x7Init[0][1] = 11;
  chamfer2D7x7Init[1][1] = 16;



  /* Mask 3D 3x3x3 */
  epsilon3D3x3x3 = 8.582576f;
  maxRelErr3D3x3x3 = 0.067879f;
  chamfer3D3x3x3[0][0][0] = 0;          // (does not exist)
  chamfer3D3x3x3[1][0][0] = 8;          // = 4 * 2
  chamfer3D3x3x3[0][1][0] = 8;          // = 4 * 2
  chamfer3D3x3x3[0][0][1] = 8;          // = 4 * 2
  chamfer3D3x3x3[1][1][0] = 12;         // = 6 * 2
  chamfer3D3x3x3[1][0][1] = 12;         // = 6 * 2
  chamfer3D3x3x3[0][1][1] = 12;         // = 6 * 2
  chamfer3D3x3x3[1][1][1] = 14;         // = 7 * 2
  // 3D 3x3x3 corresponding initialization mask
  chamfer3D3x3x3Init[0][0][0] = 0;      // (does not exist)
  chamfer3D3x3x3Init[1][0][0] = 4;      // chamfer3D3x3x3[1][0][0] * 1/2
  chamfer3D3x3x3Init[0][1][0] = 4;      // chamfer3D3x3x3[0][1][0] * 1/2
  chamfer3D3x3x3Init[0][0][1] = 4;      // chamfer3D3x3x3[0][0][1] * 1/2
  chamfer3D3x3x3Init[1][1][0] = 6;      // chamfer3D3x3x3[1][1][0] * 1/2
  chamfer3D3x3x3Init[1][0][1] = 6;      // chamfer3D3x3x3[1][0][1] * 1/2
  chamfer3D3x3x3Init[0][1][1] = 6;      // chamfer3D3x3x3[0][1][1] * 1/2
  chamfer3D3x3x3Init[1][1][1] = 7;      // chamfer3D3x3x3[1][1][1] * 1/2



  /* Mask 3D 5x5x5 */
  epsilon3D5x5x5 = 60.386264f;
  maxRelErr3D5x5x5 = 0.039993f;
  chamfer3D5x5x5[0][0][0] = 0;          // (does not exist)
  chamfer3D5x5x5[1][0][0] = 58;         // = 29 * 2
  chamfer3D5x5x5[2][0][0] = 0;          // (does not exist)
  
  chamfer3D5x5x5[0][1][0] = 58;         // = 29 * 2
  chamfer3D5x5x5[1][1][0] = 82;         // = 41 * 2
  chamfer3D5x5x5[2][1][0] = 140;        // = 70 * 2
  
  chamfer3D5x5x5[0][2][0] = 0;          // (does not exist)
  chamfer3D5x5x5[1][2][0] = 140;        // = 70 * 2
  chamfer3D5x5x5[2][2][0] = 0;          // (does not exist)
  
  chamfer3D5x5x5[0][0][1] = 58;         // = 29 * 2
  chamfer3D5x5x5[1][0][1] = 82;         // = 41 * 2
  chamfer3D5x5x5[2][0][1] = 140;        // = 70 * 2
  
  chamfer3D5x5x5[0][1][1] = 82;         // = 41 * 2
  chamfer3D5x5x5[1][1][1] = 102;        // = 51 * 2
  chamfer3D5x5x5[2][1][1] = 142;        // = 71 * 2
  
  chamfer3D5x5x5[0][2][1] = 140;        // = 70 * 2
  chamfer3D5x5x5[1][2][1] = 142;        // = 71 * 2
  chamfer3D5x5x5[2][2][1] = 174;        // = 87 * 2
  
  chamfer3D5x5x5[0][0][2] = 0;          // (does not exist)
  chamfer3D5x5x5[1][0][2] = 140;        // = 70 * 2
  chamfer3D5x5x5[2][0][2] = 0;          // (does not exist)
  
  chamfer3D5x5x5[0][1][2] = 140;        // = 70 * 2
  chamfer3D5x5x5[1][1][2] = 142;        // = 71 * 2
  chamfer3D5x5x5[2][1][2] = 174;        // = 87 * 2
  
  chamfer3D5x5x5[0][2][2] = 0;          // (does not exist)
  chamfer3D5x5x5[1][2][2] = 174;        // = 87 * 2
  chamfer3D5x5x5[2][2][2] = 0;          // (does not exist)

  // 3D 3x3x3 corresponding initialization mask
  chamfer3D5x5x5Init[0][0][0] = 0;      // (does not exist)
  chamfer3D5x5x5Init[1][0][0] = 29;     // chamfer3D5x5x5[1][0][0] * 1/2
  chamfer3D5x5x5Init[0][1][0] = 29;     // chamfer3D5x5x5[0][1][0] * 1/2
  chamfer3D5x5x5Init[0][0][1] = 29;     // chamfer3D5x5x5[0][0][1] * 1/2
  chamfer3D5x5x5Init[1][1][0] = 41;     // chamfer3D5x5x5[1][1][0] * 1/2
  chamfer3D5x5x5Init[1][0][1] = 41;     // chamfer3D5x5x5[1][0][1] * 1/2
  chamfer3D5x5x5Init[0][1][1] = 41;     // chamfer3D5x5x5[0][1][1] * 1/2
  chamfer3D5x5x5Init[1][1][1] = 51;     // chamfer3D5x5x5[1][1][1] * 1/2


  /* Mask 3D 7x7x7 */
  epsilon3D7x7x7 = 22.533548f;
  maxRelErr3D7x7x7 = 0.027431f;

  chamfer3D7x7x7[0][0][0] = 0;          // (does not exist)
  chamfer3D7x7x7[1][0][0] = 22;         // = 11 * 2
  chamfer3D7x7x7[2][0][0] = 0;          // (does not exist)
  chamfer3D7x7x7[3][0][0] = 0;          // (does not exist)

  chamfer3D7x7x7[0][1][0] = 22;         // = 11 * 2
  chamfer3D7x7x7[1][1][0] = 32;         // = 16 * 2
  chamfer3D7x7x7[2][1][0] = 50;         // = 25 * 2
  chamfer3D7x7x7[3][1][0] = 72;         // = 36 * 2
  
  chamfer3D7x7x7[0][2][0] = 0;          // (does not exist)
  chamfer3D7x7x7[1][2][0] = 50;         // = 25 * 2
  chamfer3D7x7x7[2][2][0] = 0;          // (does not exist)
  chamfer3D7x7x7[3][2][0] = 82;         // = 41 * 2

  chamfer3D7x7x7[0][3][0] = 0;          // (does not exist)
  chamfer3D7x7x7[1][3][0] = 72;         // = 36 * 2
  chamfer3D7x7x7[2][3][0] = 82;         // = 41 * 2        
  chamfer3D7x7x7[3][3][0] = 0;          // (does not exist)

  chamfer3D7x7x7[0][0][1] = 22;         // = 11 * 2        
  chamfer3D7x7x7[1][0][1] = 32;         // = 16 * 2
  chamfer3D7x7x7[2][0][1] = 50;         // = 25 * 2        
  chamfer3D7x7x7[3][0][1] = 72;         // = 36 * 2        

  chamfer3D7x7x7[0][1][1] = 32;         // = 16 * 2
  chamfer3D7x7x7[1][1][1] = 40;         // = 20 * 2
  chamfer3D7x7x7[2][1][1] = 54;         // = 27 * 2
  chamfer3D7x7x7[3][1][1] = 76;         // = 38 * 2
  
  chamfer3D7x7x7[0][2][1] = 50;         // = 25 * 2        
  chamfer3D7x7x7[1][2][1] = 54;         // = 27 * 2
  chamfer3D7x7x7[2][2][1] = 68;         // = 34 * 2        
  chamfer3D7x7x7[3][2][1] = 82;         // = 41 * 2

  chamfer3D7x7x7[0][3][1] = 72;         // = 36 * 2        
  chamfer3D7x7x7[1][3][1] = 76;         // = 38 * 2
  chamfer3D7x7x7[2][3][1] = 82;         // = 41 * 2        
  chamfer3D7x7x7[3][3][1] = 96;         // = 48 * 2

  chamfer3D7x7x7[0][0][2] = 0;          // (does not exist)
  chamfer3D7x7x7[1][0][2] = 50;         // = 25 * 2
  chamfer3D7x7x7[2][0][2] = 0;          // (does not exist)
  chamfer3D7x7x7[3][0][2] = 82;         // = 41 * 2        

  chamfer3D7x7x7[0][1][2] = 50;         // = 25 * 2
  chamfer3D7x7x7[1][1][2] = 54;         // = 27 * 2
  chamfer3D7x7x7[2][1][2] = 68;         // = 34 * 2
  chamfer3D7x7x7[3][1][2] = 82;         // = 41 * 2
  
  chamfer3D7x7x7[0][2][2] = 0;          // (does not exist)
  chamfer3D7x7x7[1][2][2] = 68;         // = 34 * 2
  chamfer3D7x7x7[2][2][2] = 0;          // (does not exist)
  chamfer3D7x7x7[3][2][2] = 94;         // = 47 * 2

  chamfer3D7x7x7[0][3][2] = 82;         // = 41 * 2        
  chamfer3D7x7x7[1][3][2] = 82;         // = 41 * 2
  chamfer3D7x7x7[2][3][2] = 94;         // = 47 * 2        
  chamfer3D7x7x7[3][3][2] = 108;        // = 54 * 2

  chamfer3D7x7x7[0][0][3] = 0;          // (does not exist)
  chamfer3D7x7x7[1][0][3] = 72;         // = 36 * 2
  chamfer3D7x7x7[2][0][3] = 82;         // = 41 * 2         
  chamfer3D7x7x7[3][0][3] = 0;          // (does not exist)

  chamfer3D7x7x7[0][1][3] = 72;         // = 36 * 2
  chamfer3D7x7x7[1][1][3] = 76;         // = 38 * 2
  chamfer3D7x7x7[2][1][3] = 82;         // = 41 * 2
  chamfer3D7x7x7[3][1][3] = 96;         // = 48 * 2
  
  chamfer3D7x7x7[0][2][3] = 82;         // = 41 * 2        
  chamfer3D7x7x7[1][2][3] = 82;         // = 41 * 2
  chamfer3D7x7x7[2][2][3] = 94;         // = 47 * 2        
  chamfer3D7x7x7[3][2][3] = 108;        // = 54 * 2

  chamfer3D7x7x7[0][3][3] = 0;          // (does not exist)
  chamfer3D7x7x7[1][3][3] = 96;         // = 48 * 2
  chamfer3D7x7x7[2][3][3] = 108;        // = 54 * 2        
  chamfer3D7x7x7[3][3][3] = 0;          // (does not exist)

  



  // 3D 3x3x3 corresponding initialization mask
  chamfer3D7x7x7Init[0][0][0] = 0;      // (does not exist)
  chamfer3D7x7x7Init[1][0][0] = 11;     // chamfer3D7x7x7[1][0][0] * 1/2
  chamfer3D7x7x7Init[0][1][0] = 11;     // chamfer3D7x7x7[0][1][0] * 1/2
  chamfer3D7x7x7Init[0][0][1] = 11;     // chamfer3D7x7x7[0][0][1] * 1/2
  chamfer3D7x7x7Init[1][1][0] = 16;     // chamfer3D7x7x7[1][1][0] * 1/2
  chamfer3D7x7x7Init[1][0][1] = 16;     // chamfer3D7x7x7[1][0][1] * 1/2
  chamfer3D7x7x7Init[0][1][1] = 16;     // chamfer3D7x7x7[0][1][1] * 1/2
  chamfer3D7x7x7Init[1][1][1] = 20;     // chamfer3D7x7x7[1][1][1] * 1/2
  
}


// destruction of the pre-defined masks
static void deletePredefinedMasks()
{
  int i, j;

  /* chamfer2D3x3 */
  for (i = 0; i < 2; i++)
    delete(chamfer2D3x3[i]);
  delete chamfer2D3x3;

  for (i = 0; i < 2; i++)
    delete chamfer2D3x3Init[i];
  delete chamfer2D3x3Init;

  
  /* chamfer2D5x5 */
  for (i = 0; i < 3; i++)
    delete chamfer2D5x5[i]; 
  delete chamfer2D5x5;

  for (i = 0; i < 2; i++)
    delete chamfer2D5x5Init[i];
  delete chamfer2D5x5Init;

  /* chamfer2D7x7 */
  for (i = 0; i < 4; i++)
    delete chamfer2D7x7[i];
  delete chamfer2D7x7;
    
  for (i = 0; i < 2; i++)
    delete chamfer2D7x7Init[i];
  delete chamfer2D7x7Init;

  /* chamfer3D3x3x3 */
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++)
      delete chamfer3D3x3x3[i][j];
    delete chamfer3D3x3x3[i];
  }
  delete chamfer3D3x3x3;

  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++)
      delete chamfer3D3x3x3Init[i][j];
    delete chamfer3D3x3x3Init[i];
  }
  delete chamfer3D3x3x3Init;

  /* chamfer3D5x5x5 */
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++)
      delete chamfer3D5x5x5[i][j];
    delete chamfer3D5x5x5[i];
    }
  delete chamfer3D5x5x5;

  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++)
      delete chamfer3D5x5x5Init[i][j];
    delete chamfer3D5x5x5Init[i];
  }
  delete chamfer3D5x5x5Init;

  /* chamfer3D7x7x7 */
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      delete chamfer3D7x7x7[i][j];
    delete chamfer3D7x7x7[i];
    }
  delete chamfer3D7x7x7;

  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++)
      delete chamfer3D7x7x7Init[i][j];
    delete chamfer3D7x7x7Init[i];
  }
  delete chamfer3D7x7x7Init;

}




#endif // PREDEFINEDMASKS_H

/// @}
