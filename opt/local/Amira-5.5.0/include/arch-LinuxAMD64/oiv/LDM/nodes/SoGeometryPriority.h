/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Jerome Hummel (Nov 2004)
**=======================================================================*/


#ifndef  _SO_WEIGHT_PROPERTY_
#define  _SO_WEIGHT_PROPERTY_

#include <Inventor/fields/SoSFFloat.h> 
#include <Inventor/nodes/SoNode.h> 



/**
 * @LDMEXT Priority property of a rendering node.
 * 
 * @ingroup LDMNodes
 * 
 * @DESCRIPTION
 * This node allows you to assign a priority to an LDM rendering node (e.g., SoOrthoslice, SoMeshSkin).
 * Each rendering node inserted after this node will have the priority
 * specified in the #priority field. The priority must be between 0 and 1 inclusive.
 * By default, VolumeViz assigns the same priority depending on the type of node:
 * (0.5 for SoVolumeRender nodes, 0.9 for all other geometry nodes).
 *
 * The SoGeometryPriority node lets you assign higher priority to specific geometry
 * nodes. For example to prioritize the loading of tiles around a Z axis ortho slice
 * against an X axis ortho slice.
 *
 * Higher resolution tiles for higher priority geometry are loaded before 
 * higher resolution tiles for lower priority geometry.
 *
 * NOTE: This feature only applies when VolumeViz is in LDM mode. It always
 * applies for ReservoivViz.
 *
 * @FILE_FORMAT_DEFAULT
 * GeometryPriority{
 *    @TABLE_FILE_FORMAT
 *    @TR weight            @TD 0.0
 *    @TABLE_END
 * }
 *
 * @ACTION_BEHAVIOR
 * SoCallbackAction,
 * SoGLRenderAction,
 * SoPickAction,
 * SoWriteAction,
 * SoGetBoundingBoxAction @BR
 * Sets geometry priority parameters in the traversal state.
 *
 * @SEE_ALSO
 *  SoDataSet
 *
 * 
 */ 
class LDM_API SoGeometryPriority : public SoNode {
  SO_NODE_HEADER( SoGeometryPriority );

 public:
   /** Constructor */
   SoGeometryPriority();

   /** Constructor that automatically initializes 
   * the #priority field to the specified value. 
   */
   SoGeometryPriority(float);

   /** 
   * Geometry priority between 0 and 1 inclusive.
   */
   SoSFFloat priority;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();


 SoEXTENDER public:
  virtual void doAction( SoAction *action );
  virtual void GLRender( SoGLRenderAction *action );
  virtual void callback( SoCallbackAction *action );
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void pick(SoPickAction *action) ;
  virtual void write(SoWriteAction *action);


protected:
  // Destructor
  virtual ~SoGeometryPriority();
};
//--------------------------------------------------------------------------------

#endif // _SO_WEIGHT_PROPERTY_
