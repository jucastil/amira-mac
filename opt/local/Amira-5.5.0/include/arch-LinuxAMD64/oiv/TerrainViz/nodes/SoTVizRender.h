/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Feb 2001)
**=======================================================================*/
#ifndef SOTVIZRENDER_H
#define SOTVIZRENDER_H

#include <TerrainViz/nodes/SoTViz.h>
#include <stdio.h>
#include <TerrainViz/SbTVizData.h>
#include <TerrainViz/SbTVizTextureList.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <TerrainViz/SbTVizColorScale.h>
#include <Inventor/fields/SoSFNode.h> 

class SiTVizFrustumManager;
class SiTVizTextureManager;
class SiTVizTesselator;
class SiTVizContouringManager;
class SoCache;


/**
 * @TVEXT Renders the terrain.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *   The TerrainViz extension allows terrain visualization using an auto-adaptive
 *   mesh technique and a quadtree of textures. It uses a multi-resolution technique
 *   that re-meshes the terrain at every frame with a constant number of triangles.
 *   The local mesh accuracy depends on the point of view and the altitude gradient.
 *   The texture level depends on the point of view only.
 *   
 *   TerrainViz attempts to render the terrain at a constant frame rate.
 *   
 *   Controls are provided for adjusting quality versus performance.
 *   
 *   SoTVizRender is the shape node of TerrainViz. It re-computes the mesh at every
 *   frame.
 *
 *   Normals are enabled/disabled by the #normals field. By default they are enabled.
 *   Until TerrainViz V2.0, normals were activated in the terrain model 
 *   when the creaseAngle of the current 
 *   SoShapeHints was different from 0. For compatibility with this older
 *   behavior, use environment
 *   variable TVIZ_COMPAT_20 (see also SoPreferences). 
 *
 *   Normals are memory consuming. If enabled, normals are pre-computed.
 *   The memory used by pre-computed normals is not freed until a new SbTVizData 
 *   is supplied in order 
 *   not to slow down the frame rate when changing and changing again the #normals field value.
 * 
 *   The terrain can be mapped with a texture tree using an SbTVizTextureList node,
 *   or with color mapping using an SbTVizColorScale node (color changes depending on altitude).
 *   
 *   All values are expressed as modeling coordinates.
 * 
 *   Data (terrain altitudes and textures) can be provided two different ways:
 *   
 *   - @B Using classes: @b
 *        - SbTVizData for elevations and SbTVizTexturelist for the textures.
 *        - Use setData() and setTextureList() to connect this data to the node.
 *   
 *   - @B Using an XML file: @b
 *        - Use the loadFromXML() method (elevations and textures provided in the XML
 *          file).
 *   
 *   The mesh computation is controlled by several fields.
 *
 * NOTE: SoTVizRender is not meant to be exported as an .iv file 
 * because it uses SbTVizData/SbTVizTextureList/SbTVizTexture 
 * instances containing the data (elevations, textures).
 * The way to save a terrain scene is to export it to an XML file
 * referencing an elevation data file and image files for textures.
 * Use writeToXML to export your scene and loadFromXML to retrieve it.
 * 
 *   
 *   @TABLE_1B
 *
 *   @B XML FILE FORMAT @b 
 *
 *   @TR \< !-- TGS TerrainViz X.X --\> @TD File header with TerrainViz version in XML comment format.
 *
 *   @TR \<TerrainViz\>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
 *   @TD Begins the file.
 *   
 *   @TR \<data\> @TD Begins the data block.
 *   
 *   @TR \<format\> @I\<value\>@i \</format\> 
 *   @BR Ex: \<format\> "REGULARGRID" \</format\> 
 *   @TD Specificies the format.
 *   Can be "REGULARGRID" (data is organized in a 2D array).
 *   Default: "REGULARGRID".
 *   
 *   @TR \<fileName\> @I\<value\>@i \</fileName\>
 *   @BR Ex: \<fileName\> "elevation.dat" \</fileName\> 
 *   @TD Data file name between "".
 *   
 *   @TR \<step\> @I\<value\>@i \</step\>
 *   @BR Ex: \<step\> (2.5E-4, 2.5E-4, 2.5E-4) \</step\> 
 *   @TD Sample size along the three dimensions.
 *   
 *   @TR \<realOffset\> @I\<value\>@i \</realOffset\>
 *   @BR Ex: \<realOffset\> (0., 0., 0.) \</realOffset\>
 *   @TD Offset of the terrain. 
 *   The terrain starts at (x=0, y=0, z(0, 0)) by default.
 *   Default (0., 0., 0.).
 *   
 *   @TR \<encoding\> @I\<value\>@i \</encoding\>
 *   @BR Ex: \<encoding\> "BIG_ENDIAN" \</encoding\>
 *   @TD Can be "LITTLE_ENDIAN" or "BIG_ENDIAN".
 *   UNIX systems are generally big endian whereas Intel systems are usually little
 *   endian. This field must refer to the system encoding where the binary file was
 *   created (necessary for binary files).
 *   
 *   @TR \<openMode\> @I\<value\>@i \</openMode\>
 *   @BR Ex: \<openMode\> "BINARY" \</openMode\>
 *   @TD Can be "ASCII" or "BINARY".
 *   Tells if the file is binary or ASCII. In the binary case, the encoding field is
 *   necessary.
 *   
 *   @TR \<type\> @I\<value\>@i \</type\>
 *   @BR Ex: \<type\> "UCHAR" \</type\>
 *   @TD Gives the data type (unsigned char, unsigned short, or float).
 *   Can be "UCHAR", "USHORT", "UINT", "FLOAT", "CHAR", "SHORT", "INT".   
 *   
 *   @TR \</data\>
 *   @TD Ends the data block.
 *   
 *   @TR \<texture\> 
 *   @TD Begins the texture block.
 *   
 *   @TR \<fileName\> @I\<value\>@i \</fileName\>
 *   @BR Ex: \<fileName\> "tex00.jpg" \</fileName\>
 *   @TD Texture file name between "".
 *   
 *   @TR \<level\> @I\<value\>@i \</level\>
 *   @BR Ex: \<level\> 0 \</level\>
 *   @TD Level of the texture. This is the level of the quadtree in which this texture
 *   appears. Levels start at 0.
 *   
 *   @TR \<position\> @I\<value\>@i \</position\>
 *   @BR Ex: \<position\> (0, 0) \</position\> 
 *   @TD Position of the texture. This is the position of the texture inside the level.
 *   Can be omitted if level is zero.
 *   
 *   @TR \</texture\>
 *   @TD Ends the texture block.
 *   
 *   @TR \</TerrainViz\>
 *   @TD Ends the file.
 *   
 *   @TR NOTE: @TD Blocks are order independent. 
 *    Fields within the parent block are order independent
 *   too. There should be one data block and zero or more texture blocks.
 *
 *   @TABLE_END  
 *
 * @FILE_FORMAT_DEFAULT
 *    TVizRender {
 *    @TABLE_FILE_FORMAT
 *       @TR camera                    @TD NULL
 *       @TR maxRenderedTriangles      @TD 2500
 *       @TR triangleSizeAttenuation   @TD 2.0  @TD deprecated
 *       @TR distanceAttenuation       @TD 3.4  @TD deprecated
 *       @TR mappingMode               @TD TVIZ_TEXTURES
 *       @TR frustumCulling            @TD TRUE
 *       @TR normals                   @TD TRUE 
 *       @TR normalQuality             @TD TVIZ_32BIT_NORMALS
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SbTVizData,
 *    SbTVizRegularGridData,
 *    SbTVizTexture,
 *    SbTVizTextureList,
 *    SoTViz
 * 
 * 
 */ 

