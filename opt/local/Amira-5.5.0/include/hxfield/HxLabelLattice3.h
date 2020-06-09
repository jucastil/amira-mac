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
#ifndef HX_LABEL_LATTICE3_H
#define HX_LABEL_LATTICE3_H

#include <hxfield/HxLattice3.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortMultiMenu.h>

/// Lattice with additional space for weights.

class HXFIELD_API HxLabelLattice3 : public HxLattice3
{
    HX_ABSTRACT_HEADER(HxLabelLattice3);

  public:
    /// Constructor.
    HxLabelLattice3(const int dims[3], HxCoordType cType, void* data=0);

    /// This constructor uses an existing coordinate object.
    HxLabelLattice3(HxCoord3* coord, void* data=0);

    /// Destructor.
    ~HxLabelLattice3();

    /// Called by the owner, creates the ports.
    void createPorts(HxObject* owner, const McTypeInfo* typeOfImageData);

    /// Called by the owner, creates initial material list.
    void customInit();

    /// Called by the owner, checks whether ports have changed.
    virtual void update();

    /// Provides easy access to corresponding material bundle.
    HxParamBundle* materials();

    /// Sets all labels to 0 and ensures that at least one material exists.
    void clear();

    /** Update labels and materials. This method determines the number
        <em> n</em> of different labels. If necessary, the volume is modified
        so that only indices <em> 0,...,n-1</em> occur. The material bundle is
        modified, so that for each label there is a corresponding material
        bundle. */
    void relabel();

    /** This method modifies the labels so that materials with equal names
        are identified by the same numbers in both data sets. If in this
        data set materials occurs which cannot be found in the other data
        set, new material bundles will be inserted into the other set.
        After calling this method both material bundles will have the same
        number of entries and all entries will be sorted in the same way. */
    void relabel(HxParamBundle& otherMaterials);

    /** This method removes all materials, to which no voxels are assigned.
	Relabeling is performed. */
    void removeEmptyMaterials(int verbose=0);

    /** Checks whether at the boundaries of the lattice non-zero labels
        occur. More precisely, bits 0...5 of the return value indicate
        in which of the six boundary slices non-zero labels were found. */
    int borderTouch();

    /** Compute bounding box of specific material. Returned bbox is
	{xmin,xmax,ymin,ymax,...}.  The number of voxels belonging to
	this material is returned in nvoxels.  if nvoxels is 0, the
	bbox is set to be empty (max<min). */
    void computeBBox(int material, int bbox[6], mculong& nvoxels);

    /**@name Methods which modify the lattice. */
    //@{

    /** Crops or enlarges the lattice. The data set is enlarged by
        replicating the last slice. The coordinates of the lattice are
        adjusted automatically. */
    virtual bool crop(const int min[3], const int max[3], const char* replicate=NULL);

    /** Does kind of a rotation about 90 degrees. didx[i] tells at which
	position the index i was before. For example, didx[] = {1,2,0} 
	mean xyz -> yzx. */
    virtual bool swapDims(const int* didx); 

    /** Flips the order of slices in any dimension. For example, in order
        to flip the data set in z direction use @c flip(2). */
    virtual bool flip(int dimension);

    /** Reinitializes the lattice. Note however, that you can't for example
        choose the number of data variables different from one if the lattice
        belongs to a scalar field. Returns true if sucessful. */
    virtual bool init(const int dims[3], int nDataVar, McPrimType pType,
	HxCoordType cType, void* data=0);

    //@}

    /// Returns pointer to array of labels in slice @c nz.
    unsigned char* getLabels(int nz=0);

    /// Returns pointer to array of weights in slice @c nz, or zero.
    unsigned char* getWeights(int nz=0);

    // / Returns pointer to array of secondary weights in slice @c nz, or zero.
    // this is obsolete with Amira 3.0
    //unsigned char* getWeights2(int nz=0);

    /// Create weights.
    void createWeights();

    /** Create weights, use predefined memory regions. This class
	takes over the control and free's the memory later.*/
    void createWeights(unsigned char* w1);

    /// Delete weights.
    void deleteWeights();

    /// Tcl-command interface.
    int interface_parse(Tcl_Interp* t, int argc, char** argv);

    /// Duplicate lattice.
    virtual HxLattice3* duplicate();

    /// Selects primary data array, or takes it from portPrimaryArray.
    void setPrimaryData(int primary=-1);

    /**@name File IO. */
    //@{

    /// Write AmiraMesh file format.
    int writeAmiraMesh(const char* filename, int doRLE=1, int ascii=-1);
    
    /// Creates and registers a label field from a AmiraMesh structure.
    static int readAmiraMesh(AmiraMesh* m, const char* filename);

    //@}

    /// Connection to associated image data.
    HxConnection* portImageData;

    /// Specifies which array is visible in the underlying lattice object.
    HxPortMultiMenu* portPrimaryArray;

    /// Create a field of matching type and insert lattice into it.
    static HxField3* create(HxLabelLattice3* existingLattice);

  protected:
    unsigned char* theLabels;
    unsigned char* theWeights;
};

#endif

/// @}
