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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_SPATIAL_DATA_H
#define HX_SPATIAL_DATA_H

#include <stdarg.h>
#include <mclib/McVec3f.h>
#include <mclib/McBox3f.h>
#include <mclib/McHistogram.h>

#include <hxcore/HxData.h>
#include <Inventor/SbLinear.h>

class SoSensor;
class SoNodeSensor;
class SoTransform;
class QxHistogramWorker;
class McProgressInterface;

/** Base class for all data objects that are defined in three dimensional space.
    Every such data object defines a 3D bounding box. It also may be
    transformed by a 4x4 homogeneous transformation matrix. The
    transformation is stored in a SoTransform node and is applied
    automatically to all downstream visualization modules (see also
    discussion of geometric transformations in the documentation of class
    HxBase). */
class HXCORE_API HxSpatialData : public HxData {
    HX_ABSTRACT_HEADER(HxSpatialData);

  public:
    /** Computes bounding box of data object. The values are stored in the
        following order: minX, maxX, minY, maxY, minZ, maxZ.
        Note: This method does not take any transformation into account. That is,
        to get the global coordinates of a transformed object, one has to apply
        the transformation to the returned values manually.
    */
    virtual void getBoundingBox(float bbox[6]) const;

    /** Set the undefined value.
        This method is provided here for
        convenience because many spatial data objects (although not all)
        contain data values for which data can be undefined.
    */
    virtual void setUndefinedValue(double undefinedValue);

    /** Tell if spatial data has undefined value.
        This method is provided here for
        convenience because many spatial data objects (although not all)
        contain data values for which data can be undefined.
    */
    bool hasUndefinedValue();

    /** Get the undefined value.
        This method is provided here for
        convenience because many spatial data objects (although not all)
        contain data values for which data can be undefined.
        If there is no undefined value, this method return 0 otherwise, 1.
    */
    virtual int getUndefinedValue(double& undefinedValue);
    
    /** Calculate the approximative data size in bytes within a 3D bounding box.
        false is returned if could not be computed or the computation is not implemented.
    */
    virtual bool getMemSize(mcuint64 &size, const McBox3f &box);

    /** Tell if spatial data has a DataWindow parameter.
        This method is provided here for
        convenience because many spatial data objects (although not all)
        contain data values for which data can be undefined.
    */
    bool hasDataWindow();

    /** Set the DataWindow parameter.
        This method is provided here for
        convenience because many spatial data objects (although not all)
        contain data values for which a data window can be defined.
        This range can be greater than the real raw data range.
        See <tt>getRange(float& min, float& max, RangeType rangeType=RAW_DATA)</tt> method to get it.
    */
    void setDataWindow(double min, double max);

    /** Remove the DataWindow parameter.
      This method is provided here for
      convenience because many spatial data objects (although not all)
      contain data values for which a data window can be defined.
    */
    void removeDataWindow();

    /// Computes bounding box of data object.
    McVec3f getBoundingBoxSize() const;

    /// Computes bounding box of data object.
    McVec3f getBoundingBoxCenter() const;

    /// returns the lower, left corner.
    McVec3f getBoundingBoxOrigin () const;

    /** Each data object can have an optional pointer to an
      SoTransform object. This allows for global scaling, translation
      and rotation of data objects.

      This transformation will automatically be applied to any
      geometry displayed by modules connected to this data
      object. Therefore there is normally no need to think about these
      transformations. However in cases where two or more datasets are
      treated by one module, transformations are to be considered.

      The transformation may be accessed using the <tt> SoTransform*
      getTransform()</tt> method, which may return a NULL pointer,
      if the data object is not transformed and create is false.

      Often it is easier to use the <tt>getTransform(SbMatrix& matrix)</tt>,
      which returns the current transformation matrix or the identity matrix,
      when there is no transformation. This matrix is to be applied by
      multiplying it to a vector from the right hand side. It
      transforms vectors from the local coordinate system to the
      global coordinate system.

      If you want to transform world coordinates to local coordinates,
      use <tt> getInverseTransform(SbMatrix& matrix)</tt>.

      As an example, consider the following code, which transforms the origin
      of a field A to the local coordinate system of a second field B.
      @code
        float bbox[6];
        SbVec3f originWorld,originB;
        SbMatrix matrixA, inverseMatrixB;

        / / Compute origin in local (A) coordinates
        fieldA->getBoundingBox(bbox);
        SbVec3f origin(bbox[0],bbox[1],bbox[2]);

        fieldA->getTransform(matrixA);
        fieldB->getInverseTransform(inverseMatrixB);

        / / transform origin to world coordinates:
        matrixA.multVecMatrix(origin,originWorld);

        / / transform origin from world to local B coordinates:
        inverseMatrixB.multVecMatrix(originWorld,originB);
        @endcode
        Instead of the last lines of code one could also combine the
        two matrices:
        @code
        SbMatrix allInOne;
        allInOne = matrixA;
        allInOne.multRight(inverseMatrixB);
        @endcode

        Note that this is the same as:
        SbMatrix allInOne;
        @code
        allInOne = inverseMatrixB;
        allInOne.multLeft(matrixA);
        @endcode

        Since the transformation could contain a translational part, special
        attention has to be paid, when directional vectors are transformed.
        In this case the method
        <tt> getTransformNoTranslation(SbMatrix& matrix)</tt>
        should be used.  */
    const SoTransform* getTransform(bool create=false) const;

