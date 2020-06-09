/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Rodolphe ALBOU (Mar 2001)
**=======================================================================*/


#ifndef _SO_CSG_OPERATION_
#define _SO_CSG_OPERATION_


#include <Inventor/SbBasic.h>

class  SoNode ;
class  SoSeparator ;
class  SoFaceSet ;
struct IPPolygonStruct ;
class  SoCallbackAction ;
class  SoPrimitiveVertex ;

/**
 * @SVEXT Class which computes a CSG operation (OR, AND, SUB, etc) from 2 solid objects.
 * 
 * @ingroup SolidViz
 * 
 * @DESCRIPTION
 *   Each input solid object is given by a scene graph. The result is also
 *   given by a scene graph.
 * 
 * @IMPORTANT_NOTE
 *   This class is provided on an as-is basis, with no support or warranty.
 *
 * @SEE_ALSO
 *    SolidViz Overview,
 *    SoCSGGroup
 *    SoSolidViz
 * 
 */ 
class SOLIDVIZ_API SoCSGOperation {

public:

  /** Available operations */
  enum OperationType {
    OR,
    AND,
    SUB,
    CUT,
    INSIDE_CUT,
    MERGE
  };

  /** Constructor */
  SoCSGOperation() ;

  /** Constructor */
  SoCSGOperation(OperationType opType) ;

  /** Defines the current operation */
  void setOperationType(OperationType opType) ;

  /** Gets the current operation */
  OperationType getOperationType() const ;

  /** Defines the 2 solid objects used for the CSG operation */
  void   setSceneGraphs(const SoNode *objectA, const SoNode *objectB) ;

  /**
   * Returns the result objectA OperationType objectB 
   * The scenegraph returned contains an SoFaceSet shape.
   */
  SoSeparator* getSceneGraph() const ;

private:
  void constructorCommon() ;
  static void triangleCB(void *userData, 
                         SoCallbackAction *action,
                         const SoPrimitiveVertex *v1,
                         const SoPrimitiveVertex *v2,
                         const SoPrimitiveVertex *v3) ;
  static IPPolygonStruct* buildIPPolygon(const SoNode *object) ;
  static SoFaceSet*       buildFaceSet(IPPolygonStruct *polygonList) ;


  const SoNode  *m_objectA, *m_objectB ;
  OperationType m_operationType ;
}; /*---------------------------------------------------------------------------*/

#endif // _SO_CSG_OPERATION_







