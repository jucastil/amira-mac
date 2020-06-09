/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_TO_Z3D_ACTION_
#define _SO_TO_Z3D_ACTION_

#if _MSC_VER > 1000
#  pragma once
#endif // _MSC_VER

#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoSubAction.h>

#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/nodes/SoCoordinate4.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoNurbsSurface.h>
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoText2.h>
#include <Inventor/nodes/SoText3.h>
#include <Inventor/nodes/SoAsciiText.h>
#include <Inventor/VRMLnodes/SoVRMLText.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoQuadMesh.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoIndexedShape.h>
#include <Inventor/nodes/SoNurbsCurve.h>
#include <Inventor/nodes/SoNurbsSurface.h>
#include <Inventor/nodes/SoIndexedNurbsCurve.h>
#include <Inventor/nodes/SoIndexedNurbsSurface.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/VRMLnodes/SoVRMLIndexedLineSet.h>
#include <Inventor/VRMLnodes/SoVRMLIndexedFaceSet.h>
#include <Inventor/VRMLnodes/SoVRMLElevationGrid.h>
#include <Inventor/VRMLnodes/SoVRMLPointSet.h>
#include <Inventor/VRMLnodes/SoVRMLCylinder.h>
#include <Inventor/VRMLnodes/SoVRMLCone.h>
#include <Inventor/VRMLnodes/SoVRMLBox.h>
#include <Inventor/VRMLnodes/SoVRMLExtrusion.h>
#include <Inventor/VRMLnodes/SoVRMLSphere.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/elements/SoCoordinateElement.h>
#include <Inventor/nodes/SoShuttle.h>
#include <Inventor/simplifier/SoDecimator.h>
#include <Inventor/SoLists.h>
#include <Inventor/threads/SbThreadMutex.h>

#ifndef _WIN32
#  include <unistd.h>
#  if defined(__hpux) && defined(IN_PATH)
#    undef IN_PATH
#  endif
#endif

/**
 * @VSGEXT Generates a Z3D file from a scene graph.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *   This action generates a Z3D file from a scene graph. The Z3D file format is a
 *   "bandwidth-friendly" 3D protocol developed by VSG for media on the web. By
 *   convention, Z3D files have the file extension .z3d.
 *   
 *   Z3D output contains only those items from the scene graph that can be converted
 *   to Z3D format, i.e., surfaces and surface textures. Surfaces may be defined with
 *   polygons (e.g., indexed face sets) or NURBS. 3D text is polygonal data and will
 *   be included in the output file. Surface textures are stored as JPEG images.
 *   
 *   Z3D format (as of this writing) does not support:
 *   
 *   - Lines (SoLineSet, SoNurbsCurve, etc.)
 *   
 *   - Points (SoPointSet, SoMarkerSet, etc.)
 *   
 *   - Bitmaps (SoText2, SoImage, etc.)
 *   
 *   - SoVRMLElevationGrid
 *   
 *   - Lights (SoDirectionalLight, SoPointLight, etc.)
 *   
 *   - Per-vertex material binding (only per-face)
 *   
 *   - Explicit texture coordinates @BR
 *   Also note that the default texture mapping in the Z3D player is not the same as
 *   Open Inventor. In general textured objects will not appear the same in the Z3D
 *   player. 
 *   
 *   - Explicit normals @BR
 *   Also note that the default normal calculation in the Z3D player is not the same
 *   as Open Inventor. In some cases, objects will not appear the same in the Z3D
 *   player. 
 *   
 *   - Background color @BR
 *    
 *   
 *   The camera properties will be included in the Z3D file if there is a camera in
 *   the specified scene graph.
 *   
 #ifdef OIV_NET_DOC
 #else
 *   If the camera was created automatically by a viewer, then typically it will not
 *   be part of the application scene graph. To get the complete viewer scene
 *   graph:
 *  
 *   <PRE>
 *    SoNode *p = pViewer->getSceneManager()->getSceneGraph();
 *    </PRE>
 #endif
 *    Z3D format is currently intended to be a highly compressed delivery
 *   mechanism for polygonal geometry. Additional features are planned and will be
 *   incorporated into the SoToZ3DAction in the future.
 *   
 *   Because the Z3D format is optimized specifically for display, Z3D files will
 *   typically be much smaller than the corresponding Open Inventor or VRML file.
 *   However in a few cases the Z3D file may be the same size or larger, particularly
 *   if SoIndexedTriangleStripSet is the primary primitive in the scene graph.
 *   
 *   One or more temporary files may be opened by Open Inventor while creating the Z3D
 *   file.
 * 
 * @SEE_ALSO
 *    SoAction
 * 
 * 
 */ 

