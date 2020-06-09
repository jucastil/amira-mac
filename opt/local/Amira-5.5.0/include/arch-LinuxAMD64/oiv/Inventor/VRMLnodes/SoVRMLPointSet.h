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


#ifndef  _SO_VRMLPOINT_SET_
#define  _SO_VRMLPOINT_SET_

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/VRMLnodes/SoVRMLVertexPoint.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLPointSet
//
//////////////////////////////////////////////////////////////////////////////

// This value, when used in the numPoints field, means use the rest of
// the coordinates as points

/**
 * @VSGEXT Point set shape node.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   See the VRML97 Specification, below.
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   The SoVRMLPointSet node specifies a set of 3D points in the local coordinate
 *   system with associated colors at each point. The @B coord @b field specifies an
 *   SoVRMLCoordinate node (or instance of an SoVRMLCoordinate node) - results are
 *   undefined if the @B coord @b field specifies any other type of node.
 *   SoVRMLPointSet uses the coordinates in order. If the @B coord @b field is NULL,
 *   then the SoVRMLPointSet is empty.
 *   
 *   SoVRMLPointSets are not lit, not texture-mapped, or collided with during
 *   collision detection.
 *   
 *   If the @B color @b field is not NULL, it must specify an SoVRMLColor node that
 *   contains at least the number of points contained in the @B coord @b node -
 *   results are undefined if the @B color @b field specifies any other type of
 *   node. Colors will be applied to each point in order. The results are undefined
 *   if the number of values in the SoVRMLColor node is less than the number of
 *   values specified in the SoVRMLCoordinate node
 *   
 *   If the @B color @b field is NULL and there is an SoVRMLMaterial defined for the
 *   SoVRMLAppearance affecting this SoVRMLPointSet, then use the
 *   @B emissiveColor @b of the Material to draw the points. See "Concepts -
 *   Lighting Model, Lighting Off" for details on lighting equations.
 *
 *   Shape Antialiasing type is SoShape::POINTS.
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLPointSet {
 *    @TABLE_FILE_FORMAT
 *       @TR coord   @TD NULL
 *       @TR color   @TD NULL
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_color      
 *       @TR   SoSFNode   @TD   set_coord
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   color_changed      
 *       @TR   SoSFNode   @TD   coord_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLPointSet : public SoVRMLVertexPoint {

  SO_NODE_HEADER(SoVRMLPointSet);

 public:

  /**
   * Constructor.
   */
  SoVRMLPointSet();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

  // Redefine this to tell open caches that they contain points
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

  virtual void        generatePick(SoRayPickAction *action, SoNode *node);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  // Generates points representing point set
  virtual void        generatePrimitives(SoAction *action);

  // Overrides standard method to create an SoPointDetail instance
  virtual SoDetail *createPointDetail(SoRayPickAction *action,
                                      const SoPrimitiveVertex *v,
                                      SoPickedPoint *pp);

 protected:
  virtual ~SoVRMLPointSet();

 private:
  // Returns TRUE if materials/normals are bound to individual points
  SbBool areMaterialsPerPoint(SoAction *action);  // const;

  ///////////////////////EXCEPTION METHODS/////////////////////////////////////
  //
  // #unfound coord
  // #unfound color
  //
  /////////////////////////////////////////////////////////////////////////////

};

#endif /* _SO_VRMLPOINT_SET_ */

