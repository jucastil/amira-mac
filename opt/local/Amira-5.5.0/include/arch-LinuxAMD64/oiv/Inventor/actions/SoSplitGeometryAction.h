/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Jerome Hummel (Nov 2001)
**=======================================================================*/

#ifndef _SO_SPLIT_GEOMETRY_ACTION_H
#define _SO_SPLIT_GEOMETRY_ACTION_H

#include <Inventor/actions/SoSubAction.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoIndexedShape.h>

class SoSplitGeometryAction;

/**
 * User pre-split callback. The action will call this function before splitting 
 * each shape.
 * A pointer to the action and the node to split is given. The action's options may
 * be modified by the callback function. The number of subdivisions can be changed as well.
 * [OIV-WRAPPER NAME{PreCallback}]
 */
typedef void SoSplitGeometryActionCB(const SoSplitGeometryAction* action, SoNode* objectToSplit, const int objectId,
                                     int divAlongX,int divAlongY,int divAlongZ, void* userData);


/**
 * 
 *  @VSGEXT Split large geometry into smaller objects to improve culling for multi-pipe 
 *  rendering.
 *
 * @ingroup actions
 * 
 * @DESCRIPTION
 * View frustum culling, for example using the SoOctreeOrdering node, is an important 
 * optimization, especially for multi-pipe rendering. However, a large object implemented
 * as a single geometry node cannot be effectively culled. For each pipe where the object
 * is partially visible, the entire object must be rendered.
 *
 * This action splits a large object into multiple geometry nodes, without changing 
 * the appearance of the object. Culling can then applied to the new nodes individually.
 
 * The scene does not need to be subdivided into a large number of parts. Usually,
 * 5 by 5 is enough to reasonably divide work between the threads.
 * The new objects use the same vertex coordinates (and normals, materials,... if specified)
 * as the original geometry. No triangles are added, removed, or split.
 * A small amount of additional memory is required for the coordinate indices in the new objects.
 *
 * Note: 
 * Currently this action applies only to SoIndexedFaceSet and SoIndexedTriangleStripSet
 * nodes. The new object is the same type of node as the original.
 *
 * Texture Mapping: If the original geometry has explicit texture coordinates, the
 * result will be correct. If texture coordinates are computed by Open Inventor,
 * the texture will be applied separately to each new object.
 *
 * @SEE_ALSO
 *        SoOctreeOrdering, SoIndexedFaceSet, SoIndexedTriangleStripSet, SoShapeHints
 * 
 * 
 */  
class INVENTOR_API SoSplitGeometryAction : public SoAction
{
  SO_ACTION_HEADER(SoSplitGeometryAction);

  public :

  /**
   *      Constructor for splitting geometry along 2 dimensions.
   *  By default, the first and second values specify the number
   *  of divisions to be used along the object's x
   *  and y bounding box dimensions respectively. 
   *  The doSmartSplitting method() can be used to change which axes
   *  of the object's 2D bounding box these division values are applied to.
   */
  SoSplitGeometryAction(int divAlongX,int divAlongY);

  /**
   *      Constructor for splitting geometry along 3 dimensions.
   *  By default, these values specify the number
   *  of divisions to be used along the object's x, y, and z bounding box
   *  dimensions respectively. 
   *  The doSmartSplitting method() can be used to change which axes
   *  of the object's 3D bounding box these division values are applied to.
   *      NOTE: Do not use this constructor to split a scene containing flat objects.
   */
  SoSplitGeometryAction(int divAlongX,int divAlongY, int divAlongZ);
        
  /**
   *  Specifies the number of divisions for splitting an object in 2D.
   *  By default, these values specify the number
   *  of divisions to be used along the object's x, y, and z bounding box
   *  dimensions respectively. 
   *  The doSmartSplitting method() can be used to change which axes
   *  of the object's 3D bounding box these division values are applied to.
   */
  void setNumDivisions(int numX, int numY);

  /**
   *  Specifies the number of divisions for splitting an object in 3D.
   *  By default, these values specify the number
   *  of divisions to be used along the object's x, y, and z bounding box
   *  dimensions respectively. 
   *  The doSmartSplitting method() can be used to change which axes
   *  of the object's 3D bounding box these division values are applied to.
   */
  void setNumDivisions(int numX, int numY, int numZ);

  /**
   * Returns the current division values to split an object in 2D.
   */
  void getNumDivisions(int &numX, int &numY);

  /**
   * Returns the current division values to split an object in 3D.
   */
  void getNumDivisions(int &numX, int &numY, int &numZ);
        
        
  //destructor
#ifndef HIDDEN_FROM_DOC
  virtual ~SoSplitGeometryAction();
#endif // HIDDEN_FROM_DOC

  /**
   *  Calling this method before applying the action allows you to see how the action
   *  has split the objects. Each new SoIndexedShape is assigned a unique material.
   *  Default is FALSE.
   */
  void setDistinguishSplitParts(SbBool enable);

  /**
   *  Returns TRUE if distinguish split parts is enabled.
   */
  SbBool isDistinguishSplitParts(void);


  /**
   *  Returns how many objects the action has split. This method must be called
   *  @I after@i the action has been applied.
   */
  int getNumObjFound(void);

