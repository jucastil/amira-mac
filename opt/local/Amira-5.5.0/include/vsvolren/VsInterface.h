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
#ifndef _VS_INTERFACE_H_
#define _VS_INTERFACE_H_


#include "VsVolrenAPI.h"
#include "Vs.h"
#include "VsHandable.h"

#include <mclib/McPrimType.h>


class VsInterfaceImpl;


////////////////////////////////////////////////////////////////////////////////
class VSVOLREN_API VsMeta
{
public:

    int                 mObjectId;
    VsInterface       * m;
    VsInterfaceImpl   * mImpl;
    bool                mIsRemoteCopy;
    bool                mRemotify;
    int                 mRelayCreationLevel;

public:

    VsMeta( bool inIsOnHeap = false, bool inRemotify = true );
   ~VsMeta();

    static VsMeta & init( VsMeta * inMeta, bool inRemotify = true );

    VsMeta & setImpl( VsInterfaceImpl * inImpl );
    VsMeta & raiseRelayCreationLevel( int inLevel );
    VsMeta & setRemotify( bool inRemotify );
};


////////////////////////////////////////////////////////////////////////////////
#define VS_DECL_INTERFACE( C )                  \
private:                                        \
    C( const C& );                              \
    C & operator=( const C & );                 \
public:                                         \
    virtual char const * className()            \
    {                                           \
        return #C;                              \
    }                                           \


////////////////////////////////////////////////////////////////////////////////
#define VS_DECL_INTERFACE_IMPL_OLD( C )         \
    friend class C##Impl;                       \
public:                                         \
    C( bool inAlreadyHaveRelay = false );       \
protected:                                      \
    virtual ~C();                               \
    C( class C##Impl * );                       \
public:                                         \
    class C##Impl * mImpl;                      \


#define VS_DECL_INTERFACE_IMPL( C )             \
    friend class C##Impl;                       \
public:                                         \
    C( VsMeta * inMeta = 0 );                   \
protected:                                      \
    C( VsMeta & inMeta );                       \
    virtual ~C();                               \
public:                                         \
    class C##Impl * mImpl;                      \


////////////////////////////////////////////////////////////////////////////////
#define VS_DECL_INTERFACE_FACTORY( C )          \
public:                                         \
    static VsInterface * factory(  class VsMeta & inMeta ) \
    {                                           \
        return new C( &inMeta );                \
    }                                           \
                                                \
    virtual INTERFACEFACTORYFUNC myFactory()    \
    {                                           \
        return C::factory;                      \
    }                                           \
                                                \
    class C##FactoryInit                        \
    {                                           \
    public:                                     \
        C##FactoryInit()                        \
        {                                       \
            Vs::registerClass( #C, C::factory );\
        }                                       \
    };                                          \
                                                \
    static C##FactoryInit sFactoryInit;         \


////////////////////////////////////////////////////////////////////////////////
#define VS_DECL_INTERFACE_RELAY( C )            \
public:                                         \
    class C##Relay * r();                       \
    virtual void createRelay();                 \



////////////////////////////////////////////////////////////////////////////////

#ifdef HIDDEN_FROM_DOC

/** This is the base class for classes that are provided by the library.

    Interface classes follow the PIMPL idiom by not providing
    any real implementations but instead routing all function calls to an
    implementation class the pointer to which is stored inside the 
    VsInterface object. With this mechanism it is possible to enhance
    the classes (internally) without breaking interface or binary compatibility.
    Customer classes may subclass any interface class as usual. 
*/

#else

/** This is the base class for classes that are provided by the library.

    The interface classes never have member variables (except a single pointer).
    Instead, there is an implementation class hidden by the library holding
    all data and methods needed to provide the functionality the interface
    specifies. Invocations of interface methods are routed to internal
    methods of the implementation class.

    In order to implement this, each subclass that is provided by the library
    includes the VS_INTERFACE macro in its definition.

    With this mechanism it's possible to enhance the internal implementation by including
    new methods, even virtual ones, and to introduce new member variables without changing
    the binary interface of the library's external interface.

    Client applications may benefit from the enhanced library without the need of
    recompilation.

    Customer classes may subclass any interface class as usual. There is no need to 
    insert the VS_INTERFACE macro. It is for library classes only.
*/
#endif

class VSVOLREN_API VsInterface
:   virtual public VsHandable
{
    VS_DECL_INTERFACE     ( VsInterface )
    VS_DECL_INTERFACE_IMPL( VsInterface )


    ////////////////////////////////////////
    //  remotification mechanism
    ////////////////////////////////////////

public:

    // For remotified instances, this key sould be unique over
    // local and remote process space.
    // For non-remotified instances this key remains 0.
    int         mRemotificationId;

    VsRelay   * mRelay;
    VsMeta    * mMeta;
                          
    int         mSyncCallDepth;

public:

    VsRelay * relay()
    {
        return mRelay;
    }

    virtual void createRelay()
    {
    }




    ////////////////////////////////////////
    //  process unique key
    ////////////////////////////////////////

private:

    // key that is unique for each instance inside the process
    mcint64     mUniqueId;

    // index of the instance inside the instance list
    mclong      mIndexInInstanceList;

public:
    
    // retrieve the unique ID
    mcint64 const & uniqueId() const
    {
        return mUniqueId;
    }

    // precache this object to accelerate the first call to uniqueIdGetVsHandable().
    // the calls to uniqueIdGetVsHandable() following the first one are fast anyway.
    void uniqueIdPrecache();


    ////////////////////////////////////////
    //  debugging
    ////////////////////////////////////////
public:

    // dump the instance list
    static void dumpInstanceList();


    ////////////////////////////////////////
    //  internal only 
    //      never use outside
    //      subject to be removed from API
    ////////////////////////////////////////
public:

    static VsInterface * instanceCacheLookup( mcint64 inUniqueId );
};


// fill a given McHandle with a reference to the instance having the given uniqueID.
template <class T>
void uniqueIdToVsHandable( mcint64 inUniqueId, McHandle<T> & ioHandle )
{
    ioHandle = 0;

    VsInterface * refedObject = VsInterface::instanceCacheLookup( inUniqueId );

    if ( refedObject==0 )
        return;

    ioHandle = dynamic_cast<T*>( refedObject );

    refedObject->unref();
}


#endif

/// @}
