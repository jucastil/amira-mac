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
#ifndef HX_LATTICE3_H
#define HX_LATTICE3_H

#include <mclib/McMath.h>
#include <hxfield/HxCoord3.h>
#include <hxfield/HxField3.h>
#include <hxfield/HxLattice3CropInterface.h>
#include <hxfield/HxLoc3Regular.h>
#include <hxfield/HxUniformCoord3.h>
#include <amiramesh/AmiraMesh.h>
#include <amiramesh/HxParamBundle.h>
#include <hxcore/HxInterface.h>

class HxLattice3;
class HxFieldEvaluator;

typedef void (*EvalLatFunc)(HxLattice3*, mculong, float*);

/// Represents a data grid with regular coordinates.

class HXFIELD_API HxLattice3 : public HxLattice3CropInterface
{
    HX_ABSTRACT_HEADER(HxLattice3);

  public:
    /// Constructor.
    HxLattice3(const int dims[3], int nDataVar, McPrimType pType,
    HxCoordType cType, void* data=0);

    /// This constructor uses an existing coordinate object.
    HxLattice3(int nDataVar, McPrimType pType, HxCoord3* coord, void* data=0);

    /// Destructor.
    ~HxLattice3();

    /// Returns dimensionalty of lattice values.
    int nDataVar() const { return myNDataVar; }

    /// Returns primitive data type.
    McPrimType primType() const { return myPrimType; }

#ifndef HX_NO_DIMS
    /** Returns the lattice dimensions. The method returns a pointer to a
        vector of three ints indicating the size of the lattice in x-, y-,
        and z-direction. Care should be taken if a single index into the
        data array is computed using these sizes. In order to support data
        sets with more than 2^31 elements such an index should not be
        computed as an int but as a mculong, which is 64-bit on 64-bit
        architectures. For convenience, the method dimsLong() is provided
        which returns the dimensions as a pointer to a mculong vector.

        Here is an example of a code which does not support large data
        sets with more than 2^32 elements even on 64-bit architectures:
\code
        unsigned char* data = (unsigned char*) lattice->dataPtr();
        unsigned char maxval = 0;

        const int* dims = lattice->dims();
        int n = dims[0]*dims[1]*dims[2];

        for (int i=0; i<n; i++) {
            if (data[i] > maxval)
                maxval = data[i];
        }
\endcode

        With dimsLong() code can be fixed for example like this:
\code
        unsigned char* data = (unsigned char*) lattice->dataPtr();
        unsigned char maxval = 0;

        const mculong* dims = lattice->dimsLong();
        mculong n = dims[0]*dims[1]*dims[2];

        for (mculong i=0; i<n; i++) {
            if (data[i] > maxval)
                maxval = data[i];
        }
\endcode

        In order to detect code which possibly fails for large data
        sets the define HX_NO_DIMS might be set. If this define is
        set the method dims() will be hidden and only dimsInt() and
        dimsLong() are declared. You can then decide in each case
        whether it is OK to work with int variables or whether mculong
        should be used.

        /sa dimsInt() /sa dimsLong() */
    const int* dims() const { return myDims32;  }
#endif

    /** Returns lattice dimensions as pointer to a mculong vector.
        In order to support data sets with more than 2^31 indices
        it is recommended to use this method instead of dims() if
        index computations are to be performed.
        /sa dims() /sa dimsInt() */
    const mculong* dimsLong() const { return myDims;  }

    /** Returns lattice dimensions as pointer to an int vector.
        This method is identical to dims() but it will also be
        declared if HX_NO_DIMS is defined. You may use this method
        if you know that it is OK to calaculate with ints even for
        data sets with more than 2^31 elements. This is the case if
        data elements are not addressed via an index operator.

        Here is an example:
\code
        unsigned char* data = (unsigned char*) lattice->dataPtr();
        unsigned char maxval = 0;

        const int* dims = lattice->dimsInt();

        for (int k=0; k<dims[2]; k++) {
            for (int j=0; j<dims[1]; j++) {
                for (int i=0; i<dims[0]; i++, data++) {
                    if (*data > maxval)
                        maxval = *data;
                }
            }
        }
\endcode
        /sa dims() /sa dimsLong() */
    const int* dimsInt() const { return myDims32;  }

    /// Returns lattice dimensions.
    void getSize(int& nx, int& ny, int& nz) const {
        nx = myDims32[0]; ny = myDims32[1]; nz = myDims32[2];
    }

    /// Returns number of lattice nodes;
    mculong nNodes() const { return myDims[0]*myDims[1]*myDims[2]; }

    /// Returns pointer to data array.
    void* dataPtr() { return myDataPtr; }

    /// Returns pointer to coordinate object.
    HxCoord3* coords() const { return myCoords; }

