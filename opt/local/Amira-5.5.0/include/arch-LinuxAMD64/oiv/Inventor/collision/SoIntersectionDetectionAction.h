/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Sebastien Dedieu (Jul 1997)
**=======================================================================*/


#ifndef _SO_INTERSECTION_DETECTION_ACTION_
#define _SO_INTERSECTION_DETECTION_ACTION_


//------------------------------------------------------------------------------
// Includes

#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/SoType.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SoPrimitiveVertex.h>


//------------------------------------------------------------------------------
// Types declaration


//------------------------------------------------------------------------------
// Types definition
/**
 * [OIV-WRAPPER NAME{FilterCB}]
 */
typedef SbBool SoIntersectionFilterCB(void *userData, 
                                      const SoPath *p1, 
                                      const SoPath *p2);
struct SoIntersectingPrimitive {
  /** Primitive type */
  enum PrimitiveType {
    /** Segment */
    SEGMENT = 2,
    /** Line segment */
    LINE_SEGMENT = 2,
    /** Triangle */
    TRIANGLE = 3
  };
  /**
   * Path of the shape
   */ 
  SoPath *path;
  /**    
   * Type of primitive
   */
  PrimitiveType type;
  /**     
   *  Vertex of the primitive
   */
  SbVec3f vertex[3];
  /**     
   *  Transformed vertex of the primitive
   */
  SbVec3f xf_vertex[3];
};

/**
 * @VSGEXT Class to detect intersections.
 * 
 * @ingroup actions collision
 * 
 * @DESCRIPTION
 *   This action allows the programmer to analyze a scene graph to know which pairs
 *   of objects within the scene intersect.
 *   
 *   The action first detects intersections between pairs of bounding boxes. If such
 *   an intersection occurs, the programmer can abort the action or allow it to
 *   determine if the primitives of the objects actually collide.
 *   
 *   The algorithm can call programmer-supplied \oivnetdoc delegates \else callbacks \endoivnetdoc
 *   when there is an intersection between two objects.
 * 
 * @SEE_ALSO
 *    SoCollisionManager,
 *    SoWinCollisionViewer
 * 
 * 
 */ 

class INVENTOR_API SoIntersectionDetectionAction : public SoAction
{
  SO_ACTION_HEADER(SoIntersectionDetectionAction);

public:

  // Types definitions ---------------------------------------------------------
  /** Types definitions */
  enum Resp {
    /** Next primitive */
    NEXT_PRIMITIVE,
    /** Next shape */
    NEXT_SHAPE,
    /** Abort */
    ABORT
  };

  /**
   * [OIV-WRAPPER NAME{IntersectionCB}]
   * [OIV-WRAPPER-ARG IN,IN,IN]
   */
  typedef Resp SoIntersectionCB(void *userData,
                                const SoIntersectingPrimitive *,
                                const SoIntersectingPrimitive *);

  /**
   * Constructor.
   */
  SoIntersectionDetectionAction ();
  /**
   * Destructor.
   */
  ~SoIntersectionDetectionAction();

  /** 
   * @deprecated No longer used. 
   * Sets epsilon (small value) to be used in the collision computation. If
   * the distance between two objects is less than epsilon, the objects are
   * considered to have collided.
   * @DEPRECATED_SINCE_OIV 4.0
   */
  static void setIntersectEpsilon(float epsilon);

  /**
   * @deprecated No longer used.
   * Queries epsilon (small value) to be used in the collision computation.
   * @DEPRECATED_SINCE_OIV 4.0
   */
  static  float getIntersectEpsilon();
   
  // Flag access ---------------------------------------------------------------

  // Applying the action -------------------------------------------------------
  void apply(SoNode *node);
  void apply(SoPath *path);
  void apply(const SoPathList &pathList, SbBool obeysRules = FALSE);