class TERRAINVIZ_API SoTVizRender : public SoShape {
  SO_NODE_HEADER(SoTVizRender);

 public:

  enum MappingMode {
    /**
     *  Mapping uses the textures.
     */
    TVIZ_TEXTURES = 0,
    /**
     *  Mapping uses the color scale.
     */
    TVIZ_COLORSCALE
  };

  enum NormalQuality {
    /**
     * 
     *  Pre-computed normals are packed as 32-bit values.
     */
    TVIZ_32BIT_NORMALS = 0,
    /**
     * 
     *  Pre-computed normals are packed as 64-bit values.
     */
    TVIZ_64BIT_NORMALS
  };

  enum CopyPolicy {
    /**
     *  TerrainViz will make a copy of the data.
     */
    COPY = 0,
    /**
     *  Passed buffer used, user will delete (default).
     */
    NO_COPY = 1,
    /**
     *  Passed buffer used, SoTVizRender will delete.     
     */
    NO_COPY_AND_DELETE = 2
  };
  
  /**
   * Constructor.
   */
  SoTVizRender();

  /**
   * Loads a TerrainViz description file (XML) and initializes the members SbTVizData
   * and SbTVizTextureList.
   * 
   * Returns TRUE if loaded successfully, FALSE otherwise.
   *
   * NOTE: In this case, files referenced in this XML file (elevation & textures) must 
   * be specified with an absolute path as the path of the XML file is unknown.
   */
  SbBool loadFromXML(const FILE* fd);
  /**
   * Loads a TerrainViz description file (XML) and initializes the members SbTVizData
   * and SbTVizTextureList.
   * 
   * Returns TRUE if loaded successfully, FALSE otherwise.
   */
  SbBool loadFromXML(const char* fileName);

