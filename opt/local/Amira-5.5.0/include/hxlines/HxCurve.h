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

/// @addtogroup hxlines hxlines
/// @{
#ifndef HX_CURVE
#define HX_CURVE

#include <mclib/McDArray.h>
#include <hxcore/HxSpatialData.h>
#include <hxcore/HxMessage.h>
#include <amiramesh/AmiraMesh.h>
#include <hxlines/HxLineSetInterface.h>
#include <hxlines/HxLinesWinDLLApi.h>

class HxLineSet;
class McParametricCurve;

/** This class is an abstract base class for parametric curves */
class HXLINES_API HxCurve : public HxSpatialData {

    HX_ABSTRACT_HEADER(HxCurve);

    friend class HxCurveToLineSetInterface;

public:

    HxCurve();

    ~HxCurve();

    /// set nodes or control points of the curve
    virtual void setPoints(const McDArray< McVec3f > & points) = 0;

    /// get nodes or control points of the curve
    virtual void getPoints(McDArray< McVec3f > & points) const = 0;

    /// interpolate points. Computes control points or nodes.
    virtual void interpolate(const McDArray< McVec3f > &points) = 0;

    /// returns the domain interval.
    virtual void getInterval(double & a, double & b) const;

    /** evaluate the function or a derivative.
    \param t  curve parameter
    \param point curve point computed
    \param deriv  evalutate the deriv-th derivative (0 is curve)
    */
    virtual bool eval(double t, McVec3f & point, int deriv = 0) const;

    /** sample curve uniformly.
    \param resolution number of points
    \param pts returned list of points
    */
    virtual bool sampleUniform(int resolution, McDArray< McVec3f > & points) const;

    /** raster curve equdistantially. An arc length parametrisation
    is approximated.
    \param resolution number of points
    \param pts returned list of points
    \param  l  returned list of point parameters
    */
    virtual bool sampleEquidistant(int N, McDArray< McVec3f > & pts, McDArray< double > & l) const;

    /** return sampled curve as HxLineSet.
    \param resolution number of points
    \return line set
    */
    HxLineSet * createLineSet(int resolution) const;

    /// file export
    static int saveAmiraMesh(HxCurve * curve, const char * filename) 
    { return curve->saveASCII(filename);}

    /// file import
    static int readAmiraMesh(AmiraMesh * m, const char * filename)
    { theMsg->printf("read not implemented"); return 0;}

    /// set bounding box of associated spatial data
    virtual void setBoundingBox(const float * bbox);

    /// get bounding box of associated spatial data
    virtual void getBoundingBox(float bbox[6]) const;

    /// get desired number of sample points
    virtual int getNumSamples(void) { return mNumSamples; }

    /// set the desired number of sample points
    virtual void setNumSamples(int n) { if ( n > 0 ) mNumSamples = n; }

    /** updates the bounding box to contain a list of points. 
    If newBox is true, the previous bounding box is discarded.
    */
    virtual void updateBox(const McDArray< McVec3f > & points, bool newBox = false);

    /// returns valid status
    virtual bool isValid(void) const;

protected:

    /// update 3D coordinates
    virtual void updateCoords(void);

    virtual const McParametricCurve& getCurve() const = 0;

    /// save method
    int saveASCII(const char * filename)
    { theMsg->printf("save ascii not implemented"); return 0;}

    // DATA
    McBox3f mBBox;

    /// 3D coordinates (temporary array for lineset interface)
    McDArray< McVec3f > coords;

    // number of samples for the lineset representation
    int  mNumSamples;
};


#endif

/// @}
