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



#ifndef  _SO_BOUNDING_BOX_CACHE
#define  _SO_BOUNDING_BOX_CACHE

#include <Inventor/SbBox.h>
#include <Inventor/caches/SoCache.h>

////////////////////////////////////////////////////////////////////////
//
//  Class SoBoundingBoxCache:
//
//  A bounding box cache stores a bounding box and center point. It
//  also stores a flag indicating whether the box contains any line or
//  point objects, meaning that intersection tests with the box should
//  use a little extra leeway.
//
////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoBoundingBoxCache : public SoCache {

 public:
  // Constructor and destructor
  SoBoundingBoxCache(SoState *state);
  virtual ~SoBoundingBoxCache();

  // Stores a bounding box and center point in the cache
  void                set(const SbXfBox3f &boundingBox,
                          SbBool centerSet,
                          const SbVec3f &centerPoint);

  const SbXfBox3f &   getBox() const          { return m_box; }

  const SbBox3f &     getProjectedBox() const { return m_projectedBox; }

  // Returns TRUE if the center is valid.
  SbBool              isCenterSet() const     { return m_centerSet; }
        

  // Returns the center (in object space)
  const SbVec3f &     getCenter() const       { return m_center; }

  // Sets the hasLinesOrPoints flag to TRUE in all open bounding box
  // caches in the given state. (The flag is FALSE by default.)
  static void         setHasLinesOrPoints(SoState *state);

  // Returns the hasLinesOrPoints flag
  SbBool              hasLinesOrPoints() const         { return m_hasLOrP; }

 private:
  SbXfBox3f           m_box;            // Bounding box
  SbBox3f             m_projectedBox;   // Box in local space
  SbBool              m_centerSet;      // If the center was set
  SbVec3f             m_center;         // Center point
  SbBool              m_hasLOrP;        // TRUE if contains lines or points
};

#endif /* _SO_BOUNDING_BOX_CACHE */
