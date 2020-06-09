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


#ifndef  _SO_VERTEX_SHAPE_
#define  _SO_VERTEX_SHAPE_

#include <Inventor/nodes/SoShape.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/threads/SbThreadSpinlock.h>
#include <Inventor/threads/SbThreadRWMutex.h>
#include <Inventor/threads/SbThreadLocalStorage.h>
#include <Inventor/STL/map>

// ideally should be a forward declaration
#include <Inventor/caches/SoVertexPropertyCache.h>
#include <Inventor/caches/SoVBOMgr.h>
#include <Inventor/caches/SoVBOCache.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVertexShape
//
//  Abstract vertex-based shape node class. All nodes derived from
//  this class are shapes that are constructed from vertices at some
//  or all of the current coordinates.  They all have vertexProperty nodes,
//  and vpCaches.
//
//////////////////////////////////////////////////////////////////////////////

class SoGLRenderAction;
class SoNormalBundle;
class SoNormalCache;
class SoShapeStyleElement;
class SoState;
class SoTextureCoordinateBundle;
class SoTextureCoordinate3Bundle;
class SoVertexAttribData;

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
 * Abstract base class for all vertex-based shape nodes.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This node is the abstract base class for all vertex-based shape (geometry)
 *   nodes. It is used as a repository for convenience functions for subclasses and
 *   to provide a type identifier to make it easy to determine whether a shape is
 *   vertex-based. It contains one public field, the SoVertexProperty field.
 *   
 *   All subclasses of this node draw objects constructed from vertices. If the
 *   vertexProperty field is non-null and there are coordinates in the associated
 *   vertex property node, then those coordinates are used. Otherwise the objects are
 *   drawn using the current coordinates in the state. The coordinates of the shape
 *   are transformed by the current transformation matrix and are drawn with the
 *   current light model and drawing style.
 *   
 *   Subclasses that construct polygons from vertices may not render or pick correctly
 *   if any of their polygons are self-intersecting or non-planar.
 *   
 *   All vertex shape subclasses use the bounding box of the shape to determine
 *   default texture coordinates. The longest dimension of the bounding box defines
 *   the S coordinates, and the next longest defines the T coordinates. The value of
 *   the S coordinate ranges from 0 to 1, from one end of the bounding box to the
 *   other. The T coordinate ranges between 0 and the ratio of the second greatest
 *   dimension of the bounding box to the greatest dimension.
 *   
 *   When a vertex-based shape is picked with an SoRayPickAction, a detail is always
 *   returned. If the shape is composed of faces (such as SoFaceSet or
 *   SoTriangleStripSet), an SoFaceDetail is returned. If the shape is composed of
 *   line segments (such as SoLineSet), an SoLineDetail is returned. If the shape is
 *   composed of points (such as SoPointSet), an SoPointDetail is returned. Note that
 *   the type of detail returned is not affected by the current drawing style.
 *   
 *   Similarly, each class of vertex-based shape invokes appropriate callbacks if
 *   those callbacks are registered with the SoCallbackAction. Shapes made of faces
 *   invoke triangle callbacks for each generated triangle. (Faces may be
 *   triangulated to create these triangles.) Shapes made of line segments invoke
 *   line segment callbacks for each segment, and shapes made of points invoke point
 *   callbacks.
 *   
 *   The subclass SoIndexedShape is a base class for vertex-based shapes that index
 *   into the current set of coordinates. The subclass SoNonIndexedShape is a base
 *   class for vertex-based shapes that use the current coordinates in order.
 * 
 * @FILE_FORMAT_DEFAULT
 *    This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 * 
 * @SEE_ALSO
 *    SoIndexedShape,
 *    SoNonIndexedShape,
 *    SoVertexProperty
 * 
 * 
 */ 

class INVENTOR_API SoVertexShape : public SoShape {

  SO_NODE_ABSTRACT_HEADER(SoVertexShape);
    
