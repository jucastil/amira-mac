/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_BEVEL_ACTION
#define _SO_BEVEL_ACTION

#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/VRMLnodes/SoVRMLMaterial.h>
#include <Inventor/SbBasic.h>

class IntArray;
class VertexArray;
class GroupArray;

class SoGroup;
class SoNode;
class SoPrimitiveVertex;
class SoBevelData;

class SoFaceSet;
class SoIndexedFaceSet;
class SoVRMLIndexedFaceSet;
class SoTriangleStripSet;
class SoIndexedTriangleStripSet;
class SoQuadMesh;
class SoCube;
class SoVRMLBox;
class SoCone;
class SoVRMLCone;
class SoCylinder;
class SoVRMLCylinder;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoBevelAction
//
//  For beveling nodes in a scene graph or a path list. This action traverses
//  a scene graph or a path list, and constructs another scene-graph where the
//  shapes are beveled.
//  The beveling properties can be set directly in this action as default
//  behaviour, or inserted in the scene-graph using a SoBevelProperties node.
//  Specific vertices and edges can be beveled / not beveled using the
//  SoEdgeFlag an SoVertexFlag nodes.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Creates a scene graph containing beveled shapes.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *   This action traverses a scene graph or paths, looking for shapes to bevel, then
 *   creating another scene graph containing the beveled shapes (in the form of
 *   SoCoordinate3 and SoIndexedFaceSet nodes). Typically it is applied to a subgraph
 *   that contains only a single shape.
 *   
 *   SoBevelAction does not take into consideration PER_FACE or PER_VERTEX materials.
 *   Therefore, the shapes to be beveled should have a uniform material
 *   (SoMaterialBinding::OVERALL). 
 *   
 *   It works like other actions, but does not modify the source scene graph. The
 *   scene graph containing beveled shapes can be accessed by calling
 *   getSceneGraph() after applying the action.
 *   
 *   The methods setAngle(), setRadius(), and enableAbsoluteRadius()
 *   set the default behavior of the beveling of the shapes this action will be
 *   applied to. If bevel property values have been set by the SoBevelProperty node,
 *   they are used. Otherwise, the values set by these methods are used.
 * 
 * @SEE_ALSO
 *    SoBevelProperty,
 *    SoEdgeFlag,
 *    SoVertexFlag
 * 
 * 
 */ 

class INVENTOR_API SoBevelAction : public SoAction
{
  SO_ACTION_HEADER(SoBevelAction);

 public:
  /**
   * Constructor.
   */
  SoBevelAction();
  /**
   * Destructor.
   */
  virtual ~SoBevelAction();

  /**
   * Sets the minimum angle (in radians) between two adjacent face normals
   * required to bevel the edge common to these two faces. The default value is 0.5.
   */
  void                  setAngle(float angle);
  /**
   * Returns the minimum angle (in radians) between two adjacent face normals
   * required to bevel the edge common to these two faces. The default value is 0.5.
   */
  float                 getAngle() const;
  /**
   * Sets the bevel radius. The default value is 0.05.
   */
  void                  setRadius(float radius);
  /**
   * Returns the bevel radius. The default value is 0.05.
   */
  float                 getRadius() const;
  /**
   * Sets the absolute radius flag. If TRUE, the radius value is absolute. Otherwise
   * the radius is a value between 0.0 and 1.0; the real radius corresponding is
   * @I max @i * @I radius @i, where @I max @i is the length of the longest edge
   * of the current shape to be beveled. The default is FALSE.
   */
  void                  enableAbsoluteRadius(SbBool flag = TRUE);
  /**
   * Returns TRUE if the radius is absolute, FALSE if it is relative to the shape.
   */
  SbBool                isAbsoluteRadiusEnabled() const;

  /**
   * Returns TRUE if the shapes created by the bevel action are VRML shapes.
   */
  SbBool                isOutputVRML() const;
  /**
   * If TRUE, each beveled shape is generated as a VRML indexed face set. Otherwise
   * the beveled shapes are generated as "classic" indexed face sets. Default value
   * is FALSE.
   */
  void                  setOutputVRML(SbBool flag = TRUE);
  /**
   * Returns TRUE if a coplanar test is performed before the beveling. 
   */
  SbBool                isCoplanarTestEnabled() const;
  /**
   * If TRUE, a test is performed to remove duplicate faces in the shapes being
   * beveled.
   */
  SbBool                isDuplicateTestEnabled() const;
  /**
   * Returns TRUE if the shapes are re-ordered before being beveled.
   */
  SbBool                isOrderingTestEnabled() const;
  /**
   * If TRUE, a coplanar test is performed on each shape before beveling it. This
   * test combines contiguous coplanar faces into one larger face because the bevel
   * method will not work properly on contiguous coplanar faces.
   * 
   * If FALSE, each shape is assumed not to have contiguous coplanar faces. This
   * provides better performance because the coplanar test is not performed. 
   * 
   * It is recommended that you turn off this test @I only @i if the shapes to be
   * beveled do not contain contiguous coplanar faces. Default value is TRUE.
   */
  void                  enableCoplanarTest(SbBool flag = TRUE);
  /**
   * If TRUE, examine each shape to bevel, removing duplicate faces if found. As this
   * test is time consuming, it can be turned on/off depending on whether the shapes
   * to be beveled contain duplicate faces or not. If a shape contains duplicate
   * faces the test is off, no beveling will be performed on the shape. Default value
   * is FALSE.
   */
  void                  enableDuplicateTest(SbBool flag = TRUE);
  /**
   * If TRUE, each shape to bevel is re-ordered so that each face is oriented like
   * the first face of the shape. This test is not time consuming. However, it may be
   * desirable to disable this test when it is not needed. Default value is TRUE.
   */
  void                  enableOrderingTest(SbBool flag = TRUE);

