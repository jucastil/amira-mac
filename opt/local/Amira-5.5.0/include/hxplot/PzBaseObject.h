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

/// @addtogroup hxplot hxplot
/// @{
#ifndef PZ_BASEOBJECT
#define PZ_BASEOBJECT

#include <hxplot/PzPlotWinDLLApi.h>

// #include <X11/Intrinsic.h>
#include <mclib/McHandable.h>

#include <hxplot/PzInterpreter.h>

// defined somewhere else
extern int convertToFloat(float **vals, int ac, char **av, int minalloc = -1);
extern int convertToInt  (int   **vals, int ac, char **av, int minalloc = -1);


#define PzUNDEFOBJ     -1
#define PzPLOTGROUP     0
#define PzDRAWAREA      1
#define PzLEGEND        2
#define PzCURVE         3
#define PzAXIS          4
#define PzMARKERLINE    5
#define PzANNOTATION    6
#define PzGRID          7
#define PzPOLARAXIS     8
#define PzCHART         9
#define PzERRORBAR     10
#define PzPLOTDATA     11
#define PzTIMEAXIS     12
#define PzPLOTAREA     13
#define PzLATTICE      14
#define PzTERNARYAXIS  15
#define PzCOLORMAP     16
#define PzANCURVE      17
#define PzSCATTER      18
#define PzSPECTRUM     19


class PzPlotGroup;
class HxParameter;
class HxParamBundle;


/**
   @brief Base class for all objects of Amira's plot package/tool.

   The following types of plot objects are defined by now:

   - PzUNDEFOBJ     -1
   - PzPLOTGROUP     0
   - PzDRAWAREA      1
   - PzLEGEND        2
   - PzCURVE         3
   - PzAXIS          4
   - PzMARKERLINE    5
   - PzANNOTATION    6
   - PzGRID          7
   - PzPOLARAXIS     8
   - PzCHART         9 (not yet implemented, for pie- and barcharts)
   - PzERRORBAR     10
   - PzPLOTDATA     11
   - PzTIMEAXIS     12
   - PzPLOTAREA     13
   - PzLATTICE      14
   - PzTERNARYAXIS  15 (not yet implemented)
   - PzCOLORMAP     16
   - PzANCURVE      17
   - PzSCATTER      18
   - PzSPECTRUM     19 (not yet implemented, for colourcoded 2d data)

   This class keeps and manages the permission which kinds of manipulations
   are allowed for an instance of this class. See enumeration
   PzBaseObject::PzObjectPermission and methods PzBaseObject::setPermission, 
   PzBaseObject::getPermission, PzBaseObject::addPermission,
   PzBaseObject::remPermission, and PzBaseObject::hasPermissionTo below.

   PzBaseObject provides a mechanism to get and set attributes. These
   attributes consist of a key-value pair. See PzBaseObject::getAttr and
   PzBaseObject::setAttr below. The attributes itself are defined and
   (partially) documented in the derived classes.


@author Olaf Paetsch
*/


class HXPLOT_API PzBaseObject: public McHandable {

  public:

    /** The permission flags specify what can be done with this object.
        They can be combined with logical operators.
    */
    enum PzObjectPermission {
            /** if set the permission of this object can be set by means of
                Tcl-commands
            */
            PzCHANGEPERMISSION =  1,
            /// object can be deleted if set
            PzDELETE =            2,
            /// attributes of object can be changed with the object editor
            PzCHANGE =            4,
            /// object can be edited in the object editor
            PzEDIT =              8,
            /// allows interaction in the plot window with object (if possible)
            PzINTERACTION =      16
    };

  private:

    HxParamBundle *theAttributes;

    HxParamBundle* getTheAttributes() { return theAttributes; }

    void showAttr(Tcl_Interp* t, HxParameter *attr);

    void processAttr(HxParameter *attr, int num, char **string);

    void initDefaults();

  protected:

    char*              theName;
    int                theType;
    bool               selected;
    bool               inUse;
    bool               isNew;
    int                thePermission;
    PzBaseObject*      theParent;
    PzBaseObject*      theChild;
    int                hasTclCmd;


    /// Constructor
    PzBaseObject(const char* name, const int type);

    /// Destructor
    ~PzBaseObject();

    /** Defines a new integer attribute (key-value pair) @p name with the
        initial (default) value @p value.
    */
    void initAttr(const char *name, int value);

    /** Defines a new float attribute (key-value pair) @p name with the
        initial (default) value @p value.
    */
    void initAttr(const char *name, float value);

