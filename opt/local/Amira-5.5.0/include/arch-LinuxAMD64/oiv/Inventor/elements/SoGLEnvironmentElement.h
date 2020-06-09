/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/*==============================================================================
 *   File        : SoGLEnvironmentElement.h
 *   Classes     : SoGLEnvironmentElement
 *   Author(s)   : N. DAGUISE
 *   Date        : 9 jan 2008
 *==============================================================================
 *
 * Description : Element that store the current environement in GL.
 *
 *============================================================================*/

                                                             /* include files */
#ifndef  _SO_GL_ENVIRONMENT_ELEMENT_
#define  _SO_GL_ENVIRONMENT_ELEMENT_

#include <Inventor/sys/port.h>
#include <Inventor/elements/SoEnvironmentElement.h>

/**
* @VSGEXT Stores the current environment in GL.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current environment in GL.
*
*   @SEE_ALSO
*   SoEnvironmentElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLEnvironmentElement : public SoEnvironmentElement {
  SO_ELEMENT_HEADER(SoGLEnvironmentElement) ;

 public:
  /**
  *  Overrides push() method to remember previous element's state so
  *  we can sometimes generate more efficient GL calls.
  */
  virtual void push(SoState *state) ;

  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void pop(SoState *state, const SoElement *prevTopElement) ;

 SoINTERNAL public:
  /** register in database */
  static void initClass() ;

  /** unregister from database */
  static void exitClass() ;

  /** Initializes element */
  virtual void init(SoState *state) ;

 protected:
  /** Sets the environemnt attributes in an instance. Has GL side effects. */
  virtual void setElt( float ambientIntensity, const SbColor &ambientColor,
                  const SbVec3f attenuation, FogType fogType, const
                  SbColor fogColor, float fogVisibility) ;

  /** Destructor */
  virtual ~SoGLEnvironmentElement() ;
  
 private:
  /**
   * We save the state to figure out if the hints were
   * copied from a parent element; if they were, then caches will have
   * to depend on that element because if it changes we have to have
   * a chance to change our decision about what GL calls to make.
   * If this is NULL, then there are no cache dependencies.
   */
  SoState *copiedFromParent ;

  /** Send environment to GL */
  void send() ;

  /** Computes fog density based on visibility */
  static float computeDensity(float visibility, SbBool squared);

} ;

#endif /* _SO_GL_ENVIRONMENT_ELEMENT_ */
