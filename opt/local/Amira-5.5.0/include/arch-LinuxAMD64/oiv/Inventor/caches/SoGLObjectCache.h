/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_GL_OBJECT_CACHE_H_
#define _SO_GL_OBJECT_CACHE_H_

#include <Inventor/SbBasic.h>
#include <Inventor/caches/SoContextedObjectCache.h>
#include <Inventor/oglObjects/SoGLDisplayList.h>

class SoGLDisplayList;
class SbThreadMutex;
class SoState;

/**
 * This class cache a OpenGL object for each contexts.
 */
class INVENTOR_API SoGLObjectCache : public SoContextedObjectCache<SoGLDisplayList>
{
public:
  SoGLObjectCache(SoGLDisplayList::Type type, bool sharable = true, int numToAllocate = 1)
    : SoContextedObjectCache<SoGLDisplayList>(sharable)
  {
    m_type = type;
    m_numToAllocate = numToAllocate;
  }

protected:
  virtual SoGLDisplayList* createObject( SoState *state )
  {
    SoGLDisplayList* obj = new SoGLDisplayList(state, m_type, m_numToAllocate);
    return obj;
  }

  /**
   * Destructor.
   */
  virtual ~SoGLObjectCache() {};

private:
   SoGLDisplayList::Type m_type;
   int m_numToAllocate;
};

#endif // _SO_GL_OBJECT_CACHE_H_
