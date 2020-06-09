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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef  _VS_FILTER_H_
#define  _VS_FILTER_H_


#include "Vs.h"

#include <mclib/McResult.h>
#include "VsData.h"
#include "VsDataAccess.h"
#include "VsMemoryData.h"
#include "VsJobControl.h"

#include "McVec3l.h"

class VsJobControl;


////////////////////////////////////////////////////////////////////////////////
// Class with collection of methods to implement a special filter. It is passed in as template argument to VsFilter.
////////////////////////////////////////////////////////////////////////////////
class MinimumFilter
{
public:
    
    /// eval value in filter window
    static float filter(float t)
    { 
        return t;
    }

    /// width of window
    static float  width()
    { 
        return 0.5f; 
    }

    /// init destination value with this value
    static float init() 
    { 
        return 1e20f; 
    }

    /// update in evaluation formula
    static void eval(float in, float weight,  float &out) 
    { 
        out = (in < out) ? in : out; 
    }
};


////////////////////////////////////////////////////////////////////////////////
// Class with collection of methods to implement a special filter. It is passed in as template argument to VsFilter.
////////////////////////////////////////////////////////////////////////////////
class MaximumFilter 
{
    public:

    static float filter(float t)
    { 
        return t;
    }

    static float width() 
    { 
        return 0.5f;
    }

    static float init() 
    { 
        return -1e20f; 
    }

    static void eval(float in, float weight,  float &out) 
    {
        out = (in > out) ? in : out;
    }
};


////////////////////////////////////////////////////////////////////////////////
// Class with collection of methods to implement a special filter. It is passed in as template argument to VsFilter.
////////////////////////////////////////////////////////////////////////////////
class BoxFilter
{
public:

    static float filter(float t)
    {
        if((t >= -0.5) && (t <= 0.5)) 
            return(1);
        return(0.0);
    }

    static float init()
    { 
        return 0;
    }

    static float width()
    { 
        return 0.5; 
    }

    static void eval( float in, float weight, float &out )
    {  
        out += in * weight; 
    }
};


////////////////////////////////////////////////////////////////////////////////
// Class with collection of methods to implement a special filter. It is passed in as template argument to VsFilter.
////////////////////////////////////////////////////////////////////////////////
class TriangleFilter 
{
public:

    static float filter(float t)
    {
        if(t < 0.0f) t = -t;
        if(t < 1.0f) return(1.0f - t);
        return(0.0f);

    }

    static float  width() 
    { 
        return 1.0f; 
    }

    static float init()
    { 
        return 0; 
    }

    static void  eval( float in, float weight, float &out )
    {  
        out += in * weight; 
    }
};


////////////////////////////////////////////////////////////////////////////////
// Class with collection of methods to implement a special filter. It is passed in as template argument to VsFilter.
////////////////////////////////////////////////////////////////////////////////
class BellFilter 
{
public:

    static float width()
    { 
        return 1.5; 
    }

    static float init()
    { 
        return 0; 
    }

    static float filter(float t)        /* box (*) box (*) box */
    {
        if(t < 0) t = -t;
        if(t < .5f) return(.75f - (t * t));
        if(t < 1.5f) 
        {
            t = (t - 1.5f);
            return(.5f * (t * t));
        }
        return(0.0f);
    }

    static void  eval(float in, float weight, float &out)
    {  
        out += in * weight; 
    }
};


////////////////////////////////////////////////////////////////////////////////
// Class with collection of methods to implement a special filter. It is passed in as template argument to VsFilter.
////////////////////////////////////////////////////////////////////////////////
class BSplineFilter 
{
public:

    static float filter(float t) 
    {
        float tt;

        if(t < 0) t = -t;
        if(t < 1) 
        {
            tt = t * t;
            return((.5f * tt * t) - tt + (2.0f / 3.0f));
        } 
        else if(t < 2) 
        {
            t = 2 - t;
            return((1.0f / 6.0f) * (t * t * t));
        }
        return(0.0f);
    }

    static float  width() 
    { 
        return 2.0; 
    }

    static float init()
    { 
        return 0; 
    }

    static void  eval(float in, float weight, float &out)
    {  
        out += in * weight; 
    }
};


