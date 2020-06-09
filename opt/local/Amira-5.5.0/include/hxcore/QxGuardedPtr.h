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
#ifndef QX_GUARDED_PTR_H
#define QX_GUARDED_PTR_H

#include <hxcore/HxAmiraWinDLLApi.h>

class QObject;
class QxGuardedPtrPrivate;

//-----------------------------------------------------------------------------
// base class for QxGuardedPtr with non template-code.
// Qt dependencies are moved exclusively into the source file.
class HXCORE_API QxGuardedPtrBase
{
public:
  bool isNull() const { 
    return !getObject(); 
  }

protected:
  QxGuardedPtrBase();

  virtual ~QxGuardedPtrBase();

  void setObject(QObject* obj);
  QObject* getObject() const;

  bool operator==( const QxGuardedPtrBase &p ) const {
    return getObject() == p.getObject();
  }

  bool operator!=( const QxGuardedPtrBase& p ) const {
    return !( *this == p );
  }

  QxGuardedPtrPrivate* m_priv;
};

//-----------------------------------------------------------------------------
// Use this class to keep valid pointer to QObject.
// Once the object is deleted, this pointer is automatically reset to zero.
// This performs the same job than the Qt QGuardedPtr, except no Qt headers is included 
// to avoid Qt dependencies with main amiraDev headers (HxPort...).
template <class T>
class QxGuardedPtr : public QxGuardedPtrBase
{
public:
  QxGuardedPtr() {}

  QxGuardedPtr(T* o) {
    setObject((QObject*)o);
  }

  QxGuardedPtr(const QxGuardedPtr<T> &p) {
    setObject(p.getObject());
  }

  QxGuardedPtr<T> &operator=(const QxGuardedPtr<T> &p) {
    setObject(p.getObject());
    return *this;
  }

  QxGuardedPtr<T> &operator=(T* o) {
    setObject((QObject*)o);
    return *this;
  }

  T* operator->() const { return (T*)getObject(); }

  T& operator*() const { return *(T*)getObject(); }

  operator T*() const { return (T*)getObject(); }
};

#endif // QX_GUARDED_PTR_H

/// @}
