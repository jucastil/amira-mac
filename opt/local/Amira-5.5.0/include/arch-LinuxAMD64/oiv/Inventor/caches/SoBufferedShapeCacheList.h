/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_BUFFERED_SHAPE_CACHE_LIST_H_
#define _SO_BUFFERED_SHAPE_CACHE_LIST_H_

#include <Inventor/devices/SoBaseContextObject.h>
#include <Inventor/caches/SoContextedObjectCache.h>
#include <Inventor/devices/SoGLBufferObject.h>
#include <Inventor/devices/SoGLContext.h>

SoINTERNAL class SoGLBufferedShapeCache : public SoBaseContextObject
{
public:
  SoGLBufferedShapeCache(SoState *)
    :SoBaseContextObject(SoGLContext::getCurrent()->getSharedGroup())
  {
    commonConstructor();
  }

  // Constructor
  SoGLBufferedShapeCache(SoGLContext *)
    :SoBaseContextObject(SoGLContext::getCurrent()->getSharedGroup())
  {
    commonConstructor();
  }

  void commonConstructor()
  {
    verticesBuffer = NULL;
    normalsBuffer = NULL;
    colorsBuffer = NULL;
    texCoordBuffer = NULL;
    indicesBuffer = NULL;
  }

  void checkVerticesBuffer(SoGLBufferObject::Usage expectedBufferUsage = SoGLBufferObject::DYNAMIC_DRAW)
  {
    checkBuffer(verticesBuffer, expectedBufferUsage, SoGLBufferObject::ARRAY_BUFFER);
  }

  void checkNormalsBuffer(SoGLBufferObject::Usage expectedBufferUsage = SoGLBufferObject::DYNAMIC_DRAW)
  {
    checkBuffer(normalsBuffer, expectedBufferUsage, SoGLBufferObject::ARRAY_BUFFER);
  }

  void checkColorsBuffer(SoGLBufferObject::Usage expectedBufferUsage = SoGLBufferObject::DYNAMIC_DRAW)
  {
    checkBuffer(colorsBuffer, expectedBufferUsage, SoGLBufferObject::ARRAY_BUFFER);
  }

  void checkTexCoordsBuffer(SoGLBufferObject::Usage expectedBufferUsage = SoGLBufferObject::DYNAMIC_DRAW)
  {
    checkBuffer(texCoordBuffer, expectedBufferUsage, SoGLBufferObject::ARRAY_BUFFER);
  }

  void checkIndicesBuffer(SoGLBufferObject::Usage expectedBufferUsage = SoGLBufferObject::DYNAMIC_DRAW)
  {
    checkBuffer(indicesBuffer, expectedBufferUsage, SoGLBufferObject::ELEMENT_ARRAY_BUFFER);
  }

  ~SoGLBufferedShapeCache()
  {
    delete verticesBuffer;
    delete normalsBuffer;
    delete colorsBuffer;
    delete texCoordBuffer;
    delete indicesBuffer;
  }

  // members
  SoGLBufferObject *verticesBuffer;
  SoGLBufferObject *normalsBuffer;
  SoGLBufferObject *colorsBuffer;
  SoGLBufferObject *texCoordBuffer;
  SoGLBufferObject *indicesBuffer;

private:

  static void checkBuffer(SoGLBufferObject*& buffer, SoGLBufferObject::Usage usage,
                   SoGLBufferObject::BufferObjectTarget target)
  {
    if (!buffer)
    {
      buffer = new SoGLBufferObject( usage );
      buffer->setTarget( target );
    }
  }

};

typedef SoContextedObjectCache<SoGLBufferedShapeCache> SoBufferedShapeCacheList;


#endif // _SO_BUFFERED_SHAPE_CACHE_LIST_H_

