/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef SO_TO_U3D_ACTION_H
#define SO_TO_U3D_ACTION_H

#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoSubAction.h>
#include <HardCopy/SoHardCopy.h>

class SoToU3DActionPrivate;
class SoPath;

/** 
 * @HCEXT Export a scene graph to a U3D file.
 * 
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 * This class can export an Open Inventor scenegraph to a U3D file.
 * U3D files can be used to import a 3D scene into a PDF file.
 * For a simple PDF export, see SoToPDFAction.
 *
 * U3D is a much simpler format than the Open Inventor scene graph and limits
 * what can be exported.
 * 
 * @B Limitations @b
 *  - Rendering
 *    - Modeling clipping (SoClipPlane) is ignored.
 *    - Drawstyle is ignored.
 *  - Lines
 *    - Per-vertex coloring and lighting are not supported on lines.
 *    - Precision issue on line vertices. Point locations may drasticaly diverge from orginal. 
 *      Since this problem increases with the number of vertices per shape, try to split lines into smaller shapes.
 *  - Points
 *    - Coloring is not supported on points.
 *  - Textures
 *    - Only MODULATE and REPLACE texture models are supported.
 *    - Only REPEAT and CLAMP texture wraps are supported.
 *    - Multitexturing is not supported.
 *  - Text
 *    - Textured Text3 and Text2 are converted into polygonal Text3.
 *  - Lights
 *    - Lights affect the whole scenegraph no matter where they are placed in the scenegraph.
 *    - Per-vertex lighting is precomputed with default lights.
 *    - Two-sided lighting is not supported. Incorrect normals will result in black triangles.
 *      However note that the end user can enable two sided rendering in the Acrobat Reader
 *      preferences dialog under the "3D & Multimedia" tab.
 *  - Cameras
 *    - Multiple cameras are ignored, only the main scenegraph is exported (no legends, logos...).
 *    - PoViews (PoSceneView, PoView, PoBaseView) are not supported.
 *  - Miscellaneous
 *    - FXViz representations are not supported.
 *    - Engines are ignored.
 *    - Dragger shapes are not exported.
 *  - VolumeViz
 *    - VolumeViz representations are not supported, except orthoslice, obliqueslice and volumeskin.
 *    - VolumeViz slices are exported with their current LOD (NB: LOD is minimal if the node has never been rendered).
 *    - LDM volumes with overlap of zero will not export correctly (gaps between tiles
 *      will be visible.
 *    - ROIs are ignored.
 *    - Lighting on VolumeViz slices is not supported.
 *    - VolumeViz slices are exported as simple RGBA textures (no colormap), which impacts visual quality (as if useRGBA field set)
 * 
 * @B Tips @b
 * - Node names
 *   - Node names are exported for SoSeparator and SoShape, as well as all derived classes.
 *     These names will appear in the "Model Tree" in Acrobat Reader.  The end user can set
 *     visibility, render mode, etc for each object.  You can also use these names in
 *     JavaScript functions that manipulate the model in the PDF file.
 *   - Separator nodes with no assigned name will appear in the tree as "Group-XXX" and
 *     Shape nodes with no assigned name will appear in the tree as "Model-XXX", where
 *     "XXX" is the address of the node (just to make the name unique).
 *   - Names in the U3D file must be unique.  Nodes with duplicate names will have a
 *     numeric value automatically appended to their name.
 * - Lights: Lights in the scene graph will be exported.  However note that the viewer's
 *   headlight will be exported as a directional light with a fixed position (it will not
 *   automatically rotate with the camera).  If Acrobat Reader finds lights in the U3D
 *   file it will use those lights.  So it may be better to export without lights and
 *   also to turn off the viewer's headlight before exporting to U3D.  Note that one of
 *   the lighting options in Acrobat Reader is a headlight (that rotates with the camera).
 * - Camera: If the action finds a camera in the scene graph, that camera will define
 *   the default view for the model in the PDF file.  Therefore if you apply the action
 *   to a Separator above the viewer's camera, the exported model will be displayed with
 *   the current on-screen view.
 * - Background color: You can export a background color using an SoGradientBackground
 *   node.  The exported color will be the average of the color0 and color1 fields.
 *   However you can also change the background color using Adobe Acrobat Pro after
 *   inserting the U3D file in a PDF.
 * - Two sided rendering: If the back faces of your geometry are black when displayed in
 *   Acrobat Reader, you may want to advise your users to enable the two sided rendering
 *   option in Reader's Preferences dialog under the "3D & Multimedia" tab.
 * - Tools:
 *   - You can use the commercial tool Adobe Acrobat Pro to create and modify PDFs
 *     with embedded U3D content.  Adobe calls this content "3D annotations".
 *   - You can also use open source tools like pdflatex, with the movie15 package,
 *     to create a PDF file with embedded 3D from a LaTeX source file.
 *
 * @B Use case @b
 *  \code
 *  SoHardCopy::init();
 *  ...
 *  // setup the root scene graph to export
 *  SoSeparator* root = new SoSeparator;
 *  ...
 *  SoToU3DAction u3dAction;
 *  bool result = u3dAction.openFile( "output.u3d" );
 *  if ( !result )
 *  {
 *     // Report error
 *  }
 *  u3dAction.apply( root );
 *  result = u3dAction.closeFile();
 *  if ( !result )
 *  {
 *     // Report error
 *  }
 * \endcode
 *
 * @B Warning @b 
 *  - On some platforms, some applications may encounter problems loading, 
 *    displaying an error message like: "IFXOSFileIterator::ProcessDir: 
 *    error opening /usr/local/u3d/lib/Plugins/ No such file or directory".
 *    In this case, declare the environment variable U3D_LIBDIR (UNIX only) and set it with 
 *    the path to the Open Inventor libraries ($OIVHOME/lib).
 *  - It is now possible to specify a directory name which will contain the U3D plug-ins by
 *    setting the environment variable U3D_PLUGINS_DIRNAME for instance: "U3DPlugins".
 *    Important: This is not a path to the directory. Moreover this directory must remain in 
 *    the same folder as IFXCore.so/dll.
 *  - By default this action always uses the alternate representation of an SoNode derived 
 *    class (if one exists).
 *  - The U3D_LIBDIR path is limited to 103 characters, path plus filename. If this length 
 *    is exceeded, an error message is outputed and U3D library is not loaded.
 *
 * @SEE_ALSO 
 *    SoToPDFAction.
 *
 */

