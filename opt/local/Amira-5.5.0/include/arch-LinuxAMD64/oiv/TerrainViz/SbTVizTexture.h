/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Feb 2001)
**=======================================================================*/

#ifndef SBTVIZTEXTURE_H
#define SBTVIZTEXTURE_H

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/sys/SoGLType.h>

class Array2D;
class Array2Duchar;

/**
 * @TVEXT Texture class.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *   This class loads and stores a texture file. It also handles the attributes of
 *   the texture to fit the texture quadtree.
 *   
 *   Each texture is characterized by its level in the the texture list quadtree, its
 *   position in this level, the number of color components, and its pixel size.
 *   
 *   This texture is to be used with an SbTVizTextureList instance.
 *
 *   See SbTVizTextureList for more details on texture levels and positions.
 *   
 *   By default the level is 0 and the position is (0,0).
 *   
 *   If the texture image's width or height is not a power of 2, or the image's width
 *   or height is greater than the maximum supported by OpenGL, then the image will
 *   be automatically scaled up or down to the next power of 2 or the maximum texture
 *   size. For maximum speed, point-sampling is used to do the scale; if you want
 *   more accurate resampling, pre-filter images to a power of 2 smaller than the
 *   maximum texture size (use the OpenGL glGetIntegerv(GL_MAX_TEXTURE_SIZE...) call
 *   to determine the maximum texture size for a specific OpenGL implementation).
 *   
 *   The following file formats are supported: SGI RGB, GIF, JPEG, PNG, TIFF, and
 *   (Windows only) BMP. 
 *
 *   When data are specified from a file (#loadTextureFile), there is no buffer copy
 *   remaining after the data are sent to OpenGL.
 *   When data are specified from a buffer (#setValues), this buffer is kept in memory, 
 *   because it can be called by #writeTextureFile.
 *   If you use large image buffers, it is recommended to save these on disk
 *   (#writeTextureFile) and then reload (#loadTextureFile) to avoid memory overload.
 * 
 *   
 * 
 * @SEE_ALSO
 *    SbTVizData,
 *    SbTVizRegularGridData,
 *    SbTVizTextureList,
 *    SoTViz,
 *    SoTVizRender
 * 
 * 
 */ 

class TERRAINVIZ_API SbTVizTexture {

  public :
    /**
     * Constructor.
     */
    SbTVizTexture();
  /**
   * Destructor.
   */
  virtual ~SbTVizTexture();
  /**
   * Sets the attributes and loads the texture file.
   */
  SbBool loadTextureFile(const char* fileName, int level, const SbVec2s& position, const SbVec2s& borders = SbVec2s(0, 0));

  /**
   * Returns the file name. Returns an empty string if 
   * @B setValues @b was used to specify the texture data.
   */
  inline const SbString& getFileName() const {return (m_fileName);};
  /**
   * Returns the level of the texture in the texture quadtree.
   */
  inline int getLevel() const                {return (m_level);};
  /**
   * Returns the position of the texture in the level.
   */
  inline const SbVec2s& getPosition() const  {return (m_position);};
  /**
   * Returns the texture size in pixels.
   */
  inline const SbVec2s& getSize() const      {return (m_size);};
  /**
   * Returns the number of color components.
   */
  inline int getNumComponents() const        {return (m_nc);};

  /**
   * Returns the X and Y borders (the number of pixels overlap)
   * used for texture continuity. The X and Y borders are specified using
   * #loadTextureFile or in the XML file itself.
   */
  inline const SbVec2s& getBorders() const  {return (m_borders);};


  /**
   * Sets the pixel values, the number of components, and the size of the texture.
   * Sets also the other necessary attributs position, level and borders (number of pixel overlap).
   * See SoSFImage for information on how the pixel values should be stored in the
   * array.
   * Remember that the buffer is kept in memory after the data is sent to OpenGL
   * (see class description).
   */
  void setValues(const SbVec2s& size, int nc, int level, const SbVec2s& position, const SbVec2s& borders, const unsigned char *bytes);
  /**
   * Returns the pixel values, the number of components, and the size of the texture.
   * The pixels in the image are returned as an array of unsigned chars. The
   * @B size @b and @B nc @b arguments are filled in with the dimensions of the
   * image and the number of components in the image; the number of bytes in the
   * array returned will be @B size @b[0]*@B size @b[1]*@B nc @b.
   */
  const unsigned char* getValues(SbVec2s& size, int& nc) const;


  /**
   *  Saves the texture buffer as a PNG file.
   *
   */
  SbBool writeTextureFile(const SbString& filename);

  /** 
   * DEPRECATED : useless. It has no effect.
   */
  enum FileType { UNKNOWN, RGB,
                  SGI, TIFF,
                  GIF, JPEG,
                  BMP, PNG,
                  NUM_FILETYPES };

  /** 
   * DEPRECATED : useless. It has no effect.
   */
  inline void setBitmapFileType(FileType in_type);

  /** 
   * DEPRECATED : useless. It has no effect.
   */
  inline FileType getBitmapFileType(void) { return UNKNOWN; };

 SoINTERNAL public:

  enum Orientation {
    NW = 0,
    NE,
    SW,
    SE
  };
        
  Orientation orientation;
  GLuint texName;
  SbBool isAvailable;

  inline const GLfloat* getParamS(){return (m_paramS);};
  inline const GLfloat* getParamT(){return (m_paramT);};
  void setParamS(SbVec4f& s);
  void setParamT(SbVec4f& t);

  void freeBufferValues();
  const unsigned char* getBufferValues(int nc);
  Array2Duchar* getBuffer(int& nc);
  inline void setIndex(int index) {m_index = index;};
  inline int  getIndex() {return m_index;};
  inline void setLevelIndex(int index) {m_levelIdx = index;};
  inline int  getLevelIndex() {return m_levelIdx;};
  void setPosition(SbVec2s pos);
  SbVec3s getNeighbours(Orientation ori);


  void rotate(double angle);



 private :

  SbVec2s m_position;
  SbVec2s m_size;
  SbVec2s m_borders;
  int     m_nc;
  int     m_index;
  int               m_levelIdx;
  int     m_level;

  SbString m_fileName;

  Array2Duchar* m_texData;

  GLfloat m_paramS[4];
  GLfloat m_paramT[4];
};


inline void 
SbTVizTexture::setBitmapFileType(FileType)
{}


#endif

