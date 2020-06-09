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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef _PrincipalAxesAligner_H
#define _PrincipalAxesAligner_H

#include <hxsurftools/HxSurfToolsWinDLLApi.h>

#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec3d.h>
#include <mclib/McDMatrix.h>
#include <mclib/McDArray.h>

class HxVertexSet;
class SbMatrix;

/** This class computes a transformation of a vertex set, such that
    its principal axes are aligned to either a) another set of principal
    axes or b) global coordinate axes. */

class HXSURFTOOLS_API PrincipalAxesAligner {

  public:

    /// Default constructor.
    PrincipalAxesAligner() {};

    /// Initialization of alignment from one vertex sets to another.
    PrincipalAxesAligner(HxVertexSet* ref,McDArray<float>* massfield=0) {
        computeRefSystem(ref, massfield);
    }

    /// Initialization of alignment from one vertex set to coordinate axes.
    PrincipalAxesAligner(int axis1, int axis2) {
        computeRefSystem(axis1, axis2);
    }

    /// Compute reference principal axes
    void computeRefSystem(HxVertexSet* ref, McDArray<float>* massfield=0);

    /// Compute reference global axes
    void computeRefSystem(int axis1, int axis2);

    /// Compute trafo of alignment
    void setTransform(HxVertexSet* model, int thinoutStep=0,
        McProgressInterface* progress=NULL, McDArray<float>* massfield=0);

    /// Rotate model vertex set around its transformed principal axes.
    void rotateModelAroundAxis(HxVertexSet* model, int axis, McDArray<float>* massfield=0);

    void getRefSystem( McVec3f &center, McVec3d &moments,  McDArray<McVec3f> &vectors);

    ~PrincipalAxesAligner() {};

  protected:

    HxVertexSet* reference;

    McVec3f centerRef;
    McVec3f m3Ref;    //> 3rd order moments
    McVec3d mMoments; //> inertia moments
    McDArray<McVec3f> paRef; //> inertia axes
    
    /// Compute moments for mass distribution given by the vertex set
    void getMoments(HxVertexSet* vs, McVec3f& center,
        McDArray<McVec3f>& pa, McVec3f& m3, McDArray<float>* massfield=0);

    /// Compute eigenvectors sorted by decreasing value of eigenvalues
    void getSortedEigenvectors(McDMatrix<double>& m, McDArray<McVec3f>& pa);

    /// Compute transformation between two sets of coordinate systems
    void computeTrafo(McVec3f& centermod, McDArray<McVec3f>& pamod, McVec3f& m3mod,
                 McVec3f& centerref, McDArray<McVec3f>& paref, McVec3f& m3ref, 
                 SbMatrix& trafo);
};



#endif

/// @}
