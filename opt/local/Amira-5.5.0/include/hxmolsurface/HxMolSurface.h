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

/// @addtogroup hxmolsurface hxmolsurface
/// @{
#ifndef HX_MOL_SURFACE_H
#define HX_MOL_SURFACE_H

#include <mclib/McVec2f.h>
#include <mclib/McVec2i.h>

#include <amiramesh/HxParamBundle.h>

#include <hxsurface/Surface.h>
#include <hxsurface/HxSurface.h>

#include "HxMolSurfaceWinDLLApi.h"

class HxMolecule;

/** Amira wrapper for Surface class.  */

class HXMOLSURFACE_API HxMolSurface : public HxSurface {

  HX_HEADER(HxMolSurface);

public:
    /// Constructor.
    HxMolSurface();

    /// Constructor.
    HxMolSurface(int nPoints, int nContours, int nPatches, int nSurfaces);

    /// Remove small edges using the surface simplifier. This only works for
    /// surfaces of type VDW and SAS.
    void contractSmallEdges(const float edgeLength,
                            const float minEdgeLengthFactor=0.3);

    /// This method creates a data instance from a file.
    static int readFromFile(const char* filename);

    ///
    int readMolSurface(const char* filename, 
                       McDArray<SurfaceData*>& additionalData);

    /// This method writes the data object back to file.
    int saveAscii(const char* filename);
    /// This method writes the data object back to file as binary
    int saveBinary(const char* filename);

    //
    int write(const char *file, int ascii);
    //
    int writeMolSurface(FILE *out, int ascii);

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Duplicates the current HxMolSurface object
    virtual HxData *duplicate() const;

    /// Copies content of source surface into this one.
    void copyData(const HxMolSurface &source);
    // The destructor should be hidden.
    ~HxMolSurface();

private:
    /// Auxiliary function.
    void initMolSurface();

protected:

    /// The info() method prints some information about the object.
    virtual void info();

public: 
    enum SurfaceType { VDW=0, SAS=1, SES=2, MOLSURFER_INTERFACE=3 };

    int surfaceType;
    float probeRadius;
    McDArray<int> nAtomsPerMol;
    McDArray<int> triToAtom;
    McDArray<McVec2i> triSidesToAtom;
    McDArray<int> pointToAtom;
    McDArray<HxMolecule * > hxmols;

    struct LocalRangeCurvature {
        McVec3f maxCurDir;
        McVec3f minCurDir;
        float maxCur;
        float minCur;
        float shapeIndex;
    };
    McDArray<LocalRangeCurvature> localRangeCurv;
    McDArray<McVec3f> criticalPoints;
    McDArray<McVec3f> cpNormals;
    int nSphericalConcavePatches;
};

#endif

/// @}