class HARDCOPY_API SoToU3DAction : public SoCallbackAction
{
  SO_ACTION_HEADER(SoToU3DAction);

public:

  /*
   * Constructor
   */
  SoToU3DAction();

  /*
   * Destructor
   */
  virtual ~SoToU3DAction();

  /**
   * Set the U3D output file. Returns false if an error has occured. 
   *
   * @UNICODE_WARNING
   * Use the SbString version instead.
   */
  SoNONUNICODE bool openFile( const char* filename );

  /**
   * Set the U3D output file. Returns false if an error has occured. 
   */
  bool openFile( const SbString& filename );


  /**
   * Finalize export to the U3D output file. Returns false if an error has occured. 
   */
  bool closeFile();

  // Apply methods

  /**
   * Initiates an action on the graph specified by a node.
   */
  virtual void apply( SoNode* node );

  /**
   * Initiates an action on the graph specified by a path.
   */
  virtual void apply( SoPath* path );

  /**
   * Initiates an action on the graph specified by list of paths.
   * TRUE can be passed for the @B obeysRules @b flag if the given path list has the 
   * following four properties:
   *   - All paths have the same head node,
   *   - Paths are sorted in traversal order,
   *   - If one path ends at node A, no other path continues through A,
   *   - No two paths are the same.
   *
   * These rules will be obeyed by path lists returned by picking and by searches 
   * for non-group nodes.
   */
  virtual void apply( const SoPathList& pathList, SbBool obeysRules = false );

  /** 
   * Forces SoText2 nodes to be exported using SoText3 (default is true).
   */
  void forcePolygonalText3( bool force );

  /** 
   * Returns true if polygonal text3 is forced (see forcePolygonalText3).
   */
  bool isPolygonalText3Forced() const;

  /** 
   * Allow the export of draggers (default is true).
   */
  void setExportDraggers( bool force );

  /** 
   * Returns true if draggers are exported.
   */
  bool areDraggersExported() const;

SoINTERNAL public:
  /**
   * Internally used to initialize the class.
   */
  static void initClass();
  static void exitClass();

  // Internal use only.
  const SoToU3DActionPrivate* getImpl() { return m_private; }

  virtual void beginTraversal( SoNode* node );

  const SoPath* getCurPath();

  SoToU3DActionPrivate* m_private;

private:

  // static callbacks
  static SoCallbackAction::Response separatorPreCBS  ( void* userData, SoCallbackAction* action, const SoNode* node );
  static SoCallbackAction::Response separatorPostCBS ( void* userData, SoCallbackAction* action, const SoNode* node ); 
  static SoCallbackAction::Response environmentPreCBS( void* userData, SoCallbackAction* action, const SoNode* node );
  static SoCallbackAction::Response lightPreCBS      ( void* userData, SoCallbackAction* action, const SoNode* node );
  static SoCallbackAction::Response cameraPreCBS     ( void* userData, SoCallbackAction* action, const SoNode* node );
  static SoCallbackAction::Response backgroundPreCBS ( void* userData, SoCallbackAction* action, const SoNode* node );
  static SoCallbackAction::Response shapePreCBS      ( void* userData, SoCallbackAction* action, const SoNode* node );
  static SoCallbackAction::Response shapePostCBS     ( void* userData, SoCallbackAction* action, const SoNode* node );
  static SoCallbackAction::Response draggerPreCBS    ( void* userData, SoCallbackAction* action, const SoNode* node );
  static void shapeTriangleCBS( void* userData, SoCallbackAction *action, 
                                const SoPrimitiveVertex *v1, const SoPrimitiveVertex *v2, const SoPrimitiveVertex *v3 );
  static void shapeLineCBS    ( void* userData, SoCallbackAction* action, 
                                const SoPrimitiveVertex* v1, const SoPrimitiveVertex* v2 );
  static void shapePointCBS   ( void* userData, SoCallbackAction* action, 
                                const SoPrimitiveVertex* v1 );

  bool m_forcePolygonalText3, m_exportDraggers;
};

#endif // SO_TO_U3D_ACTION_H
