/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_PRIMITIVE_COUNT_CACHE
#define  _SO_PRIMITIVE_COUNT_CACHE

#include <Inventor/caches/SoCache.h>

////////////////////////////////////////////////////////////////////////
//
//  Class SoPrimitiveCountCache:
//
//  A primitive count cache stores the number of triangles,
//  lines, points, text, and images contained in a scene graph.
//
////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoPrimitiveCountCache : public SoCache {

 public:
  // Constructor and destructor
  SoPrimitiveCountCache(SoState *state);
  virtual ~SoPrimitiveCountCache();

  // Stores a bounding box and center point in the cache
  void                set(int32_t numTriangles,
                          int32_t numLines,
                          int32_t numPoints,
                          int32_t numText,
                          int32_t numImage);

  // Returns counted number of primitives
  void                get(int32_t &numTriangles,
                          int32_t &numLines,
                          int32_t &numPoints,
                          int32_t &numText,
                          int32_t &numImage);

  // Sets the contains3DText flag to TRUE in all open primitive count
  // caches in the given state. (The flag is FALSE by default.)
  static void         setContains3DText(SoState *state);
    
  // 3D Text can be counted as triangles or as text.  
  // If the cache contained 3D Text, then we can
  // only use the cache if we are counting the same way.
  SbBool              contains3DText() { return has3DText; };    
  SbBool      was3DTextCountedAsTriangles() 
    { return treatedText3AsTris; };
  void        setCount3DTextAsTriangles(SbBool treatAsTris) 
    { treatedText3AsTris = treatAsTris; };

  // The primitive counts can be approximated.  If we
  // have an exact count, we can use it, if we are
  // asked for an approximated.  But we can't use an 
  // approximated count when asked for an exact count.
  SbBool      isApproximateCount() { return isApproximated; };

  // Sets the isApproximated flag to TRUE in all open primitive count
  // caches in the given state. (The flag is FALSE by default.)
  static void         setIsApproximated(SoState *state);


 private:
  int32_t     numTriangles;
  int32_t     numLines;
  int32_t     numPoints;
  int32_t     numText;
  int32_t     numImage;
    
  SbBool      treatedText3AsTris;
  SbBool      has3DText;
  SbBool      isApproximated;
   
};

#endif /* _SO_PRIMITIVE_COUNT_CACHE */