    /** Returns current transformation. If this object has no
        transformation and if create is true, a new identity transform
        node will be created. Otherwise NULL will be returned. */
    SoTransform* getTransform(bool create=false);

    /** Indicator if data has a transformation.
        @return Returns true if the transformation is not the identity, otherwise false. */
    bool hasTransform() const;

    /** Set current transformation. If xform is not null, its ref-count will
        be increased and it will be used as the new object's transform node.
        If xform is null the object's transformation will be reset to the
        identity transformation. */
    virtual void setTransform(SoTransform* xform);

    /** Set transformation to be this matrix. If no transformation
        exists one is created. */
    virtual void setTransform(const SbMatrix& matrix);

    /** Set current transformation via setTransform after rounding
        each entry to the number of digits given by @c precision.  In
        order to get the same transformation back, getTransformRounded
        needs to be called with the same precision.  For the default
        precision value of 6 and smaller, the transformation should be
        equal.  For larger precision values this is not guaranteed. */
    virtual void setTransformRounded(const SbMatrix& matrix, unsigned short precision=6);

    /** Get current transformation matrix. If this object has no
    transformation, identity is returned.*/
    void getTransform(SbMatrix& matrix) const;

    /** Get current transformation via getTransform and round each
        entry to the number of digits specified by @c precision.
        getTransformRounded should be called with the same precision
        as setTransformRounded() to obtain the same transformation.
        For the default precision value of 6 and smaller, the
        transformation should be equal.  For larger precision values
        this is not guaranteed. */
    virtual void getTransformRounded(SbMatrix& matrix, unsigned short precision=6) const;

    /** Get current transformation matrix. If this object has no
    transformation, identity is returned.*/
    /* DO NOT REMOVE !!! Otherwise gcc-3.3 claims ambiguity :
       error: ISO C++ says that `void HxSpatialData::getTransform(SbMatrix&) const'
       and `SoTransform* HxSpatialData::getTransform(bool)' are ambiguous even though
       the worst conversion for the former is better than the worst conversion for the
       latter. */
    void getTransform(SbMatrix& matrix);

    /** Get inverse of current transformation matrix. If this object
    has no transformation, identity is returned.*/
    void getInverseTransform(SbMatrix& matrix) const;

    /** Get rounded inverse of current transformation matrix. If this object
    has no transformation, identity is returned.*/
    void getInverseTransformRounded(SbMatrix& matrix, unsigned short precision=6) const;

    /** Get current transformation matrix without translational part.
        If this object has no transformation, identity is returned.*/
    void getTransformNoTranslation(SbMatrix& matrix) const;

    /** Get inverse of current transformation matrix without
        translational part. If this object has no transformation,
        identity is returned.*/
    void getInverseTransformNoTranslation(SbMatrix& matrix) const;

    /// Copy value of transformation from other data object.
    void copyTransformFrom(const HxSpatialData* other);

    /** Translates the object by modifying its transformation matrix.
        The translation is applied in local coordinates (after the
        existing transformation) if the argument @c localCoords is 1,
        Otherwise it is applied in world coordinates (before the
        existing transformation). */
    void translate(const McVec3f& displacement, int localCoords=1);

    /** Rotates the object by modifying its transformation matrix.
        The rotation is applied in local coordinates (after the
        existing transformation) if the argument @c localCoords is 1,
        Otherwise it is applied in world coordinates (before the
        existing transformation). */
    void rotate(const SbRotation& rotation, int localCoords=1);

