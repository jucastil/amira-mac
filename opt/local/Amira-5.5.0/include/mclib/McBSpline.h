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

/// @addtogroup mclib mclib
/// @{
#ifndef MC_BSPLINE
#define MC_BSPLINE

#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>
#include <mclib/McParametricCurve.h>

/**
* Class for B-spline sampling.
*/
class MCLIB_API McBSpline : public McParametricCurve
{
public:

    /** Constructor
    \param order degree+1, default is 4.
    */
    McBSpline( int order = 4 );

    /// Destructor
    virtual ~McBSpline() {}

    /** Sets the control points of the B-spline.
    \param controlPoints  array of deBoor points
    */
    void setControlPoints( const McDArray<McVec3f> & controlPoints );

    /// Computes the control points so that the result curve crosses the given points.
    void setCrossingPoints( const McDArray<McVec3f> & crossingPoints );

    /// Returns the control points.
    const McDArray<McVec3f> & getControlPoints() const;

    /// Sets the degree of spline. (order = degree + 1)
    void setDegree( int degree );

    /// Returns the degree of spline. 
    int getDegree() const;

    /// Sets the order of spline. (order = degree + 1)
    void setOrder( int order );

    /// Returns the order of spline. 
    int getOrder() const;

    /** Returns true if the curve is well defined.
    *  B-Spline order must over or equal to 2, and a number of control points at least equal to order. 
    */
    virtual bool isValid() const;

    /// Returns the parametric domain interval.
    virtual void getInterval( double & a, double & b ) const;

    /** Evaluates the function or a derivative.
    \param t        input curve 1D parameter
    \param output   output curve 3D point
    \param deriv    evaluate the deriv-th derivative (0 is curve)
    Returns false if curve is invalid.
    */
    virtual bool eval( double t, McVec3f & output, int deriv = 0 ) const;

    /** Sample curve uniformly.
    \param numSamples   number of points
    \param outputPoints returned list of points
    Returns false if curve is invalid.
    */
    virtual bool sampleUniform( int numSamples, McDArray<McVec3f> & output ) const;

private:

    /// Checks if curve is valid, and compute knot array.
    void validate();

    /// eval a basis function
    void basis( int r, float x, McDArray<float> & N ) const;

    int m_order;
    McDArray<McVec3f> m_controlPoints;
    bool m_valid;
    McDArray<float> m_knots;
};

#endif

/// @}
