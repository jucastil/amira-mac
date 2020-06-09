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
#ifndef MC_BLOW_REGION_EXT
#define MC_BLOW_REGION_EXT

#include <ctype.h>
#include <mclib/McVec2f.h>
#include <mclib/McVec2i.h>
#include <mclib/McDArray.h>
#include <mclib/McDMat.h>
#include "McBlowRegion.h"

#ifdef _WIN32
    #include <crtdbg.h>
#endif

class McBlowRegionExt: public McBlowRegion{
public:

    /// constructor
    McBlowRegionExt(int w, int h,unsigned char* input,
                 int shrink, int gaussWidth, int edgeType=2 );

    /// destructor
    ~McBlowRegionExt();

    /// initialize with circle with center at (x,y)
    //void init(int x, int y);
    /// initialize with existing contour
    //void init(McDArray <McVec2f>* contour);

    /// returns existing or newly computed contour at given time step
    //McDArray <McVec2f>* getTimeStep(int timeStep);

    /// minimal speed in order to perform a move
    //int leastSpeed;

    /// contour will grow and also shrink if set to 1, default is 0
    //static int growAndShrink;

    //static  int interpolateSpeed;
    //static int showSpeedpicture;

protected:

    /// computes the speed at each pixel
    void speedFunction();

    /// lets contour grow desired number of steps
    //void growSteps(int steps);

    /// lets contour grow or shrink one step pointwise normally
    /// to the contour
    //void grow();

    /// computes curvature at ith contour point
    //float curvature(int i, McDArray<McVec2f>& whichContour);

    /// compute normal at ith contour point
    //void findNormal(McVec2f &direction, McVec2f &next, McVec2f &prev,
//                  int i,McDArray<McVec2f>& contour);

    /// returns length of move at ith contour point
    float getMove(int i, McVec2f normal, float kappa,
                  McDArray <McVec2f>& contour);

    /// computes the gradient of the speed at each pixel
    void getGradientOfSpeed();
    /// computes the gradient of the speed at pixel (i,j)
    // McVec2f getGradientOfSpeed(int i, int j);

    /// interpolate speed at contour point c out of speed-array
    float getSpeed(McVec2f c, int dir, double weight);

    /// computes the absolute value of the gradient of given input
    void computeGradient(unsigned char*  input);

    /// insert contour points if distances between existing points
    /// are too large
    //void insertPoints(McDArray<McVec2f>& contour);

    /// delete contour points if distances between existing points
    /// are too small
    //void deletePoints(McDArray<McVec2f>& contour);

    /// deletes intersections by simply removing the smaller circles
    //void deleteIntersections();

    /// check for intersection of two contour segments given
    /// by start and end points
    //inline int intersectionTest(McVec2f a,McVec2f b,
//                       McVec2f aj,McVec2f bj,
//                       McVec2f &intersection);

    /// deletes the smaller circle at an intersection
    //void deleteCircle(int i, int j, McVec2f intersection,
//                    int &numDeletedPoints);

    /// image data
    //unsigned char*  input;

    /// dimensions of input data
    //int width, height;

    /// width of gaussian smooth filter
    //int gaussWidth;

    /// last so far computed time step
    //int lastTimeStep;

    /// Snap to all, b->w, or w->b edges
    int edgeType;

    /// holds all up to last time step computed contours
    //McDArray < McDArray<McVec2f>* > allContours;

    McDMat  speed;
    McDMat  gradient;
    McDMatrix <McVec2f> gradientOfSpeed;

    //int isConsistent (McDArray<McVec2f>& contour);
    //int isConsistent2 ();
    void normal2direction( McVec2f normal, int& dir, double& weight );
    McDArray < McDArray<McVec2f>* > debContours;
};

#endif

/// @}