  /**
   * Sets a filter which allow the user to continue or not the intersection finding
   * for a pair of shapes. If the callback returns TRUE, the action search for real
   * intersections, else it goes to the next shape pair.
   */
  void setFilterCallback(SoIntersectionFilterCB *newFilterCB, void *data=NULL);

  /**
   * Adds a callback to be called when there is an intersection.
   * [OIV-WRAPPER EVENT_NAME{Intersection}, EVENT_INVOKE_METHOD{InvokeIntersectionEventDelegates}]
   */
  void addIntersectionCallback (SoIntersectionCB* f, void* userData = NULL);

  /**
   * Removes a callback to be called when there is an intersection.
   * [OIV-WRAPPER EVENT_NAME{Intersection}, EVENT_INVOKE_METHOD{InvokeIntersectionEventDelegates}]
   */
  void removeIntersectionCallback(SoIntersectionCB* f, void* userData = NULL);

  // Computing types -----------------------------------------------------------
  /** Axis */
  enum Axis {
    /** X */
    X_AXIS = 1,
    /** Y */
    Y_AXIS = 2,
    /** Z */
    Z_AXIS = 4
  };

  /** Position */
  enum Position {
    /** Begin */
    BEGIN,
    /** End */
    END
  };
#ifndef HIDDEN_FROM_DOC
  struct ShapeInformationItem {
    SoPath *path;
    float xMin, yMin, zMin;
    float xMax, yMax, zMax;
  };

  struct CoupleTableItem {
    int overlapFlags;
    float xMin, yMin, zMin;
    float xMax, yMax, zMax;
  };
  
  struct ActiveListItem {
    int shapeIndex;
    /** Postion */
    enum Position position;
    SbBool toRemove;
    float x, y, z;
  };
  static float m_fIntersectEpsilon;
#endif // HIDDEN_FROM_DOC

SoINTERNAL public:

  static void initClass();
  static void exitClass();

private : 
  friend class SoCollisionManager;

  // General data --------------------------------------------------------------
  
  // Flags ---------------------------------------------------------------------
  SbBool m_new_test;
  SbBool m_new_shapes;

  // Managing callbacks --------------------------------------------------------
  SoIntersectionFilterCB*  filterCB;
  void*                    userDataFilterCB;
  SoIntersectionCB*        intersectionCB;
  void*                    userDataIntersectionCB;
  void*                    m_callback_list;
  Resp                     response;
  Resp invokeCallbacks (const SoIntersectingPrimitive* p1,
                        const SoIntersectingPrimitive* p2);

  // Computing variables -------------------------------------------------------
  int                      shapeCount;
  SbViewportRegion         viewportRegion;
  int                      shapeInformationSize;
  int                      shapeInformationReservedSize;
  ShapeInformationItem*    shapeInformation;
  int                      coupleTableSize;
  int                      coupleTableReservedSize;
  CoupleTableItem*         coupleTable;
  int                      activeListSize;
  int                      activeListReservedSize;
  ActiveListItem*          activeList;
  int                      primitiveTableSize;
  int                      primitiveTableReservedSize;
  SoIntersectingPrimitive* primitiveTable;
  int                      currentShapeIndex1;
  int                      currentShapeIndex2;
  CoupleTableItem*         currentCouple;

