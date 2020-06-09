/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R.ALBOU (Jan 2004)
** Modified    : David Beilloin (Jan 2010)
**=======================================================================*/

#ifndef _SO_VBO_CACHE_
#define _SO_VBO_CACHE_

#include <Inventor/SbBasic.h>

class SoVertexShape ;
class SoVertexProperty ;
class SoNodeSensor ;
class SoCache ;
class SoGLLazyElement ;

/*----------------------------------------------------------------------------*/

SoINTERNAL class SoVBOCache {
public:
  /** Constructor. */
  SoVBOCache(SoState* state, SoVertexShape *vertexShape) ;
  
  /** Destructor. */
  ~SoVBOCache() ;

  /** Check if current cache is validity and reset it if needed */
  void checkValidity(SoState *state, const int VBOFlag) ;
  
  /** Just here to work correctly in a SbThreadLocalStorage **/
  void unref();

  /** **/
  int getCurrentVBOUsage() const
  { return m_curVBOUsage; }

private:
  // SoVertexShape managed by this cache.
  SoVertexShape *m_vertexShape ;

  // Sensor attached to the shape to catch coordIndex and vp field changes
  SoNodeSensor *m_vertexShapeSensor ;
  static void vertexShapeChangedCB(void *data, SoSensor*) ;

  // Current VertexProperty.
  // indicate if we are in VP or in STATE mode
  SoVertexProperty *m_curVP ;

  int m_curVBOUsage;

  ////// IN VP MODE 
  // Sensor attached to vp to catch vp's field changes
  SoNodeSensor *m_vpFieldSensor ;
  static void vpChangedCB(void *data, SoSensor*) ;

  // Reset/delete current vertexProperty sensor
  void deleteVPMode() ;

  ////// IN STATE MODE 
  // inner class to manage all object needed for state mode
  class stateModeCaches
  {
  public:
    // constructor
    stateModeCaches();
    // destructor
    ~stateModeCaches();

    void checkValidity(SoState* state, SoVBOMgr* VBOMgr);

    // Caches
    SoCache         *m_vertexCache ;
    SoCache         *m_normalCache ;
    SoCache         *m_textureCache ;
    SoGLLazyElement *m_lazyInCache ;
  };
  stateModeCaches *m_stateModeCaches;
  void deleteStateMode() ;
  
} ;/*----------------------------------------------------------------------------*/

#endif // _SO_VBO_CACHE_
