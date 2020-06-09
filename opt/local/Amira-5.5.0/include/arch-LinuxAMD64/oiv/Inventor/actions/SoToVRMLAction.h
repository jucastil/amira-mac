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


#ifndef _SO_TOVRML_ACTION_
#define _SO_TOVRML_ACTION_


//------------------------------------------------------------------------------
// Includes

#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/fields/SoMFFloat.h>

#include <Inventor/SoType.h>

class SoConvertGuts;

/**
 * @VSGEXT Converts an Open Inventor scene graph into a VRML 1.0-style scene graph.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *   This action takes an Open Inventor scene graph and builds a new VRML 1.0 style
 *   scene graph. This scene graph can then be stored as a VRML file. The effect of
 *   this action is similar to the ivtovrml tool.
 *
 *   NOTE: During the conversion process, a temporary intermediate copy of the scene
 *   graph may be created. If your input scene graph is large, the three copies of the
 *   scene graph (initial, intermediate, and final) may use a lot of memory.
 * 
 * @SEE_ALSO
 *    SoAction,
 *    SoToVRML2Action
 * 
 * 
 */ 

class INVENTOR_API SoToVRMLAction : public SoAction
{
  SO_ACTION_HEADER(SoToVRMLAction);

public:

  /**
   * Constructor.
   */
  SoToVRMLAction () ;

  /**
   * Destructor.
   */
  ~SoToVRMLAction();

  /** Apply action to the specified root node */
  virtual void apply(SoNode *node);
  /** Apply action to the specified path */
  virtual void apply(SoPath *path);
  /** Apply action to the specified list of path */
  virtual void apply(const SoPathList &path_list, SbBool obeys_rules = FALSE);

  /**
   * Returns result as VRML style scene graph.
   */
  SoNode *getVRMLSceneGraph() const { return m_newRoot; }

  /**
   * Sets whether to read the contents of SoFile nodes into the new scene graph.
   */
  void          expandSoFile(SbBool e) { m_expandSoFile = e;}
  /**
   * Gets whether to read the contents of SoFile nodes into the new scene graph.
   */
  SbBool        areSoFileExpanded() const { return m_expandSoFile;}

  /**
   * Sets the directory in which to write VRMLInline files.
   */
  void          setUrlName(const SbString name) { m_urlName = name;}
  /**
   * Gets the directory in which to write VRMLInline files.
   */
  SbString      getUrlName() const { return m_urlName;}

  /**
   * Sets whether to put texture coordinates into the new scene graph.
   */
  void          writeTexCoords(SbBool w) { m_writeTexCoords = w;}
  /**
   * Gets whether to put texture coordinates into the new scene graph.
   */
  SbBool        areTexCoordWritten() const { return m_writeTexCoords;}

  /**
   * Sets whether to bring the contents of texture files into the new scene
   * graph , or to leave them as references to files.
   */
  void          expandTexture2Node(SbBool e) { m_expandTexture2Node = e;}
  /**
   * Gets whether to bring the contents of texture files into the new scene
   * graph , or to leave them as references to files.
   */
  SbBool        areTexture2NodeExpanded() const { return m_expandTexture2Node;}

  /**
   * Sets whether to preserve nodes of unknown type.
   */
  void          keepUnknownNodes(SbBool k) { m_keepUnknownNodes = k;}
  /**
   * Gets whether to preserve nodes of unknown type.
   */
  SbBool        areUnknownNodeKept() const { return m_keepUnknownNodes;}

  /**
   * Sets whether inline nodes are converted to VRML. If TRUE, Inline nodes are
   * converted. Default = TRUE.
   */
  void          convertInlineNodes(SbBool inlineNode) { m_inline = inlineNode;}
  /**
   * Gets whether inline nodes are converted to VRML. 
   */
  SbBool        doConvertInlineNodes() const { return m_inline; }

  /**
   * Sets whether inline nodes are conditionally converted to VRML. If TRUE, the
   * header of the Inline node is checked, and if already VRML, no conversion is
   * done. Default = FALSE.
   */
  void          conditionalConversion(SbBool conditional) { m_conditional = conditional;}
  /**
   * Gets whether inline nodes are conditionally converted to VRML. 
   */
  SbBool        doConditionalConversion() const { return m_conditional; }

 SoINTERNAL public:
  /**
   * Sets verbosity.
   * If true, the action generates messages while processing the scene graph.
   * NOTE: This method currently does nothing useful (messages are not generated).
   */
  void          setVerbosity(SbBool v) { m_verbosity = v;}
  /**
   * Returns verbosity.
   */
  SbBool        isVerbose() const { return m_verbosity;}

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

protected:

  SbBool m_inline, m_conditional;
  virtual SoConvertGuts* getNewConvertGuts() const;  
  const   SoConvertGuts* getConvertGuts() const { return m_convertGuts; }  
  virtual void beginTraversal(SoNode *) { beginTraversal();}
  virtual void endTraversal  (SoNode *) { endTraversal()  ;}

private: 

  virtual void beginTraversal();
  virtual void endTraversal  ();
  
  // new scene graph
  SoNode   *m_newRoot; 

  // if TRUE each SoFile LOD is expanded instead of being converted 
  // to Inline nodes: (default FALSE)
  SbBool m_expandSoFile;

  // base name of each inlined and SoFile sub-files (default "")
  SbString m_urlName;

  // if TRUE forces Texture Coordinates to write for all Nurbs Surfaces : (default FALSE)
  SbBool m_writeTexCoords;

  // if TRUE Expand Texture2 nodes
  SbBool m_expandTexture2Node;

  // if TRUE keeps unknown nodes instead of removing them
  SbBool m_keepUnknownNodes;

  // verbosity: is TRUE prints a lot of informations during processing
  SbBool          m_verbosity;

  SoConvertGuts *m_convertGuts;  

  void removeViewNothingCameras(SoNode *root);
  void convertLevelOfDetailToLOD(SoNode *root);

};


#endif // _SO_TOVRML_ACTION_









