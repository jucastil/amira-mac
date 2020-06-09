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
#ifndef HX_UNIFORM_LABEL_FIELD_H
#define HX_UNIFORM_LABEL_FIELD_H

#include <amiramesh/AmiraMesh.h>
#include <hxfield/HxLabelLattice3.h>
#include <hxfield/HxUniformScalarField3.h>

/// Represents a labeled volume with uniform coordinates.

class HXFIELD_API HxUniformLabelField3 : public HxUniformScalarField3
{
  HX_HEADER(HxUniformLabelField3);

  public:
    /// Default constructor.
    HxUniformLabelField3();

    /// Constructor.
    HxUniformLabelField3(const int dims[3], void* data=0);

    /// This constructor uses an existing lattice object.
    HxUniformLabelField3(HxLattice3* existingLattice);

    /// Destructor.
    ~HxUniformLabelField3();

    /// Automatically connects to a uniform scalar field.
    virtual int autoConnect(HxObject* primary);

    /// Get access to the label lattice.
    HxLabelLattice3& labelLat;

    /// Write AmiraMesh RLE-compressed file format.
    int writeAmiraMeshRLE(const char* filename);

    /// Write AmiraMesh binary file format.
    int writeAmiraMeshBinary(const char* filename);

    /// Write AmiraMesh ascii file format.
    int writeAmiraMeshAscii(const char* filename);

    /// Update method.
    virtual void update();

    /// Parse method.
    virtual int parse(Tcl_Interp* interpreter, int argc, char** argv);

    /// Duplicates the current HxUniformLabelField3 object
    virtual HxData *duplicate() const;

    /** Get surface area of all voxel faces bounding material material.*/
    float getSurfaceArea(int material);

    /**@name Methods for backward compatibility (better use labelLat). */

    /// Returns size of labeled volume.
    void getSize(int& nx, int& ny, int& nz) { labelLat.getSize(nx,ny,nz); }
	
    /// Resize labeled volume.
    void resize(int nx, int ny, int nz) { labelLat.resize(nx,ny,nz); }

    /// Returns pointer to label data.
    unsigned char* dataPtr(int slice=0) { return labelLat.getLabels(slice); }

    /// Returns pointer to label data.
    unsigned char* labelPtr(int slice=0) { return labelLat.getLabels(slice); }
    
    /// Returns pointer to confidence array.
    unsigned char* confPtr(int slice=0) { return labelLat.getWeights(slice); }

    /// Returns pointer to alternative confidence array.
//    unsigned char* confPtr2(int slice=0) { return labelLat.getWeights2(slice); }

    /// Create alternative arrays.
    void createAltData() { labelLat.createWeights(); }

    /// Delete alternative arrays.
    void deleteAltData() { labelLat.deleteWeights(); }

    /// Relabel labels.
    void relabel() { labelLat.relabel(); }

    /** Create color materials for this label field. The materials are labeled with label
        and numbered. Either numMaterials materials are created or, if the field usedLabels 
        is set, for all entries with usedLabels[i]!=0 materials are created. 
        If given, the colors are taken from the color map cmap. Otherwise distinguishable colors 
        are created, which additionally can be mixed (\see{McColor::mostDifferentColorsHSV}).
    */
    void createColorMaterials(const McString &label, int numMaterials, HxColormap* cmap=0, 
                              unsigned char* usedLabels=0, bool mix=false);
protected:
    virtual void applyTransform(SbMatrix& transform,int autoDims,
				int autoBBox, int interpol, 
				int autoCrop,float threshold,
				const int* forcedims,
				const float* forcebox);

    /// Used by duplicate(); copies the needed data
    void copyData(const HxUniformLabelField3 &source);
};

#endif

/// @}