    /** Scales the object by modifying its transformation matrix.
        The scaling is applied in local coordinates (after the
        existing transformation) if the argument @c localCoords is 1,
        Otherwise it is applied in world coordinates (before the
        existing transformation). */
    void scale(const McVec3f& scaleFactor, int localCoords=1);

    // tcl command interface of the data object
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    /// Saves transformation in addition to HxData::savePorts.
    virtual void savePorts(FILE* fp);

    /// Saves transformation.
    void saveTransform(FILE* fp);

    /// This essentially copies the parameter bundle.
    void copyData(const HxSpatialData& other);

    /// Touch method.
    virtual void touch(unsigned int mask=0xffffffff);

    /** Invalidates cached minimal and maximal values. This method is provided here for
        convenience because many spatial data objects (although not all)
        contain data values for which min max values can be computed. */
    virtual void touchMinMax() { m_rawDataMin=1; m_rawDataMax=0;
                                 m_definedRawDataMin=1; m_definedRawDataMax=0;
                                 m_dataWindowMin=1; m_dataWindowMax=0;
                                 
                                 touch(); }

    typedef enum {
      RAW_DATA = 0,
      DEFINED_RAW_DATA,
      DATA_WINDOW,
      HISTOGRAM_DATA
    } RangeType;

    /** Returns min max data values. This method is provided here for
        convenience because many spatial data objects (although not all)
        contain data values for which min max values can be computed.
        Internally, minimum and maximum values are cached to avoid
        unnecessary recomputations. If the stored values have been invalidated
        by calling touchMinMax() the protected virtual method @c computeRange
        is called to perform the actual min-max calculation.
        If @c rangeType is set to @c RAW_DATA and if data range can be computed,
        returned values represent the raw data range.
        If @c rangeType is set to @c DEFINED_RAW_DATA and if data range can be computed,
        returned values represent the valid raw data range (excluding the undefined value).
        If undefined value hasn't been set, the raw data range is returned.
        If @c rangeType is set to @c DATA_WINDOW and if data contains a DataWindow parameter,
        returned values are the defined DataWindow. If no DataWindow is set,
        the defined raw data range is returned and if no undefined value has been set,
        the raw data range is returned.
        If @c rangeType is set to @c HISTOGRAM_DATA the data range is defined, so that
        99 % of all data values are greater than \c min and 99% of all data values are 
        less than \c max.      
    */
    virtual void getRange(float& min, float& max, RangeType rangeType=RAW_DATA);

    /** Returns the data's histogram. This method is provided here for
        convenience because many spatial data objects (although not all)
        contain data values for which a histogram could be computed. 
        Internally the histogram will be cached to avoid unnecessary histogram
        recomputations. Successive histogram computations with a number of bins
        \c numBins smaller than the maximum number of bins of previous histogram 
        computations use the larger cached histogram to compute the smaller result histogram.
        The histogram will only be recomputed if the number of bins \c numBins is 
        larger than the number of bins of all previous computed histograms. In addition
        the histogram will be invalidated if the data object has been touched and the 
        HxData::NEW_DATA flag has been set.
        
        @param  numBins Number of histogram bins.
        @return Resulting histogram. Might consist of less bins than specified by \c numBins.  
        
        Note: Currently only data objects of type HxRegScalarField3 are supported.
              For all other data objects a histogram with a size equal 0 will be 
              returned. 
    */
    virtual McHistogram getHistogram(int numBins=256);

  protected:
    // Constructor is protected - this is an abstract class
    HxSpatialData(McInterfaceOwner* owner = 0);

    // Virtual destructor
    virtual ~HxSpatialData();

    virtual void computeRange(float& min, float& max, bool discardUndefinedValues=false);

    virtual McHandle<McHistogram> computeHistogram(unsigned int numBins, McProgressInterface* progress);

    double m_undefinedValue;

    float   m_rawDataMin, m_rawDataMax;
    float   m_definedRawDataMin, m_definedRawDataMax;
    float   m_dataWindowMin, m_dataWindowMax;
    float   m_histogramDataMin, m_histogramDataMax;

    SoTransform* transform;
    SoNodeSensor* transformSensor;
    static void transformSensorCB(void* userdata, SoSensor*);
    virtual void transformSensorCallBack(SoSensor *sensor){};

    QxHistogramWorker* m_histogramWorker;
    friend class QxHistogramWorker;

    bool mHasTransform;
};

#endif

/// @}
