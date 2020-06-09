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
#ifndef _HX_COMP_MODULE_
#define _HX_COMP_MODULE_

#include <hxcore/HxBatchModule.h>
#include <hxcore/HxData.h>
#include <mclib/McHandle.h>

class HxMasterConnection;

/** Base class for compute modules.
    Base class for compute modules like @c HxResample, @c HxArithmetic, or
    @c HxMagnitude. Compute modules take one or multiple input objects
    and compute one or multiple output objects of type HxData. The
    output objects should be registered by calling setResult().
    setResult connects the master connection of the data object
    to the compute module, so that the result is downstream with respect
    to the compute module. Multiple output objects can be registered
    by using an optional id when calling setResult(). Each id defines
    a so-called result slot. With each result slot a name can be
    associated by calling setNameOfResultSlot().

    Compute modules are colored indianred and are usually placed in the
    middle region of the object pool. Since this class is derived from
    HxBatchModule it is possible to submit a background thread using
    HxBatchModule::runBatch().

*/
class HXCORE_API HxCompModule : public HxBatchModule {

  HX_ABSTRACT_HEADER(HxCompModule);

  public:
    /** Associates a custom name with a result id. The name is used
        when connecting a data object to a compute module in a script
        or via the graphical user-interface. */
    void setNameOfResultSlot(int id, const char* name);

    /** Registers a data object as a result object. The method first
        adds the result to the object pool, if it was not already added
        before. It then connects the master connection of the data
        object to this module, thereby possibly disconnecting it from
        some other compute module or editor. It also touches the result
        using the specified mask and stores the result's touch time, so
        that it can be retrieved later on using getResultTouchTime.
        This is useful in order to decide whether a result can be
        recomputed later on. For details see HxObject::canCreateData.
        The result is associated with the specified @c id. If a new id
        is used a new result slot will be created on the fly. */
    void setResult(int id, HxData* result, unsigned int mask=0xffffffff);

    /** Registers a data object as the default result. The default result
        slot has id==0 and is created for every compute module. */
    void setResult(HxData* result, unsigned int mask=0xffffffff) {
        setResult(0, result, mask);
    }

    /** Registers a data object as a result object. A result slot with the
        given name @c name is used. The parameter @c name must not be 0. */
    void setResult(const char* name, HxData* result, unsigned int mask=0xffffffff);

    /** Returns the result object associated with the specified id. If
        no result object is connected to the specified result slot the
        method returns null. */
    HxData* getResult(int id=0) const;

    /** Returns the result object associated with the specified name. If
        no result object is connected to the specified result slot the
        method returns 0 */
    HxData* getResult(const char* name) const;

    /** Returns the touch time of a result slot. The touch time is set
        when registering a result using setResult(). Usually the
        touch time will only be evaluated in an overloaded implementation
        of HxObject::canCreateData. @see HxData::getTouchTime */
    int getTouchTime(int id=0) const;

    /** Checks if a data object can be used as a result. The method is
        called before a new result is actually connected to a compute
        module. For backward compatibility the default implementation
        simply returns 1, which means that any data object can be
        connected to the module. Derived classes may change this
        behaviour by overloading the method. If the result can not
        be used as a result for the slot specified by id but for some
        other slot, the check method may change the value of id and
        still return 1. */
    virtual int checkResult(int& id, HxData* result);

    /** This method is called after a new result is connected to the
        module. The id indicates which result slot has been modified. */
    virtual void resultChanged(int id);

    /** Custom fire method. The method simply calls the fire method of the
        parent class HxBatchModule. However, before it resets the
        variable @c resultTouchTime if at least one port is new. If the
        network is saved after a port has changed but before the results
        have been recomputed, an overloaded HxObject::canCreateData
        method should return false. Note, that the touch times of the
        individual result slots as returned by getTouchTime will
        not be reset by the fire method. */
    virtual void fire(int shouldCompute=1);

    /// Compute modules are indianred.
    virtual McColor getIconColor();

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    /// To get the number of result slots.
    int getNumResultSlots() const {return resultSlots.size();};

    /// Returns a free and valid result slot id.
    int getNewResultSlotID() const;


  protected:
    /// Constructor. Module may be connected to objects of given type.
    HxCompModule(const McTypeInfo* dataType, McInterfaceOwner* owner = 0);

    /// Destructor.
    virtual ~HxCompModule();

    /** Global touch time of the compute module. This time will be set
        whenever setResult() is called. It will be reset back to -1
        if any port has changed and fire is called. */
    int resultTouchTime;

    struct ResultSlot {
        int id;
        int touchTime;
        McString name;
        McHandle<HxData> result;
    };

    int blockNotify;
    McDArray<ResultSlot*> resultSlots;
    ResultSlot* findResultSlot(int id) const;
    ResultSlot* findResultSlotFromString(const char* str) const;
    static int slotCompare(ResultSlot* const&, ResultSlot* const&);

  friend class HxMasterConnection;
};

#endif

/// @}
