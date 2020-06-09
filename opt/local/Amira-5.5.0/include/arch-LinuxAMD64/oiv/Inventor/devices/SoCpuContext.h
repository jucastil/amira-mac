/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCPUCONTEXT_H
#define SOCPUCONTEXT_H

#include <Inventor/devices/SoDeviceContext.h>

class SoCpuDevice;

/**
* @VSGEXT CPU device context managment class
* 
* @ingroup CpuDevice
* 
* @DESCRIPTION
*
* This class provides functions to manage CPU device contexts.
*
*/ 

class INVENTORGL_API SoCpuContext : public SoDeviceContext
{

public:

  /**
   * Default constructor.
   *
   * @param device The SoCpuDevice on which to create the context.
   */
  SoCpuContext( SoCpuDevice* device = NULL);

  /**
   * Bind this context to the current thread.
   */
  virtual void bind();

  /**
   * Unbind this context from the current thread.
   */
  virtual void unbind();

  /**
   * Query if the specified context and this one are compatible. @BR
   *
   * Compatible means that using a buffer from one of these contexts inside 
   * the other will not require copying the data.
   * 
   * @return Returns true if the two contexts are compatible, false otherwise.
   */
  virtual bool isCompatible( SoDeviceContext* ) const;

  /**
   * Query if the context is valid and currently active.
   */
  virtual bool isCurrent() const { return true; }

  /**
   * Returns the currently bound context (if any) for the current thread.
   *
   * @return The current CPU context.
   */
  static SoCpuContext* getCurrent();

SoINTERNAL public:

  /** Initialize this class. */
  static void initClass();

  /** Finalize this class. */
  static void exitClass();

protected:
  /**
   * Destructor (used by ref/unref)
   */
  virtual ~SoCpuContext();

private:
  // context singleton always available on Host CPU device
  static SoCpuContext* s_globalContext;

SoINTERNAL public:

  virtual SbString getInfos();

};

#endif //SoCpuContext_H