    /** This method extracts a row from the Lattice. One of the three
        indices x, y, z must be -1. This index determines the direction of
        the row. All results are casted to float. @c result must point to a
        sufficiently large memory location. */
    void getRow(int x, int y, int z, float* result);

    /** This method saves a row into the lattice. One of the three
        indices x, y, z must be -1. This index determines the direction of
        the row. */
    void putRow(int x, int y, int z, const float* src);

    /// Evaluates lattice at given node. Involves cast to float.
    inline void eval(int i, int j, int k, float *result) {
        evalLatFunc(this, (k*myDims[1]+j)*myDims[0]+i, result);
    }

    /// Evaluates lattice at given node. Involves cast to float.
    inline void eval(mculong i, float *result) {
        evalLatFunc(this, i, result);
    }

    /// Saves a single lattice element, casts value to primitive data type.
    inline void set(int i, int j, int k, const float* value)
    {
        mculong idx = (k*myDims[1] + j) * myDims[0] + i;
        set(idx, value);
    }

    /// Saves a single lattice element, casts value to primitive data type.
    inline void set(mculong i, const float* value) 
    {
        if (myNDataVar==1) {
            switch (myPrimType) {
                case McPrimType::mc_uint8: {
                    unsigned char* dst = (unsigned char*) dataPtr() + i;
                    mcint64 val = McRoundEven(*value);
                    *dst = (unsigned char) MC_CLAMP(val,0,255);
                } break;

                case McPrimType::mc_int16: {
                    short* dst = (short*) dataPtr() + i;
                    mcint64 val = McRoundEven(*value);
                    *dst = (short) MC_CLAMP(val,-32768,32767);
                } break;

                case McPrimType::mc_uint16: {
                    unsigned short* dst = (unsigned short*) dataPtr() + i;
                    mcint64 val = McRoundEven(*value);
                    *dst = (unsigned short) MC_CLAMP(val,0,65535);
                } break;

                case McPrimType::mc_int32: {
                    int* dst = (int*) dataPtr() + i;
                    mcint64 val = McRoundEven(*value);
                    // cf. definition of INT_MIN in limits.h
                    *dst = (int) MC_CLAMP(val, -2147483647 -1, 2147483647 );
                } break;

                case McPrimType::mc_float: {
                    float* dst = (float*) dataPtr() + i;
                    *dst = *value;
                } break;

                case McPrimType::mc_double: {
                    double* dst = (double*) dataPtr() + i;
                    *dst = (double) *value;
                } break;
            }

        } else {
            mculong idx = i*myNDataVar;

            switch (myPrimType) {
                case McPrimType::mc_uint8: {
                    unsigned char* dst = (unsigned char*) dataPtr() + idx;
                    for (int n=myNDataVar; n--; ) {
                        mcint64 val = McRoundEven(value[n]);
                        dst[n] = (unsigned char) MC_CLAMP(val,0,255);
                    }
                } break;

                case McPrimType::mc_int16: {
                    short* dst = (short*) dataPtr() + idx;
                    for (int n=0; n<myNDataVar; n++) {
                        mcint64 val = McRoundEven(value[n]);
                        dst[n] = (short) MC_CLAMP(val,-32768,32767);
                    }
                } break;

                case McPrimType::mc_uint16: {
                    unsigned short* dst = (unsigned short*) dataPtr() + idx;
                    for (int n=myNDataVar; n--; ) {
                        mcint64 val = McRoundEven(value[n]);
                        dst[n] = (unsigned short) MC_CLAMP(val,0,65535);
                    }
                } break;

                case McPrimType::mc_int32: {
                    int* dst = (int*) dataPtr() + idx;
                    for (int n=myNDataVar; n--; ) {
                        mcint64 val = McRoundEven(value[n]);
                        // cf. definition of INT_MIN in limits.h
                        dst[n] = (int) MC_CLAMP(val, -2147483647 -1, 2147483647 );
                    }
                } break;

                case McPrimType::mc_float: {
                    float* dst = (float*) dataPtr() + idx;
                    for (int n=0; n<myNDataVar; n++)
                    //for (int n=myNDataVar; n--; )
                        dst[n] = value[n];
                } break;

                case McPrimType::mc_double: {
                    double* dst = (double*) dataPtr() + idx;
                    for (int n=0; n<myNDataVar; n++)
                        dst[n] = (double) value[n];
                } break;
            }
        }
    }

    /** Evaluates lattice at given node. Stores result in the
        native data type. */
    void evalNative(int i, int j, int k, void *result) {
        unsigned char* dst = (unsigned char*) result;
        unsigned char* src = ((unsigned char*) myDataPtr)
            + ((k*myDims[1]+j)*myDims[0]+i)*myBytesPerNode;
        for (int a=myBytesPerNode; a>0; a--)
            *dst++ = *src++;
    }