  // As for other actions, the beveling action can be applied on nodes or paths 
  virtual void          apply(SoNode *node);
  virtual void          apply(SoPath *path);
  virtual void          apply(const SoPathList &pathList,
                              SbBool obeysRules = FALSE);

  /**
   * This method returns the scene graph containing the beveled shapes created by the
   * action.
   */
  SoGroup *             getSceneGraph();

 SoINTERNAL public:
  static void           initClass();
  static void           exitClass();

 protected:
  // The beveling action uses a callback action to traverse the source scene-graph
  SoCallbackAction      callbackAction;

  // These fields are used for defining the default behaviour of the beveling
  float                 angle;
  float                 radius;
  SbBool                absoluteRadius;
  int                   _tests_to_do;
  SbBool                _vrml_output;

 private:
  class INVENTOR_API BevelMaterial : public SoVRMLMaterial
    {
    public:
      BevelMaterial();
      BevelMaterial & operator = (const SoVRMLMaterial &);
      void setMaterial(SoVRMLMaterial &);
    };

  BevelMaterial                         material;

  VertexArray                           *_generatedPoints;
  IntArray                              *_generatedTriangles;

  GroupArray                            *_groups;
  SoNode*                               _modifiedNode;
  SoGroup*                              _beveledObject;

  void                                  _bevel(SoBevelData *);
  SoBevelData*                          _getData(SoNode *) {return NULL;}

  static SoCallbackAction::Response     _beforeGroup(void *, SoCallbackAction *action, const SoNode *node);
  static SoCallbackAction::Response     _afterNode(void *, SoCallbackAction *action, const SoNode *node);
  static SoCallbackAction::Response     _afterGroup(void *, SoCallbackAction *action, const SoNode *node);

  SoBevelData*                          _getData(SoFaceSet *);
  SoBevelData*                          _getData(SoIndexedFaceSet *);
  SoBevelData*                          _getData(SoVRMLIndexedFaceSet *);
  SoBevelData*                          _getData(SoTriangleStripSet *);
  SoBevelData*                          _getData(SoIndexedTriangleStripSet *);
  SoBevelData*                          _getData(SoQuadMesh *);
  SoBevelData*                          _getData(SoCube *);
  SoBevelData*                          _getData(SoVRMLBox *);
  SoBevelData*                          _getData(SoCone *);
  SoBevelData*                          _getData(SoVRMLCone *);
  SoBevelData*                          _getData(SoCylinder *);
  SoBevelData*                          _getData(SoVRMLCylinder *);
  static SoCallbackAction::Response     _afterFS(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response     _afterIFS(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response     _afterVIFS(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response     _afterTSS(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response     _afterITSS(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response     _afterQM(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response     _afterCube(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response     _afterVBox(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response     _afterCone(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response     _afterVCone(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response     _afterCylinder(void *, SoCallbackAction *, const SoNode *);
  static SoCallbackAction::Response     _afterVCylinder(void *, SoCallbackAction *, const SoNode *);

  /* removed on 02-25-00 : was previously used to compute cone, cube and cylinder geometry
     static SoCallbackAction::Response     _beforeTriangles(void *,
     SoCallbackAction *,
     const SoNode *);
     static void                           _getTriangles(void *,
     SoCallbackAction *,
     const SoPrimitiveVertex *,
     const SoPrimitiveVertex *,
     const SoPrimitiveVertex *);
     void                                  _insertTrianglePoint(const SoPrimitiveVertex *);
  */
  void                                  getCoords(const SoNode &, SbVec3f *&, int &) const;

  static SoCallbackAction::Response     _setColors(void *, SoCallbackAction *action, const SoNode *node);
  static SoCallbackAction::Response     _setVRMLColors(void *, SoCallbackAction *action, const SoNode *node);

};

#endif