////////////////////////////////////////////////////////////////////////////////
// Class with collection of methods to implement a special filter. It is passed in as template argument to VsFilter.
////////////////////////////////////////////////////////////////////////////////
class LanzcosFilter 
{

public:

    static float sinc(float x)
    {
        x *= float(M_PI);
        if(x != 0) return(sin(x) / x);
        return(1.0f);
    }

    static float filter(float t)
    {
        if(t < 0) t = -t;
        if(t < 3.0f) return(sinc(t) * sinc(t/3.0f));
        return(0.0f);
    }

    static float  width()
    { 
        return 3.0f;
    }

    static void  eval(float in, float weight, float &out)
    {  
        out += in * weight; 
    }

    static float init() { return 0; }
};


////////////////////////////////////////////////////////////////////////////////
// Class with collection of methods to implement a special filter. It is passed in as template argument to VsFilter.
////////////////////////////////////////////////////////////////////////////////
class MitchellFilter
{
public:

    static float filter(float t)
    {
        const float B = (1.0f / 3.0f);
        const float C = (1.0f / 3.0f);

    float tt;

        tt = t * t;
        if(t < 0) t = -t;
        if(t < 1.0f) 
        {
            t = (((12.0f - 9.0f * B - 6.0f * C) * (t * tt))
                + ((-18.0f + 12.0f * B + 6.0f * C) * tt)
                + (6.0f - 2 * B));
            return(t / 6.0f);
        } 
        else if(t < 2.0f) 
        {
            t = (((-1.0f * B - 6.0f * C) * (t * tt))
                + ((6.0f * B + 30.0f * C) * tt)
                + ((-12.0f * B - 48.0f * C) * t)
                + (8.0f * B + 24 * C));
            return(t / 6.0f);
        }
        return(0.0f);
       
    }

    static float width()
    { 
        return (1.0f / 3.0f);
    }

    static float init()
    { 
        return 0;
    }

    static void  eval(float in, float weight, float &out)
    {  
        out += in * weight; 
    }
};




////////////////////////////////////////////////////////////////////////////////
// The main filter implementation class
////////////////////////////////////////////////////////////////////////////////
template <class FILTER = BoxFilter >
class VsFilter 
{
private:
    
    /// contains one look up table for one voxel in row
    typedef struct 
    {
        int         pixel;
        float       weight;
    } CONTRIB;

    /// contains look up table for all voxels
    typedef struct 
    {
        int         n; // number of contributors
        CONTRIB   * p; // pointer to list of contributions
    } CLIST;


    /// source data
    VsData            * mData;    
    
    /// access to source data
    const VsDataAccess* mSource;

    /// target data
    VsMemoryData      * mTarget;

    /// acess to target data
    const VsDataAccess* mDest;

    /// size of destination data - may have a fraction
    float               mFracDstSize[3];
    
    /// size of destination data - integer
    int                 mDstSize[3];

    /// size of source data
    McVec3l             mSrcSize;

    /// scale factors src / dest
    float               mScale[3];

    /// number of data channels 
    int                 mComponents;

    /// optional progress bar
    VsJobControl      * mJobControl;

    /// contains data after resampling in x direction
    float             * mSliceX;

    /// storage for one resampled row in x direction
    float             * mRow;
    
    /// look up tables for three coordinate directions
    CLIST             * mContrib[3];


    ////////////////////////////////////////
    // private methods
    ////////////////////////////////////////
private:

    /// resample one row
    void zoomRow( int j, int k, float * sourceRow, float * targetRow );

    /// resample one slice
    void zoomSlice( int k, float * slice );
  
    /// resample volume
    VSRESULT zoom();

    /// compute look up tables with fixed size kernel size
    VSRESULT contrib();

    /// computes loop-up tables for min/max filters
    void contribNoOverlap();

    /// Update bounding box. This method computes an adjusted bounding box for the resampled field.
    void setUniformCoords();
   

    ////////////////////////////////////////
    // public methods
    ////////////////////////////////////////
public:
 
     VsFilter( VsData *, VsJobControl * control=0 );

    ~VsFilter();

    /// resample to target volume    
    VsData * resample(float x, float y, float z);
};

#include "VsFilter_impl.h"


#endif

/// @}
