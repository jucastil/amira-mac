/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_GET_PRIMITIVE_COUNT_ACTION_
#define  _SO_GET_PRIMITIVE_COUNT_ACTION_

#include <Inventor/actions/SoSubAction.h>
#include <Inventor/elements/SoDecimationTypeElement.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGetPrimitiveCountAction
//
//  For computing the amount of primitives (triangles, lines, points,
//  text, images) in a scene.  This could be used as an estimate
//  for a scene's complexity, or rendering time.  The triangles,
//  lines, and points are counted; however, the text and images
//  count only the number of text or image nodes.
//  SoText3 can be counted as either triangles or text, depending
//  on the setting in this action.
//  The counts can be approximated depending on the setting in this
//  action.  This allows IndexedShapes to take a guess based on
//  the number of vertices, instead of searching through 
//  the actual values of their fields.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Counts number of primitives in scene.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *   This class counts the number of rendering primitives a scene would use to
 *   render. This can be used as an approximation of how long the scene would take to
 *   render. The primitives are divided into five categories: triangles, lines,
 *   points, text objects, and images.
 *   
 *   After applying the action to a path or scene graph, the results can be obtained
 *   with the functions getTriangleCount(), getLineCount(), etc. The
 *   decimation value can be altered before applying, which is useful for finding the
 *   minimum and maximum number of primitives the scene requires (use LOWEST and
 *   HIGHEST).
 *   
 *   3D Text, such as SoText3, SoVRMLText and SoAsciiText, can be counted as either
 *   text or triangles. The function setCount3DTextAsTriangles() will
 *   determine how these objects are counted.
 *   
 *   Some shapes, such as trimmed NURBS surfaces, can answer quicker if they are
 *   allowed to approximate how many primitives they will use instead of calculating
 *   an exact answer. If an exact answer is not required, passing TRUE to
 *   setCanApproximate() will speed the action.
 *
 * @B Elements @b @BR
 * Sets: SoDecimationTypeElement, SoDecimationPercentageElement
 *
 * @EXAMPLE
 *   \oivnetdoc
 *     \code
 *     SoGetPrimitiveCountAction gpca = new SoGetPrimitiveCountAction();
 *     gpca.Apply( rootNode );
 *     int numTris = gpca.GetTriangleCount();
 *     \endcode
 *   \else
 *     \code
 *     SoGetPrimitiveCountAction gpca;
 *     gpca.apply( pRootNode );
 *     int numTris = gpca.getTriangleCount();
 *     \endcode
 *   \endoivnetdoc
 * 
 * @SEE_ALSO
 *    SoAction,
 *    SoLevelOfSimplification,
 *    SoOctreeOrdering,
 *    SoRenderList,
 *    SoValueOrdering
 * 
 * 
 */ 

class INVENTOR_API SoGetPrimitiveCountAction : public SoAction {

  SO_ACTION_HEADER(SoGetPrimitiveCountAction);

 public:
  /**
   * Constructor.
   */
  SoGetPrimitiveCountAction();

  /**
   * Destructor.
   */
  virtual ~SoGetPrimitiveCountAction();

  /**
   * Returns counted number of primitives (triangles).
   */
  int32_t             getTriangleCount() const   { return numTriangles; }
  /**
   * Returns counted number of primitives (lines).
   */
  int32_t             getLineCount() const    { return numLines; }
  /**
   * Returns counted number of primitives (points).
   */
  int32_t             getPointCount() const   { return numPoints; }
  /**
   * Returns counted number of primitives (text).
   */
  int32_t             getTextCount() const    { return numText; }
  /**
   * Returns counted number of primitives (images).
   */
  int32_t             getImageCount() const   { return numImage; }

  /**
   * Returns TRUE if scene contains no primitives of any kind.
   */
  SbBool      containsNoPrimitives();
  /**
   * Returns TRUE if scene contains some primitives that are not triangles.
   */
  SbBool      containsNonTriangleShapes(); 

  /**
   * Sets decimation type and percentage. Percentage should be a number between 0.0
   * and 1.0 (1.0 is full complexity). 
   *
   * Type is one of:
   * 
   * SoDecimationTypeElement::LOWEST @BR
   * Lowest complexity possible for scene. 
   * 
   * SoDecimationTypeElement::HIGHEST @BR
   * Highest complexity possible for scene. 
   * 
   * SoDecimationTypeElement::AUTOMATIC @BR
   * Scene uses decimation percentage; LODs calculate range value and then adjust them
   * with percentage. 
   * 
   * SoDecimationTypeElement::PERCENTAGE @BR
   * Scene uses decimation percentage; LODs use child based solely on decimation
   * without looking at camera position. 
   */
  void setDecimationValue(SoDecimationTypeElement::Type type,
                          float percentage = 1.0);
  /**
   * Gets decimation type. 
   */
  SoDecimationTypeElement::Type getDecimationType() { return decType; };
  /**
   * Gets decimation percentage. 
   */
  float               getDecimationPercentage() { return decPercent; };

  /**
   * SoText3 can be counted two ways: as a triangle-based shape or as a text-based
   * shape. This routine specifies how SoText3 should be counted. The default is TRUE
   * (SoText3 adds to the triangle count, not the text count).
   */
  void        setCount3DTextAsTriangles(SbBool treatAsTris) 
    { treatText3AsTris = treatAsTris; };
  /**
   * Returns how SoText3 should be counted: as a triangle-based shape (TRUE)
   * or as a text-based shape (FALSE). 
   */
  SbBool      is3DTextCountedAsTriangles() { return treatText3AsTris; };
 
  /**
   * Some shapes may be able to guess an approximate number of triangles without
   * actually counting. In the interests of speed, and depending on how the results
   * are used, a flag is available to allow shapes to approximate their count. The
   * default is FALSE.
   */
  void        setCanApproximate(SbBool onOff)
    {  canApproximate = onOff; };
  /**
   * Returns whether shapes are allowed to approximate their count. 
   */
  SbBool      canApproximateCount() { return canApproximate; };

 SoEXTENDER public:
  // These functions are called by nodes to add a number of
  // a type of primitive to the number of primitives found.
  void        addNumTriangles(int32_t num)    { numTriangles += num; };
  void        addNumLines(int32_t num)        { numLines += num; };
  void        addNumPoints(int32_t num)       { numPoints += num; };
  void        addNumText(int32_t num)         { numText += num; };
  void        addNumImage(int32_t num)        { numImage += num; };
  void        incNumTriangles()       { numTriangles++; };
  void        incNumLines()           { numLines++; };
  void        incNumPoints()          { numPoints++; };
  void        incNumText()            { numText++; };
  void        incNumImage()           { numImage++; };

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  // Initiates action on graph
  virtual void        beginTraversal(SoNode *node);

 private:
  int32_t     numTriangles;
  int32_t     numLines;
  int32_t     numPoints;
  int32_t     numText;
  int32_t     numImage;
    
  SbBool      treatText3AsTris;
  SbBool      canApproximate;
    
  SoDecimationTypeElement::Type decType;
  float       decPercent;

};

#endif /* _SO_GET_PRIMITIVE_COUNT_ACTION_ */

