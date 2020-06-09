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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef GI_EXTRAPOLATE_CONTOURS_H
#define GI_EXTRAPOLATE_CONTOURS_H

/*
#include <Contour2D.h>
#include "GiX.h"
#include "LoopParametrization.h"
#include <hxfield/HxUniformVectorField3.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxlines/HxLineSet.h>
#include "ImageForces.h"
#include <mclib/McBitfield.h>
*/

#include "Contour2D.h"

//---------------------------------------------------------------

/// Class for extrapolating two contours
class GiExtrapolateContours {
    
public:

    /// Extrapolate contours first and second to third using arc length
    /// parametrization.  If mode is nonzero frechet distance is used 
    /// for parametrization.
    static void extrapolate(Contour2D& first, 
			 Contour2D& second,
			 Contour2D& third,
			 int mode, int* dims);
protected:
    /// Methods  	

    /// Constructor.
    GiExtrapolateContours();
    
    /// Destructor.
    ~GiExtrapolateContours();


    /// Does the extrapolation
    void doExtrapolation(Contour2D& third);
    
    /// Frechet distance parametrization to calculate korresponding vertices.
    void calculateFrechetVerticesInSecond(McDArray<McVec2f>& frechetVertices);

    /// Arc length parametrization to calculate korresponding vertices.
    void calculateVerticesInSecond(McDArray<McVec2f>& korrespVertices);

    /// Calculate starting indices for arc length parametrization.
    void getStartIndices(int &idxFirst, int &idxSecond);

    /// Compute center of gravity of given contour.
    McVec2f getCenterOfGravity(McDArray<McVec2f>& p);


    /// bounding box
    /*
    float* boundingBox;
    McVec3f origin;
    McVec3f scale;
    */
    /// Contours to be extrapolated.
    Contour2D* first,*second;
    
    /// If mode is nonzero frechet distance, otherwise arc length 
    /// parametrization is used to compute corresponding points.
    int mode;
    
    int dims[3];

};

#endif

/// @}
