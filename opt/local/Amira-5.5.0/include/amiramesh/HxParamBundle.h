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
#ifndef HX_PARAM_BUNDLE_H
#define HX_PARAM_BUNDLE_H

#include <amiramesh/AmiraMeshWinDLLApi.h>

#include <stdio.h>
#include <mclib/McDArray.h>
#include <amiramesh/HxParamBase.h>
#include <amiramesh/HxParameter.h>

///@test GW: is this necessary or can we use HxShort?
#define HxBYTE          0x01
#define HxSHORT         0x02
#define HxUSHORT        0x02
#define HxINT32         0x04
#define HxFLOAT         0x08
#define HxDOUBLE        0x10
#define HxCOMPLEX       0x20
#define HxSTRING        0x40
#define HxINT64         0x80

/// This class maintains a set of parameters.
class AMIRAMESH_API HxParamBundle : public HxParamBase {

  public:
    /// Constructor.
    HxParamBundle(const char* name=0);

    /// Copy constructor. 
    HxParamBundle(const HxParamBundle& other);

    /// Destructor.
    ~HxParamBundle();
    
    /// Returns number of parameters stored.
    int size() const { return contents.size(); }

    /// Returns pointer to @c ith parameter.
    HxParamBase* operator[](int i) const { return contents[i]; }

    /**@name Insertion and removal */
    //@{

    /// Assignment operator.
    void operator=(const HxParamBundle& other);

    /// Inserts a parameter or a parameter bundle without copying.
    void insert(HxParamBase* param, int overwriteExisting=1);

    /// Copies parameter or contents of other bundle into this one.
    void copy(const HxParamBase& param);
    
    /// Special version of copy(), ignores NO_COPY flag.
    void copyAll(const HxParamBase& other);

    /// Move contents of another parameter set.
    void move(HxParamBundle& other);

    /// Removes given parameter or parameter bundle.
    void remove(HxParamBase* param, int noDelete=0);

    /// Removes given parameter or parameter bundle.
    void remove(const char* param, int noDelete=0);

    /// Removes all parameters and parameter bundles.
    void removeAll();

    /// Relocates contents of index at insertAt depending on the move direction
    void relocate(int index, int insertAt);

    //@}

    /**@name Find methods */
    //@{

    /// Returns the number of entries of type BUNDLE.
    int nBundles() const;

    /// Returns the i-th entry of type BUNDLE.
    HxParamBundle* bundle(int i) const;

    /// Looks for sub-bundle of given name, const version.
    const HxParamBundle* bundle(const char* name) const;

    /// Looks for sub-bundle of given name, creates it if requested.
    HxParamBundle* bundle(const char* name, int create=0);

    /// Short cut for @c bundle("Materials",create).
    HxParamBundle* materials(int create=1);

    /// Short cut for  @c bundle("BoundaryIds",create).
    HxParamBundle* boundaryIds(int create=1);

    /// Returns index of the given entry or -1 if entry isn't found.
    int index(HxParamBase* entry) const;

    /// Looks up matching entry (parameter or bundle).
    HxParamBase* findBase(const char* name) const;

    /// Looks for parameter of given name, dimension, and type.
    HxParameter* find(const char* name, int dim=0, int type=0xff) const;
    
    /// Gets value of string type parameter.
    int findString(const char* name, const char*& res) const;

    /// Gets value of scalar integer type parameter.
    int findNum(const char* name, int& res) const {
            return findNum(name, 1, &res); }

    /// Gets value of scalar integer (64bit) type parameter.
    int findNum(const char* name, long long& res) const {
            return findNum(name, 1, &res); }

    /// Gets value of scalar real parameter as float.
    int findReal(const char* name, float& res) const {
            return findReal(name, 1, &res); }

    /// Gets value of scalar real parameter as double.
    int findReal(const char* name, double& res) const {
            return findReal(name, 1, &res); }

    /// Gets value of multi-dimensional integer parameter.
    int findNum(const char* name, int dim, int* res) const;

    /// Gets value of multi-dimensional integer (64bit) parameter.
    int findNum(const char* name, int dim, long long* res) const;

    /// Gets value of multi-dimensional real parameter as floats.
    int findReal(const char* name, int dim, float* res) const;

    /// Gets value of multi-dimensional real parameter as doubles.
    int findReal(const char* name, int dim, double* res) const;

    /// Looks for color parameter.
    int findColor(float rgb[3]) const;

    /// Looks for color parameter.
    int findColor(const char* name, float rgb[3]) const;

    //@}

    /**@name Set methods */
    //@{

    /// Sets string value.
    void set(const char* name, const char* str, int parse=0);

    /// Sets integer value.
    void set(const char* name, int val);

    /// Sets integer (64bit) value.
    void set(const char* name, long long val);

    /// Sets real value.
    void set(const char* name, double val);

    /// Sets multi-dimensional integer value.
    void set(const char* name, int dim, const int* values);

    /// Sets multi-dimensional integer (64bit) value.
    void set(const char* name, int dim, const long long* values);

    /// Sets multi-dimensional real value.
    void set(const char* name, int dim, const float* values);

    /// Sets multi-dimensional real value.
    void set(const char* name, int dim, const double* values);

    /// Sets color value.
    void setColor(const float rgb[3]);

    //@}

    /// Duplicates the parameter bundle.
    virtual HxParamBase* duplicate() const;

    /// Write parameter bundle to file.
    void print(FILE* fp, int indent=0, const char* aliasName=0) const;

    /// Write parameter bundle to string.
    void print(McString& out, int indent=0, const char* aliasName=0) const;

    /// Unsets the new mask of a bundle and of all children.
    void untouchAll(int mask=0x15);

#ifndef STANDALONE
    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
#endif

  protected:
    McDArray<HxParamBase*> contents;
    int mNumBundles;
};

#endif

/// @}
