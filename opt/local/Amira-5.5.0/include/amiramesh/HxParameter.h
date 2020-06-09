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

/// @addtogroup amiramesh amiramesh
/// @{
#ifndef HX_PARAMETER_H
#define HX_PARAMETER_H

#include <amiramesh/AmiraMeshWinDLLApi.h>

#ifndef STANDALONE
    #include <tcl.h>
#endif

#include <stdio.h>
#include <mclib/McString.h>
#include <mclib/McPrimType.h>
#include <amiramesh/HxParamBase.h>

/// Multi-dimensional parameter of arbitrary type.
class AMIRAMESH_API HxParameter : public HxParamBase
{
  public:
    /**@name Construction */
    //@{

    /// Copy constructor.
    HxParameter(const HxParameter& other);

    /** Creates a parameter from string. If parse is 0, a string type
        parameter is created, otherwise the string will be parsed in
        order to determine whether it contain a list of integer or real
        values. */
    HxParameter(const char* name, const char* str, int parse = 0);

    /// Creates integer parameter.
    HxParameter(const char* name, int val);

    /// Creates integer (64bit) parameter.
    HxParameter(const char* name, long long val);

    /// Creates real parameter.
    HxParameter(const char* name, double val);

    /// Creates multi-dimensional integer parameter.
    HxParameter(const char* name, int dim, const int* values);

    /// Creates multi-dimensional integer (64bit) parameter.
    HxParameter(const char* name, int dim, const long long* values);

    /// Creates multi-dimensional real parameter.
    HxParameter(const char* name, int dim, const float* values);

    /// Creates multi-dimensional real parameter.
    HxParameter(const char* name, int dim, const double* values);

    /// Low-level constructor, directly uses dataPtr if it isn't null.
    HxParameter(const char* name, int dim, McPrimType t, void* dataPtr=NULL);

    //@}

    /**@name Data access */
    //@{

    /// Returns string value.
    const char* getString() const;

    /// Returns parameter value as integer.
    int getNum(int n=0) const;

    /// Returns parameter value as integer (64bit).
    long long getNumLong(int n=0) const;

    /// Returns parameter value as double.
    double getReal(int n=0) const;

    /// Returns multi-dimensional integer.
    void getNum(int* values) const;

    /// Returns multi-dimensional integer (64bit).
    void getNum(long long* values) const;

    /// Returns multi-dimensional double.
    void getReal(double* values) const;

    //@}

    /**@name Set methods */
    //@{

    /// Sets string value.
    void set(const char* str, int parse=0);

    /// Sets integer value.
    void set(int val) { set(1, &val); }

    /// Sets integer (64bit) value.
    void set(long long val) { set(1, &val); }

    /// Sets real value.
    void set(double val) { set(1, &val); }

    /// Sets multi-dimensional integer value.
    void set(int dim, const int* values);

    /// Sets multi-dimensional integer value.
    void set(int dim, const long long* values);

    /// Sets multi-dimensional real value.
    void set(int dim, const float* values);

    /// Sets multi-dimensional real value.
    void set(int dim, const double* values);

    //@}

    /**@name Other */
    //@{

    /// Returns dimensionality.
    int dim() const { return theDim; }

    /// Returns primitive data type.
    McPrimType primType() const { return thePrimType; }

    /// Returns pointer to actual data.
    void* dataPtr() const { return theDataPtr; }

    /// Assignment operator.
    HxParameter& operator=(const HxParameter& other);

    /// Comparison operator.
    int operator==(const HxParameter& other);

    /// Write parameter values into string (without name).
    void print(McString& str) const;

    /// Read parameter values from string.
    int parse(const char* text);

    /// Destructor.
    virtual ~HxParameter();

    /// Duplicates the parameter.
    virtual HxParamBase* duplicate() const;

#ifndef STANDALONE
    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
#endif

    //@}

  protected:
    int isEqual(int dim, McPrimType, const void* ptr);

    int theDim;
    McPrimType thePrimType;
    void* theDataPtr;
};

#endif

/// @}
