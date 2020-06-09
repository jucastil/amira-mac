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
#ifndef MC_IDF_H
#define MC_IDF_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <mclib/McData2D.h>
#include <mclib/McVec2i.h>
#include <mclib/McDArray.h>

#include "GiSelection2D.h"
#include "HxGiWinDLLApi.h"


class HXSEGEDITOR_API McIdf {
public:

    class Pixel{
    public:
        int position[2];

        Pixel() { }
        Pixel(int i,int j) {
            position[0] = i;
            position[1] = j;
        }
        Pixel& operator=(const Pixel& other){
            position[0] = other.position[0];
            position[1] = other.position[1];
            return *this;
        }

    };

    ///
    //McIdf(int w, int h, McData2D<unsigned char>* input1, McData2D<unsigned char>* input2,
    //        int extrapolate=0);
    McIdf(int w, int h, GiSelection2D* input1, GiSelection2D* input2, int extrapolate=0);

    ///
    ~McIdf();

    ///
    //void interpolate(float u, unsigned char* IDF);
    void interpolate(float u, GiSelection2D* IDF);

    //void extrapolate(McData2D<unsigned char>* EDF);
    void extrapolate(GiSelection2D* EDF);

    const McDArray <int>* getDistField1();
    const McDArray <int>* getDistField2();

protected:
    //McData2D<unsigned char>* input1, *input2;
    GiSelection2D* input1, *input2;
    //int bpp,bpl;
    int width,height;

//     short* distField1;
//     short* distField2;
    McDArray<int> distField1,distField2;
    int distwidth,distheight;

    int maxDist1,maxDist2;
    void initExtrapolate();
    //void getCenterOfGravity(unsigned char* input, int center[2], int box[4]);
    void getCenterOfGravity(GiSelection2D* input, int center[2], int box[4]);
    int center1[2],center2[2];

    /// bounding boxes
    int box1[4];
    int box2[4];

    /// translation vector of the two centers
    int trans[2];

    //void initializeDistanceField(short* distField, McDArray<Pixel>& list, const unsigned char* input);
    void initializeDistanceField(int* distField, McDArray<Pixel>& list, const GiSelection2D* input);

    /// list1 and list2 contain original contour of input1 and input2
    McDArray <Pixel> list1;
    McDArray <Pixel> list2;
    int propagateDistanceField(int* distField, McDArray<Pixel>& list);
    //void signedDistanceField(short* distField, const unsigned char* input);
    void signedDistanceField(int* distField, const GiSelection2D* input);

    //int distanceField(short* distField, McDArray <Pixel>& list, const unsigned char* input);
    int distanceField(int* distField, McDArray <Pixel>& list, const GiSelection2D* input);


    /// This specifies the origin of input1 in coordinates of distField1
    McVec2i offset1, offset2;

    inline int valueOfDistField1InCoordsOfInput1(int i, int j) {
        int k = i+offset1[0] + (j+offset1[1])*distwidth;
        assert(i<distwidth+offset1[0] && j<distheight+offset1[1] && i+offset1[0]>=0 && j+offset1[1]>=0);
        return (distField1[k]);
    }

    inline int valueOfDistField2InCoordsOfInput2(int i, int j) {
        int k = i+offset2[0] + (j+offset2[1])*distwidth;
        assert(i+offset2[0]<distwidth && j+offset2[1]<distheight &&
               i+offset2[0]>=0 && j+offset2[1]>=0);
        return (distField2[k]);
    }

};

#endif

/// @}
