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

/// @addtogroup hxalign hxalign
/// @{
#ifndef HX_ALIGN_DATA
#define HX_ALIGN_DATA

#include <mclib/McBitfield.h>
#include <mclib/McDArray.h>

#include <hxcore/HxThread.h>

class HxAlignSlices;
class SliceInfo;

class HxSpatialData;
class HxLattice;
class HxLabelLattice;
class HxParamBundle;


/** Class managing the data for the alignSlices module */
class HxAlignData {

public:
    /** Constructor */
    HxAlignData(HxAlignSlices* alignmanager);

    /** Destructor */
    ~HxAlignData();

    /** Returns the lattice of src 
    *  @return the lattice, in case of errors NULL */
    HxLattice* getLattice() const;

    /** Returns the primType */
    McPrimType getPrimType() const;

    /** Returns the lattice dimension */
    const int* getDims() const;

    /** Returns the number of data variables of the data to be aligned. This is
    1 for scalar fields and 4 for color fields. */
    int getNumDataVars() const;

    /** Returns whether the data set is a color data set */
    bool isColorField();

    bool init (HxSpatialData* src, HxLattice* lat);
    void reset();
    void resetData();

    /** interface for setting the slice which is editable. */
    void setEditableSlice(int sliceNumber);

    /** interface for setting the reference slice. */
    void setReferenceSlice(int referenceSliceNumber);


    unsigned char* getComputedEditableSlicePtr() const {
        return computedEditableSlicePtr;
    }

    unsigned char* getComputedReferenceSlicePtr() const {
        return computedReferenceSlicePtr;
    }

    unsigned char* getDisplayEditableSlicePtr() const {
        return displayEditableSlicePtr;
    }

    unsigned char* getDisplayReferenceSlicePtr() const {
        return displayReferenceSlicePtr;
    }

    const unsigned char* getOriginalDataPtr(const int sliceNumber);

    /** Sets/gets the lattice for the mask data set */
    void setMaskLattice(HxLabelLattice* m);
    HxLabelLattice* getMaskLattice() {
        return maskLattice;
    }

    /** Returns a bitfield containing the mask for slice SliceNum */
    McBitfield getMaskBitfield(const int sliceNum);

    /** Get the parameter bundle of the input data */
    HxParamBundle& getParameters();

    /** Call touch on the input data */
    void touchInputData();

    /** Call getName on input data */
    const char* getInputDataName();


    /** Methods for (un)locking the data mutex */
    void lockDataMutex() {dataMutex.lock();};
    void unlockDataMutex() {dataMutex.unlock();};

    /** Computes the internal images used for the alignment operation. This method
    maps scalar input data to an internal 8-bit image taking into account the
    data window defined by minVal and maxVal. Color images are mapped to an internal
    8-bit image using the NTSC formula. The internal images are computed for the
    current slice as well as for the reference slice. */
    void mapSlices();

protected:

    HxAlignSlices* alignManager;

    /** Pointer to the data lattice */
    HxLattice* lattice;

    /** Lattice dimensions */
    int dims[3];

    /** Pointer to to the data object */
    HxSpatialData* srcPointer;

    /** Pointer to the mask lattice */
    HxLabelLattice* maskLattice;

    /** Pointer to the mapped editable slice, used for computations*/
    unsigned char* computedEditableSlicePtr;

    /** Pointer to the mapped reference slice, used for computations*/
    unsigned char* computedReferenceSlicePtr;

    /** Pointer to the mapped editable and reference slice, used for display.
     *  For non-color (scalar) data sets, this pointer is the same as computedEditableSlicePtr 
     *  resp. computedReferenceSlicePtr */
    unsigned char* displayEditableSlicePtr;
    unsigned char* displayReferenceSlicePtr;
    unsigned char* originalDataPtr;

    /** Editable slice. */
    int editableSlice;

    /** Reference slice. */
    int referenceSlice;

    /** Mutex for the data object */
    HxMutex dataMutex;

    /** These methods compute the internal representations: 1) for computations (pointed to by 
     *  computedEditableSlicePtr and computedReferencesSlicePtr). 2) for display (pointed to by 
     *  displayEditableSlicePtr and displayReferencesSlicePtr).
     *  The mapping can be normal (intensity) and maximum intensity projection.
     *  A mask is applied, when available, to both representations */
    void mapEditableSlice();
    void mapReferenceSlice();
    void mapSliceNormal(unsigned char* computedPtr, unsigned char* displayPtr, const int sliceIdx);
    void mapSliceMaxIntProj(unsigned char* resultPtr, const int minZ, const int maxZ);


private:
    /** Constructor. No standard construction is allowed */
    HxAlignData();
};


#endif

/// @}
