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

/// @addtogroup mclib mclib
/// @{
#ifndef MC_INTERFACE_OWNER_H
#define MC_INTERFACE_OWNER_H

#include "McWinDLLApi.h"
#include "McTypedObject.h"
#include "McDArray.h"
#include "McHandable.h"
#include "McHandle.h"

class McInterface;
class McTypeInfo;
class HxObject;

/** The primary object of a component handling memory and reference counting.

    Typically you should not derive from this class but from McInterface.
    In rare cases you might want to derive from this class to implement a custom 
    reference counting scheme (If you do this, you are on your own for now).
  */
class MCLIB_API McInterfaceOwner : public McTypedObject {
        MC_ABSTRACT_HEADER(McInterfaceOwner);

    public:
        enum MemoryPolicy {
              STATIC_IFACE
            , DELETE_IFACE
        };

        /** Search for an interface of type t.
          */
        McTypedObject* getInterface (const McTypeInfo* t) const;

        /** Clear and fill the array interfaces with all interfaces provided by this McInterfaceOwner.
          */
        void getAllInterfaces (McDArray<McTypedObject*>& interfaces) const;

        /** obj will be added to the list of handled objects.
            That is it will be referenced by this component,
            and will (if nothing else holds a ref to it)
            be destroyed if this component is destroyed.
          */
        void handleObject (McHandable* obj) {
            mHandledObjects.append (obj);
        }

        /** obj will be deleted on deletion of McInterfaceOwner.
          */
        void manageMemory (McTypedObject* obj) {
            mMemoryManagedObjects.append (obj);
        }

        /** Remove obj from the list of objects to be deleted upon deletion of McInterfaceOwner.
          */
        void dontManageMemory (McTypedObject* obj) {
            for (int i = 0; i < mMemoryManagedObjects.size(); i++) {
                if (mMemoryManagedObjects[i] == obj) {
                    mMemoryManagedObjects.remove(i);
                    break;
                }
            }
        }

        /** Attach an interface without handling memory by the McInterfaceOwner, i.e.
            the McTypedObject will not be deleted by the McInterfaceOwner.
            It is the responsible of the caller to handle memory and delete the interface.
            It is not possible to unregister interfaces. The caller MUST
            guarantee a life time of the registered object that is at least
            as long as the McInterfaceOwner. He MUST also guarantee that
            the interface is no longer used after deletion of the McInterfaceOwner.
          */
        void registerInterfaceStaticMemory (McTypedObject* iface);

        /** Attach an interface with memory handled by the McInterfaceOwner.
          */
        void registerInterfaceManageMemory (McTypedObject* iface) {
            registerInterfaceStaticMemory (iface);
            manageMemory (iface);
        }

        /** Attach an interface with indicated MemoryPolicy.
          */
        void registerInterface (McTypedObject* iface, MemoryPolicy mempolicy) {
            registerInterfaceStaticMemory (iface);
            if (mempolicy == DELETE_IFACE) {
                manageMemory (iface);
            }
        }

        /* You may derive from McInterfaceOwner to customize ref-counting. 
           You must stick to the protocol defined in McHandable,
           that is you must call notifyDelete() before actually
           deleting the object. 
         */
        virtual void ref () = 0;

        /** see ref().
         */
        virtual void unref () = 0;

    protected:
        McInterfaceOwner ();

        virtual ~McInterfaceOwner ();

        virtual void notifyDelete ();

    private:
        const McInterfaceOwner& operator= (const McInterfaceOwner&);
        McInterfaceOwner (const McInterfaceOwner&);

        typedef void (*attachInterfacesOnceCB_t) (void* userdat);

        /** This method is used by the amira kernel to set a callback,
            which is called once before interface lookup in getInterface().
            This allows the amira kernel to dynamically attach more interfaces
            during runtime. Do not use this method for other purposes.
          */
        void registerAttachInterfacesOnceCB (attachInterfacesOnceCB_t cb, void* userdat);

        friend class HxObject;
        McDArray<McTypedObject*> mInterfaces;
        McDArray<McHandle<McHandable> > mHandledObjects;
        McDArray<McTypedObject*> mMemoryManagedObjects;
        mutable attachInterfacesOnceCB_t mAttachInterfacesOnceCB;
        void* mAttachInterfacesOnceCBDat;

        void attachInterfacesOnce () const {
            if (mAttachInterfacesOnceCB) {
                attachInterfacesOnceCB_t cb = mAttachInterfacesOnceCB;
                mAttachInterfacesOnceCB = 0; // ensure call back is only called once to avoid recursion
                cb (mAttachInterfacesOnceCBDat);
            }
        }
};

template<class TYPE>
TYPE* mcinterface_cast (const McInterfaceOwner* component) {
    if (!component) return 0;
    return static_cast<TYPE*> (component->getInterface(TYPE::getClassTypeId()));
}

#endif

/// @}
