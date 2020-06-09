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
#ifndef GI_SNAKES_H
#define GI_SNAKES_H

#include <mclib/McVec3f.h>
#include "Contour2D.h"
//#include "GiX.h"
#include "LoopParametrization.h"
//#include <hxfield/HxUniformVectorField3.h>
//#include <hxfield/HxUniformScalarField3.h>
//#include <hxlines/HxLineSet.h>
//#include <mclib/McBitfield.h>
//---------------------------------------------------------------
class Gi;
class ImageForces;
class McTypedData3D;

/// Class for Snakes3D: active contour models
class GiSnakes {
    
public:
    /// Constructor.
    GiSnakes();
    
    /// Destructor.
    ~GiSnakes();
    
    void init(float* box, McTypedData3D* image,int slice,
	      float dataWinMin, float dataWinMax, int orientation);
    
    /// set current slice in 3D-volume
    void setSlice(int which);

    /// deform contour due to internal and external forces
    void deform(Contour2D& contours, int whichSnakes);

    /// Parameters for the snake (interface to GiAdjustTool) 
    int p1, p2, p3;			   
    int numSamples;
    int use3DGradient;
    
    void set3DGradient(int k);

    /// Extrapolate contour first to next using the gradient.
    /// If up is true direction is up, else down.
    void extrapolateGradient(Contour2D& first,Contour2D& next, int up);
    
    /// calculate area of polygon
    float getArea(const McDArray<McVec2f> &vertices);

    static int numParam;    
    Gi*   theGi;
    
protected:
    /// Methods  	
    
    /// Get second derivative of vertices (elasticity)
    McVec2f deriv2(const McDArray<McVec2f>& vertices, int vert);

    /// Get fourth derivative of vertices (curvature)
    McVec2f deriv4(const McDArray<McVec2f>& vertices, int vert);

    /// Get area force at contour point vert
    McVec2f areaForce(const McDArray<McVec2f>& vertices, int vert);
 
    
    /// Calculate all forces normal to the contour and normalization
    void getForces(const McDArray<McVec2f>& vertices);
    
    ///set forces' individual weights 
    void setWeights();
    
    ///check whether more than 95% of contour points do not move anymore
    ///in that case stop iteration
    int stopMoving(McDArray<McVec2f> &qOld, 
		   const McDArray<McVec2f> &q);
    
    /// Calculate length of contour.  
    float getLength(const McDArray<McVec2f> &vertices);

    /// Calculate resulting gradient force for each pixel in currentSlice.
    //void createForceField();
    
    ///Display initial, resulting  or corresponding contour.
    //void createLineSet(const McDArray <McVec2f>& vertices,int initial,
    //		       int slice);

    ///Display corresponding points for extrapolation
//void createAnotherLineSet(McDArray <McVec2f>& first, 
//		      McDArray <McVec2f>& korrespVertices,
//		      McDArray <McVec2f>& third);

    /// Image parameters
    McTypedData3D* image;    
    int currentSlice;
    int orientation;

    /// Storage for all forces
    McDArray<McVec2f> forces;          
    McDArray<McVec2f> forcesP, forcesQ;

    /// orientation of contour
    int clockwise;
    float optLength, curLength;
    float timeStep;

    LoopParametrization* loopParam;
    ImageForces* imageForces;

    /// Parameters/weights
    float wEl, wRi , wGr, wAr, autoWeight, L, L0;

    /// bounding box
    float* boundingBox;
    McVec3f origin;
    McVec3f scale;
};

#endif

/// @}
