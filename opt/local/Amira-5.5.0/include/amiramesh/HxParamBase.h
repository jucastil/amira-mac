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
#ifndef HX_PARAM_BASE_H
#define HX_PARAM_BASE_H

#ifndef STANDALONE
#include <tcl.h>
#endif

#include <stdio.h>
#include <amiramesh/AmiraMeshWinDLLApi.h>

class HxParamBundle;
class HxParamEditCheck;

/// Abstract base class for AmiraMesh parameters.
class AMIRAMESH_API HxParamBase
{
  public:

    /** Optional flags. Most flags are interpreted by Amira's parameter
        dialog as well as by the Tcl-command interface, but not by the
        methods of a parameter or a bundle. For example, you may still
        rename a parameter by calling @c setName() even if the NO_RENAME
        flag is set. */
    enum Flags {
	/** Prevents that a parameter or a bundle is written to file.
            The flag is interpreted in @c HxParamBundle::print().
            Typically, it will be set for parameters that are used
            internally, e.g. @c loadCmd or @c saveInfo. */
	NO_SAVE=1,

	/** Prevents that a parameter or a bundle is copied into another
            bundle. This may happen if the following methods of class
            HxParamBundle are called: the copy constructor, the
            assignment operator, or <tt>copy(const HxParamBundle&)</tt>. The
            flag is used to prevent that parameters like @c loadCmd are
            copied to a data object newly created by a computational
            module. */
	NO_COPY=2,

        /** Prevents that a parameter or a bundle is removed in Amira's
            parameter editor. This flag is used to prevent that
            the users remove materials from a LabelField or a TetraGrid.
            A bundle containing a parameter with the NO_DELETE flag set
            may still be removed from its parent bundle. You have to set
            the NO_DELETE flag for all parent bundles if you want to
            prevent this. */
        NO_DELETE=4,

        /** Prevents that a new bundle can be inserted into an existing
            bundle.*/
        NO_INSERT_BUNDLE=8,

        /** Prevents that a new parameter can be inserted into an
            existing bundle. */
        NO_INSERT_PARAM=16,

        /** Prevents changing the name of a parameter or a bundle. */
        NO_RENAME=32,

        /** Prevents that the value of a parameter is changed by one
            of HxParameter's or HxParamBundle's set methods. If set
            for a bundle the bundle may ot be replaced by another one
            with equal name using @c insert(). */
        NO_SETVALUE=64
    };

    /// Elements of the isNew()-mask.
    enum NewMask {
        /** Set if the name of a parameter or a bundle is changed
            using @c setName(). */
        NEW_NAME=1,

        /** Set if the value of a parameter is changed or if an element
            of a bundle is inserted or removed. */
        NEW_VALUE=2,

        /** Set in all parent bundles if a name of a parameter or a
            bundle is changed. */
        NEW_NAME_CHILD=4,

        /** Set in all parent bundles is the value of a parameter is
            changed or if an element of a bundle is inserted or
            removed. */
        NEW_VALUE_CHILD=8,

        /** Set if anything changed. Indicates that a bundle needs to
            be saved. */
        MODIFIED=16
    };

    /// Parameter types
    enum Type {
        /// Ordinary parameter
        PARAMETER=0,
        /// Bundle (contains other parameters and/or bundles)
        BUNDLE=1
    };

    /// Returns true if parameter is a bundle.
    int isBundle() const { return (theType==BUNDLE); }

    /// Returns parent bundle.
    HxParamBundle* parent() const { return theParent; }

    /// Returns name of parameter.
    const char* name() const { return theName; }

    /// Sets name of parameter.
    void setName(const char* name);

    /** Get the value of a given flag, e.g. flag(NO_SAVE). Multiple
        flags may be OR'ed to check whether at least one of these
        is set. 
     */
    int flag(int mask) const { return (theFlags & mask); }

    /** Set a flag on or off. Multiple flags may be OR'ed to set all
        of them on or off. */
    void setFlag(int mask, int onOff);

    /// Check if parameter changed since last call of untouchAll().
    int isNew(int mask=0xff) const { return (theNewMask & mask); }

    /** Sets new bits of a parameter or a bundle. If the mask
        contains NEW_NAME or NEW_VALUE, the parent bundles are
        automatically set to NEW_NAME_CHILD and NEW_VALUE_CHILD. */
    void touch(int mask=NEW_VALUE);

    /// Unsets the new mask of a parameter or a bundle.
    void untouch(int mask=15) { theNewMask &= ~(mask); }

    /** Returns pointer to edit checker. If this class does not
        itself provides an edit checker the checker of the class's
        parent bundle is returned. If there is no parent bundle a
        pointer to a default checker is returned. The default checker
        interpretes the NO_RENAME, NO_DELETE, NO_INSERT, and
        NO_SETVALUE flags of a parameter. */
    HxParamEditCheck* editCheck();

    /// Sets pointer to edit checker.
    void setEditCheck(HxParamEditCheck* editCheck);

    /// Duplicates this parameter.
    virtual HxParamBase* duplicate() const = 0;

#ifndef STANDALONE
    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
#endif

    /// Destructor.
    virtual ~HxParamBase();

  protected:
    // Protected, this is an abstract class.
    HxParamBase(Type type, const char* name);

    // Copy constructor
    HxParamBase(const HxParamBase& other);

    // Assignment operator
    HxParamBase& operator=(const HxParamBase& other);

    HxParamBundle* theParent;
    unsigned char theType;
    unsigned char theNewMask;
    unsigned short theFlags;
    char* theName; // Must be defined after theType
    HxParamEditCheck* theEditCheck;

  friend class HxParamBundle;
};

#endif

/// @}
