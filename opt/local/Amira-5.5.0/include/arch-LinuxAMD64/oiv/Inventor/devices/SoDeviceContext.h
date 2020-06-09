/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SODEVICECONTEXT_H
#define SODEVICECONTEXT_H

#include <Inventor/SbBase.h>
#include <Inventor/misc/SoRefCounter.h>
#include <Inventor/STL/set>
#include <Inventor/STL/list>
#include <Inventor/threads/SbThread.h>
#include <Inventor/threads/SbThreadMutex.h>
#include <Inventor/threads/SbThreadSpinlock.h>
#include <Inventor/devices/SoDeviceContextSharedGroup.h>

class SbThreadMutex;
class SoBaseContextCache;

/**
* @VSGEXT Abstract base device context managment class
*
* @ingroup Devices
*
* @DESCRIPTION
*
* This class provides generic functions to manage or to get data about specific device contexts.
*
*/

class INVENTORBASE_API SoDeviceContext : public SoRefCounter
{
public:

  /**
   * Default constructor.
   */
  SoDeviceContext();

  /**
   * Bind this context to the current thread.
   */
  virtual void bind() = 0;

  /**
   * Unbind this context from the current thread.
   */
  virtual void unbind() = 0;

  /**
   * Returns true if two contexts are compatible. @BR
   *
   * Compatible means that using a buffer from one of these contexts inside
   * the other will not require copying the data.
   */
  virtual bool isCompatible( SoDeviceContext* ) const = 0;

  /**
   * Returns true if the context is valid and currently active.
   */
  virtual bool isCurrent() const =0;

  /** Sets the sharable property. */
  void setSharable( bool sharable );

  /** Returns the sharable status of this context. By default, a context is sharable. */
  bool isSharable() const;

  /** Share this context. */
  virtual bool setSharedWith( SoDeviceContext* sourceCtx );

  /** Returns the current sharing state with passed context. */
  virtual bool isSharedWith( const SoDeviceContext* context ) const;

  /** Returns an id common to all compatible/shared contexts. */
  virtual int getSharedId() const;

  /** Returns the current shared group. */
  SoDeviceContextSharedGroup* getSharedGroup() const;

  /** Explicitly change the sharedGroup. */
  bool setSharedGroup(SoDeviceContextSharedGroup* sharedGroup);

SoINTERNAL public:

  virtual bool isValid() const;

  virtual SbString getInfos();

protected:
  /**
   * Destructor (use ref/unref to really delete).
   */
  virtual ~SoDeviceContext();

  /** Lock the context. */
  void lockContext();

  /** Unlock the context. */
  void unlockContext();
  
private:

  /** Context thread mutex. */
  SbThreadMutex m_mutex;

  /** Context shared group. */
  SoDeviceContextSharedGroup* m_sharedGroup;

  /** Sharable property. */
  bool m_isSharable;

};

#endif //#SODEVICECONTEXT_H

