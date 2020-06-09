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
#ifndef HX_BSPLINE
#define HX_BSPLINE

#include <hxlines/HxCurve.h>
#include <hxcore/HxPortInfo.h>
#include <mclib/McBSpline.h>


/** This class implements BSpline curves. Currently it only
    supports integral BSplines, but it can be extended to NURBS on demand.
*/
class HXLINES_API HxBSpline : public HxCurve
{
    HX_HEADER(HxBSpline);

//    friend class HxCurveToLineSetInterface;

private:

    //DATA
    int      mLength;	                  //!> arc length
    McBSpline m_bSpline;

public:

    /// standard constructor with order (degree+1) of spline 
    HxBSpline(int order = 4);

    /** constructor creates a valid spline. The knot vector
    is created automatically.
    \param controlpoints  array of deBoor points
    \param order  degree+1
    */
    HxBSpline(const McDArray< McVec3f > & controlpoints, int order = 4);

    /// destructor
    ~HxBSpline();

    /** set the control points. A knot vector is computed. */
    virtual void setPoints(const McDArray< McVec3f > & controlpoints);

    /// get the control points. 
    virtual void getPoints(McDArray< McVec3f > & controlpoints) const;

    /// interpolate points. Computes control points and knot vector.
    virtual void interpolate(const McDArray< McVec3f > & points);

    /** returns normal at t in point. 
    Returns 0 at singular points.
    */
    int getNormal(double t, McVec3f & normal) const;

    /** returns binormal at t in point. 
    Returns 0 at singular points.
    */
    int getBinormal(double t, McVec3f & binormal) const;

    /** returns tangent at t */
    inline void getTangent(double t, McVec3f & tangent)
    { eval(t, tangent, 1); tangent.normalize(); }

    /// return single control point
    virtual inline McVec3f getPoint(int i) const { return m_bSpline.getControlPoints()[i]; }

    /// sets the degree of spline. 
    void setDegree(int degree);

     /// gets the degree of spline. 
    int getDegree(void) const { return m_bSpline.getDegree(); }

    /// save to ascii file
    static int saveAmiraMesh(HxBSpline * curve, const char * filename); 

    /// read from file
    static int readAmiraMesh(AmiraMesh * m,const char * filename);

protected:

    /// save to ascii file
    virtual int saveASCII(const char * filename);

    /// create default knot vector for end point interpolation
    void createKnots(void);

    /// create default knot vector, do not use
    void createKnots2(void);

    /// update port info
    virtual void info(void);

    virtual const McParametricCurve& getCurve() const;
};

#endif

/// @}
