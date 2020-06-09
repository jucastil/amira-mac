/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : SGI (MMM YYYY)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : Pascal DOUX (May 1998)
**=======================================================================*/


#ifndef _SO_TOVRML2_ACTION_
#define _SO_TOVRML2_ACTION_


//------------------------------------------------------------------------------
// Includes

#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoToVRMLAction.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/fields/SoMFFloat.h>

#include <Inventor/SoType.h>

/**
 * @VSGEXT Converts an Open Inventor scene graph into a VRML 2.0-style scene graph.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *   This action takes an Open Inventor scene graph and builds a new VRML 2.0-style
 *   scene graph. This scene graph can then be stored as a VRML file. The effect of
 *   this action is similar to the effect of the ivtovrml tool.
 *   
 *   During the conversion process, a temporary intermediate copy of the scene
 *   graph may be created. If your input scene graph is large, the three copies of the
 *   scene graph (initial, intermediate, and final) may use a lot of memory.
 *   
 *   There is not always an exact match between Open Inventor items and VRML 2.0
 *   items. Some Open Inventor items, for example, 2D text (SoText2) do not exist in
 *   VRML 2.0 and will not be converted. Other items may be converted, but with
 *   subtle differences in behavior. 
 *   
 *   @B Texture Modeling @b: 3- and 4-component textures work differently in Open
 *   Inventor and VRML 2.0. In Open Inventor, by default, the texture color is
 *   @I multiplied by @i the material surface color ("modulate" mode). In VRML 2.0,
 *   a texture's RGB colors and transparency @I replace @i the material's current
 *   diffuse color and transparency (like "decal" mode). For example, if an object is
 *   red with a colored texture, in Open Inventor, the red would affect the
 *   appearance of the object. Once converted to VRML 2.0, the object would display
 *   the colors of the texture, without any influence of the red. 
 *   
 *   @B Texture Coordinates @b: Open Inventor and VRML 2.0 handle texture coordinates
 *   differently. If your scene graph uses texture coordinates for precise
 *   application of a texture to a shape, the visual results may be different after
 *   conversion to VRML 2.0.
 * 
 * @SEE_ALSO
 *    SoAction,
 *    SoToVRMLAction
 * 
 * 
 */ 

class INVENTOR_API SoToVRML2Action : public SoToVRMLAction
{
  SO_ACTION_HEADER(SoToVRML2Action);

public:

  /**
   * Constructor.
   */
  SoToVRML2Action () ;

  /**
   * Destructor.
   */
  ~SoToVRML2Action();

  /** Apply action to the specified root node */
  virtual void apply(SoNode *node);
  /** Apply action to the specified path */
  virtual void apply(SoPath *path) { SoToVRMLAction::apply(path); }; // no warning
  /** Apply action to the specified list of path */
  virtual void apply(const SoPathList &path_list, SbBool obeys_rules = FALSE) { SoToVRMLAction::apply(path_list, obeys_rules); }; // no warning

  /**
   * Returns result as VRML 2.0 scene graph
   */
  SoVRMLGroup *getVRML2SceneGraph() const { return m_newVRML2Root; }

  /**
   * Sets whether shared materials should be organized into shared appearance
   * nodes in the new scene graph.
   */
  void   reuseAppearanceNodes(SbBool appearance) { m_appearance = appearance;}
  /**
   * Returns whether shared materials should be organized into shared appearance
   * nodes in the new scene graph.
   */
  SbBool doReuseAppearanceNodes() const { return m_appearance; }

  /**
   * Sets whether shared properties should be organized into shared nodes in the
   * new scene graph.
   */
  void   reusePropertyNodes(SbBool property) { m_property = property;}
  /**
   * Returns whether shared properties should be organized into shared nodes in the
   * new scene graph.
   */
  SbBool doReusePropertyNodes() const { return m_property; }

  /**
   * Sets whether shared geometry nodes should be shared in the new scene graph.
   */
  void   reuseGeometryNodes(SbBool geometry) { m_geometry = geometry;}
  /**
   * Returns whether shared geometry nodes should be shared in the new scene graph.
   */
  SbBool doReuseGeometryNodes() const { return m_geometry; }

  void          expandTexture2Node(SbBool e) { m_expandTextureNodes = e;}
  SbBool        areTextureNodeExpanded() const { return m_expandTextureNodes;}

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  //private: 
protected:

  // new scene graph
  SoVRMLGroup   *m_newVRML2Root; 

  // Reuse flags: if TRUE do not reuse existing appearance nodes, geometry property nodes, 
  // or geometry nodes.
  // default FALSE
  SbBool m_appearance, m_property, m_geometry , m_expandTextureNodes;

};


#endif // _SO_TOVRML2_ACTION_









