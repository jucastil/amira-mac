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
#ifndef HXFIELD3
#define HXFIELD3

#include <hxfield/HxFieldWinDLLApi.h>

#include <mclib/McPrimType.h>
#include <hxcore/HxSpatialData.h>
#include <hxfield/HxLocation3.h>
#include <hxfield/HxLattice3.h>

class HxLattice3;

// Prototype for all native evaluation methods.
typedef int (*EvalNative)(void* userData, HxLocation3*, void*);

// Prototype for all cast-to-float evaluation methods.
typedef int (*EvalFloat)(void* userData, HxLocation3*, float*);

/** Generic field in 3D space.
    This class represent a generic field in @f$R^3@f$. In contrast to a
    discrete array a field may be evaluated at any point within a
    3D domain. Subclasses may choose to evaluate a functional expression
    or may interpolate values from a discrete grid. Transparent access
    to all the different field types is provided by the HxLocation3
    class. The eval() methods will return 1 on success and 0 if
    the field is not defined at the requested location.

    Dimensionalty of the field values can be queried by calling
    nDataVar(). Real valued scalar fields will return 1, real
    valued vector fields will return 3.

    Here is how the range is computed :

    */

class HXFIELD_API HxField3 : public HxSpatialData
{
  HX_DATA_HEADER(HxField3);

  public:
    /// Returns dimensionalty of field values.
    int nDataVar() const { return theNDataVar; }

    /// Returns primitive data type.
    McPrimType primType() const { return thePrimType; }

    /** Evaluates field at given location using the primitive type.
        A pointer to a general location class is used to evaluate the
        field at a particular location. An instance of the location
        class may only be created by the field itself. The user is
        responsible that the location class matches the field. No
        run-time consistency checks are performed.
        Return 0 if the data is equal to the undefined value at this location.
        Otherwise, return 1.
    */
    inline int evalNative(HxLocation3* loc, void* result) {
        return evalNativeFunc(evalNativeData, loc, result);
    }

    /** Evaluates field at given location. May involve cast to float.
        Return 0 if the data is equal to the undefined value at this location.
        Otherwise, return 1.
    */
    inline int eval(HxLocation3* loc, float result[]) {
        return evalFloatFunc(evalFloatData, loc, result);
    }

    /** Computes spatial derivative at given location
        The derivative of the <em> i</em>th field component to <em> x</em>,
        <em> y</em>, and <em> z</em> is stored in @c result[i][0], @c result[i][1],
        and @c result[i][2]. The standard method computes the derivative by
        taking finite differences. Derived methods may implement more
        appropriate algorithms. The location will not be moved.
    */
    virtual int derivative(HxLocation3* loc, float result[][3]);

    /** Creates location class for this field
        Creates an instance of a location class which can be used for this
        particular field. The location class should not be used with other
        fields. The user is responsible for deleting the location class.
    */
    virtual HxLocation3* createLocation();

    /// Invalidates cached minimal and maximal values.
    virtual void touchMinMax() { HxSpatialData::touchMinMax(); }

    /** Sets the stored minimal and maximal values. Call this function if you
        have modified the field and know the new min and max values. If the
        specified values do not match the actual min and max values of the
        field, unexpected results can occur. If the new range differs from the
        old one the NEW_RANGE bit of the touch mask is set.*/
    void touchMinMax(float min, float max, bool forRangeOfRawData=true);

    /// Creates a zero-field.
    HxField3(int nDataVar, McPrimType primType);

    /// Destructor. What about reference-counting ?
    ~HxField3();

    // Tcl-command interface.
    virtual int parse(Tcl_Interp* interpreter, int argc, char** argv);

    /// Duplicates the current HxField3 object
    virtual HxData *duplicate() const;

    /** Calculate the approximative data size in bytes within a 3D bounding box.
        data type is define in lattice object
        false is returned if could not be computed.
    */
    bool computeMemSize(mcuint64 &size, const McBox3f &box, const float* bbox, const HxLattice3* lattice);

  protected:
    const int   theNDataVar;
    McPrimType  thePrimType;
    void*       resultBuffer;

  public:
    EvalFloat   evalFloatFunc;
    void*       evalFloatData;
    EvalNative  evalNativeFunc;
    void*       evalNativeData;

  protected:
    /// Creates a zero-field.
    HxField3(McInterfaceOwner* owner, int nDataVar, McPrimType primType);

    /// Used by duplicate(); copies the needed data
    void copyData(const HxField3 &source);

    /** For scalar fields estimates of the minimal and maximal field
        components are returned.
        For vector fields estimates of minimal and
        maximal vector magnitudes are returned.
    */
    virtual void computeRange(float& min, float& max, bool discardUndefinedValues=false);

    /// Prints info about field.
    virtual void info();

    // These methods call evalFloatFrom() template method.
    static int evalFloatFromInt8  (HxField3*, HxLocation3*, float*);
    static int evalFloatFromUInt8 (HxField3*, HxLocation3*, float*);
    static int evalFloatFromInt16 (HxField3*, HxLocation3*, float*);
    static int evalFloatFromUInt16(HxField3*, HxLocation3*, float*);
    static int evalFloatFromInt32 (HxField3*, HxLocation3*, float*);
    static int evalFloatFromUInt32(HxField3*, HxLocation3*, float*);
    static int evalFloatFromDouble(HxField3*, HxLocation3*, float*);

    // These methods call evalNative() and make a cast to float.
    // In the complex case only the real part is returned.
    static int evalFloatFromFloat (HxField3*, HxLocation3*, float*);
    template<typename resultType> 
    static int evalFloatFrom(HxField3* f, HxLocation3* loc, float* res);

    // This method implements a zero field.
    static int evalNativeZero     (HxField3*, HxLocation3*, void*);

    friend class HxLattice3; // for clearing modifiedFlag in HxLattice::writeAmiraMesh()

private:
    void commonConstructor(int nDataVar, McPrimType primType);
};

#endif

/// @}
