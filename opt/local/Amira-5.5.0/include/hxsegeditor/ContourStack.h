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
#ifndef CONTOURSTACK_H
#define CONTOURSTACK_H

#include <Contour2D.h>
#include "GiX.h"
#include "LoopParametrization.h"
#include <hxfield/HxUniformVectorField3.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxlines/HxLineSet.h>
#include "Snakes3D.h"
//---------------------------------------------------------------

class ContourStack {
    
public:

    class OneContour{
    public:
	OneContour(int k, int s) {length = k; slice = s;}
	int length;
	McDArray <McVec2f> originalData;
	McDArray <McVec2f> data;
	int slice;
	McDArray <int> upperIdx;
	McDArray <int> lowerIdx;
	McVec2f center;
	int clockwise;
	McDArray <McVec2f> forces;
    };

    /// Constructor.
    ContourStack(GiX*  gi);
    
    /// Destructor.
    ~ContourStack();

    /// Initializes dims, origin and scale from result's bounding box.
    void initDimsOriginAndScale(HxUniformLabelField3* result);

    void init();

    int getNumContours();

    /// append contour to allContours
    void addContour(McDArray <McVec2f> p, int slice);
    void relax3D();
    const McDArray <McVec2f>* getData(int whichContour);
    void empty();
    
    /// delete lastContour
    void removeLast();

    /// slice of last contour
    int showLastSlice();
    

protected:
    
    McDArray <OneContour*> allContours;
    //int numContours;
    void deform();
    void getForces(int i);
    McVec2f deriv2(int i, int k);
    McVec2f deriv4(int i, int k);
    McVec2f deriv2Z(int i, int k);
    McVec2f deriv4Z(int i, int k);
    McVec2f distForce(int i, int k);
    void update(int i);
    int stopMoving(const McDArray<McVec2f> &old, int i);
    void equalize(int i);


    /// set arrays upperIdx and lowerIdx for all contours,
    /// is called once
    void calculateAllCorrespondingIndices();

    /// set arrays upperIdx and lowerIdx for contour i,
    /// is called once for each contour
    void calculateCorrespondingIndices(int i);

    /// calculate center of contour with data array p
    McVec2f getCenterOfGravity(McDArray<McVec2f>& p);
    
    /// calculate corresponding upper index for contour i with
    /// given normal at point r
    int calculateUpper(McVec2f &normal, McVec2f &r, 
		       McVec2f &transUp, int i);

    /// calculate corresponding lower index for contour i with
    /// given normal at point r
    int calculateLower(McVec2f &normal, McVec2f &r, 
		       McVec2f &transLo, int i);

    /// choose candidate for corresponding index out of array points
    /// corresponding upper index if up=1, lower index if up=0
    void chooseCandidate(McVec2f &normal, McVec2f &r,
			 int &candidate, McDArray<int>& points, 
			 int i, int up);

    /// calculate area and orientation of polynom p
    float getArea(const McDArray<McVec2f>& p);



    ///display initial, resulting  or corresponding contour
    void createLineSet(const McDArray <McVec2f>& vertices,int initial,
		       int slice);

    ///display corresponding contour points
    void createAnotherLineSet(int i);

    

    /*  
    ///check whether more than 95% of contour points do not move anymore
    ///in that case stop iteration
    int stopMoving(McDArray<McVec2f> &qOld, 
		   const McDArray<McVec2f> &q);
    */

    int dims[3];
    McVec3f origin;
    McVec3f scale;
  

};

#endif

/// @}
