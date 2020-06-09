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


#ifndef  _SO_VRMLINDEXED_LINE_SET_
#define  _SO_VRMLINDEXED_LINE_SET_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/VRMLnodes/SoVRMLIndexedLine.h>

class SoState;

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
 * @VSGEXT Indexed polyline shape node.
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
 *   The SoVRMLIndexedLineSet node represents a 3D geometry formed by constructing
 *   polylines from 3D points specified in the @B coord @b field.
 *   SoVRMLIndexedLineSet uses the indices in its #coordIndex field to specify
 *   the polylines by connecting together points from the @B coord @b field. An
 *   index of -1 indicates that the current polyline has ended and the next one
 *   begins. The last polyline may (but does not have to be) followed by a -1.
 *   SoVRMLIndexedLineSet is specified in the local coordinate system and is affected
 *   by parent transformations.
 *   
 *   The @B coord @b field specifies the 3D vertices of the line set and is specified
 *   by an SoVRMLCoordinate node. 
 *   
 *   Lines are not lit, not texture-mapped, or not collided with during collision
 *   detection.
 *   
 *   If the @B color @b field is not NULL, it must contain an SoVRMLColor node, and
 *   the colors are applied to the line(s) as follows: 
 *   
 *   - If @B colorPerVertex @b is FALSE: 
 *   
 *   - If the @B colorIndex @b field is not empty, then one color is used for each
 *   polyline of the SoVRMLIndexedLineSet. There must be at least as many indices in
 *   the @B colorIndex @b field as there are polylines in the SoVRMLIndexedLineSet.
 *   If the greatest index in the @B colorIndex @b field is N, then there must be
 *   N+1 colors in the SoVRMLColor node. The @B colorIndex @b field must not contain
 *   any negative entries. 
 *   
 *   - If the @B colorIndex @b field is empty, then the colors are applied to each
 *   polyline of the SoVRMLIndexedLineSet in order. There must be at least as many
 *   colors in the SoVRMLColor node as there are polylines. 
 *   
 *   - If colorPerVertex is TRUE: 
 *   
 *   - If the @B colorIndex @b field is not empty, then colors are applied to each
 *   vertex of the SoVRMLIndexedLineSet in exactly the same manner that the
 *   #coordIndex field is used to supply coordinates for each vertex from the
 *   SoVRMLCoordinate node. The @B colorIndex @b field must contain at least as many
 *   indices as the #coordIndex field and must contain end-of-polyline markers
 *   (-1) in exactly the same places as the #coordIndex field. If the greatest
 *   index in the @B colorIndex @b field is N, then there must be N+1 colors in the
 *   SoVRMLColor node. 
 *   
 *   - If the @B colorIndex @b field is empty, then the #coordIndex field is
 *   used to choose colors from the SoVRMLColor node. If the greatest index in the
 *   #coordIndex field is N, then there must be N+1 colors in the SoVRMLColor
 *   node. 
 *   
 *   If the @B color @b field is NULL and there is a Material defined for the
 *   SoVRMLAppearance affecting this IndexedLineSet, then use the
 *   @B emissiveColor @b of the Material to draw the lines. See "Concepts - Lighting
 *   Model, Lighting Off" for details on lighting equations.
 *
 *   Shape Antialiasing type is SoShape::LINES.
 *
 * @FILE_FORMAT_DEFAULT
 *    VRMLIndexedLineSet {
 *    @TABLE_FILE_FORMAT
 *       @TR color            @TD NULL
 *       @TR colorIndex       @TD []
 *       @TR colorPerVertex   @TD TRUE
 *       @TR coord            @TD NULL
 *       @TR coordIndex       @TD []
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
 *       @TR   SoMFInt32   @TD   set_colorIndex      
 *       @TR   SoSFNode   @TD   set_coord      
 *       @TR   SoMFInt32   @TD   set_coordIndex
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

class INVENTOR_API SoVRMLIndexedLineSet : public SoVRMLIndexedLine {

  SO_NODE_HEADER(SoVRMLIndexedLineSet);

 public:
  // Inherits all fields

  /**
   * Constructor.
   */
  SoVRMLIndexedLineSet();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        generatePick(SoRayPickAction *action, SoNode *node);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);


  // Redefine this to tell open caches that they contain lines
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
                                               
  //Typedef of pointer to method on IndexedLineSet;
  //This will be used to simplify declaration and initialization.
  typedef void (SoVRMLIndexedLineSet::*PMILS)(SoGLRenderAction *);
                                                  
 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  // This enum is used to indicate the current material or normal binding
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
  virtual ~SoVRMLIndexedLineSet();

 private:
  // Returns current material or normal binding from action's state
  static Binding getMaterialBinding(SoAction *action);
  //static Binding getNormalBinding(SoAction *action);

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

#endif /* _SO_VRMLINDEXED_LINE_SET_ */
    

