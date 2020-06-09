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

/// @addtogroup hxivdata hxivdata
/// @{
#ifndef HX_IV_DATA
#define HX_IV_DATA

#include <mclib/McHandle.h>
#include <hxcore/HxSpatialData.h>
#include <hxivdata/HxIvDataWinDLLApi.h>
#include <Inventor/SoInput.h>
#include <Inventor/nodes/SoNode.h>

/// This class wraps an Inventor scene graph as a subclass of HxSpatialData
//  an instance contains a pointer to the root of the scene graph and holds
//  the number of the geometry's triangle 

class HXIVDATA_API HxIvData : public HxSpatialData {

  HX_HEADER(HxIvData);  // defines class TypeId for run-time type 
                        // checking, should be done in any class

  class SoProgressInput : public SoInput
  {
    public:
      SoProgressInput();
      virtual void updateReadPercent(double readPercentage);
    private:
      double mPercentDone;
  };

  public:
    /// Constructor
    HxIvData();

    /// Computes bounding box of geometry.
    virtual void getBoundingBox(float bbox[6]) const;

    /// Sets user-defined bounding box (overwrites geometry's box).
    void setBoundingBox(const float b[6]);

    /// Returns root of scene graph
    SoNode* getSceneGraph() { return root; }

    /// sets the scene graph
    void setSceneGraph(SoNode* graph) {root = graph;}

    /// Writes Inventor geometry to file.
    int write(const char *filename, bool binary);

    /// Writes Inventor geometry to binary file.
    int writeBinary(const char *filename);

    /// Writes Inventor geometry to ascii file.
    int writeAscii(const char *filename);

    /// Reads Inventor file and puts it into a new HxIvData object
    static int read(const char *filename);

    /// Reads a DXF file and puts it into a new HxIvData object
    static int readDxf(const char *filename);

    /// Returns number of triangles in geometry.
    int getNumTriangles();

    /// Info method prints number of triangles.
    virtual void info();

    /// Returns a duplicate of this HxIvData object
    virtual HxData *duplicate() const;

    /// Tcl command interface.
    int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    ~HxIvData();

    /// Copy data from other HxIvData to this, used by duplicate()
    void copyData(const HxIvData &source);
    
    McHandle<SoNode> root;      
    int nTriangles;
};

#endif


/// @}
