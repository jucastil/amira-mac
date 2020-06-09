/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David BEILLOIN (MMM yyyy)
**=======================================================================*/


#ifndef SOMEMORYBUFFER2D_H
#define SOMEMORYBUFFER2D_H

#include <ScaleViz/misc/SoMemoryBuffer.h>
#include <Inventor/SbVec.h>

SoEXTENDER class SCALEVIZ_API SoMemoryBuffer2D : public SoMemoryBuffer
{
public:
  /** constructor */
  SoMemoryBuffer2D();
  
  /** setup function */
  void setSize( const unsigned short width, const unsigned short height, const size_t nbElement );

  /** setup function */
  void setSize( const SbVec2s& size, const size_t nbElement );

  /** Returns width */
  unsigned short getWidth() const;

  /** Returns height */
  unsigned short getHeight() const;

  /** Returns 2D size */
  SbVec2s getSize2D() const;

private:
  // size of the buffer 
  unsigned short m_width;
  unsigned short m_height; 
};

// INLINE METHODS
inline unsigned short
SoMemoryBuffer2D::getWidth() const
{
  return m_width;
}

inline unsigned short
SoMemoryBuffer2D::getHeight() const
{
  return m_height;
}

inline SbVec2s
SoMemoryBuffer2D::getSize2D() const
{
  return SbVec2s( m_width, m_height );
}

#endif // SOMEMORYBUFFER2D_H

