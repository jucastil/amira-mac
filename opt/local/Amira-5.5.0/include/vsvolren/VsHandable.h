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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VS_HANDABLE_H_
#define _VS_HANDABLE_H_

#include "VsVolrenAPI.h"

/** Base class for reference counted objects.

    If a single object or more precisely a pointer to a single object
    is used at multiple locations in a program there should be some
    way to detect if the object is still in use or if it can be destroyed.
    Reference counting as implemented by this class provides such a way.
    Manual reference counting means that the user has to call the methods
    \c ref() and \c unref() whenever he wants to use or discard an object.
    These methods increment or decrement an internal reference count
    variable. The object is destroyed automatically if this variable
    gets zero, i.e. the object isn't in use anymore.

    The related class McHandle implements smart pointers to
    reference counted objects. Such pointers automatically keep track of
    reference counting and therefore are safer than explicit use of \c ref()
    and \c unref().
    \see McHandle
*/
class VSVOLREN_API VsHandable
{
public:

    /** Adds a reference to an instance.
        This method is thread safe.
    */
    void ref();

    /** Removes a reference from an instance.
        This method removes a reference from the object. If the reference
        count gets zero the object is automatically destroyed.
        This method is thread safe.
    */
    void unref();

    /** Removes a reference but doesn't destroy object.
        This method is thread safe.
    */
    void unrefNoDelete();


    int refCount() { return mRefCount; }


    /** Pauses any VsHandable referencing operations performed by other threads.
        Be careful to prevent deadlocks.
        Always call operationResume() as soon as possible.
    */
    static void operationPause();

    /** Resumes the paused VsHandable subsystem.
        Has to be performed in the same thread as the matching call to operationPause().
        Be careful to prevent deadlocks.
    */
    static void operationResume();


    /** Query if the instance is being deleted after ref count reached zero.
        Usecases
            -   when subclasses query their own state to detect if code is 
                executed during object destruction
            -   between operationPause() and operationResume(), to check if an object is destructing
                make sure that the object is still in memory while calling this method
    */
    bool isZombie();


protected:

    /** Constructor.
    */
    VsHandable();

    /** Copy constructor; explictly DOES NOT copy the refcount
        \param inHandable copied object
    */
    VsHandable( const VsHandable & inHandable );

    /** Destructor is protected. Use unref() instead.
    */
    virtual ~VsHandable();

    /** Assignment operator; explictly DOES NOT copy the refcount
    */
    VsHandable & operator=(const VsHandable &) { return * this; }

    /** Will be called just before the object is deleted. You might
        want to override the method to detach objects or
        do some other cleanup which needs to be done.
        Some cleanup can't be deferred to the destructor because all
        the derived stuff is already gone.
    */
    virtual void notifyDelete();


protected:

    // Reference count.
    int mRefCount;

    // True if this object is scheduled for deletion after its refcout run to zero.
    bool mZombie;
};


#ifndef HIDDEN_FROM_DOC

class VsRefNoDelete
{
public:
    VsRefNoDelete( VsHandable * inHandable ) : mHandable ( inHandable ) {
        if (mHandable)
            mHandable->ref(); 
    }

    ~VsRefNoDelete() { 
        if (mHandable)
            mHandable->unrefNoDelete();
    }

protected:
    VsHandable * mHandable;
};

#endif // HIDDEN_FROM_DOC


#define VS_HANDABLE_REF2(N,X)        McHandle<VsHandable> N                          ((VsHandable*)X);
#define VS_HANDABLE_REF(X)           McHandle<VsHandable> _vs_handable_ref_          ((VsHandable*)X);
#define VS_HANDABLE_REF_NO_DELETE(X) VsRefNoDelete        _vs_handable_ref_no_delete_((VsHandable*)X);

#endif


/// @}