    /** Set the undefined value.
        This value will be avoid during magnitude range computation.
        Internal use only.*/
    void setUndefinedValue(double undefinedValue);

    /** Unset the undefined value use.
        The undefined default value is also reseted to its default value.
        Internal use only.*/
    void unSetUndefinedValue();

    /** Tell if lattice has an undefined value.
        Internal use only.*/
    bool hasUndefinedValue() {return m_hasUndefinedValue;}

    /** Return the undefined value. It's -FLT_MAX by default.
        Internal use only.*/
    double getUndefinedValue() {return m_undefinedValue;}

    /** Computes magnitude range.
        This method won't use undefined values to compute the range if @c discardUndefinedValues is set to true.*/
    virtual void computeRange(float& min, float& max, bool discardUndefinedValues=false);

    /**@name File IO. */
    //@{

    /// Reads a regular field from an AmiraMesh structure
    static int readAmiraMesh(AmiraMesh* m, const char* filename);

    /// Writes a regular field to an AmiraMesh file.
    int writeAmiraMesh(const char* fn, HxField3* hxfield3, int compression=0, int ascii=-1);

    /// Add contents of lattice to AmiraMesh structure.
    void addToAmiraMesh(AmiraMesh& m, const char* name, const char* codec=0);

    /// Write multiple files of raw data.
    int writeRawData(const char* basename, int reverseZOrder=0);

    //@}

    /**@name Methods which modify the lattice. */
    //@{

    /** Resizes the field. Memory is reallocated as necessary. The values
        of the lattice are undefined after this operation. Returns true if
        sucessful. */
    bool resize(int nx, int ny, int nz);

    /// This method does the same thing as the one above.
    bool resize(const int dims[3]) { return resize(dims[0],dims[1],dims[2]); }

    /** Changes the primitive data type of the lattice. Memory is
        reallocated as necessary. Data values are undefined after this
        operation. In particular, no casting is performed. */
    bool setPrimType(McPrimType newType);

    /** Crops or enlarges the lattice. If @c replicate=NULL (default),
        the data set is enlarged by replicating the last slice. Otherwise
        @c replicate will interpreted as pixel value for additional pixel.
        The coordinates of the lattice are adjusted automatically. */
    virtual bool crop(const int min[3], const int max[3], const char* replicate = NULL);

    /** Same as crop() but do not call touch().

        cropNoTouch() can be used instead of crop() if you want to avoid
        side-effects, such as calling Qt signals.
      */
    bool cropNoTouch(const int min[3], const int max[3], const char* replicate = NULL);

    /** Does kind of a rotation about 90 degrees. didx[i] tells at which
        position the index i was before. For example, didx[] = {1,2,0}
        mean xyz -> yzx. */
    virtual bool swapDims(const int* didx);

    /// This method does the same thing as the one above.
    bool swapDims(int ix, int iy, int iz);

    /** Flips the order of slices in any dimension. For example, in order
        to flip the data set in z direction use @c flip(2). */
    virtual bool flip(int dimension);

    /// Call coords()->setBoundingBox() and touches the owner.
    void setBoundingBox(const float bbox[6]) {
        coords()->setBoundingBox(bbox);
        touch( HxData::NEW_COORDINATES );
    }

    /** Reinitializes the lattice. Note however, that the number of data
        variables MUST MATCH the number implied by the type of field the
        lattice belongs to. For example, if the lattice is part of a
        HxRegScalarField3, @c nDataVar must be 1. Also, if the lattice is
        part of a uniform field, @c cType MUST BE c_uniform. If @c data is
        not null, a previously allocated block of memory is freed and
        @c data is used instead. The lattice takes over full control over
        @c data, i.e., it may call free or realloc the memory. For this
        reason @c data should have been allocated using malloc instead of
        new[]. The method returns 1 on success. */
    virtual bool init(const int dims[3], int nDataVar, McPrimType pType,
        HxCoordType cType, void* data=0);

    /// This is only a small wrapper.
    bool init(int nVars, McPrimType pType, HxCoord3* coord, void* data=0);

    /** Converts 16-bit unsigned shorts into signed shorts. Currently
        Amira only supports signed shorts as a primitive data type. In
        order to read unsigned shorts either the least significant bit
        has to be discarded or the data has to mapped from 0...2^16-1 to
        -2^15...2^15-1. Assuming, the data actually represents unsigned
        shorts this method performs such a mapping. The method usually
        is called from a read routine. The reader first copies unsigned
        shorts into the lattice (while the primType is set to mc_int16)
        and then calls this method in order to map the data. */
    void mapUInt16ToInt16(int discardLeastSignificantBit=0);
    //@}

    /// Copies the data (without const's - they MUST be equal)
    void copyData(const HxLattice3 &source);

    /// Touches the lattice owner and invalidates the stored range.
    void touchMinMax();

    /// Touches the lattice owner.
    void touch(unsigned int mask = 0xffffffff);

