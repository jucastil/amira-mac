/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Dec 2001)
**=======================================================================*/
#ifndef SOTVIZTEXTUREPREPROCESSOR_H
#define SOTVIZTEXTUREPREPROCESSOR_H

#include <Inventor/image/SbRasterImage.h>
#include <TerrainViz/nodes/SoTVizPreprocessor.h>
#include <TerrainViz/SbTVizTextureList.h>


class Array2Duchar3;


/**
 * 
 * @TVEXT Class used for texture preprocessing.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *   This class allows preprocessing of multiple texture files.
 *
 *   Please see SoTVizPreprocessor for datum and ellipsoid definitions and compatibility.
 *
 *   Input can be raster files with geo-referencing (GeoTiff and Tiff-Tfw supported),
 *   or classic raster files
 *   (see SoRasterImageRW for the list of supported formats) with separate geo-referencing 
 *   information in a geodetic coordinate system.
 *
 *   "Geodetic" is the horizontal and vertical position.
 *   The positions are commonly UTM x/y/z or latitude, longitude, elevation triplets.
 *
 *  @IMAGE DTM_geodetic.jpg
 *
 *   The output is a balanced (all tree levels available) or unbalanced quadtree of textures, 
 *   used by the SoTVizRender class.
 *
 *   Each output texture is characterized by its level and position in the tree.
 *   Each texture is saved as a PNG file (no transparency managed).
 *
 *   The writeToXML method exports the quadtree description to be read by 
 *   SoTVizRender.
 *
 * @SEE_ALSO
 *    SoTVizPreprocessor
 * 
 * 
 */ 


class TERRAINVIZ_API SoTVizTexturePreprocessor : public SoTVizPreprocessor
{
 public:


  /**
   * Constructor.
   */
  SoTVizTexturePreprocessor();
        
  
  /**
   * Destructor.
   */
  virtual ~SoTVizTexturePreprocessor();


  /**
   * 
   * Processes the file list and generates a list of PNG files.
   *
   */
   SbBool process();

  /**
   * Sets the maximum tree depth not to exceed.
   */
  void setMaximumDepth(int maxDepth);

  /**
   * Returns the texture quadtree depth.
   */
  int getQuadTreeDepth() const;

  /**
   * Sets the maximum size in pixels of the textures to be generated.
   * If not called, the maximum texture size will match the OpenGL driver capabilities.
   * Otherwise, the value will be rounded down to the largest power of two that is less than
   * the specified value, @B even if this value exceeds the hardware capabilities. @b
   */
  static void setMaxTextureSize(int size);


  /**
   * Returns the maximum size in pixels of the textures to be generated.
   */
  static int getMaxTextureSize();


  /**
   * Adds a georeferenced file to the preprocessor.
   */
  SbBool addFile(const SbString& filePath);

  /** 
   * Adds a raster file to the preprocessor.
   * Coordinates are given in the geodetic system.
   * The origin is the lower left corner.
   * @B orientation@b is the width vector of the bitmap in the geodetic system.
   */
  SbBool addFile(const SbString& filePath, const SbVec2d& origin, const SbVec2d& orientation,
                 const SbVec2d& step, TVIZUnits units);


  /** 
   * Adds an overlay raster file (transparent raster) to the preprocessor.
   * Coordinates are given in the geodetic system.
   * The origin is the lower left corner.
   * @B orientation@b is the width vector of the bitmap in the geodetic system.
   */
  SbBool addOverlayFile(const SbString& filePath, const SbVec2d& origin, const SbVec2d& orientation,
                        const SbVec2d& step, TVIZUnits units);


  /**
   * Writes resulting elevation and textures description in a 
   * TerrainViz XML file.
   * Note this is a file name, not a path. The path used is the one given by #setDestDirectory.
   * Both preprocessors (textures and data) must reference the same file.
   */
  SbBool writeToXML(const SbString& fileName);


 protected:


 private:

  static int  m_maxTextureSize;

  SbBool* m_levelAvailability;
  SbPList m_overlayFiles;

  class TVIZFileInfo {
  public: 
    SbString fileName;
    SbVec2s  position;
    int      level;
    SbVec2s  borders;
  };

  class TexTree {
  public:
    int     level;
    SbVec2d step;
  };


  SbPList m_fileList;
  int depth;
  int m_maxDepth;

  
  TVIZInputFile* addRaster(const SbString& filePath, const SbVec2d& origin, const SbVec2d& orientation, const SbVec2d& step, TVIZUnits units, SbBool isOverlay);
  SbBool isFileNecessary(TVIZInputFile* inFile);
  SbBool readRaster(TVIZInputFile* file, SbRasterImage &rasterImage, SbBool infoOnly);
  void loadAndTransformGeoTiff(TVIZInputFile* g0, Array2Duchar4*& zoneBuffer, SbBox2d& resultBox, SbVec2s& resultSize);
  void loadAndTransformRaster(TVIZInputFile* g0, SbTVizTexture*& srcTex);
  void mergeInPatch(TVIZInputFile* g0, SbBox2d& resultBox, Array2Duchar4* patchBuffer, SbBox2d& patchGeodeticROI, TexTree* levelList, int level);
};


#endif