 public:
  /**
   * vertex property node.
   * 
   */
  SoSFNode vertexProperty;

  /** 
   * Returns the current normal cache, or NULL if there is none.
   * Normal cache will only exist if the node has been traversed
   * by a render action and Inventor needed to compute normals.
   */
  SoNormalCache *getNormalCache() const { return normalCache; }

 SoEXTENDER public:

  // Subclasses may define this method to generate normals to use
  // when the normal binding is DEFAULT and there aren't enough
  // normals in the state. This should use the given SoNormalBundle
  // to generate the normals. Returns TRUE if normals were generated.
  virtual void      generateDefaultNormals(SoState *state, 
                                   const SbVec3f *coords, 
                                   int numCoords, 
                                   SoNormalBundle *nb,
                                   SbBool storeRef = FALSE);

  //Common function for normal generation
  void      commonGenerateDefaultNormals(SoState *state, SoNormalBundle *nb);

  virtual SbBool figureNormals(SoState *state, SoNormalBundle *nb);

  virtual int getNumNeededNormals(SoState *state);

  virtual void        write(SoWriteAction *writeAction);

  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  // Redefines this to invalidate normal cache
  virtual void        notify(SoNotList *list);

  // it is not in protected section because it is 
  // used by inherited class AND SoVBOCache class
  inline SoVBOMgr* getVBOMgr() const
  { return (SoVBOMgr*)(m_VBOMgr.getValue()); }

  inline SbThreadStorage<SoVBOMgr*>* getVBOMgrLocalStorage()
  { return &m_VBOMgr; }

  virtual void callDEBUGGLRender(SoGLRenderAction *action,uint32_t useTexCoordsAnyway);

  inline SoVertexPropertyCache* getVpCache();
  inline void lockVpCacheMutex() const;
  inline void unlockVpCacheMutex() const;


 protected:
  // Constructor - makes this abstract
  SoVertexShape();

  virtual ~SoVertexShape();
    
  // Returns TRUE if the shape should be rendered. 
  // Checks for transparency in vertexProperty node before invoking
  // render action.
  virtual SbBool      shouldGLRender(SoGLRenderAction *action,
                                     SbBool isPointsOrLines = FALSE);
    
  
  //********************* VBO management (Indexed shapes only) ********************
  //    Delete all objects concerning VBO.
  SoVBOMgr* allocateVBO(SoState* state);
  void deleteVBO(SoState *state) ;
  void checkValidity(SoState* state, const int VBOUsage=0);
  //******************* End VBO management *******************

  //Free memory
  virtual void exitRender(SoState *state,int stateFlag,
                  SoTextureCoordinateBundle *tcb,
                  SoTextureCoordinate3Bundle *tc3b);

  //------------------ Following result of glRender() factorization GT (Sep 2007) 
  
  // function to be inherited and returning max numer of shapes used for auto caching
  virtual int getMaxTestValueForAutoCache(){return 0;}

  // function to be inherited and returning min numer of shapes used for auto caching
  virtual int getMinTestValueForAutoCache(){return 0;}

  // sometimes used in shapes
  virtual void setupRenderFunctions(SoState *state,int &stateFlag);

  virtual void callSetupIndices(const SoShapeStyleElement* shapeStyle,uint32_t useTexCoordsAnyway);

  // check texture coordinates generation
  virtual void shouldGenerateTextureCoordinates(SoGLRenderAction *action,
                                                int &stateFlag,
                                                SoShapeStyleElement *&shapeStyle,
                                                uint32_t &useTexCoordsAnyway,
                                                SoTextureCoordinateBundle *&tcb,
                                                SoTextureCoordinate3Bundle *&tc3b);

  // check texture 3D coordinates generation
  virtual SbBool shouldGenerateTexture3DCoordinates(){return FALSE;}

  // check auto caching
  virtual void checkAutoCaching(SoState *state,const SoShapeStyleElement *shapeStyle,SbBool settingVPCache);

