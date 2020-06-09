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

/// @addtogroup hxfield hxfield
/// @{
#ifndef HX_UNIFORM_COMPLEX_COMPONENT_FIELD3
#define HX_UNIFORM_COMPLEX_COMPONENT_FIELD3

#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxTightConnection.h>
#include <amiramesh/AmiraMesh.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxfield/HxUniformComplexScalarField3.h>

/// This class represent a labeled volume with material bundle.

class HXFIELD_API HxUniformComplexComponentField3 : public HxUniformScalarField3
{
  HX_HEADER(HxUniformComplexComponentField3);

  public:
    /// Default constructor.
    HxUniformComplexComponentField3();

    /// Constructor.
    HxUniformComplexComponentField3(const int dims[3], void* data=0);

    /// This constructor uses the given coordinate object.
    HxUniformComplexComponentField3(HxUniformCoord3* coord, void* data=0);

    /// Destructor.
    ~HxUniformComplexComponentField3();

    /// Connection to associated image data.
    HxTightConnection portComplexField;

    ///  Automatically establish connection to complex field
    int autoConnect(HxObject* primary);

    /// Returns pointer to label data.
    unsigned char* dataPtr(int slice=0) { return (unsigned char*)
	lattice.dataPtr() + slice*lattice.dimsLong()[0]*lattice.dimsLong()[1]; }

    /// Returns size of labeled volume.
    void getSize(int& nx, int& ny, int& nz) const {
	nx = lattice.dimsInt()[0];
	ny = lattice.dimsInt()[1];
	nz = lattice.dimsInt()[2];
    }
	
    /// Initialize voxel grid to match size of new image data.
    void resize(HxUniformComplexScalarField3* complexField);

    /** Primary data array. This port lets the user select which 
	of the possible 4 data arrays is the primary one, i.e. which one
	can be displayed by OrthoSlice and other modules. */
    HxPortMultiMenu portComponent;

    /// Update method.
    virtual void update();

    // Parse method.
    // virtual int parse(Tcl_Interp* interpreter, int argc, char** argv);

    ///
    int saveCreation(FILE* fp, const char* dataDir, int savingFlags);

    /// Overloaded info method.
    virtual void info();

protected:

  public:
    static int readAmiraMesh(AmiraMesh* m, const char* filename);
};

#endif

/// @}