    /// Duplicate lattice.
    virtual HxLattice3* duplicate();

    /** Create a field of matching type and insert lattice into it.
        Only a typeHint of HxSym2TensorField3::getClassTypeId() is accepted
        to provide a way to indentify a tensor field from a complex vector field.
        All other identifications are done by the number of data entries nDataVar. */
    static HxField3* create(HxLattice3* existingLattice, const McTypeInfo *typeHint=0);

    /** The given field src is sampled onto the reference lattice refLattice.
        If refLattice is owned by a field, the transformation of the field
        is took into account.
        The result field is stored in the pointer dest.
        If an existing field is passed in dest, it is first checked whether
        this field is appropriate for sampling into. Otherwise a new field
        is created and stored in dest.
        If a HxFieldEvaluator, this evaluator is used. If not the standard
        evaluator is used.
        For the voxels of refLattice which are not covered by voxels in src
        due to a transformation, a padding value is applied. */
    static void sampleOntoRef (HxField3* const src, HxLattice3* const refLattice,
        HxField3** const dest, HxFieldEvaluator* eval=0, float paddingVal=0, unsigned int numThreads=1);

    /** Downsample lattice by averaging	nx*ny*nz values. In Contrast to the 
        algorithm in McRawData::downSample3D, no voxels are skipped. In case of 
        remainders resulting from myDims[i] / nX, an extra voxel is introduced and 
        the bounding box is adapted appropriately. 
        Currently only for uniform or stacked regular data. */
    void downsample(int nx, int ny, int nz, HxLattice3 *result, bool useProgress=true);

  protected:
    int                 myNDataVar;
    int                 myBytesPerNode;
    McPrimType          myPrimType;
    mculong             myDims[3];
    int                 myDims32[3];
    void*               myDataPtr;
    McHandle<HxCoord3>  myCoords;
    EvalLatFunc         evalLatFunc;

    bool    m_hasUndefinedValue;
    double  m_undefinedValue;

  private:
    /** Updates slice info, if dimension is changed.
     *  Calls @c checkParameters() and @c restoreSliceInfo()
     */
    bool fixSliceInfo(const int newMin, const int newMax);

    /** Checks parameters for correctness.
     */
    bool checkParameters(HxParamBundle* paramBundle, McString& namePattern);
    /* Updates slice info, if parameters correct.
     */
    bool restoreSliceInfo(HxParamBundle* paramBundle, const int newMin, const int newMax, McString& namePattern);

  public:
    // Initializes evaluation method pointers.
    void setEvalMethods(HxField3* field);

    // Sets content string. This lattice should be a member of @c data.
    void setContentInfo(HxSpatialData* data, const char* what=0);

    // Swap data ptr. Used by HxUniformLabelField3. Hack.
    void swapDataPtr(void*& otherPtr);

    // Tcl-command interface.
    virtual int interface_parse(Tcl_Interp* t, int argc, char** argv);

    virtual const int* cropinterface_dims() const {
        return dimsInt();
    }

    virtual HxCoord3* cropinterface_coords() const {
        return coords();
    }
    /// Delegates cropping to <tt>crop(min, max, replicate)</tt>.
    virtual bool cropinterface_crop(const int min[3], const int max[3], const char* replicate = NULL) {
        return crop(min,max,replicate);
    }

    virtual bool cropinterface_swapDims(int ix, int iy, int iz) {
        return swapDims(ix, iy, iz);
    }

    virtual bool cropinterface_flip(int dimension) {
        return flip(dimension);
    }

    virtual void cropinterface_setBoundingBox(const float bbox[6]) {
        setBoundingBox(bbox);
    }

    virtual void cropinterface_computeAutoBox(float threshold, int box[6]);

    void cropinterface_exchangeSlices(int i, int j);

  protected:

    static void evalLatByte1(HxLattice3*, mculong, float*);
    static void evalLatByteN(HxLattice3*, mculong, float*);
    static void evalLatShort1(HxLattice3*, mculong, float*);
    static void evalLatShortN(HxLattice3*, mculong, float*);
    static void evalLatUShort1(HxLattice3*, mculong, float*);
    static void evalLatUShortN(HxLattice3*, mculong, float*);
    static void evalLatInt32_1(HxLattice3*, mculong, float*);
    static void evalLatInt32N(HxLattice3*, mculong, float*);
    static void evalLatUInt32_1(HxLattice3*, mculong, float*);
    static void evalLatUInt32N(HxLattice3*, mculong, float*);
    static void evalLatFloat1(HxLattice3*, mculong, float*);
    static void evalLatFloatN(HxLattice3*, mculong, float*);
    static void evalLatDouble1(HxLattice3*, mculong, float*);
    static void evalLatDoubleN(HxLattice3*, mculong, float*);

};

#endif

/// @}