  // check 3D tex coords
  virtual SbBool checkTex3Coords(){return FALSE;}

  // actual rendering
  virtual void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  // rendering
  virtual void render(SoGLRenderAction *action,SbBool isPointsOrLines,SbBool setVPCache);

  // check normal generation
  virtual void shouldGenerateNormals(SoGLRenderAction *action,const SoShapeStyleElement *shapeStyle);

  //Wether to check or not shapeHints
  virtual SbBool shouldCheckShapeHints(){ return FALSE;}

  // check VP cache
  virtual SbBool shouldSetVPCache(SoGLRenderAction *action,SbBool isPointsOrLines);

  virtual SbBool checkVPCache(SoGLRenderAction *action,
                            const SoShapeStyleElement *shapeStyle,
                            SbThreadAutoWriteLock *autoLock = 0);

  
  virtual SbBool shapeHintsTest(){ return FALSE;}
  
  // check shape hints
  virtual SbBool checkShapeHints(SoGLRenderAction *action,SbThreadAutoWriteLock *autolock =0);

  // setup lazy element
  virtual void setupLazyElement(SoGLRenderAction *action,const SoShapeStyleElement *shapeStyle);

  // check shape style
  virtual void checkShapeStyle(SoState *state,const SoShapeStyleElement *shapeStyle);
  
  //-----------------------------------------------------------------------------

  // vpCache stores information from one render to the next about
  // what information needs to be grabbed from the state, etc.
  SoVertexPropertyCache       vpCache;

  // Sets up a cache to hold normals. This assumes the cache depends
  // on only the current coordinates, shape hints, and crease angle.
  void setNormalCache(SoState *state, int numNormals, const SbVec3f *normals, const SoNormalBindingElement::Binding binding=SoNormalBindingElement::PER_VERTEX);

  // Per-instance mutex to protect access to the vpCache
  SbThreadRWMutex *vpCacheMutex;

  // Internal use only, no public definition...
  SoVertexAttribData* m_vertexAttribData;

  // Internal routines used to allocate sequential indices so the
  // same rendering loops can be used for indexed or non-indexed
  // cases:
  static int32_t* allocateSequential(const int howMany);
  static int32_t* getConsecutiveIndices();

 private:
  // This allows instances to cache normals that have been generated
  SoNormalCache* normalCache;
  SbThreadStorage<SoVBOMgr*> m_VBOMgr;
  SbThreadStorage<SoVBOCache*> m_VBOCache ;
  
  static SbThreadSpinlock s_consecutiveIndicesMutex;
  static std::map<int,int32_t*> s_consecutiveIndices;
};

inline void 
SoVertexShape::generateDefaultNormals(SoState *, const SbVec3f *, int , SoNormalBundle *, SbBool )
{}

inline void 
SoVertexShape::setupRenderFunctions(SoState *,int &)
{}

inline void 
SoVertexShape::callSetupIndices(const SoShapeStyleElement* ,uint32_t )
{}

inline int 
SoVertexShape::getNumNeededNormals(SoState *)
{
  return 0;
}

inline void 
SoVertexShape::callDEBUGGLRender(SoGLRenderAction *,uint32_t )
{}

inline void 
SoVertexShape::doRendering(SoGLRenderAction *, const SoShapeStyleElement* )
{}

/*******************************************************************************/
SoVertexPropertyCache*
SoVertexShape::getVpCache()
{
  return &vpCache;
}

/*******************************************************************************/
void
SoVertexShape::lockVpCacheMutex() const
{
  vpCacheMutex->writelock();
}

/*******************************************************************************/
void
SoVertexShape::unlockVpCacheMutex() const
{
  vpCacheMutex->writeunlock();
}

#ifdef WIN32
#pragma warning( pop )
#endif

#endif /* _SO_VERTEX_SHAPE_ */