  /**
   * Sets the elevation data.  
   * If TVIZ_COMPAT_20 is defined, the copy policy default is NO_COPY_AND_DELETE.
   */
  void setData(const SbTVizData* data, CopyPolicy cp = SoTVizRender::NO_COPY);
  /**
   * Returns the elevation data.
   */
  const SbTVizData* getData() const;
  /**
   * Sets the texture list. 
   * If TVIZ_COMPAT_20 is defined, the copy policy default is NO_COPY_AND_DELETE.
   */
  void  setTextureList(const SbTVizTextureList* texList, CopyPolicy cp = SoTVizRender::NO_COPY);
  /**
   * Returns the texture list.
   */
  const SbTVizTextureList* getTextureList() const;
  /**
   * Sets the color scale for contouring/shading. 
   * If TVIZ_COMPAT_20 is defined, the copy policy default is NO_COPY_AND_DELETE.
   */
  void   setColorScale(const SbTVizColorScale* colorScale, CopyPolicy cp = SoTVizRender::NO_COPY);
  /**
   * Returns the color scale for contouring/shading.
   */
  const  SbTVizColorScale* getColorScale() const;


  /**
   * Writes the node description (elevation and textures) in a TerrainViz file as
   * shown above.
   * 
   */
  SbBool writeToXML(const SbString& fileName);
  /**
   * Writes the node description (elevation and textures) in a TerrainViz file as
   * shown above.
   * 
   */
  SbBool writeToXML(const char* fileName);

        
  /**
   * Displays the look-at vector
   * 
   */
  void showTarget(SbBool state);


  // Fields
  /**
   * Specifies the camera to be used for real-time mesh processing.
   * If NULL, the current camera is used.
   */
  SoSFNode camera;



  /**
   * Specifies the maximum number of rendered triangles. The number of triangles
   * displayed can be decreased using the #distanceAttenuation field.
   */
  SoSFInt32 maxRenderedTriangles;


  /**
   * @deprecated This field should not be used anymore.
   * Specifies the value used in the function
   * @B 1/distance^triangleSizeAttenuation @b which specifies the triangle size
   * variation according to the distance. In other words, this field adjusts the mesh
   * density. Larger values cause the triangle size to increase more rapidly (or
   * conversely, the mesh density decreases more rapidly).
   *
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoSFFloat triangleSizeAttenuation;

  /**
   * @deprecated This field should not be used anymore.
   * This field allows the user to decrease the number of triangles displayed as the
   * camera gets further from the terrain.
   * If @B s @b is the largest dimension of the terrain, and 
   * @B d @b is the distance between the camera and the terrain, and
   * - if @B d @b * #distanceAttenuation <= s then 
   *   - #maxRenderedTriangles are displayed.
   * - else 
   *   - the number of triangles decreases according to @B 1/d^2 @b.
   *
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoSFFloat distanceAttenuation;

  /**
   * Mapping mode.
   * Two modes are available: 
   * - you can map textures on the terrain using an SbTVizTextureList node.
   * - or do color mapping using an SbTVizColorScale node.
   */
  SoSFEnum  mappingMode;


  /**
   * 
   * Enables frustum culling so that the invisible parts of the terrain
   * are not rendered.
   */
  SoSFBool  frustumCulling;


  /**
   * Enables/disables the normals at each vertex. Default is TRUE.
   */
  SoSFBool  normals;

  /**
   * Sets the normal quality.
   * Default value is: TVIZ_32BIT_NORMALS
   * If the lighting of the terrain has black areas, you can 
   * increase the normal precision (e.g., specify TVIZ_64BIT_NORMALS) 
   * to remove this artifact.
   */
  SoSFEnum  normalQuality;

 SoEXTENDER public:
  virtual void GLRender(SoGLRenderAction *action);
  virtual void generatePrimitives(SoAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);


 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoTVizRender();

  // Computes bounding box of the terrain
  virtual void  computeBBox(SoAction *action, SbBox3f &box,
                            SbVec3f &center);


 private:
  void firstRender(SoAction* action, SbBool useNormals);
  void updateFrustumManager(SoState *state, SbViewVolume *viewVolume);
  SbBool isCacheValid(SoState *state);
  SbBool extractDirectory(const char* fileName, SbString& directory);

  SbTVizData*               m_data;
  SbTVizTextureList*        m_texList;
  SiTVizFrustumManager*     m_frustumMgr;
  SiTVizTextureManager*     m_textureMgr;
  SiTVizTesselator*         m_tesselator;
  SiTVizContouringManager*  m_contouringMgr;
  SbTVizColorScale*         m_colorScale;
  SbBool                    m_firstRender;
  SbMatrix                  m_currentModelMatrix;
  SbMatrix                  m_TVIZModelMatrix;
  SbBool                    m_showTarget;
  SbBool                    m_renderingFlag;
  SoCache*                  m_sceneCache;               
  uint64_t                  m_lastNodeId;
  float                     m_aspectRatio;
  char                      m_currentDir[2048];

  SbBool                    m_TVIZCompat20;
  CopyPolicy                m_deleteTextureListIfNewer;
  CopyPolicy                m_deleteDataIfNewer;
  CopyPolicy                m_deleteColorScaleIfNewer;

  ///////////////////////EXCEPTION METHODS/////////////////////////////////////
  //
  // #grouped loadFromXML(char * fileName)
  // #grouped getData()
  // #grouped getTextureList()
  // #grouped writeToXML(char * fileName)
  //
  /////////////////////////////////////////////////////////////////////////////

};

#endif