  // Computing functions -------------------------------------------------------
  void seek (SoSearchAction* search);
  //void shapeInformationBuild(SoNode *root);
  void shapeInformationDestroy();
  void shapeInformationClear();
  void shapeInformationAddItem(SoPath *path);
  //void coupleTableBuild();
  void coupleTableDestroy();
  void coupleTableClear();
  CoupleTableItem * coupleTableGetItem(int shapeIndex1, int shapeIndex2);
  void coupleTableSetOverlaping(int shapeIndex1, int shapeIndex2, 
                                Axis axis);
  void coupleTableUpdate(enum Axis axis);
  //void activeListBuild();
  void activeListDestroy();
  void activeListClear();
  void activeListAddItem(int shapeIndex);
  void activeListSort(int (*compareFunction)(void const *, void const *));
  static int activeListXCompare(void const *pointer1, void const *pointer2);
  static int activeListYCompare(void const *pointer1, void const *pointer2);
  static int activeListZCompare(void const *pointer1, void const *pointer2);
  void activeListClean();
  void primitiveTableBuild();
  void primitiveTableDestroy();
  void primitiveTableClear();
  void primitiveTableReserveSpace();
  void primitiveTableAddTriangle (SoCallbackAction *action,
                                  const SoPrimitiveVertex *vertex1,
                                  const SoPrimitiveVertex *vertex2,
                                  const SoPrimitiveVertex *vertex3);
  void primitiveTableAddLineSegment(SoCallbackAction *action,
                                    const SoPrimitiveVertex *vertex1,
                                    const SoPrimitiveVertex *vertex2);
  void shapesCollisionTest(int shapeIndex1, int shapeIndex2);

  void triangleCollisionTest(SoCallbackAction *action,
                             const SoPrimitiveVertex *vertex1,
                             const SoPrimitiveVertex *vertex2,
                             const SoPrimitiveVertex *vertex3);
  void lineSegmentCollisionTest(SoCallbackAction *action,
                                const SoPrimitiveVertex *vertex1,
                                const SoPrimitiveVertex *vertex2);
  static SbBool isTriangleIntersectSegment(const SbVec3f &A,
                                           const SbVec3f &B,
                                           const SbVec3f &C,
                                           const SbVec3f &D, 
                                           const SbVec3f &E);
  static SbBool isTriangleIntersectTriangle (const SoIntersectingPrimitive &triangle1,
                                             const SoIntersectingPrimitive &triangle2);
  static SbBool isSegmentIntersectSegment (const SbVec3f &A,
                                           const SbVec3f &B,
                                           const SbVec3f &C,
                                           const SbVec3f &D);
  
  // Real callbacks ------------------------------------------------------------
  static void primitiveTableAddTriangleCB (void *userData,
                                           SoCallbackAction *action,
                                           const SoPrimitiveVertex *vertex1,
                                           const SoPrimitiveVertex *vertex2,
                                           const SoPrimitiveVertex *vertex3)
  { ((SoIntersectionDetectionAction*) userData)->
      primitiveTableAddTriangle (action, vertex1, vertex2, vertex3); }
  static void primitiveTableAddLineSegmentCB (void *userData,
                                              SoCallbackAction *action,
                                              const SoPrimitiveVertex *vertex1,
                                              const SoPrimitiveVertex *vertex2)
  { ((SoIntersectionDetectionAction*) userData)->
      primitiveTableAddLineSegment (action, vertex1, vertex2); }
  static void triangleCollisionTestCB (void *userData,
                                       SoCallbackAction *action,
                                       const SoPrimitiveVertex *vertex1,
                                       const SoPrimitiveVertex *vertex2,
                                       const SoPrimitiveVertex *vertex3)
  { ((SoIntersectionDetectionAction*) userData)->
      triangleCollisionTest (action, vertex1, vertex2, vertex3); }
  static void lineSegmentCollisionTestCB (void *userData,
                                          SoCallbackAction *action,
                                          const SoPrimitiveVertex *vertex1,
                                          const SoPrimitiveVertex *vertex2)
  { ((SoIntersectionDetectionAction*) userData)->
      lineSegmentCollisionTest (action, vertex1, vertex2); }

  // Miscelaneous --------------------------------------------------------------
  void quickSort(void *array, int nElm, int elmSize,
                 int (*compare)(void const *, void const *),
                 char *tmp);
  void sort(void *array, int nElm, int elmSize,
            int (*compare)(void const *, void const *));

  static SbThreadMutex classMutex;
};


#endif // _SO_INTERSECTION_DETECTION_ACTION_









