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

/// @addtogroup hxsurface hxsurface
/// @{
#ifndef _HxSurface_h_
#define _HxSurface_h_

#include <mclib/McVec2f.h>
#include <hxcore/HxVertexSet.h>
#include <hxcore/HxPortIntSlider.h>
#include <amiramesh/HxParamBundle.h>
#include <hxsurface/Surface.h>

class ProgressSenderIface;

/** Amira wrapper for Surface class.  */

class HXSURFACE_API HxSurface : public HxVertexSet, public Surface {

  HX_HEADER(HxSurface);

  public:
    /// Constructor.
    HxSurface();

    /// Constructor.
    HxSurface(int nPoints,int nContours,int nPatches,int nSurfaces);

    /// Level of detail
    HxPortIntSlider portLOD;

    /// Update method
    virtual void update();

    /// From HxVertexSet...
    virtual McVec3f* getCoords() const { return (McVec3f*) points.dataPtr();}

    /// From HxVertexSet...
    virtual int getNumPoints() const {return points.size();}

    /// From HxVertexSet...
    virtual void applyTransform(const SbMatrix& transform);
    
    /// This method creates a data instance from a file.
    static int readFromFile(const char* filename);

    /// This method creates a data instance from a file.
    static int readFromFile(const char* filename, ProgressSenderIface *progress);

    /** This method creates a data instance from a file in ply format,
        WARNING: Only a subset of ply files can be read.*/
    static int readFromFilePLY(const char* filename);

    /// This method writes the data object back to file.
    int saveAscii(const char* filename);
    //
    int saveBinary(const char* filename);
    //
    int saveWavefront(const char* filename);

    /// Writes surface as Inventor model.
    int saveInventor(const char* filename);

    /// Returns bb of surface points.
    void getBoundingBox(float bbox[6]) const;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Duplicates the current HxSurface object
    virtual HxData *duplicate() const;

    /// Merge (i.e. copy) patches from second surface into this one
    virtual void merge(Surface& other, bool mergePatches=false);

    // copy material properties of surface with corresponding mesh
    virtual void copyMaterials(const HxSurface* other);

    /**
        Merges the surface with another one by using @c merge and additionally merges also all fields (if used within Amira).
    */
    void mergeAll(HxSurface& other);
 
 
    /**
        Removes points with identical coordinates from the connectivity of a
        mesh.  The duplicate points stay as vertices in the surface data
        structure, so attached fields do not need to change.
    */
    int mergeDuplicateGridVertices(float tol, McProgressInterface* progress);

    /** 
         Removes points with identical coordinates. This method also updates
         attached data fields with data values defined on nodes. Data values on
         duplicated points will not be averaged, the data value of the last
         occurence of a duplicated point will be used instead. If @c tol is
         non-zero points are considered to be equal even if their coordinates
         are not more than @c tol apart. The method returns the number of
         removed duplicated points. If duplicated points were removed the
         surface is touched but downstream objects will not be fired
         automatically. 
    */
    int removeDuplicatePoints(float tolerance, McProgressInterface* progress=0);

    /** Remove patches with less than 'minPatchSize' triangles.
        Returns the number of removed patches. */
    int removeSmallPatches(int minPatchSize);
    
    /** Get surface area of all triangles (default)
        or of those bounding material 'material'.*/
    float getArea(int material = -1);

    /** Get volume of the entire surface (default)
        or of the material region 'material'.*/
    float getVolume(int material = -1);

    /** Get min length of all edges.(default)
        or of those contained in material 'material' */
    float getMinEdgeLength(int material = -1);
    float minEdgeLengthOfTriangle (int);

    /** Get max length of all edges.(default)
        or of those contained in material 'material' */
    float getMaxEdgeLength(int material = -1);
    float maxEdgeLengthOfTriangle (int);

    /** Get mean length of all edges.(default)
        or of those contained in material 'material' */
    float getMeanEdgeLength(int material = -1);
    float meanEdgeLengthOfTriangle (int);

    ///
    int hasTextureCoords();
    
    ///
    McVec2f* getTextureCoords();
    
    ///
    McDArray<McVec2f> textureCoords;

    /// Copies content of source surface into this one.
    void copyData(const HxSurface &source);

    virtual McString getLoggingInfo();

  protected:
    // The destructor should be hidden.
    virtual ~HxSurface();

    /// The info() method prints some information about the object.
    virtual void info();
};

#endif

/// @}
