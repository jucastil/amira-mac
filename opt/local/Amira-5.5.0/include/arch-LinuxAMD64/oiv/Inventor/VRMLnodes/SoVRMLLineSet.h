/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRML_LINE_SET_
#define  _SO_VRML_LINE_SET_

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

class SoState;
class SoPrimitiveVertex;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLIndexedLineSet
//
//  Indexed set of (poly)lines. Each line consists of 2 or more
//  vertices, each of which is denoted by an integer index (from the
//  coordIndex field) into the current coordinates. Depending on the
//  current material and normal binding values, the materials and
//  normals for the lines or vertices may be accessed in order or
//  indexed. If they are indexed, the colorlIndex and normalIndex
//  fields are used. Texture coordinates may also be indexed, using
//  the textureCoordIndex field.
//
//////////////////////////////////////////////////////////////////////////////

// This coordinate index indicates that the current line ends and the
// next line begins
#define SO_END_LINE_INDEX       (-1)

/**
 * @VSGEXT Indexed polyline shape node.\ @NO_ACTION
 * 
 * @ingroup X3D
 * 
 * @DESCRIPTION
 *   See the X3D Specification, below.
 * 
 * @VRMLX3D_SPECIFICATION
 *   This section describes the expected behavior of the node in a conforming X3D
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the X3D specification that are not
 *   present in this help file. The complete X3D spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   The SoVRMLLineSet node represents a 3D geometry formed by constructing
 *   polylines from 3D vertices specified in the #coord field.
 *   
 *   The #coord field specifies the 3D vertices of the line set and is specified
 *   by an SoVRMLCoordinate node. 
 *   
 *   Lines are not lit, not texture-mapped, and not collided with during collision
 *   detection.
 *   
 *   If the #color field is not NULL, it must contain an SoVRMLColor node.
 *   The SoVRMLColor node specifies the color at each vertex.
 *
 *   If the #color field is NULL and there is a Material defined for the
 *   SoVRMLAppearance affecting this SoVRMLLineSet, then use the
 *   #emissiveColor of the Material to draw the lines. See "Concepts - Lighting
 *   Model, Lighting Off" for details on lighting equations.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLLineSet {
 *    @TABLE_FILE_FORMAT
 *       @TR color            @TD NULL
 *       @TR coord            @TD NULL
 *       @TR vertexCount      []
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
 *       @TR   SoSFNode    @TD   set_color      
 *       @TR   SoSFNode    @TD   set_coord      
 *       @TR   SoMFInt32   @TD   set_vertexCount
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode    @TD   color_changed      
 *       @TR   SoSFNode    @TD   coord_changed
 *       @TR   SoMFInt32   @TD   vertexCount_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLLineSet : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLLineSet);

 public:
  // Fields

  /**
   * An SoVRMLCoordinate node defining the LineSet.
   * 
   */
  SoSFNode            coord;
  /**
   * An SoVRMLColor node that specifies the color of the line set at each vertex.
   * 
   */
  SoSFNode            color;
  /**
   * Number of vertices per polyline.
   * 
   */
   SoMFInt32          vertexCount;
  /**
   * Constructor.
   */
  SoVRMLLineSet();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        generatePick(SoRayPickAction *action, SoNode *node);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);


  // Redefine this to tell open caches that they contain lines
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
                                               
  //Typedef of pointer to method on IndexedLineSet;
  //This will be used to simplify declaration and initialization.
  typedef void (SoVRMLLineSet::*PMILS)(SoGLRenderAction *);
                                                  
 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  // This enum is used to indicate the current material binding
  enum Binding {
    OVERALL,
    PER_SEGMENT,    PER_SEGMENT_INDEXED,
    PER_LINE,       PER_LINE_INDEXED,
    PER_VERTEX,     PER_VERTEX_INDEXED
  };
  // Generates line segments representing line set
  virtual void        generatePrimitives(SoAction *action);

  // Overrides standard method to create an SoLineDetail instance
  virtual SoDetail *  createLineSegmentDetail(SoRayPickAction *action,
                                              const SoPrimitiveVertex *v1,
                                              const SoPrimitiveVertex *v2,
                                              SoPickedPoint *pp);
  virtual ~SoVRMLLineSet();

 private:
  // Returns current material or normal binding from action's state
  static Binding      getMaterialBinding(SoAction *action);
  //static Binding    getNormalBinding(SoAction *action);

  // Reset numVertices/numSegments/numPolylines when notified
  virtual void        notify(SoNotList *list);
    
  // Fill in numPolylines, numSegments 
  void countPolylinesAndSegments();
    
  // Number of polylines, number of line segments, and vertices per polyline

  int         numSegments;
  int         numPolylines;
  int *       numVertices;
        
  // Returns TRUE if normal binding is AUTO and there aren't enough
  // PER_VERTEX normals, in which case we turn off lighting and draw
  // BASE_COLOR.
  //wouldGenerateNormals(SoState *state);

  // 32 different render functions; names are formed like this:
  // Om -- overall material  Pm -- per part material
  // Fm -- per face material Vm -- per vertex material
  // On -- overall normal    Pm -- per part normal
  // Fn -- per face normal   Vm -- per vertex normal
  // T  -- per vertex texture coordinates
  void OmOn(SoGLRenderAction *); void OmOnT(SoGLRenderAction *);
  void OmPn(SoGLRenderAction *); void OmPnT(SoGLRenderAction *);
  void OmFn(SoGLRenderAction *); void OmFnT(SoGLRenderAction *);
  void OmVn(SoGLRenderAction *); void OmVnT(SoGLRenderAction *);
  void PmOn(SoGLRenderAction *); void PmOnT(SoGLRenderAction *);
  void PmPn(SoGLRenderAction *); void PmPnT(SoGLRenderAction *);
  void PmFn(SoGLRenderAction *); void PmFnT(SoGLRenderAction *);
  void PmVn(SoGLRenderAction *); void PmVnT(SoGLRenderAction *);
  void FmOn(SoGLRenderAction *); void FmOnT(SoGLRenderAction *);
  void FmPn(SoGLRenderAction *); void FmPnT(SoGLRenderAction *);
  void FmFn(SoGLRenderAction *); void FmFnT(SoGLRenderAction *);
  void FmVn(SoGLRenderAction *); void FmVnT(SoGLRenderAction *);
  void VmOn(SoGLRenderAction *); void VmOnT(SoGLRenderAction *);
  void VmPn(SoGLRenderAction *); void VmPnT(SoGLRenderAction *);
  void VmFn(SoGLRenderAction *); void VmFnT(SoGLRenderAction *);
  void VmVn(SoGLRenderAction *); void VmVnT(SoGLRenderAction *);

  // Array of function pointers to render functions:
  static PMILS renderFunc[32];
    
  static const int AUTO_CACHE_MIN_WITHOUT_VP;
  static const int AUTO_CACHE_MAX;

};

#endif /* _SO_VRML_LINE_SET_ */
    

