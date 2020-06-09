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

/// @addtogroup hxisl hxisl
/// @{
#ifndef _FIELD_LINE_SET_H
#define _FIELD_LINE_SET_H

#include <hxisl/HxISLWinDLLApi.h>

#include <hxfield/HxVectorField3.h>

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>

template<class VecType>
class McODE;

class HxColormap;
class Particle;
struct Fragment;
class HxLocation3;
class HxVectorField3;


///A set of field lines; mainly stream lines.
class HXISL_API FieldLineSet : public McDArray<Particle *>
{
  protected:
    McODE<McVec3f>* forward;
    McODE<McVec3f>* backward;
    HxLocation3*        location;
    HxVectorField3*     vectorField;
    int                 status;

    static int eval(const McVec3f& r, McVec3f& f, void* userData);

  public:
    McDArray <SbVec3f>  seedPoints;
    McDArray <short>    lengthBackward;
    McDArray <short>    lengthForward;
    int			defaultLengthBackward;
    int			defaultLengthForward;

    McDArray <short>    alpha;
    McDArray <short>    age;
    McDArray <short>    traceStart;
    McDArray <short>    traceLength;
    McDArray <SbVec3f>  points;
    McDArray <SbVec3f>  tangents;
    McDArray <float>    lengths;

    //say if geodetic coord sys
    bool m_transformGeodetic;

    /// Constructor.
    FieldLineSet();

    /// Destructor.
    ~FieldLineSet();

    /** Recomputes field lines for all seed points. The argument @c h
	specifies an average step size used for field line integration.
	The size is measured as a fraction of the vectorfield's bounding
	box. */
    void computeFieldLines(HxVectorField3* v, float h=0.005);

    /** Computes a field line starting at @c pos. The sample points and the
	normalized tangent vectors are written into the corresponding
	dynamic arrays.  If field line integration terminated before the
	maximal number of samples was reached, the arrays are resized
	properly. */
    int computeFieldLine(
	    McVec3f& pos,		   // Seep point
	    McVec3f& f,			   // Derivative at seed point
	    int lengthBack,		   // Number of backward samples
	    int lengthForward,		   // Number of forward samples
	    McDArray<McVec3f>& points,	   // Store samples here
	    McDArray<McVec3f>& tangents    // Store f/|f| here
    );
};

#endif


/// @}
