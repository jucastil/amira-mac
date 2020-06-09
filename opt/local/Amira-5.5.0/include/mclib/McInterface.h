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
#ifndef MC_INTERFACE_H
#define MC_INTERFACE_H

#include "McWinDLLApi.h"
#include "McInterfaceOwner.h"

/**
    \example McInterface_example.cpp
   
    This example illustrates how to use McInterface.
*/

/** \brief Base class of all Interfaces.

    McInterface together with McInterfaceOwner implement the basis of a component model.
    You can write classes exhibiting the same behaviour through an interfaces without using direct inheritance.

    A standard way of writing object factories is not yet specified.

    An interface provides two basic services.
        - reference counting through ref(), unref().
        - Interface discovery through getInterface().

    In addition, a convenience service for handling dynamically allocated objects is provided through
    handleObject() and manageMemory().

    Each interface is owned by a McInterfaceOwner, which the interface is registered with upon creation.
    McInterface owner implements the details of handling interfaces, see McInterfaceOwner and there McInterfaceOwner::registerInterface().  

    See below in the list of examples for some a link to example interfaces and their implementation.

    Use the following guidelines
        - An interface is declared as an abstract base class MyInterface deriving from McInterface.
            - The public methods should be non-virtual, e.g. something(), and forward calls to private,
                 pure virtual methods, which are prefixed with 'do', e.g. doSomething(). This is the nonvirtual interface idiom, see http://www.gotw.ca/publications/mill18.htm .
            - Provide a single constructor with the same default arguments as McInterface::McInterface().
            - Use MC_ABSTRACT_HEADER/MC_INIT_ABSTRACT_CLASS 
        - Provide a template class named with the postfix 'Proxy', e.g. MyInterfaceProxy , which is derived from your interface and implements all pure virtual methods (the doSomething()'s) by forwarding to an implementation provided in its constructor.
            - The template MyInterfaceProxy should be friend of MyInterface. This needs a forward declaration as illustrated in the example.
            - You do not need any MC_... macros for the template.
        - Derive from McInterface and implement all doSomething() methods required by an interface and 
          attach your interface by one of the methods illustrated in the example:
            - Statically implement an interface as a member field; usually by instantiating MyInterfaceProxy.
            - Instantiate an interface by new; usually by instantiating MyInterfaceProxy.
              You may conditionally instantiate the interface depending on arguments passed to the constructor
              of your implementation.
            - Implement the interface by deriving directly from the interface class instead of McInterface.
            - EXPERIMENTAL: forward an interface to another component.
        - Provide TCL bindings for your interface (see below). 

    Note, few interfaces follow this guideline in August 2006. Good examples are rare. A major cleanup would be needed to improve this situation.

    A comparison to other component models may help to clarify some assumptions:
        - McInterfaceOwner implements interface handling and discovery, which cannot be overridden.
          Only reference counting may be overridden by deriving from McInterfaceOwner.
          Other component models require each component to provide an implementation for the 
          interface discovery. This gives more flexibility, which we don't need.
        - We assume that interfaces are light-weight. All interfaces are created upon object creation.
          Other component models defer interface creation until the interface is asked for.
        - Interfaces cannot be implemented using multiple-inheritance. The main reason is that
          multiple-inheritance is not supported by McTypeInfo.
        - We attach every interface to its owner upon creation. If no owner is given, a default owner is created. 
          This ensures valid objects right from their birth.
          Other frameworks might give more flexibility. For example HxInterface defers attaching until a call 
          to setOwner().

    You can attach TCL bindings to your interface by implementing HxTclWrapper::parse() in a class derived from HxTclWrapper.
    Declare your class in an .rc file by 

    \verbatim
    tclwrapper -class "HxTclWrapperMyInterface" -wraps "MyInterface" -package "mypackage" 
    \endverbatim

*/
class MCLIB_API McInterface : public McTypedObject {
        MC_ABSTRACT_HEADER(McInterface);
    public:
        /** Increase reference count on the owner.
          */
        void ref() {
            mOwner->ref();
        }

        /** Decrease reference count on the owner.
          */
        void unref () {
            mOwner->unref();
        }

        /** Hold a ref on obj until this's owner is deleted. 
          */
        void handleObject (McHandable* obj) {
            mOwner->handleObject (obj);
        }

        /** Delete obj upon deletetion of this's owner.
          */
        void manageMemory (McTypedObject* obj) {
            mOwner->manageMemory (obj);
        }

        /** Interface lookup (forwarded to this's owner).

            You must not call getInterface() on this in a destructor.
          */
        McTypedObject* getInterface (const McTypeInfo* t) const {
            return mOwner->getInterface (t);
        }

        /** Get a list of all interfaces (forwarded to this's owner).
          */
        void getAllInterfaces (McDArray<McTypedObject*>& interfaces) const {
            mOwner->getAllInterfaces (interfaces);
        }

        /** access the interface owner directly without 
            triggering the interface lookup mechanism.
            Note this also avoids dynamic creation of new interface.
         */
        McInterfaceOwner* getOwner () {
            return mOwner;
        }
    protected:
        /** Attach the instance to owner. If no owner is given, a default owner will be created.
            Mempolicy indicated wether the owner will delete this instance upon its deletion:
                - use McInterfaceOwner::DELETE_IFACE if deletion is requested.
                - use McInterfaceOwner::STATIC_IFACE to avoid deletion.
          */
        McInterface (McInterfaceOwner* owner = 0, McInterfaceOwner::MemoryPolicy mempolicy = McInterfaceOwner::DELETE_IFACE);

        ///
        virtual ~McInterface ();
    private:
        McInterface(const McInterface&);
        McInterface& operator=(const McInterface&);

        McInterfaceOwner* mOwner;

        friend class McInterfaceOwner;
};

template<class TYPE>
TYPE* mcinterface_cast (const McInterface* iface) {
    if (!iface) return 0;
    return static_cast<TYPE*> (iface->getInterface(TYPE::getClassTypeId()));
}

/** Use this macro to declare interface classes.  The macro includes the
    necessary McTypedObject macro and a default constructor that forwards owner
    and memory policy to the parent class. */
#define MC_INTERFACE(className) \
    MC_ABSTRACT_HEADER(className); \
  protected:\
    className(McInterfaceOwner* owner = 0 \
            , McInterfaceOwner::MemoryPolicy mempolicy = McInterfaceOwner::DELETE_IFACE) \
            : McInterface(owner, mempolicy) \
    {}

/** Use this macro to declare interface classes.  The macro includes the
    right McTypedObject macro. */
#define MC_INIT_INTERFACE(className,parentName) \
    MC_INIT_ABSTRACT_CLASS(className,parentName)

#endif

/// @}