class INVENTOR_API SoToZ3DAction : public SoAction {

  SO_ACTION_HEADER(SoToZ3DAction);

 public:

  /**
   * Constructor.
   */
  SoToZ3DAction(int quality = 100);
  /**
   * Destructor.
   */
  ~SoToZ3DAction();
  
  /**
   * Opens the output file.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE SbBool openFile(const char *fileName);

  /**
   * Opens the output file.
   */
  SbBool openFile( const SbString& fileName );

  /**
   * Closes the output file.
   */
  void closeFile(void);

  /**
   * Sets the quality of the JPEG image file(s) used for storing texture
   * image(s). Texture quality ranges from 0 (highest compression, lowest quality) to
   * 100 (lowest compression, highest quality). The default is 100.
   */
  void setTextureQuality(int quality);
  /**
   * Queries the quality of the JPEG image file(s) used for storing texture
   * image(s). 
   */
  int getTextureQuality() const;

  // Generate the Z3D output
  void apply(SoNode *scene);
  void apply(SoPath *path);
  void apply(const SoPathList &pathList, SbBool flag = FALSE);

 SoINTERNAL public:
  // Internally used to initialize the class.
  static void initClass();
  static void exitClass();

 private:
  
  static SbThreadMutex s_mutex;

  SoDecimator *m_simplifier;
  int m_Z3DShapeNum;
  int m_currentZ3DShape;
  SoNodeStack m_separatorStack;
  
  SbString m_Z3DFileName;
  FILE *m_Z3DFile;
  
  SbString m_gzipZ3DFileName;
  FILE* m_gzipZ3DFileHandle;

  void *m_gzipZ3DFile;

  int m_collectTriangles;
  int m_quality;
  SoNodeStack m_textureStack;  // Texture stack during traversal
  SoNodeList m_textureUsed;    // Textures already saved in the Z3D file
  SbPList m_textureShapeIndex; // Shape number for each stored texture.
  
  // Indicate whether an Z3D file has been
  // opened with openFile().
  SbBool m_isOpenFile;

  SbBool m_isLibraryLoaded;


  //SbBool write(char *fileName, SoSeparator *root);

  static SoCallbackAction::Response catchShapeCB(void *object, 
                                                 SoCallbackAction *action, 
                                                 const SoNode *node);
  static SoCallbackAction::Response catchEndShapeCB(void *object, 
                                                    SoCallbackAction *action, 
                                                    const SoNode *node);
  static SoCallbackAction::Response catchSeparatorNodesCB(void *object, 
                                                          SoCallbackAction *action, 
                                                          const SoNode *node);
  static SoCallbackAction::Response catchEndSeparatorNodesCB(void *object, 
                                                             SoCallbackAction *action, 
                                                             const SoNode *node);
  static SoCallbackAction::Response catchTextureNodesCB(void *object, 
                                                        SoCallbackAction *action, 
                                                        const SoNode *node);
  
  SoCallbackAction::Response catchShape(SoCallbackAction *, const SoNode *);
  SoCallbackAction::Response catchEndShape(SoCallbackAction *, const SoNode *);
  SoCallbackAction::Response catchSeparatorNodes(SoCallbackAction *, const SoNode *);
  SoCallbackAction::Response catchEndSeparatorNodes(SoCallbackAction *, const SoNode *);
  SoCallbackAction::Response catchTextureNodes(SoCallbackAction *, const SoNode *);

  static void addTriangleCB(void *userData,
                            SoCallbackAction *action,
                            const SoPrimitiveVertex *vertex1,
                            const SoPrimitiveVertex *vertex2,
                            const SoPrimitiveVertex *vertex3);
  void addTriangle(SoCallbackAction *action,
                   const SoPrimitiveVertex *vertex1,
                   const SoPrimitiveVertex *vertex2,
                   const SoPrimitiveVertex *vertex3);

  void ReverseWrite(FILE *file, void *ptr, int num, int sizetype);
  int SaveNurbsCurveToZ3D(SoCallbackAction *, SoNurbsCurve *);
  int SaveNurbsSurfaceToZ3D(SoCallbackAction *, SoNurbsSurface *);
  int SaveIndexedFaceSetToZ3D(SoCallbackAction *, SoIndexedFaceSet *);
  int SaveColorToZ3D(SoCallbackAction *);
  int SaveTextureToZ3D(SoCallbackAction *);
  int SaveGeomToZ3D(SoCallbackAction *);
  int SaveJpegImage(const unsigned char *image, int sizeX, int sizeY, int numComps);
  void SaveViewpoint(SoNode *);
  void SaveBackground(SoNode *);

};

#endif // _SO_TO_Z3D_ACTION_

