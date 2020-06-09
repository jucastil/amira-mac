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

/// @addtogroup hxarith hxarith
/// @{
#ifndef HX_MERGE
#define HX_MERGE

#include "HxArithWinDLLApi.h"

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortColorList.h>

#include <Inventor/SbLinear.h>
#include <mclib/McVec3f.h>
#include <mclib/McSmallArray.h>

class HxField3;
class HxUniformCoord3;

class HXARITH_API HxMerge : public HxCompModule {

  HX_HEADER(HxMerge);

  protected:
    enum { NINP=10 };


  public:
    /// Constructor.
    HxMerge();

    /// Update method initializes channel menus properly.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Connections to input objects.
    HxConnection* inputs[NINP];

    /** Interpol types: 0=NN 1=triangle 2=Lanczos */
    HxPortMultiMenu portInterpol;

    /// Defines number of channels of output object (1,2,3,6).
    HxPortToggleList portOptions;

        /// Padding Value
    HxPortFloatTextN portPadding;

        /// Color editor button.
    HxPortColorList portColorAction;

    /// Do it button.
    HxPortDoIt portAction;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    /// Destructor.
    ~HxMerge();

    void createResultLattice ();
    void sample ();
    // tolerance measures overall deviation in pixels
    bool isLatticeAligned (HxField3* f1, HxField3* f2, float tolerance = 0.01);

    static McVec3f snapToCoord(const McVec3f &voxSize, float* orig, const McVec3f& in, int dir);

    /** Returns the calculated label value for one position.
     *  The return value is the most occurring label value.
     *  If two or more label values haves the same occurence, the one
     *  with largest distance to an image border is used. This method is only
     *  used for inputs with type of @c HxLabelField. */
    int getValueForLabelField();

    /** Returns the minimum of two float values. */
    float minf(const float &f1, const float &f2) const{
        return f1 < f2 ? f1 : f2;
    }

    float tolerance;
    int verbose;

    /** Array tupel of picture labels and pixel dinstances from border.
     *  Used for the determination of picture values when merging @c HxLabelField3.
     */
        struct ArrayEntry{
        ArrayEntry(int val, float dis){
            value = val;
            distance = dis;
        }
        ArrayEntry(){};
          // Compare function for sort a valueArray. First compare constraint
          // is the pixel label. If two labels equal, second constraint
          // considered the pixel distance from border.
          static int compare(const ArrayEntry& e1, const ArrayEntry& e2){
            if(e1.value > e2.value)
                return 1;
            else if(e1.value < e2.value)
                return -1;
            else if(e1.distance > e2.distance)
                return 1;
            else if(e1.distance < e2.distance)
                return -1;
            else return 0;
        }
        // Label value for a pixel.
        int value;
        // Minimum pixel distance to an image border.
        float distance;
    };

    /** Array of @c ArrayEntry. Used to calculate label values
     *  from information of different images at one position. */
    McSmallArray<ArrayEntry,NINP> valueArray;
};

#endif

/// @}