  /**
   *  By default, the action modifies the scene graph by replacing the original node
   *  it has split with a new separator containing all the new nodes. 
   *  The behavior can be changed by a call to this method.
   *  Instead of replacing the node with a separator, the original node is replaced 
   *  with an SoSwitch node containing the original node and the separator
   *  containing all the new nodes. 
   *  Each new SoSwitch node added in the scene graph is named "switchX" where X
   *  is the Xth object split. For instance, the first object split by the action
   *  will have a corresponding switch node named "switch0".
   *  Default is FALSE.
   */
  void setKeepOriginalGeometry(SbBool enable);

  /**
   *  Returns TRUE if keep original geometry is enabled.
   */
  SbBool isKeepOriginalGeometry(void); 

  /**
   *  These add a callback function to call when a node of the given type is
   *  encountered during traversal. The PreCallback is called just before the node
   *  is traversed.
   *  For each node to split, you can "customize" how to split it by enabling,
   *  or disabling options, changing the division values, etc.
   * [OIV-WRAPPER EVENT_NAME{PreTraversal}]
   */
  static void setSplitGeometryActionPreCB(SoSplitGeometryActionCB*, void*);

  /**
   *  If this option is set before the action is applied, objects will be split
   *  by dividing the greatest bounding box side into the largest number of divisions,
   *  the next largest side by the next largest number of divisions,
   *  and so on.
   *  Otherwise the action will divide objects by using the first division value given in the
   *  constructor for the x side of the bounding box, the second for y, and so on.
   *  Default is FALSE.
   */
  void setSmartSplitting(SbBool enable);

  /**
   *  Returns TRUE if smart splitting is enabled.
   */
  SbBool isSmartSplitting(void);
  /**
   *  By default the action will only traverse the active child of SoSwitch nodes.
   *  A call to this method tells the action to traverse all children.
   *  Default is FALSE.
   */
  void setTraverseAllSoSwitchChildren(SbBool enable);

  /**
   *  Returns TRUE if traverse all SoSwitch children is enabled.
   */
  int isTraverseAllSoSwitchChildren(void);

  /**
   *  There is a maximum number of division to divide an object because this object 
   *  is composed by some primitives (triangles) that cannot be split without 
   *  changing the geometry. If one of the arguments specified in the constructor is
   *  greater than this maximum division value, then the action will naturally split
   *  the object with the maximum division it is possible to.
   *  A call to this function enable Inventor warnings to know if you've reached this 
   *  maximum value. Turning it on will slow the action traversal because, to know if
   *  the division value is good or not, the length average of every primitives is calculated.
   *  Inventor warnings are Off by default.
   */
  void setMaximumDivisionWarning(SbBool enable);

  /**
   *  If the initial geometry is composed of SoIndexedTriangleStripSet and 
   *  uses an SoShapeHints with a known vertex ordering 
   *  (SoShapeHints::CLOCKWISE or SoShapeHints::COUNTERCLOCKWISE),
   *  the action has to maintain the initial vertex ordering or problems
   *  with normals will appear.
   *  A call to this function will maintain initial vertex ordering.
   *  Default is TRUE.
   */
  void setMaintainVertexOrdering(SbBool enable);

  /**
   *  Returns TRUE if the option to maintain initial vertex ordering is on.
   */
  SbBool isMaintainVertexOrdering(void);

  virtual void apply(SoNode *node);
  virtual void apply(SoPath *path) { SoAction::apply(path); }; // no warning
  virtual void apply(const SoPathList &path_list, 
    SbBool obeys_rules = FALSE) { 
    SoAction::apply(path_list, obeys_rules); }; // no warning

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  protected :
    virtual void beginTraversal(SoNode *node);
  void increaseCurrentNumOfDiv(void);
  void resetCurrentNumOfDiv(void);
  int getCurrentNumOfDiv(void);
  SbBool isDivisionValueGood(SoIndexedShape*,float,int,float,int&);
  static void sortAxesAndDivValues(SoSplitGeometryAction*, int &, int&, int&, int&, int&, int&);
  void commonConstructor(void);
  int getNumberOfDivisions(void);


 private:
  //private constructor to not use it!
  SoSplitGeometryAction(){};

  static void splitStrip(SoAction*, SoNode*);
  static void splitFace(SoAction*, SoNode*);
  static void callDoAction(SoAction*, SoNode*);
  static void nullAction(SoAction*, SoNode*);
  static void beginSwitchTraversal(SoAction*, SoNode*);

  void splitStrip1Dimension(SoNode* node,int div, int axe,float &lastRed,float &lastGreen, float &lastBlue);
  void splitFace1Dimension(SoNode* node,int div, int axe,float &lastRed,float &lastGreen, float &lastBlue);
        
  void replaceNode(SoNode* substitute);

  SbBool areEqual(float, float);

  //number of subdivision
  int numDivX; 
  int numDivY;
  int numDivZ;

  //this node contains the result of the action.
  SoNode* result; 

  //This boolean tells us if the user wants to add some materials for the different parts.
  SbBool enableMaterial;

  //current number of subdivision in the set the action is splitting.
  int currentNumOfDiv;

  //number of objects found during the traversal of the action.
  int numObjFound;

  //the user wants to keep the initial geometry or not.
  SbBool keepMyGeometry;

  //boolean for veretxOrdering
  SbBool keepVertexOrdering;

  //pre callback for user
  static SoSplitGeometryActionCB *userCB;
  static void *userData;

  //boolean for a smart division
  SbBool smartDivision;

  //for the switch node
  int whoHasToBeTraversed;

  //split in 3d or not depending on the constructor used.
  SbBool splitIn3D;

  //to compare 2 floating values.
  float epsilon;

  //turn error on/off :
  SbBool errorOn;
};

#endif
