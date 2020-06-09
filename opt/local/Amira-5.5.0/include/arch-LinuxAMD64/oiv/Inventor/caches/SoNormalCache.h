/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_NORMAL_CACHE
#define  _SO_NORMAL_CACHE

#include <Inventor/SbLinear.h>
#include <Inventor/caches/SoCache.h>
#include <Inventor/elements/SoNormalBindingElement.h>

/**
 * Class SoNormalCache:
 *
 * A normal cache stores a list of normals.
 */
SoEXTENDER class INVENTOR_API SoNormalCache : public SoCache
{
 public:
  /** Constructor */
  SoNormalCache(SoState *state);

  /** Destructor */
  virtual ~SoNormalCache();

  /** Stores a list of normals in the cache
   * [OIV-WRAPPER-ARG NO_WRAP{(normals != NULL? normals->Length: 0)},ARRAY]
   */
  void set(int numNormals, const SbVec3f *normals, const SoNormalBindingElement::Binding normalBinding /*= SoNormalBindingElement::PER_VERTEX */);

  /** Returns the number of normals in the cache */
  int getNum() const
  { return numNormals; }

  /** Returns the list of normals in the cache
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetNum()}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE ARRAY{getNum()}]
   */
  const SbVec3f* getNormals() const
  { return normals; }

  /** Returns the normal binding in the cache */
  SoNormalBindingElement::Binding getNormalBinding() const
  { return normalBinding; }

SoINTERNAL public:
  inline uint32_t getTimeStamp()const
  { return m_timeStamp; }

  inline void setTimeStamp(const uint32_t timestamp)
  { m_timeStamp = timestamp; }


 private:
  int                 numNormals;                 // Number of normals
  const SbVec3f       *normals;                   // Array of normals
  SoNormalBindingElement::Binding normalBinding;  // normal binding
  uint32_t m_timeStamp;
};

#endif /* _SO_NORMAL_CACHE */