    /** Defines a new attribute @p name with a float array of length @p n
        with the initial (default) values @p values.
    */
    void initAttr(const char *name, int n, float *values);

    /** Removes an attribute @p.
        Returns false if not found.
    */
    bool remAttr(const char *name);

    /** Inhibits further setting of values of attribute @p.
        Locked attributes are not saved.
        Returns false if not found.
    */
    bool lockAttr(const char *name);

    // Interface to Tcl scripting language.
    static int staticParse(ClientData, Tcl_Interp*, int, char**);

  public:

    virtual const char* className() = 0;

    static const char* className2(int typenum);

    /** Saves the state of the object as Tcl-commands. Derived classes
        should call this method as well together with saving their
        specific state. This method saves the state of all attributes
        defined with PzBaseObject::initAttr.
    */
    virtual void save(FILE *fp, char* globalName);

    /// Copies plot object.
    virtual PzBaseObject *copy();

    /// Returns if object is selected (e.g. by an editor).
    bool isSelected() { return selected; }

    /// Sets the selection flag.
    void setSelect(bool select = true) { selected = select; }

    /** Sets the permissions.
        Possible permissions are defined in PzBaseObject::PzObjectPermission.
    */
    void setPermission(int permission) { thePermission = permission; }

    /** Adds a permission
        Possible permissions are defined in PzBaseObject::PzObjectPermission.
    */
    void addPermission(int permission) { thePermission |= permission; }

    /** Removes a permission
        Possible permissions are defined in PzBaseObject::PzObjectPermission.
    */
    void remPermission(int permission);

    /** Returns the permission.
        Possible permissions are defined in PzBaseObject::PzObjectPermission.
    */
    int getPermission() { return thePermission; }

    /** Returns if an object has (a) specific permission(s)
        Possible permissions are defined in PzBaseObject::PzObjectPermission.
    */
    bool hasPermissionTo(int permissionmask)
                        { return (thePermission & permissionmask) > 0; }

    /// Returns reference count.
    int getRefCount() { return refcount; }

    /// Returns object's name.
    const char* getName() { return theName; }

    /// Returns object's type.
    int getType() const { return theType; }

    /// Static object type.
    static int getTypeId() { return PzUNDEFOBJ; }

    /// Returns object's parent.
    PzBaseObject* getParent() const { return theParent; }

    /// Returns the child object if any.
    PzBaseObject* getChild() const { return theChild; }

    /// Sets object's name.
    virtual void setName(const char* name);

    ///
    virtual bool isGraphicsObject() { return false; }

    ///
    virtual bool hasData() { return false; }

    /// Turns the rendering of object on or off.
    void setUsage(bool useit = true) { inUse = useit; }

    ///
    bool toBeUsed() { return inUse; }

    /// Returns new flag.
    virtual bool touched() { return isNew; }

    /// Sets new flag.
    virtual void touch() { isNew = true; }

    /// Resets new flag.
    virtual void untouch();

    /// Tcl command interface of the object
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Sets all attributes according to @p fromObj
    virtual bool setAllAttr(PzBaseObject* fromObj);

    /** Sets an integer value with key @p name.
        Returns false if not previously initialized by @c initAttr.
    */
    bool setAttr(const char* name, int value);

    /** Sets a float value with key @p name.
        Returns false if not previously initialized by @c initAttr.
    */
    bool setAttr(const char* name, float value);

    /** Sets three float values with key @p name.
        Convenience method for colours.
        Returns false if not previously initialized by @c initAttr.
    */
    bool setAttr(const char* name, float r, float g, float b);

    /** Sets a float array with key @p name.
        Returns false if not previously initialized by @c initAttr.
    */
    bool setAttr(const char* name, int n, float *values);

    /** Gets the integer value associated with key @p name.
        Returns false if not found.
    */
    bool getAttr(const char* name, int &value);

    /** Gets the float value associated with key @p name.
        Returns false if not found.
    */
    bool getAttr(const char* name, float &value);

    /** Gets the three float values (usually colours) associated with key
         @p name. Return false if not found.
    */
    bool getAttr(const char* name, float &r, float &g, float &b);

    /** Gets n float values associated with key @p name.
        Return false if not found.
    */
    bool getAttr(const char* name, int n, float *values);

    /// Returns number of attributes defined.
    int getNumAttr();

    /// Returns the name of attribute @p i.
    const char* getAttrName(int i);

    friend class PzPlotGroup;
    friend class PzBaseGroup;
};

#endif /* PZ_BASEOBJECT */

/// @}
