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
#ifndef CHAMFERTRIANGLESTRUCT_H
#define CHAMFERTRIANGLESTRUCT_H

#ifdef _YAV_
namespace yav {
#endif

  typedef struct {
    int x;
    int y;
    int z;
    int w; // wheight of the point
  } chamferTriElmt;

  typedef struct {
    int A; // index of the 1rst point in myElmts
    int B; // index of the 2nd  point in myElmts
    int C; // index of the 3rd  point in myElmts

    int Abc; // index of the symetric of A (/BC) (may be > nbPts)
    int Bac; // index of the symetric of B (/AC) (may be > nbPts)
    int Cab; // index of the symetric of C (/AB) (may be > nbPts)

    int whichPlan; 
    // = 0 -> projection on the plan x = 1
    // = 1 ->                        y = 1
    // = 2 ->                        z = 1

    /* For the error calculation, we use a projection of the triangle
       on a plan x = cst or y = cste or z = cste
    */
    float xA1;
    float xB1;
    float xC1;
    float yA1;
    float zA1;
    float yB1;
    float zB1;
    float yC1;
    float zC1;

    // For quick error calculation
    int denoAB;
    float PAB;
    float QAB;

    int denoBC;
    float PBC;
    float QBC;

    int denoAC;
    float PAC;
    float QAC;


    /* alpha = wA*(yB*zC - yC*zB) + wB*(yC*zA - yA*zC) + wC*(yA*zB - yB*zA);
       beta  = wA*(xC*zB - xB*zC) + wB*(xA*zC - xC*zA) + wC*(xB*zA - xA*zB);
       gamma = wA*(xB*yC - xC*yB) + wB*(xC*yA - xA*yC) + wC*(xA*yB - xB*yA);
       => nC[0][0] = yB*zC - yC*zB, nC[0][1] = yC*zA - yA*zC, nC[0][2] = yA*zB - yB*zA
       => nC[1][0] = xC*zB - xB*zC, nC[1][1] = xA*zC - xC*zA, nC[1][2] = xB*zA - xA*zB
       => nC[2][0] = xB*yC - xC*yB, nC[2][1] = xC*yA - xA*yC, nC[2][2] = xA*yB - xB*yA 
    */
    int nC[3][3];

  } chamferTriangle;


  /* a Local Convexity Criterion has the form :
     wX/yz - D1 wA - D2 wB - D3 wC >= 0
  */
  typedef struct {
    int w0; // index of the point which wheight will be wX/yz
    int w1; // index of the point which wheight will be wA
    int w2; // index of the point which wheight will be wB
    int w3; // index of the point which wheight will be wC

    int D1; // first  coefficient (pre-calculated)
    int D2; // second coefficient (pre-calculated)
    int D3; // third  coefficient (pre-calculated)

    unsigned char flag;
    // flag = 0 -> condition = false
    // flag = 1 -> condition = true
    // flag = 2 -> condition not tested
  }LCCElmt;



  typedef struct {
    float tauMin;
    float tauMax;
    float tau;

    float tauOpt;
    float epsOpt;
  }RelErrorElmt;



#ifdef _YAV_
} //namespace yav
#endif

#endif // CHAMFERTRIANGLESTRUCT_H

/// @}
