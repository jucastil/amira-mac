/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David BEILLOIN (MMM yyyy)
**=======================================================================*/


#ifndef SO_MEMORY_BUFFER_H
#define SO_MEMORY_BUFFER_H

#include <ScaleViz/SoScaleViz.h>

class SoMemoryObject;

SoEXTENDER class SCALEVIZ_API SoMemoryBuffer
{
public:

  /** Default constructor. */
  SoMemoryBuffer();

  /** constructor form a user memory area */
  SoMemoryBuffer( char* data,
                  const size_t size,
                  const size_t nbElement = 1,
                  char* externalPointer = NULL );

  /** Constructor: take a memory Object (including smart ref pointer) */
  SoMemoryBuffer(SoMemoryObject* memObj);

  /** Destructor */
  virtual ~SoMemoryBuffer();
  
  /** setup functions */
  void setSize( const size_t size, const size_t nbElement = 1 );

  /** Returns size in bytes */
  size_t getSize() const;

  /** Returns number of element */
  size_t getNbElement() const;

  /** Returns direct pointer to data */
  char* getPointer() const;

  /** Returns external pointer attached to this buffer */
  char* getExternalPointer() const;

private:
  // Size of the buffer 
  size_t m_size;
  size_t m_nbElement;

  // Pointer on the current data
  char* m_data;
  
  // Current internal byte size
  size_t m_ByteSize;

  // Indicate if the internal memory has been allocated outside by the user
  // in this case only the user can free the memory area
  bool m_externalAlloc;

  char* m_externalPointer;

  SoMemoryObject* m_memObj;
};

// INLINE METHODS
inline size_t
SoMemoryBuffer::getSize() const
{
  return ( m_size * m_nbElement );
}

inline size_t
SoMemoryBuffer::getNbElement() const
{
  return m_nbElement;
}

inline char*
SoMemoryBuffer::getPointer() const
{
  return m_data;
}

inline char*
SoMemoryBuffer::getExternalPointer() const
{
  return m_externalPointer;
}

#endif // SO_MEMORY_BUFFER_H

/**/
