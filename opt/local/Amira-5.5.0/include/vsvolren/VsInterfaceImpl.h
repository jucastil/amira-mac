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
#ifndef _VS_INTERFACE_IMPL_H
#define _VS_INTERFACE_IMPL_H

#include "VsInterface.h"

#include <assert.h>
#include <stdio.h>


////////////////////////////////////////////////////////////////////////////////
#define VS_IMPLEMENTATION( C, B, I )                        \
                                                            \
    friend class I;                                         \
                                                            \
public:                                                     \
    static int * theObjectCounter()                         \
    {                                                       \
        static int counter = 0;                             \
        return &counter;                                    \
    }                                                       \
                                                            \
    C()                                                     \
    :   m        ( 0 )                                      \
    ,   _deleted ( 0 )                                      \
    ,   _created ( 0 )                                      \
    {                                                       \
        (*theObjectCounter())++;                            \
        /* fprintf(stderr, #C " created %d\n", *theObjectCounter());*/ \
    }                                                       \
                                                            \
    virtual ~C()                                            \
    {                                                       \
        (*theObjectCounter())--;                            \
        /*fprintf(stderr, #C " deleted %d\n", *theObjectCounter());*/ \
    }                                                       \
                                                            \
protected:                                                  \
             I * m;                                         \
private:                                                    \
    int _deleted:1;                                         \
    int _created:1;                                         \
                                                            \
private:                                                    \
    void onCreate();                                        \
    void onDelete();                                        \
                                                            \
protected:                                                  \
    virtual void propagateCreate()                          \
    {                                                       \
        if (!_created)                                      \
        {                                                   \
            _created = 1;                                   \
            B::propagateCreate();                           \
            m = dynamic_cast<I*>(VsInterfaceImpl::m);       \
            assert(m);                                      \
            onCreate();                                     \
        }                                                   \
    }                                                       \
    virtual void propagateDelete()                          \
    {                                                       \
        if (!_deleted)                                      \
        {                                                   \
            _deleted = 1;                                   \
            onDelete();                                     \
            B::propagateDelete();                           \
        }                                                   \
    }                                                       \


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
////////////////////////////////////////////////////////////////////////////////
#define VS_DEF_INTERFACE_IMPL_OLD( C, B, IMP )              \
C::C( bool inAlreadyHaveRelay )                             \
:   B       ( new IMP )                                     \
{                                                           \
    mImpl   = dynamic_cast<C##Impl*>(VsInterface::mImpl);   \
    assert(mImpl);                                          \
    mImpl->propagateCreate();                               \
                                                            \
    if ( !inAlreadyHaveRelay )                              \
        createRelay();                                      \
}                                                           \
C::C( C##Impl * inImpl )                                    \
:   B       ( inImpl )                                      \
{                                                           \
    mImpl   = dynamic_cast<C##Impl*>(VsInterface::mImpl);   \
}                                                           \
C::~C()                                                     \
{                                                           \
    mImpl->propagateDelete();                               \
}                                                           \
*/





#define VS_DEF_INTERFACE_IMPL( C, B, IMP )                  \
C::C( VsMeta * inMeta )                                     \
:   B ( VsMeta::init(inMeta).setImpl( (inMeta && inMeta->mImpl) ? 0 : new IMP ) )  \
{                                                           \
    mImpl = dynamic_cast<C##Impl*>(VsInterface::mImpl);     \
    assert(mImpl);                                          \
    mImpl->propagateCreate();                               \
                                                            \
    createRelay();                                          \
                                                            \
    if ( inMeta == 0 )                                      \
    {                                                       \
        if ( mMeta )                                        \
            delete mMeta;                                   \
        mMeta = 0;                                          \
    }                                                       \
}                                                           \
C::C( VsMeta & inMeta )                                     \
:   B ( inMeta )                                            \
{                                                           \
    mImpl   = dynamic_cast<C##Impl*>(VsInterface::mImpl);   \
}                                                           \
C::~C()                                                     \
{                                                           \
    mImpl->propagateDelete();                               \
}                                                           \




#define VS_DEF_INTERFACE_IMPL_NOREMOTIFY( C, B, IMP )       \
C::C( VsMeta * inMeta )                                     \
:   B ( VsMeta::init(inMeta, false).setImpl( (inMeta && inMeta->mImpl) ? 0 : new IMP ) )  \
{                                                           \
    mImpl = dynamic_cast<C##Impl*>(VsInterface::mImpl);     \
    assert(mImpl);                                          \
    mImpl->propagateCreate();                               \
                                                            \
    createRelay();                                          \
                                                            \
    if ( inMeta == 0 )                                      \
    {                                                       \
        if ( mMeta )                                        \
            delete mMeta;                                   \
        mMeta = 0;                                          \
    }                                                       \
}                                                           \
C::C( VsMeta & inMeta )                                     \
:   B ( inMeta )                                            \
{                                                           \
    mImpl   = dynamic_cast<C##Impl*>(VsInterface::mImpl);   \
}                                                           \
C::~C()                                                     \
{                                                           \
    mImpl->propagateDelete();                               \
}                                                           \






////////////////////////////////////////////////////////////////////////////////
#define VS_DEF_INTERFACE_FACTORY( C, B, IMP )               \
C::C##FactoryInit C::sFactoryInit;                          \


////////////////////////////////////////////////////////////////////////////////
#define VS_DEF_INTERFACE_RELAY( C, B, IMP )                         \
class C##Relay * C::r()                                             \
{                                                                   \
    return (C##Relay*)(mRelay);                                     \
}                                                                   \
                                                                    \
void C::createRelay()                                               \
{                                                                   \
    VsServer * s = theServer;                                       \
                                                                    \
    if (    s                                                       \
        &&  s->remoteObjectConstructionEnabled()                    \
        &&  mMeta                                                   \
        &&  mMeta->mRemotify                                        \
        &&  C##Relay::level() >= mMeta->mRelayCreationLevel         \
    )                                                               \
    {                                                               \
        assert( VsInterface::mRelay==0 );                           \
        mMeta->mRelayCreationLevel = C##Relay::level();             \
        VsInterface::mRelay = new C##Relay(this);                   \
                                                                    \
        if ( ! mMeta->mIsRemoteCopy )                               \
            s->createRemoteObject( #C, this );                      \
    }                                                               \
}                                                                   \



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
class VsInterfaceImpl
{
    VS_IMPLEMENTATION( VsInterfaceImpl, VsInterfaceImpl, VsInterface )
};


#endif


/// @}
