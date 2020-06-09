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

/// @addtogroup hxwarp hxwarp
/// @{
#ifndef MY_ANALYSER
#define MY_ANALYSER

#include <hxwarp/HxWarpWinDLLApi.h>
#include <mclib/McVec3f.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortDoIt.h>
#include <hxlandmark/HxLandmarkSet.h>


/// Dieses Modul berechnet die Referenzpunkte neu ..

class HXWARP_API MyRefPointComp : public HxCompModule {

  HX_HEADER(MyRefPointComp);
  
  public:

    struct t_RefPunkt {
	McVec3f     punkt;
	int         strahl;
	float       lambda;
        int         innerRegion;
        int         outerRegion;
     }; 

    /// Konstruktor.
    MyRefPointComp();

    /// Hier wird der Schwerpunkt angezeigt.
    HxPortInfo portInfo;

    /** Do it button. */
    HxPortDoIt portAction;

    ///
    HxConnection portSurface2;

    /// Compute Methode.
    virtual void compute();

  protected:
    ~MyRefPointComp(); 			// Der Destruktor wird nur von unref() aufgerufen.

    SbVec3f 	center; 		// Hier merken wir uns den Schwerpunkt.
    t_RefPunkt 	*rp_set1, *rp_set2;
    int 	rp_anz1, rp_anz2;

    void computeRefPointSet(class HxSurface* field, SbVec3f& center, t_RefPunkt **schnittpunkt, int *schnittpunkt_anz);

    //-----------------------------------------------------------------------

    short SchnittpunktGeradeEbene(McVec3f o1, McVec3f r1, McVec3f o2, McVec3f r2, McVec3f r3,
                                  float *lambda, float  *mu, float  *nu);
    short SortPoints_Dist3D(McVec3f zentralpunkt, t_RefPunkt *schnittpunkt, int min_l, int max_l);

    void rp_ausduennen(t_RefPunkt *rp, int *rp_anz, float *bbox);
    HxLandmarkSet* rp_zusammenfuegen(t_RefPunkt *rp, int rp_anz, t_RefPunkt *rp2, int rp2_anz);

    float dist2Punkte(t_RefPunkt    p1, t_RefPunkt  p2);
    //-----------------------------------------------------------------------

};

#endif

/// @}
